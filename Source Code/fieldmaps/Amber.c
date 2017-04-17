#include "../openpoke.h"

extern const Map16_Tile tileset_Outdoors[];
extern const Map16_Tile tileset_Amber[];

extern const unsigned char Amber_MapScript_Script[];
extern const unsigned char Amber_Villager2_Script[];
extern const unsigned char Amber_Villager1_Script[];
extern const unsigned char Amber_Villager3_Script[];
extern const unsigned char Amber_YourHouse_Script[];
extern const unsigned char Amber_HisHouse_Script[];
extern const unsigned char Amber_Warning_Script[];
extern const unsigned char Amber_Warning_Script[];
extern const unsigned char Amber_Warning_Script[];
extern const unsigned char Amber_Warning_Script[];

const unsigned short Amber_Map[] =
{
	0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x10, 0x11, 0x11, 0x11, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D,
	0x16, 0x15, 0x16, 0x15, 0x24, 0x25, 0x24, 0x25, 0x24, 0x25, 0x11, 0x162,0x164,0x11, 0x24, 0x25, 0x24, 0x25, 0x24, 0x25, 0x24, 0x25, 0x16, 0x15,
	0x1E, 0x1D, 0x1E, 0x1D, 0x8,  0x9,  0x9,  0x9,  0x9,  0x9,  0x9,  0x16A,0x16C,0x10, 0x2A8,0x2A9,0x2A9,0x2A9,0x2A9,0x2BD,0x2B5,0x9,  0x1E, 0x1D,
	0x16, 0x15, 0x16, 0x15, 0x8,  0x4,  0x9,  0x11, 0x11, 0x11, 0x11, 0x16A,0x16C,0x11, 0x2B0,0x2B1,0x2B1,0x2B1,0x2B1,0x2B3,0x2B4,0x9,  0x16, 0x15,
	0x1E, 0x1D, 0x1E, 0x1D, 0x10, 0x10, 0x10, 0x162,0x163,0x163,0x163,0x16B,0x16C,0x11, 0x2B8,0x2B9,0x2B9,0x2B9,0x2B9,0x2BB,0x2BC,0x11, 0x1E, 0x1D,
	0x16, 0x15, 0x16, 0x15, 0x9,  0x4,  0x9,  0x16A,0x16B,0x16B,0x16B,0x16B,0x16C,0x8,  0x2C0,0x2C1,0x2D0,0x2C2,0x2C3,0x2C1,0x2C5,0x8,  0x16, 0x15,
	0x1E, 0x1D, 0x1E, 0x1D, 0x10, 0x9,  0x10, 0x16A,0x16B,0x16B,0x173,0x173,0x174,0x10, 0x2C8,0x2C9,0x2D8,0x2AC,0x2CB,0x2CC,0x2CD,0x8,  0x1E, 0x1D,
	0x16, 0x15, 0x16, 0x15, 0x10, 0x4,  0x9,  0x16A,0x16B,0x16C,0x11, 0x11, 0x4,  0x11, 0x5,  0x5,  0x162,0x16B,0x164,0x5,  0x5,  0x9,  0x16, 0x15,
	0x1E, 0x1D, 0x1E, 0x1D, 0x10, 0x10, 0x10, 0x16A,0x16B,0x16C,0x8,  0x8,  0x9,  0x4,  0x10, 0x10, 0x16A,0x16B,0x16C,0x8,  0x11, 0x10, 0x1E, 0x1D,
	0x16, 0x15, 0x16, 0x15, 0x10, 0x162,0x163,0x16B,0x16B,0x16B,0x163,0x164,0x10, 0x10, 0x162,0x163,0x16B,0x16B,0x16B,0x163,0x164,0x10, 0x16, 0x15,
	0x1E, 0x1D, 0x1E, 0x1D, 0x8,  0x16A,0x281,0x282,0x282,0x282,0x283,0x16C,0x10, 0x10, 0x16A,0x281,0x282,0x282,0x282,0x283,0x16C,0x9,  0x1E, 0x1D,
	0x16, 0x15, 0x16, 0x15, 0x9,  0x16A,0x289,0x28A,0x28A,0x28A,0x28B,0x16B,0x163,0x163,0x16B,0x289,0x28A,0x28A,0x28A,0x28B,0x16C,0x8,  0x16, 0x15,
	0x1E, 0x1D, 0x1E, 0x1D, 0x11, 0x16A,0x291,0x293,0x293,0x293,0x294,0x16B,0x173,0x173,0x16B,0x291,0x293,0x293,0x293,0x294,0x16C,0x11, 0x1E, 0x1D,
	0x16, 0x15, 0x16, 0x15, 0x9,  0x16A,0x298,0x299,0x29A,0x29B,0x29C,0x16C,0x161,0x161,0x16A,0x298,0x299,0x29A,0x29B,0x29C,0x16C,0x8,  0x16, 0x15,
	0x1E, 0x1D, 0x1E, 0x1D, 0x10, 0x16A,0x2A0,0x2A3,0x2A2,0x2A1,0x2A4,0x16C,0x169,0x169,0x16A,0x2A0,0x2A3,0x2A2,0x2A1,0x2A4,0x16C,0x11, 0x1E, 0x1D,
	0x16, 0x15, 0x16, 0x15, 0x9,  0x172,0x173,0x173,0x173,0x173,0x173,0x174,0x8,  0x8,  0x172,0x173,0x173,0x173,0x173,0x173,0x174,0x10, 0x16, 0x15,
	0x1E, 0x1D, 0x1E, 0x1D, 0x9,  0x8,  0x9,  0x9,  0x8,  0x9,  0x8,  0x9,  0x8,  0x10, 0x8,  0x10, 0x8,  0x10, 0x11, 0x9,  0x8,  0x9,  0x1E, 0x1D,
	0x16, 0x15, 0x16, 0x15, 0xE,  0xF,  0xE,  0xF,  0xE,  0xF,  0xE,  0xF,  0xE,  0xF,  0xE,  0xF,  0xE,  0xF,  0xE,  0xF,  0xE,  0xF,  0x16, 0x15,
	0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D, 0x1E, 0x1D,
};

