/* Copyright (c) Stichting Mathematisch Centrum, Amsterdam, 1985. */
/* objects.h - version 1.0.3 */

/* objects have letter " % ) ( 0 _ ` [ ! ? / = * */
#include "config.h"
#include "objclass.h"
#define	NULL	(char *)0

#ifdef MSDOS
/* Separate all the names of all objects into a separate static location
 * and make the objects[] array point into this location.  This is to
 * make it possible to replace any pointers that objects[] uses with
 * indices into this array for storing.
 */
struct {
	char	*name, *descr;
} objname[] = {
	NULL, NULL,		/* A place holder */

/* illegal object */
#define STRANGE_OBJECTn		(char *) 1
	"strange object",	NULL,

/* amulet */
#define AMULET_OF_YENDORn	(char *) 2
	"amulet of Yendor",	NULL,

/* foods */
#define FOODBASE		3
#define Food(i)			(char *) (FOODBASE+i)
	"food ration",		NULL,
	"tripe ration",		NULL,
	"pancake",		NULL,
	"dead lizard",		NULL,
	"fortune cookie",	NULL,
	"carrot",		NULL,
	"tin",			NULL,
	"orange",		NULL,
	"apple",		NULL,
	"pear",			NULL,
	"melon",		NULL,
	"banana",		NULL,
	"candy bar",		NULL,
	"egg",			NULL,
	"clove of garlic",	NULL,
	"lump of royal jelly",	NULL,
		
	"dead human",		NULL,
	"dead giant ant",	NULL,
	"dead giant bat",	NULL,
	"dead centaur",		NULL,
	"dead dragon",		NULL,
	"dead floating eye",	NULL,
	"dead freezing sphere",	NULL,
	"dead gnome",		NULL,
	"dead hobgoblin",	NULL,
	"dead stalker",		NULL,
	"dead jackal",		NULL,
	"dead kobold",		NULL,
	"dead leprechaun",	NULL,
	"dead mimic",		NULL,
	"dead nymph",		NULL,
	"dead orc",		NULL,
	"dead purple worm",	NULL,
	"dead quasit",		NULL,
	"dead rust monster",	NULL,
	"dead snake",		NULL,
	"dead troll",		NULL,
	"dead umber hulk",	NULL,
	"dead vampire",		NULL,
	"dead wraith",		NULL,
	"dead xorn",		NULL,
	"dead yeti",		NULL,
	"dead zombie",		NULL,
	"dead acid blob",	NULL,
	"dead giant beetle",	NULL,
	"dead cockatrice",	NULL,
	"dead dog",		NULL,
	"dead ettin",		NULL,
	"dead fog cloud",	NULL,
	"dead gelatinous cube",	NULL,
	"dead homunculus",	NULL,
	"dead imp",		NULL,
	"dead jaguar",		NULL,
	"dead killer bee",	NULL,
	"dead leocrotta",	NULL,
	"dead minotaur",	NULL,
	"dead nurse",		NULL,
	"dead owlbear",		NULL,
	"dead piercer",		NULL,
	"dead quivering blob",	NULL,
	"dead giant rat",	NULL,
	"dead giant scorpion",	NULL,
	"dead tengu",		NULL,
	"dead unicorn",		NULL,
	"dead violet fungi",	NULL,
	"dead long worm",	NULL,
	"dead xan",		NULL,
	"dead yellow light",	NULL,
	"dead zruty",		NULL,
#define FOODCOUNT		69

/* weapons */
#define WEAPONBASE		FOODBASE+FOODCOUNT
#define	Weapon(i)		(char *) (WEAPONBASE+i)
	"arrow",		NULL,
	"sling bullet",		NULL,
	"crossbow bolt",	NULL,
	"dart",			NULL,
	"rock",			NULL,
	"boomerang",		NULL,
	"mace",			NULL,
	"axe",			NULL,
	"flail",		NULL,
	"long sword",		NULL,
	"two handed sword",	NULL,
	"dagger",		NULL,
	"worm tooth",		NULL,
	"crysknife",		NULL,
	"spear",		NULL,
	"bow",			NULL,
	"sling",		NULL,
	"crossbow",		NULL,
#define WEAPONCOUNT	18

/* Miscellaneous other objects */
#define OTHERBASE		WEAPONBASE+WEAPONCOUNT
#define Other(i)		(char *) (OTHERBASE+i)
	"whistle",		"whistle",
	"magic whistle",	"whistle",
	"expensive camera",	NULL,
	"ice box",		"large box",
	"pick-axe",		NULL,
	"can opener",		NULL,
	"heavy iron ball",	NULL,
	"iron chain",		NULL,
	"enormous rock",	NULL,
#define OTHERCOUNT	9

/* armor */
#define ARMORBASE		OTHERBASE+OTHERCOUNT
#define	Armor(i)		(char *) (ARMORBASE+i)
	"helmet",		NULL,
	"plate mail",		NULL,
	"splint mail",		NULL,
	"banded mail",		NULL,
	"chain mail",		NULL,
	"scale mail",		NULL,
	"ring mail",		NULL,
	"studded leather armor",NULL,
	"leather armor",	NULL,
	"elven cloak",		NULL,
	"shield",		NULL,
	"pair of gloves",	NULL,
#define ARMORCOUNT		12

/* potions */
#define POTIONBASE		ARMORBASE+ARMORCOUNT
#define	Potion(i)		(char *) (POTIONBASE+i)
	"restore strength",	"orange",
	"booze",		"bubbly",
	"invisibility",		"glowing",
	"fruit juice",		"smoky",
	"healing",		"pink",
	"paralysis",		"puce",
	"monster detection",	"purple",
	"object detection",	"yellow",
	"sickness",		"white",
	"confusion",		"swirly",
	"gain strength",	"purple-red",
	"speed",		"ruby",
	"blindness",		"dark green",
	"gain level",		"emerald",
	"extra healing",	"sky blue",
	"levitation",		"brown",
	NULL,			"brilliant blue",
	NULL,			"clear",
	NULL,			"magenta",
	NULL,			"ebony",
#define POTIONCOUNT		20

/* scrolls */
#define SCROLLBASE		POTIONBASE+POTIONCOUNT
#define	Scroll(i)		(char *) (SCROLLBASE+i)
	"mail",			"KIRJE",
	"enchant armor",	"ZELGO MER",
	"destroy armor",	"JUYED AWK YACC",
	"confuse monster",	"NR 9",
	"scare monster",	"XIXAXA XOXAXA XUXAXA",
	"blank paper",		"READ ME",
	"remove curse",		"PRATYAVAYAH",
	"enchant weapon",	"DAIYEN FOOELS",
	"damage weapon",	"HACKEM MUCHE",
	"create monster",	"LEP GEX VEN ZEA",
	"taming",		"PRIRUTSENIE",
	"genocide",		"ELBIB YLOH",
	"light",		"VERR YED HORRE",
	"teleportation",	"VENZAR BORGAVVE",
	"gold detection",	"THARR",
	"food detection",	"YUM YUM",
	"identify",		"KERNOD WEL",
	"magic mapping",	"ELAM EBOW",
	"amnesia",		"DUAM XNAHT",
	"fire",			"ANDOVA BEGARIN",
	"punishment",		"VE FORBRYDERNE",
	NULL,			"VELOX NEB",
	NULL,			"FOOBIE BLETCH",
	NULL,			"TEMOV",
	NULL,			"GARVEN DEH",
#define SCROLLCOUNT		25

/* wands */
#define	WANDBASE		SCROLLBASE+SCROLLCOUNT
#define	Wand(i) 		(char *) (WANDBASE+i)
	"light",		"iridium",
	"secret door detection","tin",
	"create monster",	"platinum",
	"wishing",		"glass",
	"striking",		"zinc",
	"slow monster",		"balsa",
	"speed monster",	"copper",
	"undead turning",	"silver",
	"polymorph",		"brass",
	"cancellation",		"maple",
	"teleportation",	"pine",
	"make invisible",	"marble",
	"digging",		"iron",
	"magic missile",	"aluminium",
	"fire",			"steel",
	"sleep",		"curved",
	"cold",			"short",
	"death",		"long",
	NULL,			"oak",
	NULL,			"ebony",
	NULL,			"runed",
#define WANDCOUNT	21

/* rings */
#define RINGBASE		WANDBASE+WANDCOUNT
#define	Ring(i)			(char *) (RINGBASE+i)
	"adornment",		"engagement",
	"teleportation",	"wooden",
	"regeneration",		"black onyx",
	"searching",		"topaz",
	"see invisible",	"pearl",
	"stealth",		"sapphire",
	"levitation",		"moonstone",
	"poison resistance",	"agate",
	"aggravate monster",	"tiger eye",
	"hunger",		"shining",
	"fire resistance",	"gold",
	"cold resistance",	"copper",
	"protection from shape changers", "diamond",
	"conflict",		"jade",
	"gain strength",	"ruby",
	"increase damage",	"silver",
	"protection",		"granite",
	"warning",		"wire",
	"teleport control",	"iron",
	NULL,			"ivory",
	NULL,			"blackened",
#define RINGCOUNT		21

/* gems */
#define GEMBASE			RINGBASE+RINGCOUNT
#define	Gem(i)			(char *) (GEMBASE+i)
	"diamond",		"blue",
	"ruby",			"red",
	"sapphire",		"blue",
	"emerald",		"green",
	"turquoise",		"green",
	"aquamarine",		"blue",
	"tourmaline",		"green",
	"topaz",		"yellow",
	"opal",			"yellow",
	"garnet",		"dark",
	"amethyst",		"violet",
	"agate",		"green",
	"onyx",			"white",
	"jasper",		"yellowish brown",
	"jade",			 "green",
	"worthless piece of blue glass", "blue",
	"worthless piece of red glass", "red",
	"worthless piece of yellow glass", "yellow",
	"worthless piece of green glass", "green",
#define GEMCOUNT		19
};

