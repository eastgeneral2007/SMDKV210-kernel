/*
 * linux/sound/soc/s3c/s5p-spdif.c
 *
 * Copyright (c) 2010 Samsung Electronics Co., Ltd.
 *          http://www.samsung.com/
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * - ALSA device driver for SPDIF transmitter
 */

#include <linux/delay.h>
#include <linux/interrupt.h>

#include <sound/soc.h>

#include <linux/io.h>

#include <plat/regs-spdif.h>

#include <mach/dma.h>

#include "s5p-spdif.h"
#include "s3c-dma.h"

#ifdef CONFIG_SND_DEBUG
#define s3cdbg(x...) printk(x)
#else
#define s3cdbg(x...)
#endif


static struct s3c2410_dma_client s5p_spdif_dma_client_out = {
	.name = "SPDIF out"
};


static struct s3c_dma_params s5p_spdif_pcm_stereo_out = {
	.client	 = &s5p_spdif_dma_client_out,
	.channel = DMACH_SPDIF_OUT,
	.dma_addr = S5P_PA_SPDIF + S5P_SPDIF_SPDDAT,
	.dma_size = 2,
};


static void s5p_spdif_snd_txctrl(int on)
{

	s3cdbg("Entered %s: on=%d \n", __func__, on);

	if (on) {
		writel(S5P_SPDIF_SPDCLKCON_SPDIFOUT_POWER_OFF,
		       s5p_spdif.regs + S5P_SPDIF_SPDCLKCON);
		writel(S5P_SPDIF_SPDCLKCON_MAIN_AUDIO_CLK_INT |
		       S5P_SPDIF_SPDCLKCON_SPDIFOUT_POWER_ON,
		       s5p_spdif.regs + S5P_SPDIF_SPDCLKCON);
	} else {
		writel(S5P_SPDIF_SPDCON_SOFTWARE_RESET_EN,
		       s5p_spdif.regs + S5P_SPDIF_SPDCON);
		mdelay(100);
		writel(S5P_SPDIF_SPDCLKCON_SPDIFOUT_POWER_OFF,
		       s5p_spdif.regs + S5P_SPDIF_SPDCLKCON);
	}
}


static int s5p_spdif_hw_params(struct snd_pcm_substream *substream,
			       struct snd_pcm_hw_params *params,
			       struct snd_soc_dai *dai)
{
	struct snd_soc_pcm_runtime *rtd = substream->private_data;
	int sampling_freq, ret;

	s3cdbg("Entered %s: rate=%d\n", __func__, params_rate(params));

	ret = snd_soc_dai_set_sysclk(dai, 0,
				     params_rate(params), SND_SOC_CLOCK_OUT);

	if (ret < 0)
		return ret;

