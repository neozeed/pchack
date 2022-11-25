# pchack
PC HACK version 1.03

I managed to get this to compile with Microsoft C 6.00 and the linker 
from Visual C++ 1.52.  It seems as buggy as the original

============================================================================
/-\
|@|  You are being digested by a mysterious monster --More--
\-/
  
  
Welcome to ....


               PC HACK version 1.03 for MSDOS(tm) computers
               --------------------------------------------

                           by Don Kneller
                              2 Panoramic Way #204
                              Berkeley, CA 94704
                              October 31, 1985


============================================================================
To: All
Re: PC HACK 1.03

	Well, here it is.  I have not had as much time to play with this
	version as I did with 1.0.1, so I don't know if it is bug free or not.

	This is the full UNIX version 1.03 with a several enhancements.
		1) Easier configuration that uses less environment space.
		2) PC HACK can use graphics characters for the dungeon.
		3) Ramdisk support.  Makes the game much faster, especially
		   for floppy-only systems.
		4) A bunch of new options.  Pack sorting, confirmation before
		   hitting tame monsters, turning the bell off, whether you
		   pick up everything you step on, or just look at it. Cursor
		   key use on IBM BIOS compatible computers.
		5) Some protection against disk full problems.
		6) Another way to survive cockatrice attacks.

	The documentation HACK103.DOC is formatted for 66 line paper in
	case you want to print it out.  The simplest way to print the
	documentation is:

		copy hack103.doc prn:

	The problem with ^P causing 'echo to printer' being turned on has been
	solved, thanks to help from Mark Zbikowski (markz@microsoft.UUCP).  The
	solution was the use an MSDOS function call for IOCTLS to change the
	terminal into 'raw' mode. An added bonus is noticeably faster display
	speed.
		Also, the niggling bug that caused the first line of the help
	files to appear out of position was traced to a bug in ANSI.SYS which
	results in improper tab expansion.  This has been fixed by expanding
	the tabs 'by hand' in the code.


Configuration Overview
----------------------

	Basically, people with HardDisks will want to create the
	directory: \GAMES\HACK for the PC HACK support files (of
	course, you can choose your own directory names, but for this
	short discussion, assume these names).  Copy all files except
	HACK103.EXE into \GAMES\HACK.  Copy HACK103.EXE into a
	directory accessible with the PATH environment variable
	(you might use \GAMES).  Create an environment variable called
	HACKDIR with value \GAMES\HACK (use the command:
		set HACKDIR=\GAMES\HACK
	probably in your AUTOEXEC.BAT file).  Edit the HACK103.CNF file
	to put in your player name and other options.  At the MSDOS prompt
	type:
		C> hack103
	and you should be playing.
	
	People with floppy only systems will want to keep all PC HACK files
	on one floppy (called the "GAME" disk), and have 2 extra formatted
	floppies, one called "LEVELS" and one called "SAVE".  The SAVE floppy
	will store saved games and will be swapped with the GAME disk in drive
	"A" at the appropriate times.  The LEVELS floppy will be in "B" drive.  If you don't have any saved games
	If you don't have any saved games yet, or you don't want to restart
	from a saved game, you can leave the GAME disk in drive "A" even when
	PC HACK asks you to insert the SAVE disk.  If you have more than 2
	floppy drives, all 3 diskettes can be used at the same time.
	Edit the HACK103.CNF file and put comment characters ('#') in front
	of all lines for the "possible hard disk configuration" and remove
	the comment characters from the lines of the "possible two floppy
	configuration".  At the MSDOS prompt type:
		A> hack103
	and you should be playing.

	The documentation HACK103.DOC has details for configuration of
	PC HACK for your system.


============================================================================
To: All beginner HACKERS
Re: An overview and some hints

	There is a special section in HACK103.DOC called
		"Hints for beginner HACKERS"
	This is for people who have never played HACK or ROGUE
	before and want a description of what they can do in HACK.

============================================================================


		Don Kneller.
		2 Panoramic Way #204
		Berkeley, CA 94704

		UUCP:	...ucbvax!ucsfcgl!kneller
		ARPA:	ucsfcgl!kneller@berkeley.arpa