struct objclass objects[] = {

	{STRANGE_OBJECTn, NULL, NULL, 1, 0, ILLOBJ_SYM, 0, 0, 0, 0, 0, 0 },
	{AMULET_OF_YENDORn, NULL, NULL, 1, 0, AMULET_SYM, 100, 0, 2, 0, 0, 0 },

#define	FOOD(number,prob,delay,weight,nutrition) {Food(number),\
	NULL, NULL, 1, 1, FOOD_SYM, prob, delay, weight, 0, 0, nutrition }

/* dog eats foods 0-4 but prefers 1 above 0,2,3,4 */
/* food 4 can be read */
/* food 5 improves your vision */
/* food 6 makes you stronger (like Popeye) */
/* foods CORPSE up to CORPSE+52 are cadavers */

	FOOD(0,	50, 5, 4, 800),
	FOOD(1,	20, 1, 2, 200),
	FOOD(2,	3, 1, 1, 200),
	FOOD(3,	3, 0, 1, 40),
	FOOD(4,	7, 0, 1, 40),
	FOOD(5,	2, 0, 1, 50),
	FOOD(6,	7, 0, 1, 0),
	FOOD(7,	1, 0, 1, 80),
	FOOD(8,	1, 0, 1, 50),
	FOOD(9,	1, 0, 1, 50),
	FOOD(10, 1, 0, 1, 100),
	FOOD(11, 1, 0, 1, 80),
	FOOD(12, 1, 0, 1, 100),
	FOOD(13, 1, 0, 1, 80),
	FOOD(14, 1, 0, 1, 40),
	FOOD(15, 0, 0, 1, 200),

	FOOD(16, 0, 4, 40, 400),
	FOOD(17, 0, 1, 3, 30),
	FOOD(18, 0, 1, 3, 30),
	FOOD(19, 0, 5, 50, 500),
	FOOD(20, 0, 15, 150, 1500),
	FOOD(21, 0, 1, 1, 10),
	FOOD(22, 0, 1, 1, 10),
	FOOD(23, 0, 1, 10, 100),
	FOOD(24, 0, 2, 20, 200),
	FOOD(25, 0, 4, 40, 400),
	FOOD(26, 0, 1, 10, 100),
	FOOD(27, 0, 1, 10, 100),
	FOOD(28, 0, 4, 40, 400),
	FOOD(29, 0, 4, 40, 400),
	FOOD(30, 0, 4, 40, 400),
	FOOD(31, 0, 2, 20, 200),
	FOOD(32, 0, 7, 70, 700),
	FOOD(33, 0, 2, 20, 200),
	FOOD(34, 0, 5, 50, 500),
	FOOD(35, 0, 1, 10, 100),
	FOOD(36, 0, 4, 40, 400),
	FOOD(37, 0, 5, 50, 500),
	FOOD(38, 0, 4, 40, 400),
	FOOD(39, 0, 1, 1, 10),
	FOOD(40, 0, 7, 70, 700),
	FOOD(41, 0, 7, 70, 700),
	FOOD(42, 0, 1, 3, 30),
	FOOD(43, 0, 1, 3, 30),
	FOOD(44, 0, 1, 1, 10),
	FOOD(45, 0, 1, 3, 30),
	FOOD(46, 0, 2, 20, 200),
	FOOD(47, 0, 1, 3, 30),
	FOOD(48, 0, 1, 1, 10),
	FOOD(49, 0, 1, 10, 100),
	FOOD(50, 0, 2, 20, 200),
	FOOD(51, 0, 1, 1, 10),
	FOOD(52, 0, 3, 30, 300),
	FOOD(53, 0, 1, 1, 10),
	FOOD(54, 0, 5, 50, 500),
	FOOD(55, 0, 7, 70, 700),
	FOOD(56, 0, 4, 40, 400),
	FOOD(57, 0, 7, 70, 700),
	FOOD(58, 0, 2, 20, 200),
	FOOD(59, 0, 1, 10, 100),
	FOOD(60, 0, 1, 3, 30),
	FOOD(61, 0, 1, 10, 100),
	FOOD(62, 0, 3, 30, 300),
	FOOD(63, 0, 3, 30, 300),
	FOOD(64, 0, 1, 10, 100),
	FOOD(65, 0, 5, 50, 500),