	if (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		rtd->dai->cpu_dai->dma_data = &s5p_spdif_pcm_stereo_out;

	switch (params_rate(params)) {
	case 32000:
		sampling_freq = S5P_SPDIF_SPDCSTAS_SAMPLING_FREQ_32;
		break;
	case 44100:
		sampling_freq = S5P_SPDIF_SPDCSTAS_SAMPLING_FREQ_44_1;
		break;
	case 48000:
		sampling_freq = S5P_SPDIF_SPDCSTAS_SAMPLING_FREQ_48;
		break;
	case 96000:
		sampling_freq = S5P_SPDIF_SPDCSTAS_SAMPLING_FREQ_96;
		break;
	default:
		sampling_freq = S5P_SPDIF_SPDCSTAS_SAMPLING_FREQ_48;
		return -EINVAL;
	}

	writel(S5P_SPDIF_SPDCON_SOFTWARE_RESET_EN,
	       s5p_spdif.regs + S5P_SPDIF_SPDCON);

	mdelay(100);

	/* Clear Interrupt */
	writel(S5P_SPDIF_SPDCON_FIFO_LEVEL_INT_STATUS_PENDING |
	       S5P_SPDIF_SPDCON_USER_DATA_INT_STATUS_PENDING |
	       S5P_SPDIF_SPDCON_BUFFER_EMPTY_INT_STATUS_PENDING |
	       S5P_SPDIF_SPDCON_STREAM_END_INT_STATUS_PENDING,
	       s5p_spdif.regs + S5P_SPDIF_SPDCON);

	/* set SPDIF Control Register */
	writel(S5P_SPDIF_SPDCON_FIFO_LEVEL_THRESHOLD_7 |
	       S5P_SPDIF_SPDCON_FIFO_LEVEL_INT_ENABLE |
	       S5P_SPDIF_SPDCON_ENDIAN_FORMAT_BIG |
	       S5P_SPDIF_SPDCON_USER_DATA_ATTACH_AUDIO_DATA |
	       S5P_SPDIF_SPDCON_USER_DATA_INT_ENABLE |
	       S5P_SPDIF_SPDCON_BUFFER_EMPTY_INT_ENABLE |
	       S5P_SPDIF_SPDCON_STREAM_END_INT_ENABLE |
	       S5P_SPDIF_SPDCON_SOFTWARE_RESET_NO |
	       S5P_SPDIF_SPDCON_MAIN_AUDIO_CLK_FREQ_512 |
	       S5P_SPDIF_SPDCON_PCM_DATA_SIZE_16 |
	       S5P_SPDIF_SPDCON_PCM,
	       s5p_spdif.regs + S5P_SPDIF_SPDCON);

	/* Set SPDIFOUT Burst Status Register */
	writel(S5P_SPDIF_SPDBSTAS_BURST_DATA_LENGTH(16) |
	       S5P_SPDIF_SPDBSTAS_BITSTREAM_NUMBER(0) |
	       S5P_SPDIF_SPDBSTAS_DATA_TYPE_DEP_INFO |
	       S5P_SPDIF_SPDBSTAS_ERROR_FLAG_VALID |
	       S5P_SPDIF_SPDBSTAS_COMPRESSED_DATA_TYPE_NULL,
	       s5p_spdif.regs + S5P_SPDIF_SPDBSTAS);

	/* Set SPDIFOUT Channel Status Register */
	writel(S5P_SPDIF_SPDCSTAS_CLOCK_ACCURACY_50 |
	       sampling_freq |
	       S5P_SPDIF_SPDCSTAS_CHANNEL_NUMBER(0) |
	       S5P_SPDIF_SPDCSTAS_SOURCE_NUMBER(0) |
	       S5P_SPDIF_SPDCSTAS_CATEGORY_CODE_CD |
	       S5P_SPDIF_SPDCSTAS_CHANNEL_SATAUS_MODE |
	       S5P_SPDIF_SPDCSTAS_EMPHASIS_WITHOUT_PRE_EMP |
	       S5P_SPDIF_SPDCSTAS_COPYRIGHT_ASSERTION_NO |
	       S5P_SPDIF_SPDCSTAS_AUDIO_SAMPLE_WORD_LINEAR_PCM |
	       S5P_SPDIF_SPDCSTAS_CHANNEL_STATUS_BLOCK_CON,
	       s5p_spdif.regs + S5P_SPDIF_SPDCSTAS);

	/* SPDIFOUT Repitition Count register */
	writel(S5P_SPDIF_SPDCNT_STREAM_REPETITION_COUNT(0),
	       s5p_spdif.regs + S5P_SPDIF_SPDCNT);

	return 0;
}


static int s5p_spdif_trigger(struct snd_pcm_substream 	*substream,
			     int 			cmd,
			     struct snd_soc_dai 	*dai)
{
	int ret = 0;

	s3cdbg("Entered %s: cmd=%d\n", __func__, cmd);

	switch (cmd) {
	case SNDRV_PCM_TRIGGER_START:
	case SNDRV_PCM_TRIGGER_RESUME:
	case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:

		s5p_spdif_snd_txctrl(1);
		break;

	case SNDRV_PCM_TRIGGER_STOP:
	case SNDRV_PCM_TRIGGER_SUSPEND:
	case SNDRV_PCM_TRIGGER_PAUSE_PUSH:

		s5p_spdif_snd_txctrl(0);
		break;

	default:
		ret = -EINVAL;
		break;
	}

