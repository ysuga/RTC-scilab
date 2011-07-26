/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : CorbaNaming.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */

#ifndef CORBANAMING_HEADER_INCLUDED
#define CORBANAMING_HEADER_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif
	/**
	 * CorbaNaming_create
	 *  -address : IP address of Naming server
	 *  -ret      : return value for rtc-scilab. 
	 * If success, *ret is the number of naming service object.
	 * If error, *ret is negative value.
	 */
	EXPORT_FUNCTION_TYPE CorbaNaming_create(const char* address, int* ret);

	/**
	 * CorbaNaming_destroy
	 *  -address : IP address of Naming server.
	 *  -ret     : return value for scilab.
	 * Before calling this, the CorbaNaming object should be created by calling
	 *  CorbaNaming_create function.
	 * If success, *ret will be 0. If error, negative value.
	 */
	EXPORT_FUNCTION_TYPE CorbaNaming_destroy(int* id, int* ret);


	/**
	 * CorbaNaming_destroyAll
	 *  -ret     : return value for scilab.
	 * If success, *ret will be 0. If error, negative value.
	 */
	EXPORT_FUNCTION_TYPE CorbaNaming_destroyAll(int* retval);

	/**
	 * CorbaNaming_getRTCNameList
	 *  -address : IP addresss of CorbaNaming object. 
	 *  -componentName: RT-Component name list. Each name is separated by 
	 *    the RTCSCILAB_DELIMITER. The scilab function will be re-recognize the strings.
	 * If error, componentName will be "failed"
	 */
	EXPORT_FUNCTION_TYPE CorbaNaming_getRTCNameList(int *id, char* componentName);

#ifdef __cplusplus
};
#endif


#endif



