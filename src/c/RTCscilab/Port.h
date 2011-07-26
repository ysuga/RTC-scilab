/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : Port.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */

#ifndef PORT_HEADER_INCLUDED
#define PORT_HEADER_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif


	EXPORT_FUNCTION_TYPE Port_create(const int *Handle, const char* portName, int* retval);
	EXPORT_FUNCTION_TYPE Port_destroy(const int* Handle, int* retval);



	/** Port_getProfile
	 * Get RTC's configuration value.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -portName: port's name
	 *  -retval : return value for scilab process.
	 * If success, *retval will be the port profile name list.
	 * Each value is separated by RTCSCILAB_DELIMITER.
	 * this format will be...
	 *  Name1 DELIMITER Value1 DELIMITER Name2 DELIMITER Value2
	 *  The retval will be recognized by scilab process.
	 *  if failed to find RTC, *retval is "failed".
	 */
	EXPORT_FUNCTION_TYPE Port_getProfile(const int *Handle,
										 char* retval);

	
EXPORT_FUNCTION_TYPE Port_getName(const int *Handle,
									 char* retval);

#ifdef __cplusplus
};
#endif


#endif



