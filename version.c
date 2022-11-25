/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* version.c - version 1.0.3 */
/* $Header: version.c,v 1.5 85/05/09 00:40:41 aeb Exp $ */

#include "config.h"
#ifdef DGK

doversion()
{
	pline("PC HACK 1.03 - Oct 15, 1985");
	return (0);
}

doMSCversion()
{
	pline("PC HACK 1.03 is the MSDOS(tm) version of UNIX(tm) HACK 1.03");
	pline("PC implementation in Microsoft(tm) C by D.Kneller, Berkeley, CA");
	return (0);
}

#else DGK

#include	"date.h"

doversion(){
	pline("%s 1.0.3 - last edit %s.", (
#ifdef QUEST
		"Quest"
#else
		"Hack"
#endif QUEST
		), datestring);
	return(0);
}
#endif DGK
