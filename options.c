/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* options.c - version 1.0.3 */

#include "hack.h"
extern char *eos();
boolean female;		/* should have been flags.female */
#ifdef DGK
static boolean set_order;	/* user has set a different pack ordering */
#endif DGK

initoptions()
{
	register char *opts;
	extern char *getenv();

	flags.time = flags.nonews = flags.notombstone = flags.end_own =
	flags.standout = flags.nonull = FALSE;
	flags.invlet_constant = TRUE;
	flags.no_rest_on_space = TRUE;
	flags.end_top = 5;
	flags.end_around = 4;
	female = FALSE;			/* players are usually male */

#ifdef DGK
	flags.silent = FALSE;
	flags.BIOSok = FALSE;
	flags.confirm = TRUE;
	flags.pickup = TRUE;
	flags.sortpack = TRUE;
	read_config_file();
#else
	if(opts = getenv("HACKOPTIONS"))
		parseoptions(opts,TRUE);
#endif DGK
}

parseoptions(opts, from_env)
register char *opts;
boolean from_env;
{
	register char *op,*op2;
	unsigned num;
	boolean negated;

	if(op = index(opts, ',')) {
		*op++ = 0;
		parseoptions(op, from_env);
	}
	if(op = index(opts, ' ')) {
		op2 = op;
		while(*op++)
			if(*op != ' ') *op2++ = *op;
	}
	if(!*opts) return;
	negated = FALSE;
	while((*opts == '!') || !strncmp(opts, "no", 2)) {
		if(*opts == '!') opts++; else opts += 2;
		negated = !negated;
	}
	
	if(!strncmp(opts,"standout",4)) {
		flags.standout = !negated;
		return;
	}

	if(!strncmp(opts,"null",4)) {
		flags.nonull = negated;
		return;
	}

	if(!strncmp(opts,"tombstone",4)) {
		flags.notombstone = negated;
		return;
	}

#ifdef DGK
	if (!strncmp(opts, "sile", 4)) {
		flags.silent = !negated;
		return;
	}

	if (!strncmp(opts, "conf", 4)) {
		flags.confirm = !negated;
		return;
	}

	if (!strncmp(opts, "pick", 4)) {
		flags.pickup = !negated;
		return;
	}

	if (!strncmp(opts, "BIOS", 4)) {
		flags.BIOSok = !negated;
		return;
	}

	if (!strncmp(opts, "sort", 4)) {
		flags.sortpack = !negated;
		return;
	}

	/*
	 * packorder specifies the order to list the pack -kcrca
	 */
	if (!strncmp(opts,"packorder",4)) {
		register char	*sp;
		extern char	inv_order[];
		char tmp[BUFSZ];
		int tmpend;

		op = index(opts,':');
		if(!op) goto bad;
		op++;					/* skip over ':' */

		/*
		 * The new order must have exactly one occurrance of
		 * the valid characters, but if some are missing they
		 * are filled in from inv_order at the end of the order
		 */
		for (sp = op; *sp; sp++)
			if (!index(inv_order, *sp))
				goto bad;		/* bad char in order */
			else if (index(sp + 1, *sp))
				goto bad;		/* dup char in order */
		(void) strcpy(tmp, op);
		for (sp = inv_order, tmpend = strlen(tmp); *sp; sp++)
			if (!index(tmp, *sp)) {
				tmp[tmpend++] = *sp;
				tmp[tmpend] = 0;
			}
		(void) strcpy(inv_order, tmp);
		set_order = TRUE;
		return;
	}
#endif DGK

#ifdef NEWS
	if(!strncmp(opts,"news",4)) {
		flags.nonews = negated;
		return;
	}
#endif NEWS

	if(!strncmp(opts,"time",4)) {
		flags.time = !negated;
		flags.botl = 1;
		return;
	}

	if(!strncmp(opts,"restonspace",4)) {
		flags.no_rest_on_space = negated;
		return;
	}

	if(!strncmp(opts,"fixinv",4)) {
#ifdef DGK
		flags.invlet_constant = !negated;
		if (flags.invlet_constant)
			fixinv();
#else
		if(from_env)
			flags.invlet_constant = !negated;
		else
			pline("The fixinvlet option must be in HACKOPTIONS.");
#endif DGK
		return;
	}

	if(!strncmp(opts,"male",4)) {
		female = negated;
		return;
	}
	if(!strncmp(opts,"female",4)) {
		female = !negated;
		return;
	}

	/* name:string */
	if(!strncmp(opts,"name",4)) {
		extern char plname[PL_NSIZ];
		if(!from_env) {
		  pline("The playername can be set only from HACKOPTIONS.");
		  return;
		}
		op = index(opts,':');
		if(!op) goto bad;
		(void) strncpy(plname, op+1, sizeof(plname)-1);
		return;
	}

	/* endgame:5t[op] 5a[round] o[wn] */
	if(!strncmp(opts,"endgame",3)) {
		op = index(opts,':');
		if(!op) goto bad;
		op++;
		while(*op) {
			num = 1;
			if(digit(*op)) {
				num = atoi(op);
				while(digit(*op)) op++;
			} else
			if(*op == '!') {
				negated = !negated;
				op++;
			}
			switch(*op) {
			case 't':
				flags.end_top = num;
				break;
			case 'a':
				flags.end_around = num;
				break;
			case 'o':
				flags.end_own = !negated;
				break;
			default:
				goto bad;
			}
			while(letter(*++op)) ;
			if(*op == '/') op++;
		}
		return;
	}
bad:
	if(!from_env) {
		if(!strncmp(opts, "help", 4)) {
			pline("%s%s%s",
#ifdef DGK

"To set options use OPTIONS=<options> in your configuration file, or ",
"give the command \"O\" followed by the line <options> while playing.  ",
"Here <options> is a list of options separated by commas." );
			pline("%s%s%s",
"The boolean options are restonspace, time, tombstone, male, female, ",
"standout, fixinv, sortpack, pickup, BIOSok, confirm, and silent. ",
"These can be negated by prefixing them with '!' or \"no\"." );
  			pline("%s%s%s",
"The compound options are name, as in OPTIONS=name:Merlin-W, packorder, ",
"which lists the order that items should appear in your pack (the ",
"default is:  packorder:\")[%?/=!(*0  ), and endgame." );
			pline("%s%s%s",
"Endgame is followed by a description of which parts of the scorelist ",
"you wish to see.  You might for example say: ",
"\"endgame:own scores/5 top scores/4 around my score\"." );

#else

"To set options use `HACKOPTIONS=\"<options>\"' in your environment, or ",
"give the command 'o' followed by the line `<options>' while playing. ",
"Here <options> is a list of <option>s separated by commas." );
			pline("%s%s%s",
"Simple (boolean) options are rest_on_space, news, time, ",
"null, tombstone, (fe)male. ",
"These can be negated by prefixing them with '!' or \"no\"." );
			pline("%s",
"A string option is name, as in HACKOPTIONS=\"name:Merlin-W\"." );
			pline("%s%s%s",
"A compound option is endgame; it is followed by a description of what ",
"parts of the scorelist you want to see. You might for example say: ",
"`endgame:own scores/5 top scores/4 around my score'." );

#endif DGK
			return;
		}
		pline("Bad option: %s.", opts);
		pline("Type \"O help<cr>\" for help.");
		return;
	}