	return ret;
}


static void s5p_spdif_shutdown(struct snd_pcm_substream *substream,
			       struct snd_soc_dai *dai)
{
	s3cdbg("Entered %s\n", __func__);

	writel(S5P_SPDIF_SPDCON_SOFTWARE_RESET_EN,
	       s5p_spdif.regs + S5P_SPDIF_SPDCON);

	mdelay(100);

	writel(S5P_SPDIF_SPDCLKCON_SPDIFOUT_POWER_OFF,
	       s5p_spdif.regs + S5P_SPDIF_SPDCLKCON);
}


static int s5p_spdif_prepare(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *dai)
{
	s3cdbg("Entered %s\n", __func__);
	return 0;
}


static int s5p_spdif_set_sysclk(struct snd_soc_dai *cpu_dai,
				int clk_id, unsigned int freq, int dir)
{
#ifdef CONFIG_ARCH_S5PV2XX
	struct clk *temp_mout_epll;
	struct clk *temp_fout_epll;
	struct clk *temp_sclk_audio0;
#endif

	s3cdbg("Entered %s\n", __func__);

#ifdef CONFIG_ARCH_S5PV2XX
	temp_fout_epll = clk_get(NULL, "fout_epll");

	if (IS_ERR(temp_fout_epll)) {
		printk(KERN_ERR "failed to get fout_epll\n");
		return -EBUSY;
	}

	temp_mout_epll = clk_get(NULL, "mout_epll");

	if (IS_ERR(temp_mout_epll)) {
		printk(KERN_ERR "failed to get FOUTepll\n");
		clk_put(temp_fout_epll);
		return -EBUSY;
	}

	temp_sclk_audio0 = clk_get(NULL, "sclk_audio0");

	if (IS_ERR(temp_sclk_audio0)) {
		printk(KERN_ERR "failed to get sclk_audio0\n");
		clk_put(temp_fout_epll);
		clk_put(temp_mout_epll);
		return -EBUSY;
	}

	if (clk_set_parent(temp_mout_epll, temp_fout_epll)) {
		printk(KERN_ERR
		       "failed to set fout_epll as parent of mout_epll\n");
		clk_put(temp_fout_epll);
		clk_put(temp_mout_epll);
		clk_put(temp_sclk_audio0);
		return -EBUSY;
	}

	if (clk_set_parent(temp_sclk_audio0, temp_mout_epll)) {
		printk(KERN_ERR
		       "failed to set mout_epll as parent of sclk_audio0\n");
		clk_put(temp_fout_epll);
		clk_put(temp_mout_epll);
		clk_put(temp_sclk_audio0);
		return -EBUSY;
	}

	clk_disable(temp_sclk_audio0);
	clk_disable(temp_fout_epll);

	switch (freq) {
	case 44100:
		/* 45158000 is fixed value for epll */
		clk_set_rate(temp_fout_epll, 45158000);
		break;
	case 32000:
	case 48000:
	case 96000:
	default:
		/* 49152000 is fixed value for epll */
		clk_set_rate(temp_fout_epll, 49152000);
		break;
	}

	clk_set_rate(temp_sclk_audio0, freq * 512); /* freq*512 is bit freq */

	s3cdbg("sclk_audio0 is %ld\n",
	       clk_get_rate(temp_sclk_audio0));

	clk_enable(temp_fout_epll);
	clk_enable(temp_sclk_audio0);

	clk_put(temp_fout_epll);
	clk_put(temp_mout_epll);
	clk_put(temp_sclk_audio0);
#endif

	return 0;
}


static int s5p_spdif_set_clkdiv(struct snd_soc_dai *cpu_dai,
				int div_id,
				int div)
{
	s3cdbg("Entered %s: div_id=%d, div=%d\n", __func__, div_id, div);
	return 0;
}

u32 s5p_spdif_get_clockrate(void)
{
	return clk_get_rate(s5p_spdif.spdif_clk);
}
EXPORT_SYMBOL_GPL(s5p_spdif_get_clockrate);

#define SPDIF_SPDCON_INT_MASK						\
		(S5P_SPDIF_SPDCON_FIFO_LEVEL_INT_STATUS_PENDING | 	\
		 S5P_SPDIF_SPDCON_BUFFER_EMPTY_INT_STATUS_PENDING | 	\
		 S5P_SPDIF_SPDCON_STREAM_END_INT_STATUS_PENDING | 	\
		 S5P_SPDIF_SPDCON_USER_DATA_INT_STATUS_PENDING)

static irqreturn_t s5p_spdif_irq(int irqno, void *dev_id)
{
	u32 spdifcon;

	spdifcon = readl(s5p_spdif.regs + S5P_SPDIF_SPDCON);

	if ((spdifcon & (S5P_SPDIF_SPDCON_FIFO_LEVEL_INT_ENABLE |
			 S5P_SPDIF_SPDCON_FIFO_LEVEL_INT_STATUS_PENDING))
	    == (S5P_SPDIF_SPDCON_FIFO_LEVEL_INT_ENABLE |
		S5P_SPDIF_SPDCON_FIFO_LEVEL_INT_STATUS_PENDING)) {
		s3cdbg("Entered %s: SPDIF_INT_FIFOLVL \n", __func__);
	}

	if ((spdifcon & (S5P_SPDIF_SPDCON_BUFFER_EMPTY_INT_ENABLE
			 | S5P_SPDIF_SPDCON_BUFFER_EMPTY_INT_STATUS_PENDING))
	    == (S5P_SPDIF_SPDCON_BUFFER_EMPTY_INT_ENABLE |
		S5P_SPDIF_SPDCON_BUFFER_EMPTY_INT_STATUS_PENDING)) {
		s3cdbg("Entered %s: SPDIF_INT_BUFEMPTY \n", __func__);
	}

	if ((spdifcon & (S5P_SPDIF_SPDCON_STREAM_END_INT_ENABLE |
			 S5P_SPDIF_SPDCON_STREAM_END_INT_STATUS_PENDING))
	    == (S5P_SPDIF_SPDCON_STREAM_END_INT_ENABLE |
		S5P_SPDIF_SPDCON_STREAM_END_INT_STATUS_PENDING)) {
		s3cdbg("Entered %s: SPDIF_INT_STREAMEND \n", __func__);
	}

	if ((spdifcon & (S5P_SPDIF_SPDCON_USER_DATA_INT_ENABLE |
			 S5P_SPDIF_SPDCON_USER_DATA_INT_STATUS_PENDING))
	    == (S5P_SPDIF_SPDCON_USER_DATA_INT_ENABLE |
		S5P_SPDIF_SPDCON_USER_DATA_INT_STATUS_PENDING)) {
		s3cdbg("Entered %s: SPDIF_INT_USERDATA \n", __func__);
	}

	writel(spdifcon, s5p_spdif.regs + S5P_SPDIF_SPDCON);

	return IRQ_HANDLED;
}

static int s5p_spdif_probe(struct platform_device *pdev,
			   struct snd_soc_dai *dai)
{
	int ret;

