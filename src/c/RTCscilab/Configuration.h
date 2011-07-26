/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : Configuration.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */
#ifndef CONFIGURATION_HEADER_INCLUDED
#define CONFIGURATION_HEADER_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif
	/** ConfigurationSet_getConfNameList
	 *  Get RTC's configuration names.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -confSetName: configuration_set's name
	 *  -retval : return value for scilab process.
	 *  If success, *retval will be the name list of configuration.
	 *  each name is separated by the RTCSCILAB_DELIMITER.
	 *  if failed *retval will be "failed"
	 */
	EXPORT_FUNCTION_TYPE ConfigurationSet_getConfNameList(const int *Handle,
														  const char* confSetName,
														  char* retval);


	/** Configuration_configure
	 *  Set RTC's configuration value.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -confSetName: configuration_set's name
	 *  -confName: configuration name.
	 *  -retval : return value for scilab process.
	 *  If success, *retval will be zero.
	 *  if failed *retval will be non-zero value
	 */
	EXPORT_FUNCTION_TYPE Configuration_configure(const int* Handle,
												 const char* confSetName,
												 const char* confName, 
												 const char* confValue,
											     int* retval);

	/** Configuration_getValue
	 *  Get RTC's configuration value.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -configurationSetName: configuration_set's name
	 *  -configurationName: configuration name.
	 *  -retval : return value for scilab process.
	 * If success, *retval will be the configuration value.
	 *  The retval will be recognized by scilab process.
	 *  if failed to find RTC, *retval is "failed".
	 */
	EXPORT_FUNCTION_TYPE Configuration_getValue(const int *Handle,
											   const char* confSetName,
											   const char* confName,
											   char* retval);

#ifdef __cplusplus
};
#endif



#endif


