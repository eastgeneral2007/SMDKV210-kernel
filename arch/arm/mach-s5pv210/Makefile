# arch/arm/mach-s5pv210/Makefile
#
# Copyright 2008 Openmoko, Inc.
# Copyright 2008 Simtec Electronics
#
# Licensed under GPLv2

obj-y				:=
led-y                           := leds.o
obj-m				:=
obj-n				:=
obj-				:=

# Core support for S5PV210 system

obj-$(CONFIG_CPU_S5PV210)	+= cpu.o
obj-$(CONFIG_CPU_S5PV210)	+= dma.o
obj-$(CONFIG_CPU_S5PV210)	+= irq.o

# Helper and device support
obj-$(CONFIG_S5PV210_PM)    += pm.o
obj-$(CONFIG_S5PV2XX_SETUP_SDHCI)       += setup-sdhci.o

# machine support

obj-$(CONFIG_MACH_SMDKV210)	+= mach-smdkv210.o
obj-$(CONFIG_MACH_SMDKV210)	+= button-smdkv210.o

# LEDs support
led-$(CONFIG_MACH_SMDKV210)     += leds-s5pv210.o
obj-$(CONFIG_LEDS)              += $(led-y)

obj-$(CONFIG_CPU_IDLE)		+= cpuidle.o
