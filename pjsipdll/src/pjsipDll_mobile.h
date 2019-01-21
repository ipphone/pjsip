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

#ifdef LINUX
	#define __stdcall
	#define PJSIPDLL_DLL_API
#else
#ifdef PJSIPDLL_EXPORTS
	#define PJSIPDLL_DLL_API __declspec(dllexport)
#else
	#define PJSIPDLL_DLL_API __declspec(dllimport)
#endif
#endif


// Structure containing pjsip configuration parameters
// Should be synhronized with appropriate .Net structure!!!!!
struct SipConfigStruct
{
	int listenPort;
	bool noUDP;
	bool noTCP;
	wchar_t stunAddress[255];
	bool publishEnabled;
	int expires;

	bool VADEnabled;
	int ECTail;

	wchar_t nameServer[255];

	bool pollingEventsEnabled;

	int logLevel;

	// IMS specifics
	bool imsEnabled;
	bool imsIPSecHeaders;
	bool imsIPSecTransport;
};

// calback function definitions
typedef int __stdcall fptr_regstate(int, int);				// on registration state changed
typedef int __stdcall fptr_callstate(int, int);	// on call state changed
typedef int __stdcall fptr_callincoming(int, wchar_t*);	// on call incoming
typedef int __stdcall fptr_getconfigdata(int);	// get config data
typedef int __stdcall fptr_callholdconf(int);
typedef int __stdcall fptr_callretrieveconf(int);
typedef int __stdcall fptr_msgrec (wchar_t*, wchar_t*);
typedef int __stdcall fptr_buddystatus(int, int, const wchar_t*);
typedef int __stdcall fptr_dtmfdigit(int callId, int digit);
typedef int __stdcall fptr_mwi(int mwi, wchar_t* info);
typedef int __stdcall fptr_crep(int oldid, int newid);

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

// pjsip common API
extern "C" PJSIPDLL_DLL_API void dll_setSipConfig(SipConfigStruct* config);
extern "C" PJSIPDLL_DLL_API int dll_init();
extern "C" PJSIPDLL_DLL_API int dll_shutdown(); 
extern "C" PJSIPDLL_DLL_API int dll_main(void);
extern "C" PJSIPDLL_DLL_API int dll_getNumOfCodecs();
extern "C" PJSIPDLL_DLL_API int dll_getCodec(int index, wchar_t* codec);
extern "C" PJSIPDLL_DLL_API int dll_setCodecPriority(wchar_t* name, int index);
// pjsip call API
extern "C" PJSIPDLL_DLL_API int dll_registerAccount(wchar_t* uri, wchar_t* reguri, wchar_t* name, wchar_t* username, 
																										wchar_t* password, wchar_t* proxy, bool isdefault);

extern "C" PJSIPDLL_DLL_API int dll_makeCall(int accountId, wchar_t* uri); 
extern "C" PJSIPDLL_DLL_API int dll_releaseCall(int callId); 
extern "C" PJSIPDLL_DLL_API int dll_answerCall(int callId, int code);
extern "C" PJSIPDLL_DLL_API int dll_holdCall(int callId);
extern "C" PJSIPDLL_DLL_API int dll_retrieveCall(int callId);
extern "C" PJSIPDLL_DLL_API int dll_xferCall(int callid, char* uri);
extern "C" PJSIPDLL_DLL_API int dll_xferCallWithReplaces(int callId, int dstSession);
extern "C" PJSIPDLL_DLL_API int dll_serviceReq(int callId, int serviceCode, const wchar_t* destUri);
extern "C" PJSIPDLL_DLL_API int dll_dialDtmf(int callId, wchar_t* digits, int mode);
extern "C" PJSIPDLL_DLL_API int dll_removeAccounts();
extern "C" PJSIPDLL_DLL_API int dll_sendInfo(int callid, wchar_t* content);
extern "C" PJSIPDLL_DLL_API int dll_getCurrentCodec(int callId, wchar_t* codec);
extern "C" PJSIPDLL_DLL_API int dll_makeConference(int callId);
extern "C" PJSIPDLL_DLL_API int dll_sendCallMessage(int callId, wchar_t* message);
// IM & Presence api
extern "C" PJSIPDLL_DLL_API int dll_addBuddy(wchar_t* uri, bool subscribe);
extern "C" PJSIPDLL_DLL_API int dll_removeBuddy(int buddyId);
extern "C" PJSIPDLL_DLL_API int dll_sendMessage(int accId, wchar_t* uri, wchar_t* message);
extern "C" PJSIPDLL_DLL_API int dll_setStatus(int accId, int presence_state);

extern "C" PJSIPDLL_DLL_API int dll_setSoundDevice(wchar_t* playbackDeviceId, wchar_t* recordingDeviceId);

extern "C" PJSIPDLL_DLL_API int dll_pollForEvents(int timeout);