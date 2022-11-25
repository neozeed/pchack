/* An assortment of MSDOS functions.
 */

#include <stdio.h>
#include "hack.h"

#ifdef MSDOS
#include <dos.h>

getuid()
{
	return 1;
}

char *
getlogin()
{
	return ((char *) NULL);
}

#define VIDEO 0x10
int display_page = -1;

void
fastat(x, y, ch)
register xchar x,y;
char ch;
{
	union REGS inregs;

	if(!ch) {
		impossible("At gets null at %d %d.", x, y);
		return;
	}
	if (display_page < 0) {
		inregs.h.ah = 15;
		int86(VIDEO, &inregs, &inregs);
		display_page = inregs.h.bh;
	}
	if (x != curx || y != cury) {
		inregs.h.ah = 2;
		inregs.h.dl = x - 1;
		inregs.h.dh = y + 1;
		inregs.h.bh = display_page;
		int86(VIDEO, &inregs, &inregs);
		curx = x;
		cury = y;
	}
	inregs.h.ah = 14;
	inregs.h.al = ch;
	inregs.h.bh = display_page;
	inregs.x.cx = 1;
	int86(VIDEO, &inregs, &inregs);
	curx++;
}

tgetch()
{
	char ch;
#ifdef DGK
	if (flags.BIOSok)
		ch = BIOSgetch();
	else
#endif DGK
		ch = getch();
	return ((ch == '\r') ? '\n' : ch);
}


#ifdef DGK
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/utime.h>
#include <ctype.h>
#include <fcntl.h>

#undef creat	/* Note that creat() is used once in this file, but
		 * the disk free space doesn't need not be checked as
		 * it will have already been checked.  Thus the undef
		 * can occur here.
		 */

#define LEVELS	"level.00"
#define BONES	"bones.00"
#define Sprintf (void) sprintf

extern char hackdir[], levels[], SAVEF[], bones[], permbones[];
extern int ramdisk;

#ifdef SHELL
#include <process.h>
dosh()
{
	char *comspec, *getenv();
	extern char orgdir[];

	if (comspec = getenv("COMSPEC")) {
		end_screen();
		clear_screen();
		puts("To return to HACK, type \"exit\" at the DOS prompt.");
		fflush(stdout);
		chdirx(orgdir, 0);
		if (spawnl(P_WAIT, comspec, NULL)) {
			printf("\nCan't execute COMSPEC \"%s\"!\n", comspec);
			flags.toplin = 0;
			more();
		}
		chdirx(hackdir, 0);
		start_screen();
		docrt();
	}
	return(0);
}
#endif SHELL

/* Map the keypad to equivalent character output.  If scroll lock is turned
 * on, run without stopping at interesting branches (like YUHJKLBN keys), if
 * it is off, run with stopping at branches (like ^Y^U^H^J^K^L^B^N keys).
 */
#define KEYPADHI	83
#define KEYPADLOW	71
#define CTRL(ch)	(ch ^ 0x40)
#define KEYBRD	0x16
#define iskeypad(x)	(KEYPADLOW <= (x) && (x) <= KEYPADHI)
#define SHIFT		(0x1 | 0x2)
#define CONTROL		0x4
static struct {
	char normal, shift, ctrl;
	} keypad[KEYPADHI - KEYPADLOW + 1] = {
			{'y', 'Y', CTRL('Y')},	/* 7 */
			{'k', 'K', CTRL('K')},	/* 8 */
			{'u', 'U', CTRL('U')},	/* 9 */
			{'m', 'M', 'M'},	/* - */
			{'h', 'H', CTRL('H')},	/* 4 */
			{'.', '.', '.'},	/* 5 */
			{'l', 'L', CTRL('L')},	/* 6 */
			{'p', 'P', CTRL('P')},	/* + */
			{'b', 'B', CTRL('B')},	/* 1 */
			{'j', 'J', CTRL('J')},	/* 2 */
			{'n', 'N', CTRL('N')},	/* 3 */
			{'i', 'I', 'I'},	/* Ins */
			{':', ',', ','}		/* Del */
			};
static char
BIOSgetch()
{
	char scan, shift_state, ch;
	union REGS inregs, outregs;

	do {
		inregs.h.ah = 0;
		int86(KEYBRD, &inregs, &outregs);
	} while (outregs.x.ax == 0);
	ch = outregs.h.al;
	scan = outregs.h.ah;
	inregs.h.ah = 2;
	int86(KEYBRD, &inregs, &outregs);
	shift_state = outregs.h.al;

	if (iskeypad(scan))
		if (shift_state & SHIFT)
			ch = keypad[scan - KEYPADLOW].shift;
		else if (shift_state & CONTROL)
			ch = keypad[scan - KEYPADLOW].ctrl;
		else
			ch = keypad[scan - KEYPADLOW].normal;
	return (ch);
}