/* %% wt of long worm should be proportional to its length */
	FOOD(66, 0, 3, 30, 300),
	FOOD(67, 0, 1, 1, 10),
	FOOD(68, 0, 6, 60, 600),

/* weapons ... - ROCK come several at a time */
/* weapons ... - (ROCK-1) are shot using idem+(BOW-ARROW) */
/* weapons AXE, SWORD, THSWORD are good for worm-cutting */
/* weapons (PICK-)AXE, DAGGER, CRYSKNIFE are good for tin-opening */
#define WEAPON(number,prob,wt,ldam,sdam) { Weapon(number), NULL, NULL, 1,\
		0 /*%%*/, WEAPON_SYM, prob, 0, wt, ldam, sdam, 0 }

	WEAPON(0, 7, 0, 6, 6),
	WEAPON(1, 7, 0, 4, 6),
	WEAPON(2, 7, 0, 4, 6),
 	WEAPON(3, 7, 0, 3, 2),
	WEAPON(4, 6, 1, 3, 3),
	WEAPON(5, 2, 3, 9, 9),
	WEAPON(6, 9, 3, 6, 7),
	WEAPON(7, 6, 3, 6, 4),
	WEAPON(8, 6, 3, 6, 5),
	WEAPON(9, 8, 3, 8, 12),
	WEAPON(10, 6, 4, 12, 6),
	WEAPON(11, 6, 3, 4, 3),
	WEAPON(12, 0, 4, 2, 2),
	WEAPON(13, 0, 3, 10, 10),
	WEAPON(14, 6, 3, 6, 8),
	WEAPON(15, 6, 3, 4, 6),
	WEAPON(16, 5, 3, 6, 6),
	WEAPON(17, 6, 3, 4, 6),

	{Other(0), Other(0),	NULL, 0, 0, TOOL_SYM, 90, 0, 2, 0, 0, 0 },
	{Other(1), Other(1),	NULL, 0, 0, TOOL_SYM, 10, 0, 2, 0, 0, 0 },
	{Other(2), NULL,	NULL, 1, 1, TOOL_SYM, 0, 0, 3, 0, 0, 0 },
	{Other(3), Other(3),	NULL, 0, 0, TOOL_SYM, 0, 0, 40, 0, 0, 0 },
	{Other(4), NULL, 	NULL, 1, 1, TOOL_SYM, 0, 0, 5, 6, 3, 0 },
	{Other(5), NULL,	NULL, 1, 1, TOOL_SYM, 0, 0, 1, 0, 0, 0 },
	{Other(6), NULL,	NULL, 1, 0, BALL_SYM, 100, 0, 20, 0, 0, 0 },
	{Other(7), NULL,	NULL, 1, 0, CHAIN_SYM, 100, 0, 20, 0, 0, 0 },
	{Other(8), NULL,	NULL, 1, 0,
			ROCK_SYM, 100, 0, 200 /* > MAX_CARR_CAP */, 0, 0, 0 },

