/*
 * Copyright (C) 2007 Sasa Coh <sasacoh[at]gmail.com>
 *
 * Updated by Tanguy Floc'h <tanguy.floch[at]gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

 
// pjsipDll.h : Declares the entry point for the .Net GUI application.
//

// #ifdef PJSIPDLL_EXPORTS
//        #define PJSIPDLL_DLL_API __declspec(dllexport)
// #else
//        #define PJSIPDLL_DLL_API __declspec(dllimport)
// #endif

#define PJSIPDLL_DLL_API __declspec(dllexport)

// calback function definitions
typedef int __cdecl fptr_wavplayerEnded(int CallId, int PlayerId);

 
// Callback registration
extern "C" PJSIPDLL_DLL_API int onWavPlayerEndedCallback(fptr_wavplayerEnded cb); // register Wav Player Eof notifier
extern "C" PJSIPDLL_DLL_API int dll_playWav(char* waveFile, bool loopFile, int callId);
extern "C" PJSIPDLL_DLL_API bool dll_releaseWav(int playerId);
