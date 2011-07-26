/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : Connection.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */


#ifndef CONNECTION_HEADER_INCLUDED
#define CONNECTION_HEADER_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif
	/**
	 * Connection_create
	 *
	 *  -address: IP address of Naming Service
	 *  -connectorID: identifier of connector to be created.
	 *  -connectorName: name of connector to be created.
	 *  -compA: name of component A
	 *  -portNameA: name of componentA's port
	 *  -compB: name of component B
	 *  -portNameB: name of componentB's port
	 *  -retval: return value for scilab process.
	 *  if success, *retval = 0, if error, non-zero value.
	 */
	EXPORT_FUNCTION_TYPE Connection_create(const char* connectorID,
										   const char* connectorName, 
										   const int* HandleA,
										   const int* HandleB,
										   int* retval);
	EXPORT_FUNCTION_TYPE Connection_destroy(const int* Handle,
		int* retval);


#ifdef __cplusplus
};
#endif



#endif