#define ARMOR(number,prob,delay,ac,can)	{ Armor(number), NULL, NULL, 1, 0,\
		ARMOR_SYM, prob, delay, 8, ac, can, 0 }
	ARMOR(0, 3, 1, 9, 0),
	ARMOR(1, 5, 5, 3, 2),
	ARMOR(2, 8, 5, 4, 1),
	ARMOR(3, 10, 5, 4, 0),
	ARMOR(4, 10, 5, 5, 1),
 	ARMOR(5, 10, 5, 6, 0),
	ARMOR(6, 15, 5, 7, 0),
	/* the armors below do not rust */
	ARMOR(7, 13, 3, 7, 1),
	ARMOR(8, 17, 3, 8, 0),
	ARMOR(9,  5, 0, 9, 3),
	ARMOR(10, 3, 0, 9, 0),
	ARMOR(11, 1, 1, 9, 0),

#define POTION(number)	{ Potion(number), Potion(number), NULL,\
		0, 1, POTION_SYM, 0, 0, 2, 0, 0, 0 }

	POTION(0),
	POTION(1),
	POTION(2),
	POTION(3),
	POTION(4),
	POTION(5),
	POTION(6),
	POTION(7),
	POTION(8),
	POTION(9),
	POTION(10),
	POTION(11),
	POTION(12),
	POTION(13),
	POTION(14),
	POTION(15),
	POTION(16),
	POTION(17),
	POTION(18),
	POTION(19),

#define SCROLL(number,prob) { Scroll(number), Scroll(number), NULL, 0,\
		1, SCROLL_SYM, prob, 0, 3, 0, 0, 0 }
	SCROLL(0,	0),
	SCROLL(1,	6),
	SCROLL(2,	5),
	SCROLL(3,	5),
	SCROLL(4,	4),
	SCROLL(5,	3),
	SCROLL(6,	6),
	SCROLL(7,	6),
	SCROLL(8,	5),
	SCROLL(9,	5),
	SCROLL(10,	1),
	SCROLL(11,	2),
	SCROLL(12,	10),
	SCROLL(13,	5),
	SCROLL(14,	4),
	SCROLL(15,	1),
	SCROLL(16,	18),
	SCROLL(17,	5),
	SCROLL(18,	3),
	SCROLL(19,	5),
	SCROLL(20,	1),
	SCROLL(21,	0),
	SCROLL(22,	0),
	SCROLL(23,	0),
	SCROLL(24,	0),

