// *******************************************************************************************************************************
// *******************************************************************************************************************************
//
//		Name:		drivers.h
//		Purpose:	Hardware interface (Header)
//		Created:	21st September 2015
//		Author:		Paul Robson (paul@robsons.org.uk)
//
// *******************************************************************************************************************************
// *******************************************************************************************************************************

#ifndef _DRIVERS_H
#define _DRIVERS_H

#define DRVKEY_RUN 			('R')
#define DRVKEY_STEP			('S')
#define DRVKEY_INTERRUPT	('I')

BYTE8 DRVIsPushButtonPressed(BYTE8 button);
BYTE8 DRVReadToggleSwitches(void);
void DRVReset(void);
void DRVEndFrame(void);
void DRVWriteScope(WORD16 latches);
void DRVRefreshPanel(WORD16 address,BYTE8 data,BYTE8 status,BYTE8 intMode,BYTE8 halt,BYTE8 runMode);
void DRVWriteScopeCharacter(BYTE8 x,BYTE8 y,WORD16 latches);
BYTE8 DRVGetASCIICharacter(WORD16 pattern);
void DRVSwitchLEDPanel(void);
void DRVClearKeyboardLatch(void);
BYTE8 DRVReadKeyboardLatch(void);

#define APIN_INTERRUPT 		(12)
#define APIN_STEP			(11)
#define APIN_RUN 			(10)

#define APIN_D7				(9)
#define APIN_D6				(8)
#define APIN_D5				(7)
#define APIN_D4				(6)
#define APIN_D3				(5)
#define APIN_D2				(4)
#define APIN_D1				(3)
#define APIN_D0				(2)

#define APIN_KEYBOARDDATA	(17)
#define APIN_KEYBOARDCLOCK	(18)
#endif