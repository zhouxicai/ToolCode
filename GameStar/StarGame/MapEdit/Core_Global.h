/**************************************************
Core_Global.h
GameCore Component


Programming Role-Playing Games with DirectX, 2nd Edition
by Jim Adams (Jan 2004)
**************************************************/

#ifndef _CORE_GLOBAL_H_
#define _CORE_GLOBAL_H_

// Windows includes
//#include <windows.h>

// Standard ANSI-C includes
//#include <stdio.h>

// DirectX includes
//#include "d3d9.h"
//#include "d3dx9.h"
//#include "dmusici.h"
//#include "dsound.h"
//#include "dplay8.h"
//#include "dpaddr.h"
//#include "dinput.h"
//#include "dshow.h"

// Core includes
//#include "Core_System.h"
//#include "Core_Graphics.h"
//#include "Core_Input.h"
//#include "Core_Sound.h"
//#include "Core_Network.h"

enum eSound
{
	RAIN01	,
	RAIN03	
};
// Global sound effect filenames
#if 1
#define NUM_SOUNDS 2
char *g_SoundFilenames[NUM_SOUNDS] = 
{
	{ "audios\\rain01.wav" },
	{ "audios\\rain03.wav" }
};

// Global music filenames
long g_CurrentMusic = -1;
char *g_MusicFilenames[] = 
{
	{ "audios\\TMEMO01.mid" },
	{ "audios\\zzjb01.mid"  }
};	   
#endif
#endif
