/*
 * msdos.h
 *
 * This include file contains the function declarations for the functions
 * contained in msdos.c
 *
 */

/* function declarations for those who want strong type checking
 * on arguments to library function calls
 */

#ifdef LINT_ARGS		/* arg. checking enabled */

long	all_files_size(char *);
void	append_slash(char *);
char	BIOSgetch();
void	chdrive(char *);
int	check_then_creat(char *, int);
void	copybones(int);
int	dosh();
int	dotogglepickup();
void	fastat(xchar, xchar, char);
long	filesize(char *);
void	fixinv();
long	freediskspace(char *);
void	gameDiskPrompt();
char *	getlogin();
void	getreturn(char *);
int	getuid();
char *	let_to_name(char);
void	msexit(int);
void	name_file(char *, int);
void	read_config_file();
int	saveDiskPrompt(int);
void	set_lock_and_bones();
int	tgetch();

#else

extern long	all_files_size(), filesize(), freediskspace();
extern char	BIOSgetch(), *getlogin(), *let_to_name();
extern void	append_slash(), chdrive(), copybones(), fastat(), fixinv();
extern void	gameDiskPrompt(), getreturn(), msexit(), name_file();
extern void	read_config_file(), set_lock_and_bones();

#endif /* LINT_ARGS */
