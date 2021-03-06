/*
 * s5p-i2s_sec.c  --  Secondary Fifo driver for I2S_v5
 *
 * (c) 2009 Samsung Electronics Co. Ltd
 *   - Jaswinder Singh Brar <jassi.brar@samsung.com>
 *
 *  This program is free software; you can redistribute  it and/or modify it
 *  under  the terms of  the GNU General  Public License as published by the
 *  Free Software Foundation;  either version 2 of the  License, or (at your
 *  option) any later version.
 */

#include <linux/io.h>
#include <linux/delay.h>
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>

#include <plat/map.h>
#include <plat/regs-clock.h>
#include <plat/regs-s3c2412-iis.h>

#include <mach/s3c-dma.h>

#include "s3c-dma.h"

extern void s5p_idma_init(void *);

static void __iomem *s5p_i2s0_regs;

static struct s3c2410_dma_client s5p_dma_client_outs = {
	.name		= "I2S_Sec PCM Stereo out"
};

static struct s3c_dma_params s5p_i2s_sec_pcm_out = {
	.channel	= DMACH_I2S0_OUT_S,
	.client		= &s5p_dma_client_outs,
	.dma_size	= 4,
};

static void s5p_snd_txctrl(int on)
{
	u32 iiscon, iismod;

	iiscon = readl(s5p_i2s0_regs + S3C2412_IISCON);
	iismod = readl(s5p_i2s0_regs + S3C2412_IISMOD);

	if (on) {
		iiscon |= S3C2412_IISCON_IIS_ACTIVE;
		iiscon &= ~S3C2412_IISCON_TXCH_PAUSE;
		iiscon &= ~S5P_IISCON_TXSDMAPAUSE;
		iiscon |= S5P_IISCON_TXSDMACTIVE;

		switch (iismod & S3C2412_IISMOD_MODE_MASK) {
		case S3C2412_IISMOD_MODE_TXONLY:
		case S3C2412_IISMOD_MODE_TXRX:
			/* do nothing, we are in the right mode */
			break;

		case S3C2412_IISMOD_MODE_RXONLY:
			iismod &= ~S3C2412_IISMOD_MODE_MASK;
			iismod |= S3C2412_IISMOD_MODE_TXRX;
			break;

		default:
			printk("TXEN: Invalid MODE %x in IISMOD\n",
				iismod & S3C2412_IISMOD_MODE_MASK);
			break;
		}

		writel(iiscon, s5p_i2s0_regs + S3C2412_IISCON);
		writel(iismod, s5p_i2s0_regs + S3C2412_IISMOD);
	} else {
		iiscon |= S5P_IISCON_TXSDMAPAUSE;
		iiscon &= ~S5P_IISCON_TXSDMACTIVE;

		/* return if primary is active */
		if (iiscon & S3C2412_IISCON_TXDMA_ACTIVE) {
			writel(iiscon, s5p_i2s0_regs + S3C2412_IISCON);
			return;
		}

		iiscon |= S3C2412_IISCON_TXCH_PAUSE;

		switch (iismod & S3C2412_IISMOD_MODE_MASK) {
		case S3C2412_IISMOD_MODE_TXRX:
			iismod &= ~S3C2412_IISMOD_MODE_MASK;
			iismod |= S3C2412_IISMOD_MODE_RXONLY;
			break;

		case S3C2412_IISMOD_MODE_TXONLY:
			iismod &= ~S3C2412_IISMOD_MODE_MASK;
			iiscon &= ~S3C2412_IISCON_IIS_ACTIVE;
			break;

		default:
			printk("TXDIS: Invalid MODE %x in IISMOD\n",
				iismod & S3C2412_IISMOD_MODE_MASK);
			break;
		}

		writel(iismod, s5p_i2s0_regs + S3C2412_IISMOD);
		writel(iiscon, s5p_i2s0_regs + S3C2412_IISCON);
	}
}

#define msecs_to_loops(t) (loops_per_jiffy / 1000 * HZ * t)

/*
 * Wait for the LR signal to allow synchronisation to the L/R clock
 * from the codec. May only be needed for slave mode.
 */
static int s5p_snd_lrsync(void)
{
	u32 iiscon;
	unsigned long loops = msecs_to_loops(1);

	pr_debug("Entered %s\n", __func__);

	while (--loops) {
		iiscon = readl(s5p_i2s0_regs + S3C2412_IISCON);
		if (iiscon & S3C2412_IISCON_LRINDEX)
			break;

		cpu_relax();
	}

	if (!loops) {
		pr_debug("%s: timeout\n", __func__);
		return -ETIMEDOUT;
	}

	return 0;
}

static int s5p_i2s_hw_params(struct snd_pcm_substream *substream,
		struct snd_pcm_hw_params *params, struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	struct snd_soc_dai_link *dailink = rtd->dai;
	u32 iismod;

	dailink->cpu_dai->dma_data = &s5p_i2s_sec_pcm_out;

	iismod = readl(s5p_i2s0_regs + S3C2412_IISMOD);

	if (dailink->cpu_dai->use_idma)
		iismod |= S5P_IISMOD_TXSLP;
	else
		iismod &= ~S5P_IISMOD_TXSLP;

	/* Copy the same bps as Primary */
	iismod &= ~S5P_IISMOD_BLCSMASK;
	iismod |= ((iismod & S5P_IISMOD_BLCPMASK) << 2);

	writel(iismod, s5p_i2s0_regs + S3C2412_IISMOD);

	return 0;
}

