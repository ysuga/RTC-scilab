/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : dllmain.cpp
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */


#include "stdafx.h"
#include "RTCscilab.h"
#include "GlobalUtility.h"
#include "Manager.h"
#include "CorbaNaming.h"
#include "RTC.h"

extern "C" {
	/**
	 * Initilization function for Dynamic Loading in the Unix process.
	 * This function will also be called in the dllmain function in 
	 * Win32 process.
	 */
	void _init() 
	{

	}

	/**
	 * Finalization function for Dynamic Loading in the Unix process.
	 * This function will also be called in the dllmain function in 
	 * Win32 process.
	 */
	void _fini()
	{
		//void CleanUpSciPorts();
		int ret;
		//CorbaNaming_destroyAll(&ret);
		if(g_pManager) {
			Manager_destroy();
		}
	}
}

#ifdef WIN32
/**
 * DLL entry point.
 */
BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		// Initialize Code.
		_init();
		break;
	case DLL_THREAD_ATTACH:

		break;
	case DLL_THREAD_DETACH:

		break;
	case DLL_PROCESS_DETACH:
		// Cleanup Code.
		_fini();
		break;
	}
	return TRUE;
}

#endif