	s3cdbg("Entered %s\n", __func__);

	s5p_spdif.regs = ioremap(S5P_PA_SPDIF, 0x40);

	if (s5p_spdif.regs == NULL)
		return -ENXIO;


	s5p_spdif.spdif_clk = clk_get(&pdev->dev, "spdif");

	if (IS_ERR(s5p_spdif.spdif_clk)) {
		s3cdbg("failed to get clock spdif\n");
		iounmap(s5p_spdif.regs);
		return -ENODEV;
	}

	clk_enable(s5p_spdif.spdif_clk);

	clk_put(s5p_spdif.spdif_clk);

#ifdef CONFIG_ARCH_S5PC1XX

	s5p_spdif.spdif_sclk = clk_get(&pdev->dev, "sclk_spdif");

	if (IS_ERR(s5p_spdif.spdif_clk)) {
		s3cdbg("failed to get clock sclk_spdif\n");
		iounmap(s5p_spdif.regs);
		return -ENODEV;
	}

	clk_enable(s5p_spdif.spdif_sclk);
#endif

	ret = request_irq(IRQ_SPDIF, s5p_spdif_irq, 0,
			  "s5p_spdif", pdev);

	if (ret < 0) {
		s3cdbg("fail to claim i2s irq , ret = %d\n", ret);
		return -ENODEV;
	}

