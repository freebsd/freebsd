/*-
 * SPDX-License-Identifier: BSD-2-Clause-FreeBSD
 *
 * Copyright (c) 2015-2016 Landon Fuller <landon@landonf.org>
 * Copyright (c) 2010 Broadcom Corporation
 * All rights reserved.
 *
 * This file is derived from the sbchipc.h header contributed by Broadcom
 * to to the Linux staging repository, as well as later revisions of sbchipc.h
 * distributed with the Asus RT-N16 firmware source code release.
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 * $FreeBSD$
 */

#ifndef _BHND_CORES_PMU_BHND_PMUREG_H_
#define	_BHND_CORES_PMU_BHND_PMUREG_H_

#define BHND_PMU_GET_FLAG(_value, _flag)	\
	(((_value) & _flag) != 0)
#define	BHND_PMU_GET_BITS(_value, _field)	\
	(((_value) & _field ## _MASK) >> _field ## _SHIFT)
#define	BHND_PMU_SET_BITS(_value, _field)	\
	(((_value) << _field ## _SHIFT) & _field ## _MASK)

#define	BHND_PMU_ILP_CLOCK	32000		/**< default ILP freq */
#define	BHND_PMU_ALP_CLOCK	20000000	/**< default ALP freq */
#define	BHND_PMU_HT_CLOCK	80000000	/**< default HT freq */

/**
 * Common per-core clock control/status register available on PMU-equipped
 * devices.
 */
#define BHND_CLK_CTL_ST			0x1e0		/**< clock control and status */

/*
 * BHND_CLK_CTL_ST register
 *
 * Clock Mode		Name	Description
 * High Throughput	(HT)	Full bandwidth, low latency. Generally supplied
 * 				from PLL.
 * Active Low Power	(ALP)	Register access, low speed DMA.
 * Idle Low Power	(ILP)	No interconnect activity, or if long latency
 * 				is permitted.
 */
#define	BHND_CCS_FORCEALP		0x00000001	/**< force ALP request */
#define	BHND_CCS_FORCEHT		0x00000002	/**< force HT request */
#define	BHND_CCS_FORCEILP		0x00000004	/**< force ILP request */
#define	BHND_CCS_FORCE_MASK		0x0000000F

#define	BHND_CCS_ALPAREQ		0x00000008	/**< ALP Avail Request */
#define	BHND_CCS_HTAREQ			0x00000010	/**< HT Avail Request */
#define	BHND_CCS_AREQ_MASK		0x00000018

#define	BHND_CCS_FORCEHWREQOFF		0x00000020	/**< Force HW Clock Request Off */

#define	BHND_CCS_ERSRC_REQ_MASK		0x00000700	/**< external resource requests */
#define	BHND_CCS_ERSRC_REQ_SHIFT	8
#define	BHND_CCS_ERSRC_MAX		2		/**< maximum ERSRC value (corresponding to bits 0-2) */

#define	BHND_CCS_ALPAVAIL		0x00010000	/**< ALP is available */
#define	BHND_CCS_HTAVAIL		0x00020000	/**< HT is available */
#define	BHND_CCS_AVAIL_MASK		0x00030000

#define	BHND_CCS_BP_ON_APL		0x00040000	/**< RO: Backplane is running on ALP clock */
#define	BHND_CCS_BP_ON_HT		0x00080000	/**< RO: Backplane is running on HT clock */
#define	BHND_CCS_ERSRC_STS_MASK		0x07000000	/**< external resource status */
#define	BHND_CCS_ERSRC_STS_SHIFT	24

#define	BHND_CCS0_HTAVAIL		0x00010000	/**< HT avail in chipc and pcmcia on 4328a0 */
#define	BHND_CCS0_ALPAVAIL		0x00020000	/**< ALP avail in chipc and pcmcia on 4328a0 */

/* PMU registers */
#define	BHND_PMU_CTRL			0x600
#define	  BHND_PMU_CTRL_ILP_DIV_MASK	0xffff0000
#define	  BHND_PMU_CTRL_ILP_DIV_SHIFT	16
#define	  BHND_PMU_CTRL_PLL_PLLCTL_UPD	0x00000400	/* rev 2 */
#define	  BHND_PMU_CTRL_NOILP_ON_WAIT	0x00000200	/* rev 1 */
#define	  BHND_PMU_CTRL_HT_REQ_EN	0x00000100
#define	  BHND_PMU_CTRL_ALP_REQ_EN	0x00000080
#define	  BHND_PMU_CTRL_XTALFREQ_MASK	0x0000007c
#define	  BHND_PMU_CTRL_XTALFREQ_SHIFT	2
#define	  BHND_PMU_CTRL_ILP_DIV_EN	0x00000002
#define	  BHND_PMU_CTRL_LPO_SEL		0x00000001
#define	BHND_PMU_CAP			0x604
#define	  BHND_PMU_CAP_REV_MASK		0x000000ff
#define	  BHND_PMU_CAP_REV_SHIFT	0
#define	  BHND_PMU_CAP_RC_MASK		0x00001f00
#define	  BHND_PMU_CAP_RC_SHIFT		8
#define	  BHND_PMU_CAP_RC_MAX		\
	(BHND_PMU_CAP_RC_MASK >> BHND_PMU_CAP_RC_SHIFT)
#define	  BHND_PMU_CAP_TC_MASK		0x0001e000
#define	  BHND_PMU_CAP_TC_SHIFT		13
#define	  BHND_PMU_CAP_PC_MASK		0x001e0000
#define	  BHND_PMU_CAP_PC_SHIFT		17
#define	  BHND_PMU_CAP_VC_MASK		0x01e00000
#define	  BHND_PMU_CAP_VC_SHIFT		21
#define	  BHND_PMU_CAP_CC_MASK		0x1e000000
#define	  BHND_PMU_CAP_CC_SHIFT		25
#define	  BHND_PMU_CAP5_PC_MASK		0x003e0000	/* PMU corerev >= 5 */
#define	  BHND_PMU_CAP5_PC_SHIFT	17
#define	  BHND_PMU_CAP5_VC_MASK		0x07c00000
#define	  BHND_PMU_CAP5_VC_SHIFT	22
#define	  BHND_PMU_CAP5_CC_MASK		0xf8000000
#define	  BHND_PMU_CAP5_CC_SHIFT	27
#define	BHND_PMU_ST			0x608
#define	  BHND_PMU_ST_EXTLPOAVAIL	0x0100
#define	  BHND_PMU_ST_WDRESET		0x0080
#define	  BHND_PMU_ST_INTPEND		0x0040
#define	  BHND_PMU_ST_SBCLKST		0x0030
#define	  BHND_PMU_ST_SBCLKST_ILP	0x0010
#define	  BHND_PMU_ST_SBCLKST_ALP	0x0020
#define	  BHND_PMU_ST_SBCLKST_HT	0x0030
#define	  BHND_PMU_ST_ALPAVAIL		0x0008
#define	  BHND_PMU_ST_HTAVAIL		0x0004
#define	  BHND_PMU_ST_RESINIT		0x0003
#define	BHND_PMU_RES_STATE		0x60c
#define	BHND_PMU_RES_PENDING		0x610
#define	BHND_PMU_TIMER			0x614
#define	BHND_PMU_MIN_RES_MASK		0x618
#define	BHND_PMU_MAX_RES_MASK		0x61c
#define	BHND_PMU_RES_TABLE_SEL		0x620
#define	BHND_PMU_RES_DEP_MASK		0x624
#define	BHND_PMU_RES_UPDN_TIMER		0x628
#define	  BHND_PMU_RES_UPDN_UPTME_MASK	0xFF00
#define	  BHND_PMU_RES_UPDN_UPTME_SHIFT	8
#define	BHND_PMU_RES_TIMER		0x62C
#define	BHND_PMU_CLKSTRETCH		0x630
#define	  BHND_PMU_CSTRETCH_HT		0xffff0000
#define	  BHND_PMU_CSTRETCH_ALP		0x0000ffff
#define	BHND_PMU_WATCHDOG		0x634
#define	BHND_PMU_GPIOSEL		0x638		/* pmu rev >= 1 ? */
#define	BHND_PMU_GPIOEN			0x63C		/* pmu rev >= 1 ? */
#define	BHND_PMU_RES_REQ_TIMER_SEL	0x640
#define	BHND_PMU_RES_REQ_TIMER		0x644
#define	  BHND_PMU_RRQT_TIME_MASK	0x03ff
#define	  BHND_PMU_RRQT_INTEN		0x0400
#define	  BHND_PMU_RRQT_REQ_ACTIVE	0x0800
#define	  BHND_PMU_RRQT_ALP_REQ		0x1000
#define	  BHND_PMU_RRQT_HT_REQ		0x2000
#define	BHND_PMU_RES_REQ_MASK		0x648
#define	BHND_PMU_CHIP_CONTROL_ADDR	0x650
#define	BHND_PMU_CHIP_CONTROL_DATA	0x654
#define	BHND_PMU_REG_CONTROL_ADDR	0x658
#define	BHND_PMU_REG_CONTROL_DATA	0x65C
#define	BHND_PMU_PLL_CONTROL_ADDR 	0x660
#define	BHND_PMU_PLL_CONTROL_DATA 	0x664
#define	BHND_PMU_STRAPOPT		0x668		/* chipc rev >= 28 */
#define	BHND_PMU_XTALFREQ		0x66C		/* pmu rev >= 10 */

/* PMU resource bit position */
#define	BHND_PMURES_BIT(bit)		(1 << (bit))

/* PMU resource number limit */
#define	BHND_PMU_RESNUM_MAX		30

/* PMU chip control0 register */
#define	BHND_PMU_CHIPCTL0		0

/* PMU chip control1 register */
#define	BHND_PMU_CHIPCTL1		1
#define	BHND_PMU_CC1_RXC_DLL_BYPASS	0x00010000

#define	BHND_PMU_CC1_IF_TYPE_MASK	0x00000030
#define	BHND_PMU_CC1_IF_TYPE_RMII	0x00000000
#define	BHND_PMU_CC1_IF_TYPE_MII	0x00000010
#define	BHND_PMU_CC1_IF_TYPE_RGMII	0x00000020

#define	BHND_PMU_CC1_SW_TYPE_MASK	0x000000c0
#define	BHND_PMU_CC1_SW_TYPE_EPHY	0x00000000
#define	BHND_PMU_CC1_SW_TYPE_EPHYMII	0x00000040
#define	BHND_PMU_CC1_SW_TYPE_EPHYRMII	0x00000080
#define	BHND_PMU_CC1_SW_TYPE_RGMII	0x000000c0

/* PMU corerev and chip specific PLL controls.
 * PMU<rev>_PLL<num>_XX where <rev> is PMU corerev and <num> is an arbitrary number
 * to differentiate different PLLs controlled by the same PMU rev.
 */

/* pllcontrol registers */
/* PDIV, div_phy, div_arm, div_adc, dith_sel, ioff, kpd_scale, lsb_sel, mash_sel, lf_c & lf_r */
#define	BHND_PMU0_PLL0_PLLCTL0		0
#define	BHND_PMU0_PLL0_PC0_PDIV_MASK	1
#define	BHND_PMU0_PLL0_PC0_PDIV_FREQ	25000
#define	BHND_PMU0_PLL0_PC0_DIV_ARM_MASK	0x00000038
#define	BHND_PMU0_PLL0_PC0_DIV_ARM_SHIFT	3
#define	BHND_PMU0_PLL0_PC0_DIV_ARM_BASE	8

/* PC0_DIV_ARM for PLLOUT_ARM */
#define	BHND_PMU0_PLL0_PC0_DIV_ARM_110MHZ	0
#define	BHND_PMU0_PLL0_PC0_DIV_ARM_97_7MHZ	1
#define	BHND_PMU0_PLL0_PC0_DIV_ARM_88MHZ	2
#define	BHND_PMU0_PLL0_PC0_DIV_ARM_80MHZ	3	/* Default */
#define	BHND_PMU0_PLL0_PC0_DIV_ARM_73_3MHZ	4
#define	BHND_PMU0_PLL0_PC0_DIV_ARM_67_7MHZ	5
#define	BHND_PMU0_PLL0_PC0_DIV_ARM_62_9MHZ	6
#define	BHND_PMU0_PLL0_PC0_DIV_ARM_58_6MHZ	7

/* Wildcard base, stop_mod, en_lf_tp, en_cal & lf_r2 */
#define	BHND_PMU0_PLL0_PLLCTL1		1
#define	BHND_PMU0_PLL0_PC1_WILD_INT_MASK	0xf0000000
#define	BHND_PMU0_PLL0_PC1_WILD_INT_SHIFT	28
#define	BHND_PMU0_PLL0_PC1_WILD_FRAC_MASK	0x0fffff00
#define	BHND_PMU0_PLL0_PC1_WILD_FRAC_SHIFT	8
#define	BHND_PMU0_PLL0_PC1_STOP_MOD		0x00000040

/* Wildcard base, vco_calvar, vco_swc, vco_var_selref, vso_ical & vco_sel_avdd */
#define	BHND_PMU0_PLL0_PLLCTL2		2
#define	BHND_PMU0_PLL0_PC2_WILD_INT_MASK	0xf0
#define	BHND_PMU0_PLL0_PC2_WILD_INT_SHIFT	4

/* pllcontrol registers */
/* ndiv_pwrdn, pwrdn_ch<x>, refcomp_pwrdn, dly_ch<x>, p1div, p2div, _bypass_sdmod */
#define	BHND_PMU1_PLL0_PLLCTL0		0
#define	BHND_PMU1_PLL0_PC0_P1DIV_MASK		0x00f00000
#define	BHND_PMU1_PLL0_PC0_P1DIV_SHIFT		20
#define	BHND_PMU1_PLL0_PC0_P2DIV_MASK		0x0f000000
#define	BHND_PMU1_PLL0_PC0_P2DIV_SHIFT		24
#define	BHND_PMU1_PLL0_PC0_BYPASS_SDMOD_MASK	0x10000000
#define	BHND_PMU1_PLL0_PC0_BYPASS_SDMOD_SHIFT	28

/* m<x>div */
#define	BHND_PMU1_PLL0_PLLCTL1		1
#define	BHND_PMU1_PLL0_PC1_M1DIV_MASK	0x000000ff
#define	BHND_PMU1_PLL0_PC1_M1DIV_SHIFT	0
#define	BHND_PMU1_PLL0_PC1_M2DIV_MASK	0x0000ff00
#define	BHND_PMU1_PLL0_PC1_M2DIV_SHIFT	8
#define	BHND_PMU1_PLL0_PC1_M3DIV_MASK	0x00ff0000
#define	BHND_PMU1_PLL0_PC1_M3DIV_SHIFT	16
#define	BHND_PMU1_PLL0_PC1_M4DIV_MASK	0xff000000
#define	BHND_PMU1_PLL0_PC1_M4DIV_SHIFT	24

#define	BHND_PMU_DOT11MAC_880MHZ_CLK_DIVISOR_SHIFT 8
#define	BHND_PMU_DOT11MAC_880MHZ_CLK_DIVISOR_MASK (0xFF << BHND_PMU_DOT11MAC_880MHZ_CLK_DIVISOR_SHIFT)
#define	BHND_PMU_DOT11MAC_880MHZ_CLK_DIVISOR_VAL  (0xE << BHND_PMU_DOT11MAC_880MHZ_CLK_DIVISOR_SHIFT)

/* m<x>div, ndiv_dither_mfb, ndiv_mode, ndiv_int */
#define	BHND_PMU1_PLL0_PLLCTL2		2
#define	BHND_PMU1_PLL0_PC2_M5DIV_MASK	0x000000ff
#define	BHND_PMU1_PLL0_PC2_M5DIV_SHIFT	0
#define	BHND_PMU1_PLL0_PC2_M6DIV_MASK	0x0000ff00
#define	BHND_PMU1_PLL0_PC2_M6DIV_SHIFT	8
#define	BHND_PMU1_PLL0_PC2_NDIV_MODE_MASK	0x000e0000
#define	BHND_PMU1_PLL0_PC2_NDIV_MODE_SHIFT	17
#define	BHND_PMU1_PLL0_PC2_NDIV_MODE_INT	0
#define	BHND_PMU1_PLL0_PC2_NDIV_MODE_MASH	1
#define	BHND_PMU1_PLL0_PC2_NDIV_MODE_MFB	2	/* recommended for 4319 */
#define	BHND_PMU1_PLL0_PC2_NDIV_INT_MASK	0x1ff00000
#define	BHND_PMU1_PLL0_PC2_NDIV_INT_SHIFT	20

/* ndiv_frac */
#define	BHND_PMU1_PLL0_PLLCTL3		3
#define	BHND_PMU1_PLL0_PC3_NDIV_FRAC_MASK	0x00ffffff
#define	BHND_PMU1_PLL0_PC3_NDIV_FRAC_SHIFT	0

/* pll_ctrl */
#define	BHND_PMU1_PLL0_PLLCTL4			4
#define	BHND_PMU1_PLL0_PC4_KVCO_XS_MASK		0x38000000
#define	BHND_PMU1_PLL0_PC4_KVCO_XS_SHIFT	27

/* pll_ctrl, vco_rng, clkdrive_ch<x> */
#define	BHND_PMU1_PLL0_PLLCTL5			5
#define	BHND_PMU1_PLL0_PC5_CLK_DRV_MASK		0xffffff00
#define	BHND_PMU1_PLL0_PC5_CLK_DRV_SHIFT	8
#define	BHND_PMU1_PLL0_PC5_PLL_CTRL_37_32_MASK	0x0000003f
#define	BHND_PMU1_PLL0_PC5_PLL_CTRL_37_32_SHIFT	0
#define	BHND_PMU1_PLL0_PC5_VCO_RNG_MASK		0x000000C0
#define	BHND_PMU1_PLL0_PC5_VCO_RNG_SHIFT	6

/* PMU rev 2 control words */
#define	BHND_PMU2_PHY_PLL_PLLCTL		4
#define	BHND_PMU2_SI_PLL_PLLCTL		10

/* PMU rev 2 */
/* pllcontrol registers */
/* ndiv_pwrdn, pwrdn_ch<x>, refcomp_pwrdn, dly_ch<x>, p1div, p2div, _bypass_sdmod */
#define	BHND_PMU2_PLL_PLLCTL0		0
#define	BHND_PMU2_PLL_PC0_P1DIV_MASK 	0x00f00000
#define	BHND_PMU2_PLL_PC0_P1DIV_SHIFT	20
#define	BHND_PMU2_PLL_PC0_P2DIV_MASK 	0x0f000000
#define	BHND_PMU2_PLL_PC0_P2DIV_SHIFT	24

/* m<x>div */
#define	BHND_PMU2_PLL_PLLCTL1		1
#define	BHND_PMU2_PLL_PC1_M1DIV_MASK 	0x000000ff
#define	BHND_PMU2_PLL_PC1_M1DIV_SHIFT	0
#define	BHND_PMU2_PLL_PC1_M2DIV_MASK 	0x0000ff00
#define	BHND_PMU2_PLL_PC1_M2DIV_SHIFT	8
#define	BHND_PMU2_PLL_PC1_M3DIV_MASK 	0x00ff0000
#define	BHND_PMU2_PLL_PC1_M3DIV_SHIFT	16
#define	BHND_PMU2_PLL_PC1_M4DIV_MASK 	0xff000000
#define	BHND_PMU2_PLL_PC1_M4DIV_SHIFT	24

/* m<x>div, ndiv_dither_mfb, ndiv_mode, ndiv_int */
#define	BHND_PMU2_PLL_PLLCTL2		2
#define	BHND_PMU2_PLL_PC2_M5DIV_MASK 	0x000000ff
#define	BHND_PMU2_PLL_PC2_M5DIV_SHIFT	0
#define	BHND_PMU2_PLL_PC2_M6DIV_MASK 	0x0000ff00
#define	BHND_PMU2_PLL_PC2_M6DIV_SHIFT	8
#define	BHND_PMU2_PLL_PC2_NDIV_MODE_MASK	0x000e0000
#define	BHND_PMU2_PLL_PC2_NDIV_MODE_SHIFT	17
#define	BHND_PMU2_PLL_PC2_NDIV_INT_MASK	0x1ff00000
#define	BHND_PMU2_PLL_PC2_NDIV_INT_SHIFT	20

/* ndiv_frac */
#define	BHND_PMU2_PLL_PLLCTL3		3
#define	BHND_PMU2_PLL_PC3_NDIV_FRAC_MASK	0x00ffffff
#define	BHND_PMU2_PLL_PC3_NDIV_FRAC_SHIFT	0

/* pll_ctrl */
#define	BHND_PMU2_PLL_PLLCTL4		4

/* pll_ctrl, vco_rng, clkdrive_ch<x> */
#define	BHND_PMU2_PLL_PLLCTL5			5
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH1_MASK		0x00000f00
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH1_SHIFT	8
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH2_MASK		0x0000f000
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH2_SHIFT	12
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH3_MASK		0x000f0000
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH3_SHIFT	16
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH4_MASK		0x00f00000
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH4_SHIFT	20
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH5_MASK		0x0f000000
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH5_SHIFT	24
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH6_MASK		0xf0000000
#define	BHND_PMU2_PLL_PC5_CLKDRIVE_CH6_SHIFT	28

/* PMU rev 5 (& 6) */
#define	BHND_PMU5_PLL_P1P2_OFF		0
#define	BHND_PMU5_PLL_P1_MASK		0x0f000000
#define	BHND_PMU5_PLL_P1_SHIFT		24
#define	BHND_PMU5_PLL_P2_MASK		0x00f00000
#define	BHND_PMU5_PLL_P2_SHIFT		20
#define	BHND_PMU5_PLL_M14_OFF		1
#define	BHND_PMU5_PLL_MDIV_MASK		0x000000ff
#define	BHND_PMU5_PLL_MDIV_WIDTH		8
#define	BHND_PMU5_PLL_NM5_OFF		2
#define	BHND_PMU5_PLL_NDIV_MASK		0xfff00000
#define	BHND_PMU5_PLL_NDIV_SHIFT		20
#define	BHND_PMU5_PLL_NDIV_MODE_MASK	0x000e0000
#define	BHND_PMU5_PLL_NDIV_MODE_SHIFT	17
#define	BHND_PMU5_PLL_FMAB_OFF		3
#define	BHND_PMU5_PLL_MRAT_MASK		0xf0000000
#define	BHND_PMU5_PLL_MRAT_SHIFT		28
#define	BHND_PMU5_PLL_ABRAT_MASK		0x08000000
#define	BHND_PMU5_PLL_ABRAT_SHIFT		27
#define	BHND_PMU5_PLL_FDIV_MASK		0x07ffffff
#define	BHND_PMU5_PLL_PLLCTL_OFF		4
#define	BHND_PMU5_PLL_PCHI_OFF		5
#define	BHND_PMU5_PLL_PCHI_MASK		0x0000003f

/* pmu XtalFreqRatio */
#define	BHND_PMU_XTALFREQ_REG_ILPCTR_MASK	0x00001FFF
#define	BHND_PMU_XTALFREQ_REG_ILPCTR_SHIFT	0
#define	BHND_PMU_XTALFREQ_REG_MEASURE_MASK	0x80000000
#define	BHND_PMU_XTALFREQ_REG_MEASURE_SHIFT	31

/* Divider allocation in 4716/47162/5356/5357 */
#define	BHND_PMU5_MAINPLL_CPU		1
#define	BHND_PMU5_MAINPLL_MEM		2
#define	BHND_PMU5_MAINPLL_SI		3

/* PMU rev 6 (BCM4706/Northstar) */
#define	BHND_PMU4706_MAINPLL_PLL0		0
#define	BHND_PMU6_4706_PROCPLL_OFF		4	/* The CPU PLL */
#define	BHND_PMU6_4706_PROC_P1DIV_MASK		0x000f0000
#define	BHND_PMU6_4706_PROC_P1DIV_SHIFT		16
#define	BHND_PMU6_4706_PROC_P2DIV_MASK		0x0000f000
#define	BHND_PMU6_4706_PROC_P2DIV_SHIFT		12
#define	BHND_PMU6_4706_PROC_NDIV_INT_MASK	0x00000ff8
#define	BHND_PMU6_4706_PROC_NDIV_INT_SHIFT	3
#define	BHND_PMU6_4706_PROC_NDIV_MODE_MASK	0x00000007
#define	BHND_PMU6_4706_PROC_NDIV_MODE_SHIFT	0

/* Divider allocation in 4706 */
#define	BHND_PMU6_MAINPLL_CPU		1
#define	BHND_PMU6_MAINPLL_MEM		2
#define	BHND_PMU6_MAINPLL_SI		3

/* PMU7 (?) */
#define	BHND_PMU7_PLL_PLLCTL7		7
#define	BHND_PMU7_PLL_PLLCTL8		8
#define	BHND_PMU7_PLL_PLLCTL11		11

/* PLL usage in 4716/47162 */
#define	BHND_PMU4716_MAINPLL_PLL0	12

/* PLL usage in 5356/5357 */
#define	BHND_PMU5356_MAINPLL_PLL0	0
#define	BHND_PMU5357_MAINPLL_PLL0	0

/* 4716/47162 PMU resources */
#define	BHND_PMU_RES4716_PROC_PLL_ON		0x00000040
#define	BHND_PMU_RES4716_PROC_HT_AVAIL		0x00000080

/* 4716/4717/4718 chip-specific CHIPCTRL PMU register bits */
#define	BHND_PMU_CCTRL471X_I2S_PINS_ENABLE	0x0080	/* I2S pins off by default, shared with pflash */

/* 5354 PMU resources */
#define	BHND_PMU_RES5354_EXT_SWITCHER_PWM	0	/* 0x00001 */
#define	BHND_PMU_RES5354_BB_SWITCHER_PWM	1	/* 0x00002 */
#define	BHND_PMU_RES5354_BB_SWITCHER_BURST	2	/* 0x00004 */
#define	BHND_PMU_RES5354_BB_EXT_SWITCHER_BURST	3	/* 0x00008 */
#define	BHND_PMU_RES5354_ILP_REQUEST		4	/* 0x00010 */
#define	BHND_PMU_RES5354_RADIO_SWITCHER_PWM	5	/* 0x00020 */
#define	BHND_PMU_RES5354_RADIO_SWITCHER_BURST	6	/* 0x00040 */
#define	BHND_PMU_RES5354_ROM_SWITCH		7	/* 0x00080 */
#define	BHND_PMU_RES5354_PA_REF_LDO		8	/* 0x00100 */
#define	BHND_PMU_RES5354_RADIO_LDO		9	/* 0x00200 */
#define	BHND_PMU_RES5354_AFE_LDO		10	/* 0x00400 */
#define	BHND_PMU_RES5354_PLL_LDO		11	/* 0x00800 */
#define	BHND_PMU_RES5354_BG_FILTBYP		12	/* 0x01000 */
#define	BHND_PMU_RES5354_TX_FILTBYP		13	/* 0x02000 */
#define	BHND_PMU_RES5354_RX_FILTBYP		14	/* 0x04000 */
#define	BHND_PMU_RES5354_XTAL_PU		15	/* 0x08000 */
#define	BHND_PMU_RES5354_XTAL_EN		16	/* 0x10000 */
#define	BHND_PMU_RES5354_BB_PLL_FILTBYP		17	/* 0x20000 */
#define	BHND_PMU_RES5354_RF_PLL_FILTBYP		18	/* 0x40000 */
#define	BHND_PMU_RES5354_BB_PLL_PU		19	/* 0x80000 */

/* 5357 chip-specific CHIPCTRL register bits */
#define	BHND_PMU_CCTRL5357_EXTPA		(1<<14)	/* extPA in CHIPCTRL1, bit 14 */
#define	BHND_PMU_CCTRL5357_ANT_MUX_2o3		(1<<15)	/* 2o3 in CHIPCTRL1, bit 15 */

/* 4328 PMU resources */
#define	BHND_PMU_RES4328_EXT_SWITCHER_PWM	0	/* 0x00001 */
#define	BHND_PMU_RES4328_BB_SWITCHER_PWM	1	/* 0x00002 */
#define	BHND_PMU_RES4328_BB_SWITCHER_BURST	2	/* 0x00004 */
#define	BHND_PMU_RES4328_BB_EXT_SWITCHER_BURST	3	/* 0x00008 */
#define	BHND_PMU_RES4328_ILP_REQUEST		4	/* 0x00010 */
#define	BHND_PMU_RES4328_RADIO_SWITCHER_PWM	5	/* 0x00020 */
#define	BHND_PMU_RES4328_RADIO_SWITCHER_BURST	6	/* 0x00040 */
#define	BHND_PMU_RES4328_ROM_SWITCH		7	/* 0x00080 */
#define	BHND_PMU_RES4328_PA_REF_LDO		8	/* 0x00100 */
#define	BHND_PMU_RES4328_RADIO_LDO		9	/* 0x00200 */
#define	BHND_PMU_RES4328_AFE_LDO		10	/* 0x00400 */
#define	BHND_PMU_RES4328_PLL_LDO		11	/* 0x00800 */
#define	BHND_PMU_RES4328_BG_FILTBYP		12	/* 0x01000 */
#define	BHND_PMU_RES4328_TX_FILTBYP		13	/* 0x02000 */
#define	BHND_PMU_RES4328_RX_FILTBYP		14	/* 0x04000 */
#define	BHND_PMU_RES4328_XTAL_PU		15	/* 0x08000 */
#define	BHND_PMU_RES4328_XTAL_EN		16	/* 0x10000 */
#define	BHND_PMU_RES4328_BB_PLL_FILTBYP		17	/* 0x20000 */
#define	BHND_PMU_RES4328_RF_PLL_FILTBYP		18	/* 0x40000 */
#define	BHND_PMU_RES4328_BB_PLL_PU		19	/* 0x80000 */

/* 4325 A0/A1 PMU resources */
#define	BHND_PMU_RES4325_BUCK_BOOST_BURST	0	/* 0x00000001 */
#define	BHND_PMU_RES4325_CBUCK_BURST		1	/* 0x00000002 */
#define	BHND_PMU_RES4325_CBUCK_PWM		2	/* 0x00000004 */
#define	BHND_PMU_RES4325_CLDO_CBUCK_BURST	3	/* 0x00000008 */
#define	BHND_PMU_RES4325_CLDO_CBUCK_PWM		4	/* 0x00000010 */
#define	BHND_PMU_RES4325_BUCK_BOOST_PWM		5	/* 0x00000020 */
#define	BHND_PMU_RES4325_ILP_REQUEST		6	/* 0x00000040 */
#define	BHND_PMU_RES4325_ABUCK_BURST		7	/* 0x00000080 */
#define	BHND_PMU_RES4325_ABUCK_PWM		8	/* 0x00000100 */
#define	BHND_PMU_RES4325_LNLDO1_PU		9	/* 0x00000200 */
#define	BHND_PMU_RES4325_OTP_PU			10	/* 0x00000400 */
#define	BHND_PMU_RES4325_LNLDO3_PU		11	/* 0x00000800 */
#define	BHND_PMU_RES4325_LNLDO4_PU		12	/* 0x00001000 */
#define	BHND_PMU_RES4325_XTAL_PU		13	/* 0x00002000 */
#define	BHND_PMU_RES4325_ALP_AVAIL		14	/* 0x00004000 */
#define	BHND_PMU_RES4325_RX_PWRSW_PU		15	/* 0x00008000 */
#define	BHND_PMU_RES4325_TX_PWRSW_PU		16	/* 0x00010000 */
#define	BHND_PMU_RES4325_RFPLL_PWRSW_PU		17	/* 0x00020000 */
#define	BHND_PMU_RES4325_LOGEN_PWRSW_PU		18	/* 0x00040000 */
#define	BHND_PMU_RES4325_AFE_PWRSW_PU		19	/* 0x00080000 */
#define	BHND_PMU_RES4325_BBPLL_PWRSW_PU		20	/* 0x00100000 */
#define	BHND_PMU_RES4325_HT_AVAIL		21	/* 0x00200000 */

/* 4325 B0/C0 PMU resources */
#define	BHND_PMU_RES4325B0_CBUCK_LPOM		1	/* 0x00000002 */
#define	BHND_PMU_RES4325B0_CBUCK_BURST		2	/* 0x00000004 */
#define	BHND_PMU_RES4325B0_CBUCK_PWM		3	/* 0x00000008 */
#define	BHND_PMU_RES4325B0_CLDO_PU		4	/* 0x00000010 */

/* 4325 C1 PMU resources */
#define	BHND_PMU_RES4325C1_LNLDO2_PU		12	/* 0x00001000 */

/* 4325 PMU resources */
#define	BHND_PMU_RES4329_RESERVED0		0	/* 0x00000001 */
#define	BHND_PMU_RES4329_CBUCK_LPOM		1	/* 0x00000002 */
#define	BHND_PMU_RES4329_CBUCK_BURST		2	/* 0x00000004 */
#define	BHND_PMU_RES4329_CBUCK_PWM		3	/* 0x00000008 */
#define	BHND_PMU_RES4329_CLDO_PU		4	/* 0x00000010 */
#define	BHND_PMU_RES4329_PALDO_PU		5	/* 0x00000020 */
#define	BHND_PMU_RES4329_ILP_REQUEST		6	/* 0x00000040 */
#define	BHND_PMU_RES4329_RESERVED7		7	/* 0x00000080 */
#define	BHND_PMU_RES4329_RESERVED8		8	/* 0x00000100 */
#define	BHND_PMU_RES4329_LNLDO1_PU		9	/* 0x00000200 */
#define	BHND_PMU_RES4329_OTP_PU			10	/* 0x00000400 */
#define	BHND_PMU_RES4329_RESERVED11		11	/* 0x00000800 */
#define	BHND_PMU_RES4329_LNLDO2_PU		12	/* 0x00001000 */
#define	BHND_PMU_RES4329_XTAL_PU		13	/* 0x00002000 */
#define	BHND_PMU_RES4329_ALP_AVAIL		14	/* 0x00004000 */
#define	BHND_PMU_RES4329_RX_PWRSW_PU		15	/* 0x00008000 */
#define	BHND_PMU_RES4329_TX_PWRSW_PU		16	/* 0x00010000 */
#define	BHND_PMU_RES4329_RFPLL_PWRSW_PU		17	/* 0x00020000 */
#define	BHND_PMU_RES4329_LOGEN_PWRSW_PU		18	/* 0x00040000 */
#define	BHND_PMU_RES4329_AFE_PWRSW_PU		19	/* 0x00080000 */
#define	BHND_PMU_RES4329_BBPLL_PWRSW_PU		20	/* 0x00100000 */
#define	BHND_PMU_RES4329_HT_AVAIL		21	/* 0x00200000 */

/* 4312 PMU resources (all PMU chips with little memory constraint) */
#define	BHND_PMU_RES4312_SWITCHER_BURST		0	/* 0x00000001 */
#define	BHND_PMU_RES4312_SWITCHER_PWM    	1	/* 0x00000002 */
#define	BHND_PMU_RES4312_PA_REF_LDO		2	/* 0x00000004 */
#define	BHND_PMU_RES4312_CORE_LDO_BURST		3	/* 0x00000008 */
#define	BHND_PMU_RES4312_CORE_LDO_PWM		4	/* 0x00000010 */
#define	BHND_PMU_RES4312_RADIO_LDO		5	/* 0x00000020 */
#define	BHND_PMU_RES4312_ILP_REQUEST		6	/* 0x00000040 */
#define	BHND_PMU_RES4312_BG_FILTBYP		7	/* 0x00000080 */
#define	BHND_PMU_RES4312_TX_FILTBYP		8	/* 0x00000100 */
#define	BHND_PMU_RES4312_RX_FILTBYP		9	/* 0x00000200 */
#define	BHND_PMU_RES4312_XTAL_PU		10	/* 0x00000400 */
#define	BHND_PMU_RES4312_ALP_AVAIL		11	/* 0x00000800 */
#define	BHND_PMU_RES4312_BB_PLL_FILTBYP		12	/* 0x00001000 */
#define	BHND_PMU_RES4312_RF_PLL_FILTBYP		13	/* 0x00002000 */
#define	BHND_PMU_RES4312_HT_AVAIL		14	/* 0x00004000 */

/* 4322 PMU resources */
#define	BHND_PMU_RES4322_RF_LDO			0
#define	BHND_PMU_RES4322_ILP_REQUEST		1
#define	BHND_PMU_RES4322_XTAL_PU		2
#define	BHND_PMU_RES4322_ALP_AVAIL		3
#define	BHND_PMU_RES4322_SI_PLL_ON		4
#define	BHND_PMU_RES4322_HT_SI_AVAIL		5
#define	BHND_PMU_RES4322_PHY_PLL_ON		6
#define	BHND_PMU_RES4322_HT_PHY_AVAIL		7
#define	BHND_PMU_RES4322_OTP_PU			8

/* 43224 chip-specific CHIPCTRL register bits */
#define	BHND_PMU_CCTRL43224_GPIO_TOGGLE	0x8000
#define	BHND_PMU_CCTRL43224A0_12MA_LED_DRIVE	0x00F000F0	/* 12 mA drive strength */
#define	BHND_PMU_CCTRL43224B0_12MA_LED_DRIVE	0xF0		/* 12 mA drive strength for later 43224s */

/* 43236 PMU resources */
#define	BHND_PMU_RES43236_REGULATOR		0
#define	BHND_PMU_RES43236_ILP_REQUEST		1
#define	BHND_PMU_RES43236_XTAL_PU		2
#define	BHND_PMU_RES43236_ALP_AVAIL		3
#define	BHND_PMU_RES43236_SI_PLL_ON		4
#define	BHND_PMU_RES43236_HT_SI_AVAIL		5

/* 43236 chip-specific CHIPCTRL register bits */
#define	BHND_PMU_CCTRL43236_BT_COEXIST		(1<<0)	/* 0 disable */
#define	BHND_PMU_CCTRL43236_SECI		(1<<1)	/* 0 SECI is disabled (JATG functional) */
#define	BHND_PMU_CCTRL43236_EXT_LNA		(1<<2)	/* 0 disable */
#define	BHND_PMU_CCTRL43236_ANT_MUX_2o3		(1<<3)	/* 2o3 mux, chipcontrol bit 3 */
#define	BHND_PMU_CCTRL43236_GSIO		(1<<4)	/* 0 disable */

/* 4331 PMU resources */
#define	BHND_PMU_RES4331_REGULATOR		0
#define	BHND_PMU_RES4331_ILP_REQUEST		1
#define	BHND_PMU_RES4331_XTAL_PU		2
#define	BHND_PMU_RES4331_ALP_AVAIL		3
#define	BHND_PMU_RES4331_SI_PLL_ON		4
#define	BHND_PMU_RES4331_HT_SI_AVAIL		5

/* 4315 PMU resources */
#define	BHND_PMU_RES4315_CBUCK_LPOM		1	/* 0x00000002 */
#define	BHND_PMU_RES4315_CBUCK_BURST		2	/* 0x00000004 */
#define	BHND_PMU_RES4315_CBUCK_PWM		3	/* 0x00000008 */
#define	BHND_PMU_RES4315_CLDO_PU		4	/* 0x00000010 */
#define	BHND_PMU_RES4315_PALDO_PU		5	/* 0x00000020 */
#define	BHND_PMU_RES4315_ILP_REQUEST		6	/* 0x00000040 */
#define	BHND_PMU_RES4315_LNLDO1_PU		9	/* 0x00000200 */
#define	BHND_PMU_RES4315_OTP_PU			10	/* 0x00000400 */
#define	BHND_PMU_RES4315_LNLDO2_PU		12	/* 0x00001000 */
#define	BHND_PMU_RES4315_XTAL_PU		13	/* 0x00002000 */
#define	BHND_PMU_RES4315_ALP_AVAIL		14	/* 0x00004000 */
#define	BHND_PMU_RES4315_RX_PWRSW_PU		15	/* 0x00008000 */
#define	BHND_PMU_RES4315_TX_PWRSW_PU		16	/* 0x00010000 */
#define	BHND_PMU_RES4315_RFPLL_PWRSW_PU		17	/* 0x00020000 */
#define	BHND_PMU_RES4315_LOGEN_PWRSW_PU		18	/* 0x00040000 */
#define	BHND_PMU_RES4315_AFE_PWRSW_PU		19	/* 0x00080000 */
#define	BHND_PMU_RES4315_BBPLL_PWRSW_PU		20	/* 0x00100000 */
#define	BHND_PMU_RES4315_HT_AVAIL		21	/* 0x00200000 */

/* 4319 PMU resources */
#define	BHND_PMU_RES4319_CBUCK_LPOM		1	/* 0x00000002 */
#define	BHND_PMU_RES4319_CBUCK_BURST		2	/* 0x00000004 */
#define	BHND_PMU_RES4319_CBUCK_PWM		3	/* 0x00000008 */
#define	BHND_PMU_RES4319_CLDO_PU		4	/* 0x00000010 */
#define	BHND_PMU_RES4319_PALDO_PU		5	/* 0x00000020 */
#define	BHND_PMU_RES4319_ILP_REQUEST		6	/* 0x00000040 */
#define	BHND_PMU_RES4319_LNLDO1_PU		9	/* 0x00000200 */
#define	BHND_PMU_RES4319_OTP_PU			10	/* 0x00000400 */
#define	BHND_PMU_RES4319_LNLDO2_PU		12	/* 0x00001000 */
#define	BHND_PMU_RES4319_XTAL_PU		13	/* 0x00002000 */
#define	BHND_PMU_RES4319_ALP_AVAIL		14	/* 0x00004000 */
#define	BHND_PMU_RES4319_RX_PWRSW_PU		15	/* 0x00008000 */
#define	BHND_PMU_RES4319_TX_PWRSW_PU		16	/* 0x00010000 */
#define	BHND_PMU_RES4319_RFPLL_PWRSW_PU		17	/* 0x00020000 */
#define	BHND_PMU_RES4319_LOGEN_PWRSW_PU		18	/* 0x00040000 */
#define	BHND_PMU_RES4319_AFE_PWRSW_PU		19	/* 0x00080000 */
#define	BHND_PMU_RES4319_BBPLL_PWRSW_PU		20	/* 0x00100000 */
#define	BHND_PMU_RES4319_HT_AVAIL		21	/* 0x00200000 */

/* 4319 chip-specific CHIPCTL register bits */
#define	BHND_PMU1_PLL0_CHIPCTL0		0
#define	BHND_PMU1_PLL0_CHIPCTL1		1
#define	BHND_PMU1_PLL0_CHIPCTL2		2
#define	BHND_PMU_CCTRL4319USB_XTAL_SEL_MASK	0x00180000
#define	BHND_PMU_CCTRL4319USB_XTAL_SEL_SHIFT	19
#define	BHND_PMU_CCTRL4319USB_48MHZ_PLL_SEL	1
#define	BHND_PMU_CCTRL4319USB_24MHZ_PLL_SEL	2

/* 4336 PMU resources  */
#define	BHND_PMU_RES4336_CBUCK_LPOM		0
#define	BHND_PMU_RES4336_CBUCK_BURST		1
#define	BHND_PMU_RES4336_CBUCK_LP_PWM		2
#define	BHND_PMU_RES4336_CBUCK_PWM		3
#define	BHND_PMU_RES4336_CLDO_PU		4
#define	BHND_PMU_RES4336_DIS_INT_RESET_PD	5
#define	BHND_PMU_RES4336_ILP_REQUEST		6
#define	BHND_PMU_RES4336_LNLDO_PU		7
#define	BHND_PMU_RES4336_LDO3P3_PU		8
#define	BHND_PMU_RES4336_OTP_PU			9
#define	BHND_PMU_RES4336_XTAL_PU		10
#define	BHND_PMU_RES4336_ALP_AVAIL		11
#define	BHND_PMU_RES4336_RADIO_PU		12
#define	BHND_PMU_RES4336_BG_PU			13
#define	BHND_PMU_RES4336_VREG1p4_PU_PU		14
#define	BHND_PMU_RES4336_AFE_PWRSW_PU		15
#define	BHND_PMU_RES4336_RX_PWRSW_PU		16
#define	BHND_PMU_RES4336_TX_PWRSW_PU		17
#define	BHND_PMU_RES4336_BB_PWRSW_PU		18
#define	BHND_PMU_RES4336_SYNTH_PWRSW_PU		19
#define	BHND_PMU_RES4336_MISC_PWRSW_PU		20
#define	BHND_PMU_RES4336_LOGEN_PWRSW_PU		21
#define	BHND_PMU_RES4336_BBPLL_PWRSW_PU		22
#define	BHND_PMU_RES4336_MACPHY_CLKAVAIL	23
#define	BHND_PMU_RES4336_HT_AVAIL		24
#define	BHND_PMU_RES4336_RSVD			25

/* 4330 resources */
#define	BHND_PMU_RES4330_CBUCK_LPOM		0
#define	BHND_PMU_RES4330_CBUCK_BURST		1
#define	BHND_PMU_RES4330_CBUCK_LP_PWM		2
#define	BHND_PMU_RES4330_CBUCK_PWM		3
#define	BHND_PMU_RES4330_CLDO_PU		4
#define	BHND_PMU_RES4330_DIS_INT_RESET_PD	5
#define	BHND_PMU_RES4330_ILP_REQUEST		6
#define	BHND_PMU_RES4330_LNLDO_PU		7
#define	BHND_PMU_RES4330_LDO3P3_PU		8
#define	BHND_PMU_RES4330_OTP_PU			9
#define	BHND_PMU_RES4330_XTAL_PU		10
#define	BHND_PMU_RES4330_ALP_AVAIL		11
#define	BHND_PMU_RES4330_RADIO_PU		12
#define	BHND_PMU_RES4330_BG_PU			13
#define	BHND_PMU_RES4330_VREG1p4_PU_PU		14
#define	BHND_PMU_RES4330_AFE_PWRSW_PU		15
#define	BHND_PMU_RES4330_RX_PWRSW_PU		16
#define	BHND_PMU_RES4330_TX_PWRSW_PU		17
#define	BHND_PMU_RES4330_BB_PWRSW_PU		18
#define	BHND_PMU_RES4330_SYNTH_PWRSW_PU		19
#define	BHND_PMU_RES4330_MISC_PWRSW_PU		20
#define	BHND_PMU_RES4330_LOGEN_PWRSW_PU		21
#define	BHND_PMU_RES4330_BBPLL_PWRSW_PU		22
#define	BHND_PMU_RES4330_MACPHY_CLKAVAIL	23
#define	BHND_PMU_RES4330_HT_AVAIL		24
#define	BHND_PMU_RES4330_5gRX_PWRSW_PU		25
#define	BHND_PMU_RES4330_5gTX_PWRSW_PU		26
#define	BHND_PMU_RES4330_5g_LOGEN_PWRSW_PU	27

/* 4313 resources */
#define	BHND_PMU_RES4313_BB_PU_RSRC		0
#define	BHND_PMU_RES4313_ILP_REQ_RSRC		1
#define	BHND_PMU_RES4313_XTAL_PU_RSRC		2
#define	BHND_PMU_RES4313_ALP_AVAIL_RSRC		3
#define	BHND_PMU_RES4313_RADIO_PU_RSRC		4
#define	BHND_PMU_RES4313_BG_PU_RSRC		5
#define	BHND_PMU_RES4313_VREG1P4_PU_RSRC	6
#define	BHND_PMU_RES4313_AFE_PWRSW_RSRC		7
#define	BHND_PMU_RES4313_RX_PWRSW_RSRC		8
#define	BHND_PMU_RES4313_TX_PWRSW_RSRC		9
#define	BHND_PMU_RES4313_BB_PWRSW_RSRC		10
#define	BHND_PMU_RES4313_SYNTH_PWRSW_RSRC	11
#define	BHND_PMU_RES4313_MISC_PWRSW_RSRC	12
#define	BHND_PMU_RES4313_BB_PLL_PWRSW_RSRC	13
#define	BHND_PMU_RES4313_HT_AVAIL_RSRC		14
#define	BHND_PMU_RES4313_MACPHY_CLK_AVAIL_RSRC	15

/* 4313 chip-specific CHIPCTRL register bits */
#define	BHND_PMU_CCTRL4313_12MA_LED_DRIVE	0x00000007	/* 12 mA drive strengh for later 4313 */

/* 43228 resources */
#define	BHND_PMU_RES43228_NOT_USED		0
#define	BHND_PMU_RES43228_ILP_REQUEST		1
#define	BHND_PMU_RES43228_XTAL_PU		2
#define	BHND_PMU_RES43228_ALP_AVAIL		3
#define	BHND_PMU_RES43228_PLL_EN		4
#define	BHND_PMU_RES43228_HT_PHY_AVAIL		5

/*
* Maximum delay for the PMU state transition in us.
* This is an upper bound intended for spinwaits etc.
*/
#define	BHND_PMU_MAX_TRANSITION_DLY		15000

/* PMU resource up transition time in ILP cycles */
#define	BHND_PMURES_UP_TRANSITION		2

#endif /* _BHND_CORES_PMU_BHND_PMUREG_H_ */
