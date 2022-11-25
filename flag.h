/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* flag.h - version 1.0.3 */

struct flag {
	unsigned ident;		/* social security number for each monster */
	unsigned debug;		/* in debugging mode */
#define	wizard	flags.debug
	unsigned toplin;	/* a top line (message) has been printed */
				/* 0: top line empty; 2: no --More-- reqd. */
	unsigned cbreak;	/* in cbreak mode, rogue format */
	unsigned standout;	/* use standout for --More-- */
	unsigned nonull;	/* avoid sending nulls to the terminal */
	unsigned time;		/* display elapsed 'time' */
	unsigned nonews;	/* suppress news printing */
	unsigned notombstone;
	unsigned end_top, end_around;	/* describe desired score list */
	unsigned end_own;		/* idem (list all own scores) */
	unsigned no_rest_on_space;	/* spaces are ignored */
	unsigned beginner;
	unsigned move;
	unsigned invlet_constant;	/* let objects keep their
					   inventory symbol */
	unsigned mv;
	unsigned run;		/* 0: h (etc), 1: H (etc), 2: fh (etc) */
				/* 3: FH, 4: ff+, 5: ff-, 6: FF+, 7: FF- */
	unsigned nopick;	/* do not pickup objects */
	unsigned echo;		/* 1 to echo characters */
	unsigned botl;		/* partially redo status line */
	unsigned botlx;		/* print an entirely new bottom line */
	unsigned nscrinh;	/* inhibit nscr() in pline(); */
	unsigned made_amulet;
	unsigned no_of_wizards;	/* 0, 1 or 2 (wizard and his shadow) */
				/* reset from 2 to 1, but never to 0 */
	unsigned moonphase;
#define	NEW_MOON	0
#define	FULL_MOON	4

#ifdef DGK
	unsigned silent;	/* whether the bell rings or not */
	unsigned confirm;	/* confirm before hitting tame monsters */
	unsigned pickup;	/* whether you pickup or move and look */
	unsigned BIOSok;	/* whether we can use a BIOS call for
				 * redrawing the screen and character input */
	unsigned sortpack;
	unsigned extra2;
#endif DGK
};

extern struct flag flags;