	return 0;
}

static void s5p_spdif_remove(struct platform_device *pdev,
			     struct snd_soc_dai *dai)
{
	s3cdbg("Entered %s\n", __func__);
	return;
}

static int s5p_spdif_startup(struct snd_pcm_substream *substream,
			     struct snd_soc_dai *dai)
{
	s3cdbg("Entered %s\n", __func__);
	return 0;
}

static int s5p_spdif_set_fmt(struct snd_soc_dai *cpu_dai,
			     unsigned int fmt)
{
	s3cdbg("Entered %s\n", __func__);
	return 0;
}

#ifdef CONFIG_PM
static int s5p_spdif_suspend(struct snd_soc_dai *dai)
{
	s3cdbg("Entered %s\n", __func__);
	return 0;
}

static int s5p_spdif_resume(struct snd_soc_dai *dai)
{
	s3cdbg("Entered %s\n", __func__);
	return 0;
}
#else
#define s5p_spdif_suspend	NULL
#define s5p_spdif_resume	NULL
#endif

/*
 * SPDIF supports various sampling rate of 32KHz~96KHz.
 * In case of SMDKV210 all sampling rates are tested.
 */
#ifdef CONFIG_ARCH_S5PV2XX
#define S5P_SPDIF_RATES \
	(SNDRV_PCM_RATE_32000 | SNDRV_PCM_RATE_44100 |\
	 SNDRV_PCM_RATE_48000 | SNDRV_PCM_RATE_96000)
#else
#define S5P_SPDIF_RATES \
	(SNDRV_PCM_RATE_48000)
#endif
/*
 * SPDIF supports formats of 16, 20 24 bits.
 * But currently it supports 16 bits only.
 */
#define S5P_SPDIF_FORMATS \
	(SNDRV_PCM_FMTBIT_S16_LE)

static struct snd_soc_dai_ops s5p_spdif_dai_ops = {
	.hw_params  = s5p_spdif_hw_params,
	.prepare    = s5p_spdif_prepare,
	.startup    = s5p_spdif_startup,
	.trigger    = s5p_spdif_trigger,
	.set_fmt    = s5p_spdif_set_fmt,
	.set_clkdiv = s5p_spdif_set_clkdiv,
	.set_sysclk = s5p_spdif_set_sysclk,
	.shutdown   = s5p_spdif_shutdown,
};

struct snd_soc_dai s5p_spdif_dai = {
	.name = "s5p-spdif",
	.id = 0,
	.probe = s5p_spdif_probe,
	.remove = s5p_spdif_remove,
	.suspend = s5p_spdif_suspend,
	.resume = s5p_spdif_resume,
	.playback = {
		.channels_min = 1,
		.channels_max = 2,
		.rates = S5P_SPDIF_RATES,
		.formats = S5P_SPDIF_FORMATS
	},
	.capture = {
		.channels_min = 2,
		.channels_max = 2,
		.rates = S5P_SPDIF_RATES,
		.formats = S5P_SPDIF_FORMATS,
	},
	.ops = &s5p_spdif_dai_ops,
};
EXPORT_SYMBOL_GPL(s5p_spdif_dai);

static int __init s5p_spdif_init(void)
{
	s3cdbg("Entered %s\n", __func__);
	return snd_soc_register_dai(&s5p_spdif_dai);
}
module_init(s5p_spdif_init);


static void __exit s5p_spdif_exit(void)
{
	s3cdbg("Entered %s\n", __func__);
	snd_soc_unregister_dai(&s5p_spdif_dai);
}
module_exit(s5p_spdif_exit);

/* Module information */
MODULE_DESCRIPTION("s5p SPDIF SoC Interface");
MODULE_LICENSE("GPL");
