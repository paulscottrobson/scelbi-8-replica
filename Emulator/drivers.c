// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		drivers.c
//		Purpose:	Hardware interface
//		Created:	21st September 2015
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#include "sys_processor.h"
#include "drivers.h"
#include "gfx.h"

static void _DRV20x4Initialise(void);
static void _DRV20x4RefreshPanel(WORD16 address,BYTE8 data,BYTE8 status,BYTE8 intMode,BYTE8 halt,BYTE8 runMode);

#ifdef WINDOWS

#define WRITEDISPLAY(x,y,c) DBGXWriteDisplay(x,y,c)

static BYTE8 toggles = 0;

BYTE8 DRVIsPushButtonPressed(BYTE8 button) {
	return GFXIsKeyPressed(button);
}

BYTE8 DRVReadToggleSwitches(void) {
	return toggles;
}

BYTE8 DRVKeyMapper(BYTE8 key,BYTE8 inRunMode) {
	if (inRunMode != 0 && key >= '0' && key <= '7') {
		toggles = (toggles << 3) | (key & 7);
	}
	return key;
}

void DRVRefreshPanel(WORD16 address,BYTE8 data,BYTE8 status,BYTE8 intMode,BYTE8 halt,BYTE8 runMode) {
	_DRV20x4RefreshPanel(address,data,status,intMode,halt,runMode);
}

void DRVReset(void) {
	GFXDefineCharacter(126,0x3e,0x7F,0x7F,0x7F,0x3E);
	GFXDefineCharacter(127,0x3e,0x41,0x41,0x41,0x3E);
	_DRV20x4Initialise();
}

void DRVEndFrame(void) {
}

#endif

#define WR(c) WRITEDISPLAY(0xFF,0xFF,c)

static void _DRV20x4Initialise(void) {
	WRITEDISPLAY(0,0,' ');
	for (BYTE8 i = 0;i < 79;i++) WRITEDISPLAY(0xFF,0xFF,' ');
	WRITEDISPLAY(4,0,'P');WR('a');WR('g');WR('e');
	WRITEDISPLAY(0,3,'R');
	WRITEDISPLAY(2,3,'I');WR('S');WR('t');
	WRITEDISPLAY(6,3,'H');
	WRITEDISPLAY(13,0,'A');WR('d');WR('d');WR('r');
	WRITEDISPLAY(13,3,'D');WR('a');WR('t');WR('a');
}

static void _DRV20x4Binary(BYTE8 x,BYTE8 y,BYTE8 data,BYTE8 width) {
	BYTE8 mask = 1 << (width - 1);
	while (width-- > 0) {
		WRITEDISPLAY(x++,y,(data & mask) ? 126 : 127);
		mask = mask >> 1;
	}
}

static void _DRV20x4RefreshPanel(WORD16 address,BYTE8 data,BYTE8 status,BYTE8 intMode,BYTE8 halt,BYTE8 runMode) {
	_DRV20x4Binary(2,1,address >> 11,3);_DRV20x4Binary(6,1,address >> 8,3);
	_DRV20x4Binary(10,1,address >> 6,2);_DRV20x4Binary(13,1,address >> 3,3);_DRV20x4Binary(17,1,address,3);
	_DRV20x4Binary(10,2,data >> 6,2);_DRV20x4Binary(13,2,data >> 3,3);_DRV20x4Binary(17,2,data,3);
	_DRV20x4Binary(0,2,runMode,1);_DRV20x4Binary(2,2,intMode,1);
	_DRV20x4Binary(3,2,status,2);_DRV20x4Binary(6,2,halt,1);

	#ifdef OCTAL_HELPER
	WRITEDISPLAY(0,0,(toggles >> 6) | '0');
	WRITEDISPLAY(1,0,((toggles >> 3) & 7) | '0');
	WRITEDISPLAY(2,0,(toggles & 7) | '0');
	#endif
}
