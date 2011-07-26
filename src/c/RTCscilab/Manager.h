/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : Manager.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */


#ifndef MANAGER_HEADER_INCLUDED
#define MANAGER_HEADER_INCLUDED

/**
 * linkage should be "C", because of scilab.
 */
#ifdef __cplusplus 
extern "C" {
#endif

	/**
	 * Manager_create
	 *   -managername -- identifier of ScilabComp component.
	 *
	 * Manager object is created. The pointer to the object
	 * is stored in the global variable g_pManager.
	 * The argument will be used as the default instance name 
	 * of the RTC which will be created by the Manager.
	 */
	EXPORT_FUNCTION_TYPE Manager_create(char* managername, char* pathrtcconf);

	/**
	 * Manager_destroy
	 * Manager object is destroyed.
	 */
	EXPORT_FUNCTION_TYPE Manager_destroy(void);

#ifdef __cplusplus
}
#endif


#endif