dotogglepickup()
{
	flags.pickup = !flags.pickup;
	pline("Pickup: %s.", flags.pickup ? "ON" : "OFF");
	return (0);
}

/* from objects.h
char obj_symbols[] = {
	ILLOBJ_SYM, AMULET_SYM, FOOD_SYM, WEAPON_SYM, TOOL_SYM,
	BALL_SYM, CHAIN_SYM, ROCK_SYM, ARMOR_SYM, POTION_SYM, SCROLL_SYM,
	WAND_SYM, RING_SYM, GEM_SYM, 0 };
 */
extern char obj_symbols[];
static char *names[] = {"Illegal objects", "Amulets", "Edibles", "Weapons",
			"Tools", "Iron balls", "Chains", "Rocks", "Armor",
			"Potions", "Scrolls", "Wands", "Rings", "Gems"};
char *
let_to_name(let)
char let;
{
	char *pos = index(obj_symbols, let);
	extern char *HI, *HE;
	/* buffer size is len(HI) + len(HE) + max len(names[]) + 1 */
	static char buf[4 + 4 + 15 + 1];

	if (pos == NULL)
		pos = obj_symbols;
	Sprintf(buf, "%s%s%s", HI, names[pos - obj_symbols], HE);
	return (buf);
}

/* After changing the value of flags.invlet_constant, make the current
 * inventory letters the fixed ones. -dgk
 */
void
fixinv()
{
	struct obj *otmp;
	extern int lastinvnr;
	char ilet = 'a';

	for(otmp = invent; otmp; otmp = otmp->nobj) {
		otmp->invlet = ilet;
		if (++ilet > 'z') ilet = 'A';
	}
	lastinvnr = 51;
}

/* construct the string  file.level 
 * This assumes there is space on the end of 'file' to append
 * a two digit number.  This is true for 'bones' and 'level'
 * but be careful if you use it for other things -dgk
 */
void
name_file(file, level)
char *file;
int level;
{
	char *tf;
	
	if (tf = rindex(file, '.'))
		Sprintf(tf+1, "%d", level);
}

long
freediskspace(path)
char *path;
{
	int drive = 0;
	union	REGS	inregs;
	union	REGS	outregs;

	inregs.h.ah = 0x36;	/* get free space -- DOS 2.0 page D-33 */
	if (path[0] && path[1] == ':')
		drive = (toupper(path[0]) - 'A') + 1;
	inregs.h.dl = drive;
	intdos(&inregs, &outregs);
	if (outregs.x.ax == 0xFFFF)
		return (-1);		/* bad drive number */
	return ((long) outregs.x.bx * outregs.x.cx * outregs.x.ax);
}

long
filesize(file)
char *file;
{
	struct stat buf;

	if (stat(file, &buf) == 0)
		return (buf.st_size);
	else
		return (-1L);
}

long
all_files_size(path)
char *path;
{
	register int level;
	long size, tmp;
	char buf[PATHLEN];

	strcpy(buf, path);
	for (level = 1, size = 0; level <= MAXLEVEL; level++) {
		name_file(buf, level);
		tmp = filesize(buf);
		if (tmp > 0)
			size += tmp;
	}
	return (size);
}