#define	WAND(number,prob,flags)	{ Wand(number), Wand(number), NULL,\
		0, 0, WAND_SYM, prob, 0, 3, flags, 0, 0 }

	WAND(0,		10,	NODIR),
	WAND(1,		5,	NODIR),
	WAND(2,		5,	NODIR),
	WAND(3,		1,	NODIR),
	WAND(4,		9,	IMMEDIATE),
	WAND(5,		5,	IMMEDIATE),
	WAND(6,		5,	IMMEDIATE),
	WAND(7,		5,	IMMEDIATE),
	WAND(8,		5,	IMMEDIATE),
	WAND(9,		5,	IMMEDIATE),
	WAND(10,	5,	IMMEDIATE),
	WAND(11,	9,	IMMEDIATE),
	WAND(12,	5,	RAY),
	WAND(13,	10,	RAY),
	WAND(14,	5,	RAY),
	WAND(15,	5,	RAY),
	WAND(16,	5,	RAY),
	WAND(17,	1,	RAY),
	WAND(18,	0,	0),
	WAND(19,	0,	0),
	WAND(20,	0,	0),

#define	RING(number,spec)	{ Ring(number), Ring(number), NULL,\
		0, 0, RING_SYM, 0, 0, 1, spec, 0, 0 }

	RING(0,		0),
	RING(1,		0),
	RING(2,		0),
	RING(3,		0),
	RING(4,		0),
	RING(5,		0),
	RING(6,		0),
	RING(7,		0),
	RING(8,		0),
	RING(9,		0),
	RING(10,	0),
	RING(11,	0),
	RING(12,	0),
	RING(13,	0),
	RING(14,	SPEC),
	RING(15,	SPEC),
	RING(16,	SPEC),
	RING(17,	0),
	RING(18,	0),
	RING(19,	0),
	RING(20,	0),

/* gems ************************************************************/
#define	GEM(number,prob,gval)	{ Gem(number), Gem(number), NULL, 0,\
				1, GEM_SYM, prob, 0, 1, 0, 0, gval }
	GEM(0,	1,	4000),
	GEM(1,	1,	3500),
	GEM(2,	1,	3000),
	GEM(3,	1,	2500),
	GEM(4,	1,	2000),
	GEM(5,	1,	1500),
	GEM(6,	1,	1000),
	GEM(7,	1,	900),
	GEM(8,	1,	800),
	GEM(9,	1,	700),
	GEM(10,	2,	650),
	GEM(11,	2,	600),
	GEM(12,	2,	550),
	GEM(13,	2,	500),
	GEM(14,	2,	450),
	GEM(15,	20,	0),
	GEM(16,	20,	0),
	GEM(17,	20,	0),
	GEM(18,	20,	0),
	{ NULL, NULL, NULL, 0, 0, ILLOBJ_SYM, 0, 0, 0, 0, 0, 0 }
};

#else

struct objclass objects[] = {

	{ "strange object", NULL, NULL, 1, 0,
		ILLOBJ_SYM, 0, 0, 0, 0, 0, 0 },
	{ "amulet of Yendor", NULL, NULL, 1, 0,
		AMULET_SYM, 100, 0, 2, 0, 0, 0 },

#define	FOOD(name,prob,delay,weight,nutrition)	{ name, NULL, NULL, 1, 1,\
		FOOD_SYM, prob, delay, weight, 0, 0, nutrition }

