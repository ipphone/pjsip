/* 
 * Copyright (C) 2007 Sasa Coh <sasacoh@gmail.com>
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

// #ifdef LINUX
// 	#define __stdcall
// 	#define PJSIPDLL_DLL_API
// #else
// #ifndef PJSIPDLL_EXPORTS
// 	#define PJSIPDLL_DLL_API __declspec(dllexport)
// #else
// 	#define PJSIPDLL_DLL_API __declspec(dllimport)
// #endif
// #endif

#define PJSIPDLL_DLL_API __declspec(dllexport)


// Structure containing pjsip configuration parameters
// Should be synhronized with appropriate .Net structure!!!!!
struct SipConfigStruct
{
	int listenPort;
	bool noUDP;
	bool noTCP;
	char stunAddress[255];
	bool publishEnabled;
	int expires;

	bool VADEnabled;
	int ECTail;

	char nameServer[255];

	bool pollingEventsEnabled;

	int logLevel;

	// IMS specifics
	bool imsEnabled;
	bool imsIPSecHeaders;
	bool imsIPSecTransport;

	int rtpPort;
};

// SIP header to passing for outgoing call
struct SipHeader
{
	char name[64];
	char value[255];
};

struct SipHeaderCollection
{
	SipHeader *headers;
};

// Clone of pjmedia_aud_dev_info
struct PjMediaAudDevInfo 
{
    char name[64];
    int inputCount;
    int outputCount;
    int defaultSamplesPerSec;
    char driver[32];
    int caps;
    int routes;
    int extFmtCnt;
	int isNull;
};

// calback function definitions
typedef int __cdecl fptr_regstate(int, int);				// on registration state changed
typedef int __cdecl fptr_callstate(int, int);	// on call state changed
typedef int __cdecl fptr_callmediastate(int, int); // on call media state changed
typedef int __cdecl fptr_callincoming(int, char*, char*, char*);	// on call incoming
typedef int __cdecl fptr_getconfigdata(int);	// get config data
typedef int __cdecl fptr_callholdconf(int);
typedef int __cdecl fptr_callretrieveconf(int);
typedef int __cdecl fptr_msgrec (char*, char*);
typedef int __cdecl fptr_buddystatus(int, int, const char*);
typedef int __cdecl fptr_dtmfdigit(int callId, int digit);
typedef int __cdecl fptr_mwi(int mwi, char* info);
typedef int __cdecl fptr_crep(int oldid, int newid);

// Callback registration 
extern "C" PJSIPDLL_DLL_API int onRegStateCallback(fptr_regstate cb);	  // register registration notifier
extern "C" PJSIPDLL_DLL_API int onCallStateCallback(fptr_callstate cb); // register call notifier
extern "C" PJSIPDLL_DLL_API int onCallIncoming(fptr_callincoming cb); // register incoming call notifier
extern "C" PJSIPDLL_DLL_API int onCallHoldConfirmCallback(fptr_callholdconf cb); // register call notifier
//extern "C" PJSIPDLL_DLL_API int onCallRetrieveConfirm(fptr_callretrieveconf cb); // register call notifier
extern "C" PJSIPDLL_DLL_API int onMessageReceivedCallback(fptr_msgrec cb); // register call notifier
extern "C" PJSIPDLL_DLL_API int onBuddyStatusChangedCallback(fptr_buddystatus cb); // register call notifier
extern "C" PJSIPDLL_DLL_API int onDtmfDigitCallback(fptr_dtmfdigit cb); // register dtmf digit notifier
extern "C" PJSIPDLL_DLL_API int onMessageWaitingCallback(fptr_mwi cb); // register MWI notifier
extern "C" PJSIPDLL_DLL_API int onCallReplaced(fptr_crep cb); // register Call replaced notifier
extern "C" PJSIPDLL_DLL_API int onCallMediaStateChanged(fptr_callmediastate cb);

// pjsip common API
extern "C" PJSIPDLL_DLL_API int dll_setSipConfig(SipConfigStruct* config);
extern "C" PJSIPDLL_DLL_API int dll_init();
extern "C" PJSIPDLL_DLL_API int dll_shutdown(); 
extern "C" PJSIPDLL_DLL_API int dll_main(void);
extern "C" PJSIPDLL_DLL_API int dll_isThreadRegistered();
extern "C" PJSIPDLL_DLL_API int dll_threadRegister(char* name);
extern "C" PJSIPDLL_DLL_API int dll_getNumOfCodecs();
extern "C" PJSIPDLL_DLL_API int dll_getCodec(int index, char* codec);
extern "C" PJSIPDLL_DLL_API int dll_setCodecPriority(char* name, int index);
// pjsip call API
extern "C" PJSIPDLL_DLL_API int dll_registerAccount(char* uri, char* reguri, char* name, char* username, char* password, char* proxy, bool isdefault);
extern "C" PJSIPDLL_DLL_API void dll_renewAccount(int accountId);

extern "C" PJSIPDLL_DLL_API int dll_makeCall(int accountId, char* uri, SipHeader* headers, int headersCount); 
extern "C" PJSIPDLL_DLL_API int dll_releaseCall(int callId); 
extern "C" PJSIPDLL_DLL_API int dll_answerCall(int callId, int code);
extern "C" PJSIPDLL_DLL_API int dll_holdCall(int callId);
extern "C" PJSIPDLL_DLL_API int dll_retrieveCall(int callId);
extern "C" PJSIPDLL_DLL_API int dll_xferCall(int callid, char* uri);
extern "C" PJSIPDLL_DLL_API int dll_xferCallWithHeaders(int callid, char* uri, SipHeader* headers, int headersCount);
extern "C" PJSIPDLL_DLL_API int dll_xferCallWithReplaces(int callId, int dstSession);
extern "C" PJSIPDLL_DLL_API int dll_xferCallWithReplacesAndHeaders(int callId, int dstSession, SipHeader* headerCollection, int headersCount);
extern "C" PJSIPDLL_DLL_API int dll_serviceReq(int callId, int serviceCode, const char* destUri);
extern "C" PJSIPDLL_DLL_API int dll_dialDtmf(int callId, char* digits, int mode);
extern "C" PJSIPDLL_DLL_API int dll_removeAccounts();
extern "C" PJSIPDLL_DLL_API int dll_sendInfo(int callid, char* content);
extern "C" PJSIPDLL_DLL_API int dll_getCurrentCodec(int callId, char* codec);
extern "C" PJSIPDLL_DLL_API int dll_makeConference(int callId);
extern "C" PJSIPDLL_DLL_API int dll_sendCallMessage(int callId, char* message);
extern "C" PJSIPDLL_DLL_API int dll_connectCallsMedia(int call1_id, int call2_id);
extern "C" PJSIPDLL_DLL_API int dll_isCallsMediaConnected(int call1_id, int call2_id);
// IM & Presence api
extern "C" PJSIPDLL_DLL_API int dll_addBuddy(char* uri, bool subscribe);
extern "C" PJSIPDLL_DLL_API int dll_removeBuddy(int buddyId);
extern "C" PJSIPDLL_DLL_API int dll_sendMessage(int accId, char* uri, char* message);
extern "C" PJSIPDLL_DLL_API int dll_setStatus(int accId, int presence_state);

extern "C" PJSIPDLL_DLL_API int dll_pollForEvents(int timeout);

extern "C" PJSIPDLL_DLL_API void dll_getSoundDevices(int* playbackDevice, int* recordingDevice);
extern "C" PJSIPDLL_DLL_API int dll_setSoundDevice(char* playbackDeviceId, char* recordingDeviceId);
extern "C" PJSIPDLL_DLL_API int dll_enumerateSoundDevicesCount();
extern "C" PJSIPDLL_DLL_API int dll_enumerateSoundDevices(PjMediaAudDevInfo *devices, int count);
extern "C" PJSIPDLL_DLL_API float dll_getMicLevel();
extern "C" PJSIPDLL_DLL_API void dll_setMicLevel(float value);
extern "C" PJSIPDLL_DLL_API float dll_getSpeakerLevel();
extern "C" PJSIPDLL_DLL_API void dll_setSpeakerLevel(float value);