void
copybones(mode)
int mode;
{
	register int fd, level;
	char from[PATHLEN], to[PATHLEN];
	long sizes[MAXLEVEL + 1];
	extern boolean level_exists[];

	if (!ramdisk)
		return;
	strcpy(to, (mode == TOPERM) ? permbones : bones);
	strcpy(from, (mode == TOPERM) ? bones : permbones);

	for (level = 1; level <= MAXLEVEL; level++) {
		name_file(from, level);
		sizes[level] = filesize(from);	/* -1 if file doesn't exist */
		name_file(to, level);
		(void) unlink(to);	/* remove old bones files in 'to' */
	}
	for (level = 1; level <= MAXLEVEL; level++) {
		if (sizes[level] == -1L)
			continue;
		name_file(from, level);
		name_file(to, level);
		if (sizes[level] > freediskspace(to)) {
			fprintf(stderr,
				"Not enough room to copy file '%s' to '%s'.\n",
				from, to);
			goto cleanup;
		}
		/* We use savelev and getlev to move the bones files around,
		 * but savelev sets level_exists[] TRUE for this level, so
		 * we have to set it back FALSE again.
		 */
		if ((fd = open(from, 0)) < 0) {
			fprintf(stderr, "Warning: can't open '%s'.\n", from);
			continue;
		} else {
			sizes[level] = 0;	/* 'from' bones exists */
			getlev(fd, 0, level);
			(void) close(fd);
			if ((fd = creat(to, FMASK)) < 0) {
				fprintf(stderr,
					"Warning: can't create '%s'.\n", to);
				continue;
			} else {
				savelev(fd, level);
				(void) close(fd);
				level_exists[level] = FALSE;	/* see above */
			}
		}
	}
	/* If we are copying bones files back to permanent storage, unlink
	 * the bones files in the LEVELS directory.
	 */
	if (mode == TOPERM)
		for (level = 1; level <= MAXLEVEL; level++) {
			if (sizes[level] == -1)
				continue;
			name_file(from, level);
			(void) unlink(from);
		}
	return;

cleanup:
	/* Ran out of disk space!  Unlink the "to" files and issue an
	 * appropriate message.
	 */
	for (level = 1; level <= MAXLEVEL; level++)
		if (sizes[level] == 0) {
			name_file(to, level);
			(void) unlink(to);
		}
	fprintf(stderr, "There is not enough room in ");
	if (mode == TOPERM) {
		fprintf(stderr, "permanent storage for bones files!\n");
		fprintf(stderr,
			"Bones will be left in LEVELS directory '%s'!\n",
			levels[0] ? levels : ".");
			return;
	} else {
		fprintf(stderr,	"LEVELS directory '%s' to copy bones files!\n",
			levels[0] ? levels : ".");
		getreturn("to quit");
		settty("Be seeing you ...\n");
		exit(0);
	}
}

saveDiskPrompt(start)
int start;
{
	extern saveprompt;
	char buf[BUFSIZ];
	int i, newname = FALSE;

	if (saveprompt) {
		remember_topl();
		home();
		cl_end();
		printf("If save file is on a SAVE disk, put that disk in now.\n");
		cl_end();
		printf("Name of save file (default: '%s'%s) ? ", SAVEF,
			start ? "" : ", <Esc> aborts save");
		fflush(stdout);
		getlin(buf);
		if (!start && buf[0] == '\033') {
			home();
			cl_end();
			curs(1, 2);
			cl_end();
			return 0;
		}
		for (i = 0; buf[i]; i++)
			if (!isspace(buf[i])) {
				strncpy(SAVEF, buf, PATHLEN);
				break;
			}
	}
	return 1;
}

/* Prompt for the game disk, then check if you can access the record file.
 * If not, warn the player.
 */
void
gameDiskPrompt()
{
	FILE	*fp;
	extern saveprompt;

	if (saveprompt) {
		fputc('\n', stderr);
		getreturn("when the GAME disk is ready");
	}
	if ((fp = fopen(RECORD, "r")))	/* check for GAME disk */
		fclose(fp);
	else {
		fprintf(stderr,
			"\n\nWARNING: I can't find record file '%s'!\n",
			 RECORD);
		fprintf(stderr,
			"If the GAME disk is not in, put it in now.\n");
		getreturn("to continue");
	}
}