/* dog eats foods 0-4 but prefers 1 above 0,2,3,4 */
/* food 4 can be read */
/* food 5 improves your vision */
/* food 6 makes you stronger (like Popeye) */
/* foods CORPSE up to CORPSE+52 are cadavers */

	FOOD("food ration", 	50, 5, 4, 800),
	FOOD("tripe ration",	20, 1, 2, 200),
	FOOD("pancake",		3, 1, 1, 200),
	FOOD("dead lizard",	3, 0, 1, 40),
	FOOD("fortune cookie",	7, 0, 1, 40),
	FOOD("carrot",		2, 0, 1, 50),
	FOOD("tin",		7, 0, 1, 0),
	FOOD("orange",		1, 0, 1, 80),
	FOOD("apple",		1, 0, 1, 50),
	FOOD("pear",		1, 0, 1, 50),
	FOOD("melon",		1, 0, 1, 100),
	FOOD("banana",		1, 0, 1, 80),
	FOOD("candy bar",	1, 0, 1, 100),
	FOOD("egg",		1, 0, 1, 80),
	FOOD("clove of garlic",	1, 0, 1, 40),
	FOOD("lump of royal jelly", 0, 0, 1, 200),

	FOOD("dead human",	0, 4, 40, 400),
	FOOD("dead giant ant",	0, 1, 3, 30),
	FOOD("dead giant bat",	0, 1, 3, 30),
	FOOD("dead centaur",	0, 5, 50, 500),
	FOOD("dead dragon",	0, 15, 150, 1500),
	FOOD("dead floating eye",	0, 1, 1, 10),
	FOOD("dead freezing sphere",	0, 1, 1, 10),
	FOOD("dead gnome",	0, 1, 10, 100),
	FOOD("dead hobgoblin",	0, 2, 20, 200),
	FOOD("dead stalker",	0, 4, 40, 400),
	FOOD("dead jackal",	0, 1, 10, 100),
	FOOD("dead kobold",	0, 1, 10, 100),
	FOOD("dead leprechaun",	0, 4, 40, 400),
	FOOD("dead mimic",	0, 4, 40, 400),
	FOOD("dead nymph",	0, 4, 40, 400),
	FOOD("dead orc",	0, 2, 20, 200),
	FOOD("dead purple worm",	0, 7, 70, 700),
	FOOD("dead quasit",	0, 2, 20, 200),
	FOOD("dead rust monster",	0, 5, 50, 500),
	FOOD("dead snake",	0, 1, 10, 100),
	FOOD("dead troll",	0, 4, 40, 400),
	FOOD("dead umber hulk",	0, 5, 50, 500),
	FOOD("dead vampire",	0, 4, 40, 400),
	FOOD("dead wraith",	0, 1, 1, 10),
	FOOD("dead xorn",	0, 7, 70, 700),
	FOOD("dead yeti",	0, 7, 70, 700),
	FOOD("dead zombie",	0, 1, 3, 30),
	FOOD("dead acid blob",	0, 1, 3, 30),
	FOOD("dead giant beetle",	0, 1, 1, 10),
	FOOD("dead cockatrice",	0, 1, 3, 30),
	FOOD("dead dog",	0, 2, 20, 200),
	FOOD("dead ettin",	0, 1, 3, 30),
	FOOD("dead fog cloud",	0, 1, 1, 10),
	FOOD("dead gelatinous cube",	0, 1, 10, 100),
	FOOD("dead homunculus",	0, 2, 20, 200),
	FOOD("dead imp",	0, 1, 1, 10),
	FOOD("dead jaguar",	0, 3, 30, 300),
	FOOD("dead killer bee",	0, 1, 1, 10),
	FOOD("dead leocrotta",	0, 5, 50, 500),
	FOOD("dead minotaur",	0, 7, 70, 700),
	FOOD("dead nurse",	0, 4, 40, 400),
	FOOD("dead owlbear",	0, 7, 70, 700),
	FOOD("dead piercer",	0, 2, 20, 200),
	FOOD("dead quivering blob",	0, 1, 10, 100),
	FOOD("dead giant rat",	0, 1, 3, 30),
	FOOD("dead giant scorpion",	0, 1, 10, 100),
	FOOD("dead tengu",	0, 3, 30, 300),
	FOOD("dead unicorn",	0, 3, 30, 300),
	FOOD("dead violet fungi",	0, 1, 10, 100),
	FOOD("dead long worm",	0, 5, 50, 500),
/* %% wt of long worm should be proportional to its length */
	FOOD("dead xan",	0, 3, 30, 300),
	FOOD("dead yellow light",	0, 1, 1, 10),
	FOOD("dead zruty",	0, 6, 60, 600),