const aBorderTile AmberBorder = { 0x1C, 0x1D, 0x14, 0x15 };

const aMap AmberMap =
{
	24,19,
	(aBorderTile*)&AmberBorder,
	(unsigned short*)Amber_Map,
	(aTileset*)tileset_Outdoors,
	(aTileset*)tileset_Amber
};

const aPeopleEvent AmberPeople[] =
{
	{ 13,6, 0x0, 0, (unsigned int)Amber_Villager2_Script, sprGirl1, 0, 0, 0, 0, 0 },
	{ 7,8, 0x0, 0, (unsigned int)Amber_Villager1_Script, sprGuy1, 0, 0, 0, 1, 0 },
	{ 19,9, 0x0, 0, (unsigned int)Amber_Villager3_Script, sprGuy5, 0, 0, 0, 3, 0 },
	{ 15,15, 0x5, 0, 0, sprDanny, 0, 1, 0, 3, 0 }
};

const aWarpEvent AmberWarps[] =
{
	{ 7,15,WARP_DOOROUTSIDE,0,21 }, //To map #21 - AmberHouse1
	{ 16,15,WARP_DOOROUTSIDE,0,23 }, //To map #23 - AmberHouse2
	{ 17,7,WARP_DOOROUTSIDE,0,25 } //To map #25 - AmberLab
};

const aSignEvent AmberSigns[] =
{
	{ 12,14, (unsigned int)Amber_YourHouse_Script, 1 },
	{ 13,14, (unsigned int)Amber_HisHouse_Script, 1 }
};

const aTrapEvent AmberTraps[] =
{
	{ 10,1, 0, 0xA, 0, (unsigned int)Amber_Warning_Script },
	{ 11,1, 0, 0xA, 0, (unsigned int)Amber_Warning_Script },
	{ 12,1, 0, 0xA, 0, (unsigned int)Amber_Warning_Script },
	{ 13,1, 0, 0xA, 0, (unsigned int)Amber_Warning_Script }
};

const aEventSet AmberEvents =
{
	4,3,4,2,
	(aPeopleEvent*)AmberPeople, (aWarpEvent*)AmberWarps, (aTrapEvent*)AmberTraps, (aSignEvent*)AmberSigns
};

const aConnection AmberConns[] =
{
	{ 0, 0, 11 }, //To map #11 - Route1
//	{ 2, 0, 19 } //To map #19 - Route8
};

const aConnectionSet AmberConnSet =
{
	1, (aConnection*)&AmberConns
};

const aMapHeader mhdrAmber =
{
	(aMap*)&AmberMap, //map
	(aEventSet*)&AmberEvents, //events
	0, //init script
	(void*)&Amber_MapScript_Script, //after script
	(aConnectionSet*)&AmberConnSet, //conns
	73, //music
	0, //filler
	1, //name
	0, //cave
	2, //weather
	0, //transition
	1, //show name
	0, //perms
	0, //floor
	0, //battleground
	0, //encounters
};

