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
*
* This code is based on pjsip from Benny Prijono <benny@prijono.org>
*
*/

#include "pjsipDll_PlayWav.h"
#include <pjsua-lib/pjsua.h>


#define THIS_FILE      "pjsipDll_playWav.cpp"
#define NO_LIMIT       (int)0x7FFFFFFF


static fptr_wavplayerEnded* cb_wavplayerEnded = 0;
 
/* Data callback "wavplayerEof" */
struct wavplayerEof_Data
{
       pjsua_player_id playerId;
       pjsua_call_id callId;
};


PJSIPDLL_DLL_API int onWavPlayerEndedCallback(fptr_wavplayerEnded cb)
{
  cb_wavplayerEnded = cb;
  return 1;
}

/************************************************************
    C callback
    Launch when the player has reached the end of wav file
------------------------------------------------------------*/

static PJ_DEF(pj_status_t) on_wavplayerEof_callback(pjmedia_port* media_port, void* args)
{
       //pj_status_t status;
       wavplayerEof_Data* WavePlayerData = ((wavplayerEof_Data*) args);
 
       // Read info from args
       pjsua_call_id call_id = WavePlayerData->callId;
       pjsua_player_id player_id = WavePlayerData->playerId;
 
       //Destroy the Wav Player
       //status = pjsua_player_destroy(player_id);   // ! Problem if Destroying Here : cash at the end of callback, for most of wavs files
 
       // Free the memory allocated for the args
       free(args);
 
       PJ_LOG(3,(THIS_FILE, "End of Wav File, media_port: %d", media_port));
       // Invoke the Callback for C# managed code
       if (cb_wavplayerEnded != 0)
               (*cb_wavplayerEnded)(call_id, player_id);

       //if (status == PJ_SUCCESS)    // Player correctly Destroyed
       //        return -1;                      // Don't return PJ_SUCCESS, to prevent crash when returning from callback after Player Destruction

       return PJ_SUCCESS;             // Else, return PJ_SUCCESS

}      //// -> goes back to the function wich has invoke the callback : fill_buffer() in pjmedia\src\pjmedia\wav_player.c
       /////   CRASH HERE WITH MOST OF WAV FILES, if player has been destroyed above ////

/************************************************************
  Play the wav file "wavFile", in the call session "callId"
------------------------------------------------------------*/
 
int dll_playWav(char* wavFile, bool loopFile, int callId)
{
       pj_status_t status;

       /* Infos Player */
       pjsua_player_id player_id;            // Ident. for the player
       pjmedia_port *media_port;           // Struct. media_port
       pjsua_conf_port_id conf_port;       // Conference port for the player
 
       /* Infos Call Session */
       pjsua_call_info call_info;

       /********************************************
       / 1- Check if Call exists and is active
       ********************************************/

       // Get call_info from callId
	   if (callId >= 0)
	   {
		   pjsua_call_get_info(callId, &call_info);

		   if (call_info.media_status != PJSUA_CALL_MEDIA_ACTIVE)
				callId = -1; // Try to play into sound card
	   }

       /********************************************
       / 2- Load the WAV File - Create the player
       ********************************************/
	   status = pjsua_player_create(&pj_str(wavFile), loopFile ? 0 : PJMEDIA_FILE_NO_LOOP, &player_id);

       /********************************************
       / 3- Register the Callback C++ Function "on_wavplayerEof_callback"
       ********************************************/

       if (status == PJ_SUCCESS)
       {
               // Get media_port from player_id
               status = pjsua_player_get_port(player_id, &media_port);
       }
 
	   if (status == PJ_SUCCESS && !loopFile)
       {
               // Prepare argument for Callback
               wavplayerEof_Data* args = (wavplayerEof_Data*)malloc(sizeof(wavplayerEof_Data));
               args->playerId = player_id;
               args->callId = callId;     

               // Register the Callback, launched when the End of the Wave File is reached
			   status = pjmedia_wav_player_set_eof_cb(media_port, args, &on_wavplayerEof_callback);
       }
 
       /********************************************
       / 4- Stream the file to the Call Session
       ********************************************/

       // Get conf_port from player_id
       if (status == PJ_SUCCESS)
               conf_port = pjsua_player_get_conf_port(player_id);

 
       // one way connect conf_port (wav player) to call_info.conf_slot (call)
	   if (status == PJ_SUCCESS)
	   {
		   if (callId >= 0 && conf_port != PJSUA_INVALID_ID && call_info.conf_slot != 0)        // test if conf_port valid, and if conf_slot != soundcard
			   status = pjsua_conf_connect(conf_port, call_info.conf_slot);

		   if (callId < 0 && conf_port != PJSUA_INVALID_ID)
		   {
			   status = pjsua_conf_connect(conf_port, 0);
		   }
	   }

       PJ_LOG(3,(THIS_FILE,"Wav Play, status %d",status));

       if (status != PJ_SUCCESS)
	   {
		   if (player_id != PJSUA_INVALID_ID)
			   pjsua_player_destroy(player_id);

		   return -1;
	   }

       return player_id;
}

/************************************************************
  To stop player, without waiting the end of wav file
------------------------------------------------------------*/
bool dll_releaseWav(int playerId)
{
       //Destroy the Wav Player
       return (pjsua_player_destroy(playerId) == PJ_SUCCESS);
}