#ifdef DGK
	puts("Bad syntax in OPTIONS in the configuration file");
#else
	puts("Bad syntax in HACKOPTIONS.");
	puts("Use for example:");
	puts(
"HACKOPTIONS=\"!restonspace,notombstone,endgame:own/5 topscorers/4 around me\""
	);
#endif DGK
	getret();
}

doset()
{
	char buf[BUFSZ];
#ifdef DGK
 	extern char inv_order[];
#endif DGK

	pline("What options do you want to set? ");
	getlin(buf);
 	if(!buf[0] || buf[0] == '\033') {
	    (void) strcpy(buf,"HACKOPTIONS=");
	    (void) strcat(buf,female ? "female," : "male,");
	    if(flags.standout) (void) strcat(buf,"standout,");
	    if(flags.nonull) (void) strcat(buf,"nonull,");
#ifdef NEWS
	    if(flags.nonews) (void) strcat(buf,"nonews,");
#endif NEWS
	    if(flags.time) (void) strcat(buf,"time,");
	    if(flags.notombstone) (void) strcat(buf,"!tombstone,");
	    if(flags.invlet_constant) (void) strcat(buf,"fixinv,");
	    if(!flags.no_rest_on_space) (void) strcat(buf,"restonspace,");
#ifdef DGK
	    if (flags.sortpack) (void) strcat(buf,"sortpack,");
	    if (flags.pickup) (void) strcat(buf,"pickup,");
	    if (flags.BIOSok) (void) strcat(buf,"BIOSok,");
	    if (flags.confirm) (void) strcat(buf,"confirm,");
	    if (flags.silent) (void) strcat(buf,"silent,");
	    if (set_order){
		(void) strcat(buf, "packorder: ");
		(void) strcat(buf, inv_order);
		(void) strcat(buf, ",");
	    }
#endif DGK
	    if(flags.end_top != 5 || flags.end_around != 4 || flags.end_own){
		(void) sprintf(eos(buf), "endgame: %u topscores/%u around me",
			flags.end_top, flags.end_around);
		if(flags.end_own) (void) strcat(buf, "/own scores");
	    } else {
		register char *eop = eos(buf);
		if(*--eop == ',') *eop = 0;
	    }
	    pline(buf);
	} else
	    parseoptions(buf, FALSE);

	return(0);
}