#define CONFIGFILE	"hack103.cnf"
void
read_config_file()
{
	char	config[FILENAME], tmp_ramdisk[PATHLEN], tmp_levels[PATHLEN];
	char	buf[BUFSZ], *bufp;
	FILE	*fp;
	extern	char plname[];
	extern	int saveprompt;

	tmp_ramdisk[0] = 0;
	tmp_levels[0] = 0;
	strcpy(config, hackdir);
	append_slash(config);
	strcat(config, CONFIGFILE);
	if (!(fp = fopen(config, "r"))) {
		fprintf(stderr, "Warning: no configuration file '%s'!\n",
			config);
		getreturn("to continue");
		return;
	}
	while (fgets(buf, BUFSZ, fp)) {
		if (*buf == '#')		/* comment first character */
			continue;

		/* remove any trailing whitespace
		 */
		bufp = index(buf, '\n');
		while (bufp > buf && isspace(*bufp))
			bufp--;
		if (bufp == buf)
			continue;		/* skip all-blank lines */
		else
			*(bufp + 1) = 0;	/* 0 terminate line */

		/* find the '=' separating option name from option value
		 */
		if (!(bufp = strchr(buf, '='))) {
			fprintf(stderr, "Bad option line: '%s'\n", buf);
			getreturn("to continue");
			continue;
		}
		
		/* move past whitespace between '=' and option value
		 */
		while (isspace(*++bufp))
			;

		/* Now go through the possible configurations
		 */
		if (!strncmp(buf, "RAMDISK", 3)) {
			strncpy(tmp_ramdisk, bufp, PATHLEN);

		} else if (!strncmp(buf, "LEVELS", 4)) {
			strncpy(tmp_levels, bufp, PATHLEN);

		} else if (!strncmp(buf, "OPTIONS", 4)) {
			parseoptions(bufp, TRUE);
			if (plname[0])		/* If a name was given */
				plnamesuffix();	/* set the character class */

		} else if (!strncmp(buf, "SAVE", 4)) {
			char *ptr;
			if (ptr = index(bufp, ';')) {
				*ptr = '\0';
				if (*(ptr+1) == 'n' || *(ptr+1) == 'N')
					saveprompt = FALSE;
			}
			(void) strncpy(SAVEF, bufp, PATHLEN);
			append_slash(SAVEF);

		} else if (!strncmp(buf, "GRAPHICS", 4)) {
			struct symbols s;

			if (sscanf(bufp, "%u%u%u%u%u%u%u%u%u", &s.vwall,
				    &s.hwall, &s.tlcorn, &s.trcorn, &s.blcorn,
				    &s.brcorn, &s.door, &s.room, &s.corr) == 9)
				symbol = s;
			else {
				fprintf(stderr,
					"GRAPHICS did not contain 9 values\n");
				getreturn("to continue");
			}

		} else if (!strncmp(buf, "DISPLAY", 4)) {
			/* There was a variable called DISPLAY which never
			 * work very well and was too confusing.  Leave this
			 * code in here for now for 'backward compatibility'.
			 */
			;

		} else {
			fprintf(stderr, "Bad option line: '%s'\n", buf);
			getreturn("to continue");
		}
	}
	fclose(fp);

	strcpy(permbones, tmp_levels);
	if (tmp_ramdisk[0]) {
		strcpy(levels, tmp_ramdisk);
		if (strcmpi(permbones, levels))		/* if not identical */
			ramdisk = TRUE;
	} else
		strcpy(levels, tmp_levels);
	strcpy(bones, levels);
}

void
set_lock_and_bones()
{
	if (!ramdisk) {
		strcpy(levels, permbones);
		strcpy(bones, permbones);
	}
	append_slash(bones);
	strcat(bones, BONES);
	append_slash(permbones);
	strcat(permbones, BONES);
	strcpy(lock, levels);
	append_slash(lock);
	strcat(lock, LEVELS);
}

void
append_slash(name)
char *name;
{
	char *ptr;

	if (!name[0])
		return;
	ptr = name + (strlen(name) - 1);
	if (*ptr != '\\' && *ptr != '/' && *ptr != ':') {
		*(ptr + 1) = '\\';
		*(ptr + 2) = 0;
	}
}


check_then_creat(file, pmode)
char *file;
int pmode;
{
	long freespace = freediskspace(file);
	extern boolean restoring;

	if (freespace < 0)
		return (-1);
	if (!restoring && freespace < 8000L) {
		pline("HACK is almost out of disk space for making levels!");
		pline("You should save the game now.  Save this game [y/n] ?");
		fflush(stdout);
		if (getchar() == 'y')
			dosave();
		return(-1);	/* In case he decides not to save don't let him
				 * change levels
				 */
	}
	return( creat(file, pmode));
}

void
getreturn(str)
char *str;
{
	int ch;

	fprintf(stderr, "Hit <RETURN> %s.", str);
	while ((ch = getchar()) != '\n')
		putch(ch);
}

#define SELECTDISK	0xE
void
chdrive(str)
char *str;
{
	char *ptr;
	union REGS inregs;
	char drive;

	if ((ptr = index(str, ':')) != NULL) {
		drive = toupper(*(ptr - 1));
		inregs.h.ah = SELECTDISK;
		inregs.h.dl = drive - 'A';
		intdos(&inregs, &inregs);
	}
}

#endif DGK

/* Do a chdir back to the original directory
 */
#undef exit
#if defined(MSDOS) && defined(LINT_ARGS)
void
#endif
msexit(code)
{
#ifdef CHDIR
	extern char orgdir[];
#endif CHDIR

#ifdef DGK
	fflush(stdout);
	if (ramdisk)
		copybones(TOPERM);
#endif DGK
#ifdef CHDIR
	chdir(orgdir);	/* do the chdir, but not with chdirx */
#	ifdef DGK
		chdrive(orgdir);
#	endif DGK
#endif CHDIR
	exit(code);
}

#endif MSDOS
                                                                   