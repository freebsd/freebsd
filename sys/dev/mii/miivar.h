/*	$NetBSD: miivar.h,v 1.8 1999/04/23 04:24:32 thorpej Exp $	*/

/*-
 * Copyright (c) 1998, 1999 The NetBSD Foundation, Inc.
 * All rights reserved.
 *
 * This code is derived from software contributed to The NetBSD Foundation
 * by Jason R. Thorpe of the Numerical Aerospace Simulation Facility,
 * NASA Ames Research Center.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE NETBSD FOUNDATION, INC. AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR CONTRIBUTORS
 * BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * $FreeBSD$
 */

#ifndef _DEV_MII_MIIVAR_H_
#define	_DEV_MII_MIIVAR_H_

#include <sys/queue.h>

/*
 * Media Independent Interface data structure definitions.
 */

/*
 * This is the interface from the network interface driver to the MII
 * layer.  A NIC driver grabs the structure via device_get_softc(miibus).
 */
struct mii_data {
	/*
	 * Current media word.  Matches the one that if_media.c stores.
	 * Modified by mii_mediachg().  Most functions descent from
	 * mii_mediachg(), and carry requested media word as argument,
	 * however some require it to be saved in softc.
	 */
	if_media_t mii_media;

	/*
	 * For network interfaces with multiple PHYs, a list of all
	 * PHYs is required so they can all be notified when a media
	 * request is made.
	 */
	LIST_HEAD(mii_listhead, mii_softc) mii_phys;
	u_int mii_instance;

	/*
	 * PHY driver fills this in with active media status.
	 */
	u_int mii_media_status;
	u_int mii_media_active;

	/*
	 * The number of MII_MAX_MEDIAE was taken quite carelessly.
	 * The mii_physubr.c can add at maximum 20 mediae per phy.
	 * Some phys (acphy) can a couple of extra mediae on top of
	 * that.  However, there could be several phys per miibus(4).
	 * On the other hand, all known NICs that may have several
	 * phys, are quite old and their twisted pair phy can run
	 * at maximum of 100 Mbit/s.
	 * We could allocate this array dynamically, but looks like
	 * miibus(4) enabled drivers are now legacy, so a more simple
	 * static design was chosen.
	 */
#define	MII_MAX_MEDIAE	30
	u_int mii_index;
	if_media_t mii_mediae[MII_MAX_MEDIAE + 1];
};
typedef struct mii_data mii_data_t;

/*
 * Requests that can be made to the downcall.
 */
typedef enum {
	MII_TICK = 1,	/* once-per-second tick */
	MII_MEDIACHG,	/* user changed media; perform the switch */
	MII_POLLSTAT,	/* user requested media status; fill it in */
} mii_cmd_t;

struct mii_softc;

/*
 * Functions provided by the PHY to perform various functions.
 */
struct mii_phy_funcs {
	int (*pf_service)(struct mii_softc *, struct mii_data *, mii_cmd_t,
	    if_media_t media);
	void (*pf_status)(struct mii_softc *, if_media_t);
	void (*pf_reset)(struct mii_softc *, if_media_t);
};

/*
 * Each PHY driver's softc has one of these as the first member.
 * XXX This would be better named "phy_softc", but this is the name
 * XXX BSDI used, and we would like to have the same interface.
 */
struct mii_softc {
	device_t mii_dev;		/* generic device glue */

	LIST_ENTRY(mii_softc) mii_list;	/* entry on parent's PHY list */

	uint32_t mii_mpd_oui;		/* the PHY's OUI (MII_OUI())*/
	uint32_t mii_mpd_model;		/* the PHY's model (MII_MODEL())*/
	uint32_t mii_mpd_rev;		/* the PHY's revision (MII_REV())*/
	u_int mii_capmask;		/* capability mask for BMSR */
	u_int mii_phy;			/* our MII address */
	u_int mii_offset;		/* first PHY, second PHY, etc. */
	u_int mii_inst;			/* instance for ifmedia */

	/* Our PHY functions. */
	const struct mii_phy_funcs *mii_funcs;

	struct mii_data *mii_pdata;	/* pointer to parent's mii_data */

	u_int mii_flags;		/* misc. flags; see below */
	u_int mii_capabilities;		/* capabilities from BMSR */
	u_int mii_extcapabilities;	/* extended capabilities */
	u_int mii_ticks;		/* MII_TICK counter */
	u_int mii_anegticks;		/* ticks before retrying aneg */
	u_int mii_media_active;		/* last active media */
	u_int mii_media_status;		/* last active status */
};
typedef struct mii_softc mii_softc_t;

/* mii_flags */
#define	MIIF_INITDONE	0x00000001	/* has been initialized (mii_data) */
#define	MIIF_NOISOLATE	0x00000002	/* do not isolate the PHY */
#if 0
#define	MIIF_NOLOOP	0x00000004	/* no loopback capability */
#endif
#define	MIIF_DOINGAUTO	0x00000008	/* doing autonegotiation (mii_softc) */
#define	MIIF_AUTOTSLEEP	0x00000010	/* use tsleep(), not callout() */
#define	MIIF_HAVEFIBER	0x00000020	/* from parent: has fiber interface */
#define	MIIF_HAVE_GTCR	0x00000040	/* has 100base-T2/1000base-T CR */
#define	MIIF_IS_1000X	0x00000080	/* is a 1000BASE-X device */
#define	MIIF_DOPAUSE	0x00000100	/* advertise PAUSE capability */
#define	MIIF_IS_HPNA	0x00000200	/* is a HomePNA device */
#define	MIIF_FORCEANEG	0x00000400	/* force auto-negotiation */
#define	MIIF_NOMANPAUSE	0x00100000	/* no manual PAUSE selection */
#define	MIIF_FORCEPAUSE	0x00200000	/* force PAUSE advertisement */
#define	MIIF_MACPRIV0	0x01000000	/* private to the MAC driver */
#define	MIIF_MACPRIV1	0x02000000	/* private to the MAC driver */
#define	MIIF_MACPRIV2	0x04000000	/* private to the MAC driver */
#define	MIIF_PHYPRIV0	0x10000000	/* private to the PHY driver */
#define	MIIF_PHYPRIV1	0x20000000	/* private to the PHY driver */
#define	MIIF_PHYPRIV2	0x40000000	/* private to the PHY driver */