/* weapons ... - ROCK come several at a time */
/* weapons ... - (ROCK-1) are shot using idem+(BOW-ARROW) */
/* weapons AXE, SWORD, THSWORD are good for worm-cutting */
/* weapons (PICK-)AXE, DAGGER, CRYSKNIFE are good for tin-opening */
#define WEAPON(name,prob,wt,ldam,sdam)	{ name, NULL, NULL, 1, 0 /*%%*/,\
		WEAPON_SYM, prob, 0, wt, ldam, sdam, 0 }

	WEAPON("arrow",		7, 0, 6, 6),
	WEAPON("sling bullet",	7, 0, 4, 6),
	WEAPON("crossbow bolt",	7, 0, 4, 6),
	WEAPON("dart",		7, 0, 3, 2),
	WEAPON("rock",		6, 1, 3, 3),
	WEAPON("boomerang",	2, 3, 9, 9),
	WEAPON("mace",		9, 3, 6, 7),
	WEAPON("axe",		6, 3, 6, 4),
	WEAPON("flail",		6, 3, 6, 5),
	WEAPON("long sword",	8, 3, 8, 12),
	WEAPON("two handed sword",	6, 4, 12, 6),
	WEAPON("dagger",	6, 3, 4, 3),
	WEAPON("worm tooth",	0, 4, 2, 2),
	WEAPON("crysknife",	0, 3, 10, 10),
	WEAPON("spear",		6, 3, 6, 8),
	WEAPON("bow",		6, 3, 4, 6),
	WEAPON("sling",		5, 3, 6, 6),
	WEAPON("crossbow",	6, 3, 4, 6),

	{ "whistle", "whistle", NULL, 0, 0,
		TOOL_SYM, 90, 0, 2, 0, 0, 0 },
	{ "magic whistle", "whistle", NULL, 0, 0,
		TOOL_SYM, 10, 0, 2, 0, 0, 0 },
	{ "expensive camera", NULL, NULL, 1, 1,
		TOOL_SYM, 0, 0, 3, 0, 0, 0 },
	{ "ice box", "large box", NULL, 0, 0,
		TOOL_SYM, 0, 0, 40, 0, 0, 0 },
	{ "pick-axe", NULL, NULL, 1, 1,
		TOOL_SYM, 0, 0, 5, 6, 3, 0 },
	{ "can opener", NULL, NULL, 1, 1,
		TOOL_SYM, 0, 0, 1, 0, 0, 0 },
	{ "heavy iron ball", NULL, NULL, 1, 0,
		BALL_SYM, 100, 0, 20, 0, 0, 0 },
	{ "iron chain", NULL, NULL, 1, 0,
		CHAIN_SYM, 100, 0, 20, 0, 0, 0 },
	{ "enormous rock", NULL, NULL, 1, 0,
		ROCK_SYM, 100, 0, 200 /* > MAX_CARR_CAP */, 0, 0, 0 },

#define ARMOR(name,prob,delay,ac,can)	{ name, NULL, NULL, 1, 0,\
		ARMOR_SYM, prob, delay, 8, ac, can, 0 }
	ARMOR("helmet",		 3, 1, 9, 0),
	ARMOR("plate mail",		 5, 5, 3, 2),
	ARMOR("splint mail",	 8, 5, 4, 1),
	ARMOR("banded mail",	10, 5, 4, 0),
	ARMOR("chain mail",		10, 5, 5, 1),
	ARMOR("scale mail",		10, 5, 6, 0),
	ARMOR("ring mail",		15, 5, 7, 0),
	/* the armors below do not rust */
	ARMOR("studded leather armor", 13, 3, 7, 1),
	ARMOR("leather armor",	17, 3, 8, 0),
	ARMOR("elven cloak",	 5, 0, 9, 3),
	ARMOR("shield",		 3, 0, 9, 0),
	ARMOR("pair of gloves",	 1, 1, 9, 0),

#define POTION(name,color)	{ name, color, NULL, 0, 1,\
		POTION_SYM, 0, 0, 2, 0, 0, 0 }

	POTION("restore strength",	"orange"),
	POTION("booze",		"bubbly"),
	POTION("invisibility",	"glowing"),
	POTION("fruit juice",	"smoky"),
	POTION("healing",	"pink"),
	POTION("paralysis",	"puce"),
	POTION("monster detection",	"purple"),
	POTION("object detection",	"yellow"),
	POTION("sickness",	"white"),
	POTION("confusion",	"swirly"),
	POTION("gain strength",	"purple-red"),
	POTION("speed",		"ruby"),
	POTION("blindness",	"dark green"),
	POTION("gain level",	"emerald"),
	POTION("extra healing",	"sky blue"),
	POTION("levitation",	"brown"),
	POTION(NULL,	"brilliant blue"),
	POTION(NULL,	"clear"),
	POTION(NULL,	"magenta"),
	POTION(NULL,	"ebony"),

#define SCROLL(name,text,prob) { name, text, NULL, 0, 1,\
		SCROLL_SYM, prob, 0, 3, 0, 0, 0 }
	SCROLL("mail",	"KIRJE", 0),
	SCROLL("enchant armor", "ZELGO MER", 6),
	SCROLL("destroy armor", "JUYED AWK YACC", 5),
	SCROLL("confuse monster", "NR 9", 5),
	SCROLL("scare monster", "XIXAXA XOXAXA XUXAXA", 4),
	SCROLL("blank paper", "READ ME", 3),
	SCROLL("remove curse", "PRATYAVAYAH", 6),
	SCROLL("enchant weapon", "DAIYEN FOOELS", 6),
	SCROLL("damage weapon", "HACKEM MUCHE", 5),
	SCROLL("create monster", "LEP GEX VEN ZEA", 5),
	SCROLL("taming", "PRIRUTSENIE", 1),
	SCROLL("genocide", "ELBIB YLOH",2),
	SCROLL("light", "VERR YED HORRE", 10),
	SCROLL("teleportation", "VENZAR BORGAVVE", 5),
	SCROLL("gold detection", "THARR", 4),
	SCROLL("food detection", "YUM YUM", 1),
	SCROLL("identify", "KERNOD WEL", 18),
	SCROLL("magic mapping", "ELAM EBOW", 5),
	SCROLL("amnesia", "DUAM XNAHT", 3),
	SCROLL("fire", "ANDOVA BEGARIN", 5),
	SCROLL("punishment", "VE FORBRYDERNE", 1),
	SCROLL(NULL, "VELOX NEB", 0),
	SCROLL(NULL, "FOOBIE BLETCH", 0),
	SCROLL(NULL, "TEMOV", 0),
	SCROLL(NULL, "GARVEN DEH", 0),