static int s5p_i2s_startup(struct snd_pcm_substream *substream,
		struct snd_soc_dai *dai)
{
	u32 iiscon, iisfic;

	iiscon = readl(s5p_i2s0_regs + S3C2412_IISCON);

	/* FIFOs must be flushed before enabling PSR and other MOD bits, so we do it here. */
	if (iiscon & S5P_IISCON_TXSDMACTIVE)
		return 0;

	iisfic = readl(s5p_i2s0_regs + S5P_IISFICS);
	iisfic |= S3C2412_IISFIC_TXFLUSH;
	writel(iisfic, s5p_i2s0_regs + S5P_IISFICS);

	do {
		cpu_relax();
	} while ((__raw_readl(s5p_i2s0_regs + S5P_IISFICS) >> 8) & 0x7f);

	iisfic = readl(s5p_i2s0_regs + S5P_IISFICS);
	iisfic &= ~S3C2412_IISFIC_TXFLUSH;
	writel(iisfic, s5p_i2s0_regs + S5P_IISFICS);

	return 0;
}

static int s5p_i2s_trigger(struct snd_pcm_substream *substream,
		int cmd, struct snd_soc_dai *dai)
{
	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		/* We don't configure clocks from this Sec i/f.
		 * So, we simply wait enough time for LRSYNC to
		 * get synced and not check return 'error'
		 */
		s5p_snd_lrsync();
		s5p_snd_txctrl(1);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		s5p_snd_txctrl(0);
		break;
	}

	return 0;
}

static struct snd_soc_dai_ops i2s_sec_ops = {
	.hw_params = s5p_i2s_hw_params,
	.startup   = s5p_i2s_startup,
	.trigger   = s5p_i2s_trigger,
};

struct snd_soc_dai i2s_sec_fifo_dai = {
	.name = "i2s-sec-fifo",
	.id = 0,
	.ops = &i2s_sec_ops,
};
EXPORT_SYMBOL_GPL(i2s_sec_fifo_dai);

static int get_dma_mode(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol)
{
	ucontrol->value.integer.value[0] = i2s_sec_fifo_dai.use_idma;

	return 0;
}

static int set_dma_mode(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol)
{
	if (i2s_sec_fifo_dai.use_idma == ucontrol->value.integer.value[0]
		|| i2s_sec_fifo_dai.active)
		return 0;

	i2s_sec_fifo_dai.use_idma = ucontrol->value.integer.value[0];

	return 1;
}

static int get_dma_mode(struct snd_kcontrol *kcontrol,
	struct snd_ctl_elem_value *ucontrol);
static int set_dma_mode(struct snd_kcontrol *kcontrol,
		struct snd_ctl_elem_value *ucontrol);

static const char *dma_modes[] = {
	"SysDMA",
	"iDMA",
};

static const struct soc_enum dma_mode_enum[] = {
	SOC_ENUM_SINGLE_EXT(ARRAY_SIZE(dma_modes), dma_modes),
};

const struct snd_kcontrol_new s5p_idma_control =
	SOC_ENUM_EXT("Sec_Fifo Mode", dma_mode_enum[0],
		get_dma_mode, set_dma_mode);
EXPORT_SYMBOL_GPL(s5p_idma_control);

void s5p_i2s_sec_init(void *regs, dma_addr_t phys_base)
{
	u32 val;

#ifdef CONFIG_ARCH_S5PV2XX
/* S5PC110 or S5PV210 */
#include <plat/map.h>
#define S3C_VA_AUDSS	S3C_ADDR(0x01600000)	/* Audio SubSystem */
#include <plat/regs-audss.h>
	/* We use I2SCLK for rate generation, so set EPLLout as
	 * the parent of I2SCLK.
	 */
	val = readl(S5P_CLKSRC_AUDSS);
	val &= ~(0x3<<2);
	val |= (1<<0);
	writel(val, S5P_CLKSRC_AUDSS);

	val = readl(S5P_CLKGATE_AUDSS);
	val |= (0x7f<<0);
	writel(val, S5P_CLKGATE_AUDSS);
#else
	#error INITIALIZE HERE!
#endif

	val  = S5P_IISAHB_DMARLD | S5P_IISAHB_DISRLDINT;
	writel(val, regs + S5P_IISAHB);

	s5p_i2s0_regs = regs;
	s5p_i2s_sec_pcm_out.dma_addr = phys_base + S5P_IISTXDS;
	s5p_idma_init(regs);
}

/* Module information */
MODULE_AUTHOR("Jaswinder Singh <jassi.brar@samsung.com>");
MODULE_DESCRIPTION("S5P I2S-SecFifo SoC Interface");
MODULE_LICENSE("GPL");