/* Default mii_anegticks values */
#define	MII_ANEGTICKS		5
#define	MII_ANEGTICKS_GIGE	17

#define	MIIF_INHERIT_MASK	(MIIF_NOISOLATE|MIIF_NOLOOP|MIIF_AUTOTSLEEP)

/*
 * Special `locators' passed to mii_attach().  If one of these is not
 * an `any' value, we look for *that* PHY and configure it.  If both
 * are not `any', that is an error, and mii_attach() will fail.
 */
#define	MII_OFFSET_ANY		-1
#define	MII_PHY_ANY		-1

/*
 * Used to attach a PHY to a parent.
 */
struct mii_attach_args {
	struct mii_data *mii_data;	/* pointer to parent data */
	u_int mii_phyno;		/* MII address */
	u_int mii_offset;		/* first PHY, second PHY, etc. */
	uint32_t mii_id1;		/* PHY ID register 1 */
	uint32_t mii_id2;		/* PHY ID register 2 */
	u_int mii_capmask;		/* capability mask for BMSR */
};
typedef struct mii_attach_args mii_attach_args_t;

/*
 * Used to match a PHY.
 */
struct mii_phydesc {
	uint32_t mpd_oui;		/* the PHY's OUI */
	uint32_t mpd_model;		/* the PHY's model */
	const char *mpd_name;		/* the PHY's name */
};
#define MII_PHY_DESC(a, b) { MII_OUI_ ## a, MII_MODEL_ ## a ## _ ## b, \
	MII_STR_ ## a ## _ ## b }
#define MII_PHY_END	{ 0, 0, NULL }

#ifdef _KERNEL

#define PHY_READ(p, r) \
	MIIBUS_READREG((p)->mii_dev, (p)->mii_phy, (r))

#define PHY_WRITE(p, r, v) \
	MIIBUS_WRITEREG((p)->mii_dev, (p)->mii_phy, (r), (v))

#define	PHY_SERVICE(p, d, o, m) \
	(*(p)->mii_funcs->pf_service)((p), (d), (o), (m))

#define	PHY_STATUS(p, m) \
	(*(p)->mii_funcs->pf_status)((p), (m))

#define	PHY_RESET(p, m) \
	(*(p)->mii_funcs->pf_reset)((p), (m))

enum miibus_device_ivars {
	MIIBUS_IVAR_FLAGS
};

/*
 * Simplified accessors for miibus
 */
#define	MIIBUS_ACCESSOR(var, ivar, type)				\
	__BUS_ACCESSOR(miibus, var, MIIBUS, ivar, type)

MIIBUS_ACCESSOR(flags,		FLAGS,		u_int)

extern devclass_t	miibus_devclass;
extern driver_t		miibus_driver;

int	mii_attach(device_t, device_t *, int, int, int, int);
int	mii_mediachg(struct mii_data *, if_media_t);
void	mii_tick(struct mii_data *);
void	mii_pollstat(struct mii_data *);
void	mii_phy_add_media(struct mii_data *, if_media_t);
void	mii_phy_generic_media(struct mii_softc *);

int	mii_phy_auto(struct mii_softc *, if_media_t);
int	mii_phy_detach(device_t dev);
u_int	mii_phy_flowstatus(struct mii_softc *);
void	mii_phy_reset(struct mii_softc *, if_media_t);
void	mii_phy_setmedia(struct mii_softc *, if_media_t);
void	mii_phy_update(struct mii_softc *, mii_cmd_t);
int	mii_phy_tick(struct mii_softc *);
int	mii_phy_mac_match(struct mii_softc *, const char *);
int	mii_dev_mac_match(device_t, const char *);
void	*mii_phy_mac_softc(struct mii_softc *);
void	*mii_dev_mac_softc(device_t);

const struct mii_phydesc * mii_phy_match(const struct mii_attach_args *ma,
    const struct mii_phydesc *mpd);
const struct mii_phydesc * mii_phy_match_gen(const struct mii_attach_args *ma,
    const struct mii_phydesc *mpd, size_t endlen);
int mii_phy_dev_probe(device_t dev, const struct mii_phydesc *mpd, int mrv);
void mii_phy_dev_attach(device_t dev, u_int flags,
    const struct mii_phy_funcs *mpf, int add_media);

void	ukphy_status(struct mii_softc *, if_media_t);

u_int	mii_oui(u_int, u_int);
#define	MII_OUI(id1, id2)	mii_oui(id1, id2)
#define	MII_MODEL(id2)		(((id2) & IDR2_MODEL) >> 4)
#define	MII_REV(id2)		((id2) & IDR2_REV)

/* Arguments for miibus_readvar(). */
enum {
	MIIVAR_MTU,
};

/* miibus(4) uses some bits of if_media_t for its own cookies. */
#define MII_MEDIA_MASK    (IFM_IMASK | IFM_FLAG0 | IFM_FLAG1 | IFM_FLAG2)

#endif /* _KERNEL */

#endif /* _DEV_MII_MIIVAR_H_ */