#define	WAND(name,metal,prob,flags)	{ name, metal, NULL, 0, 0,\
		WAND_SYM, prob, 0, 3, flags, 0, 0 }

	WAND("light",	"iridium",		10,	NODIR),
	WAND("secret door detection",	"tin",	5,	NODIR),
	WAND("create monster",	"platinum",	5,	NODIR),
	WAND("wishing",		"glass",	1,	NODIR),
	WAND("striking",	"zinc",		9,	IMMEDIATE),
	WAND("slow monster",	"balsa",	5,	IMMEDIATE),
	WAND("speed monster",	"copper",	5,	IMMEDIATE),
	WAND("undead turning",	"silver",	5,	IMMEDIATE),
	WAND("polymorph",	"brass",	5,	IMMEDIATE),
	WAND("cancellation",	"maple",	5,	IMMEDIATE),
	WAND("teleportation",	"pine",		5,	IMMEDIATE),
	WAND("make invisible",	"marble",	9,	IMMEDIATE),
	WAND("digging",		"iron",		5,	RAY),
	WAND("magic missile",	"aluminium",	10,	RAY),
	WAND("fire",	"steel",	5,	RAY),
	WAND("sleep",	"curved",	5,	RAY),
	WAND("cold",	"short",	5,	RAY),
	WAND("death",	"long",		1,	RAY),
	WAND(NULL,	"oak",		0,	0),
	WAND(NULL,	"ebony",	0,	0),
	WAND(NULL,	"runed",	0,	0),

#define	RING(name,stone,spec)	{ name, stone, NULL, 0, 0,\
		RING_SYM, 0, 0, 1, spec, 0, 0 }

	RING("adornment",	"engagement",	0),
	RING("teleportation",	"wooden",	0),
	RING("regeneration",	"black onyx",	0),
	RING("searching",	"topaz",	0),
	RING("see invisible",	"pearl",	0),
	RING("stealth",		"sapphire",	0),
	RING("levitation",	"moonstone",	0),
	RING("poison resistance", "agate",	0),
	RING("aggravate monster", "tiger eye",	0),
	RING("hunger",		"shining",	0),
	RING("fire resistance",	"gold",		0),
	RING("cold resistance",	"copper",	0),
	RING("protection from shape changers", "diamond", 0),
	RING("conflict",	"jade",		0),
	RING("gain strength",	"ruby",		SPEC),
	RING("increase damage",	"silver",	SPEC),
	RING("protection",	"granite",	SPEC),
	RING("warning",		"wire",		0),
	RING("teleport control", "iron",	0),
	RING(NULL,		"ivory",	0),
	RING(NULL,		"blackened",	0),

/* gems ************************************************************/
#define	GEM(name,color,prob,gval)	{ name, color, NULL, 0, 1,\
		GEM_SYM, prob, 0, 1, 0, 0, gval }
	GEM("diamond", "blue", 1, 4000),
	GEM("ruby", "red", 1, 3500),
	GEM("sapphire", "blue", 1, 3000),
	GEM("emerald", "green", 1, 2500),
	GEM("turquoise", "green", 1, 2000),
	GEM("aquamarine", "blue", 1, 1500),
	GEM("tourmaline", "green", 1, 1000),
	GEM("topaz", "yellow", 1, 900),
	GEM("opal", "yellow", 1, 800),
	GEM("garnet", "dark", 1, 700),
	GEM("amethyst", "violet", 2, 650),
	GEM("agate", "green", 2, 600),
	GEM("onyx", "white", 2, 550),
	GEM("jasper", "yellowish brown", 2, 500),
	GEM("jade", "green", 2, 450),
	GEM("worthless piece of blue glass", "blue", 20, 0),
	GEM("worthless piece of red glass", "red", 20, 0),
	GEM("worthless piece of yellow glass", "yellow", 20, 0),
	GEM("worthless piece of green glass", "green", 20, 0),
	{ NULL, NULL, NULL, 0, 0, ILLOBJ_SYM, 0, 0, 0, 0, 0, 0 }
};

#endif MSDOS

char obj_symbols[] = {
	ILLOBJ_SYM, AMULET_SYM, FOOD_SYM, WEAPON_SYM, TOOL_SYM,
	BALL_SYM, CHAIN_SYM, ROCK_SYM, ARMOR_SYM, POTION_SYM, SCROLL_SYM,
	WAND_SYM, RING_SYM, GEM_SYM, 0 };
int bases[sizeof(obj_symbols)];
