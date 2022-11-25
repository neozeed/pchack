/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* ioctl.c - version 1.0.2 */

/* This cannot be part of tty.c (as it was earlier) since on some
   systems (e.g. MUNIX) the include files <termio.h> and <sgtty.h>
   define the same constants, and the C preprocessor complains. */
#include <stdio.h>
#include "config.h"
#ifndef MSDOS
#ifdef BSD
#include	<sgtty.h>
struct ltchars ltchars, ltchars0;
#else
#include	<termio.h>	/* also includes part of <sgtty.h> */
struct termio termio;
#endif BSD
#endif MSDOS

getioctls() {
#ifndef MSDOS
#ifdef BSD
	(void) ioctl(fileno(stdin), (int) TIOCGLTC, (char *) &ltchars);
	(void) ioctl(fileno(stdin), (int) TIOCSLTC, (char *) &ltchars0);
#else
	(void) ioctl(fileno(stdin), (int) TCGETA, &termio);
#endif BSD
#endif MSDOS
}

setioctls() {
#ifndef MSDOS
#ifdef BSD
	(void) ioctl(fileno(stdin), (int) TIOCSLTC, (char *) &ltchars);
#else
	(void) ioctl(fileno(stdin), (int) TCSETA, &termio);
#endif BSD
#endif MSDOS
}

#ifdef SUSPEND		/* implies BSD */
dosuspend() {
#include	<signal.h>
#ifdef SIGTSTP
	if(signal(SIGTSTP, SIG_IGN) == SIG_DFL) {
		settty((char *) 0);
		(void) signal(SIGTSTP, SIG_DFL);
		(void) kill(0, SIGTSTP);
		gettty();
		setftty();
		docrt();
	} else {
		pline("I don't think your shell has job control.");
	}
#else SIGTSTP
	pline("Sorry, it seems we have no SIGTSTP here. Try ! or S.");
#endif SIGTSTP
	return(0);
}
#endif SUSPEND
