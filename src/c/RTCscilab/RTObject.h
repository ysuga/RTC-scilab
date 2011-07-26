/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : RTC.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtcsiclab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */
#ifndef RTC_HEADER_INCLUDED
#define RTC_HEADER_INCLUDED


extern "C" {
	/** RTObjet_create
	 * activate RT component.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -retval : return value for scilab process.
	 * *retval will be...
	 *  success: RTObjet_OK(0)
	 *  error  : Non-zero vlaue.
	 */
	EXPORT_FUNCTION_TYPE RTObject_create(const int *CorbaNamingID, const char* componentName, int *retval);

	/** RTObjet_destroy
	 * activate RT component.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -retval : return value for scilab process.
	 * *retval will be...
	 *  success: RTObjet_OK(0)
	 *  error  : Non-zero vlaue.
	 */
	EXPORT_FUNCTION_TYPE RTObject_destroy(const int *componentID, int *retval);





	/** RTObjet_activate
	 * activate RT component.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -retval : return value for scilab process.
	 * *retval will be...
	 *  success: RTObjet_OK(0)
	 *  error  : Non-zero vlaue.
	 */
	EXPORT_FUNCTION_TYPE RTObject_activate(const int *Handle, int *retval);

	/** RTObjet_deactivate
	 * deactivate RT component.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -retval : return value for scilab process.
	 * *retval will be...
	 *  success: RTObjet_OK(0)
	 *  error  : Non-zero vlaue.
	 */
	EXPORT_FUNCTION_TYPE RTObject_deactivate(const int *Handle, int *retval);

	/** RTObjet_reset
	 * reset RT component.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -retval : return value for scilab process.
	 * *retval will be...
	 *  success: RTObjet_OK(0)
	 *  error  : Non-zero vlaue.
	 */
	EXPORT_FUNCTION_TYPE RTObject_reset(const int *Handle, int *retval);


	/** RTObjet_exit
	 * reset RT component.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -retval : return value for scilab process.
	 * *retval will be...
	 *  success: RTObjet_OK(0)
	 *  error  : Non-zero vlaue.
	 */
	EXPORT_FUNCTION_TYPE RTObject_exit(const int *Handle, int* retval);



	/** RTObjet_reset
	 * reset RT component.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -retval : return value for scilab process.
	 * If success, *retval will be...
	 *  "active", "error", "inactive", "created", and "unknown".
	 *  if failed to find RTC, *retval is "failed".
	 */
	EXPORT_FUNCTION_TYPE RTObject_getCurrentState(const int *Handle, char* retval);

	/** RTObjet_getPortNameList
	 * Get RTC's ports name list.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -retval : return value for scilab process.
	 * If success, *retval will be the names of RTC-posts. Each name is separated by RTCSCILAB_DELIMITER.
	 *  The retval will be recognized by scilab process.
	 *  if failed to find RTC, *retval is "failed".
	 */
	EXPORT_FUNCTION_TYPE RTObject_getPortNameList(const int *Handle, char* retval);

	/** RTObjet_getConfSetNameList
	 * Get RTC's configuration_set name list.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -retval : return value for scilab process.
	 * If success, *retval will be the names of RTC-configuration_sets. Each name is separated by RTCSCILAB_DELIMITER.
	 *  The retval will be recognized by scilab process.
	 *  if failed to find RTC, *retval is "failed".
	 */
	EXPORT_FUNCTION_TYPE RTObject_getConfSetNameList(const int *Handle, char* retval);

	/** RTObjet_getConfigurationValue
	 * Get RTC's configuration value.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -configurationSetName: configuration_set's name
	 *  -configurationName: configuration name.
	 *  -retval : return value for scilab process.
	 * If success, *retval will be the configuration value.
	 *  The retval will be recognized by scilab process.
	 *  if failed to find RTC, *retval is "failed".
	 */
	EXPORT_FUNCTION_TYPE RTObject_getConfigurationValue(const int *Handle, const char* configurationSetName,
		const char* configurationName, char* retval);


	/** RTObjet_getInstanceName
	 * Get RTC's instance name.
	 *  -address: IP address of naming service.
	 *  -componentName: name of component. this should include naming context.
	 *  -retval : return value for scilab process.
	 * If success, *retval will be the instance_name.
	 *  The retval will be recognized by scilab process.
	 *  if failed to find RTC, *retval is "failed".
	 */
	EXPORT_FUNCTION_TYPE RTObject_getInstanceName(const int *Handle, 
											char* retval);

};






#endif


