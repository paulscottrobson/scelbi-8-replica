// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		sys_debug_system.h
//		Purpose:	Debugger Code (System Dependent) Header
//		Created:	21st September 2015
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************


#ifndef _DEBUG_SYS_H
#define _DEBUG_SYS_H

#include "sys_processor.h"
#include "drivers.h"

#define WIN_TITLE 		"Scelbi Emulator"									// Initial Window stuff
#define WIN_WIDTH		(38*8*3)
#define WIN_HEIGHT		(25*9*3)
#define WIN_BACKCOLOUR	0x004

// *******************************************************************************************************************************
//							These functions need to be implemented by the dependent debugger.
// *******************************************************************************************************************************

#define DEBUG_ARGUMENTS(ac,av) if (ac == 2) CPULoadBinary(av[1]);					// Handle CLI arguments
#define DEBUG_CPURENDER(x) 	DBGXRender(x,0)											// Render the debugging display
#define DEBUG_VDURENDER(x)	DBGXRender(x,1)											// Render the game display etc.

#define DEBUG_RESET() 		CPUReset()												// Reset the CPU / Hardware.
#define DEBUG_HOMEPC()		(CPUGetStatus()->pc) 									// Get PC Home Address (e.g. current PCTR value)

//#define DEBUG_SINGLESTEP()	CPUExecuteSinglePhase()									// Execute a single instruction, return 0 or Frame rate on frame end.
#define DEBUG_SINGLESTEP() 	CPUExecuteInstruction()

#define DEBUG_RUN(b1,b2) 	CPUExecute(b1,b2) 										// Run a frame or to breakpoint, returns -1 if breakpoint
#define DEBUG_GETOVERBREAK() CPUGetStepOverBreakpoint()								// Where would we break to step over here. (0 == single step)

#define DEBUG_RAMSTART 		(0)														// Initial RAM address for debugger.
#define DEBUG_SHIFT(d,v)	((((d) << 4) | v) & 0xFFFF)								// Shifting into displayed address.

#define DEBUG_KEYMAP(k,r) 	DRVKeyMapper(k,r)										// Runtime can remap/process keys etc.

void DBGXRender(int *address,int show);												// Render the debugger screen.
void DBGXWriteScopeCharacter(BYTE8 x,BYTE8 y,WORD16 latches);						// Write to scope screen.
void DBGXSetLEDDisplay(void);

#endif