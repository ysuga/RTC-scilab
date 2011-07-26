/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : RTC.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */
#ifndef SCILABCOMPINTERFACE_HEADER_INCLUDED
#define SCILABCOMPINTERFACE_HEADER_INCLUDED


#ifdef __cplusplus
extern "C" {
#endif
	/**
	 * RTC_create
	 * create RTC object.
	 *  -retval: return value for scilab process.
	 * if success, instance_name will be set to retval.
	 * if error, retval will be "failed".
	 */
	EXPORT_FUNCTION_TYPE RTC_create(int* retval);


	/**
	 * RTC_destroy
	 * destroy & exit RTC object.
	 *  -retval: return value for scilab process.
	 * if success, instance_name will be zero.
	 * if error, non-zero value.
	 */
	EXPORT_FUNCTION_TYPE RTC_destroy(const int* handle, int* retval);

	/**
	 * RTC_wait
	 * wait for  RTC object's onExecute function
	 *  -retval: return value for scilab process.
	 * if success, instance_name will be zero.
	 * if error, non-zero value.
	 */
	EXPORT_FUNCTION_TYPE RTC_wait(const int* handle, int* retval);


	/**
	 * RTC_notify
	 * notify for RTC object.
	 *  -retval: return value for scilab process.
	 * if success, instance_name will be zero.
	 * if error, non-zero value.
	 */
	EXPORT_FUNCTION_TYPE RTC_notify(const int* handle, int* retval);

	/**
	 * RTC_startSync
	 * notify for RTC object.
	 *  -retval: return value for scilab process.
	 * if success, instance_name will be zero.
	 * if error, non-zero value.
	 */
	EXPORT_FUNCTION_TYPE RTC_startSync(const int* handle, int* retval);

	/**
	 * RTC_stopSync
	 * notify for RTC object.
	 *  -retval: return value for scilab process.
	 * if success, instance_name will be zero.
	 * if error, non-zero value.
	 */
	EXPORT_FUNCTION_TYPE RTC_stopSync(const int* handle, int* retval);



	/**
	 * RTC_registerOutPort
	 * register OutPort to RTC object.
	 *  -instanceName: instance_name of RT component.
	 *  -Type: type_name of DataPort
	 *  -Name: name of DataPort
	 *  -retval: return value for scilab process.
	 * if success, *retval = 0, if error, retval will be no-zero value.
	 */	
	EXPORT_FUNCTION_TYPE RTC_registerOutPort(const int* handle,
													const char* Type, 
													const char* Name,
													int* retval);

	/**
	 * RTC_registerInPort
	 * register InPort to RTC object.
	 *  -instanceName: instance_name of RT component.
	 *  -Type: type_name of DataPort
	 *  -Name: name of DataPort
	 *  -retval: return value for scilab process.
	 * if success, *retval = 0, if error, retval will be no-zero value.
	 */
	EXPORT_FUNCTION_TYPE RTC_registerInPort(const int* handle,
												   const char* Type,
												   const char* Name,
												   int* retval);

	/**
	 * RTC_create
	 * create RTC object.
	 *  -retval: return value for scilab process.
	 * if success, instance_name will be set to retval.
	 * if error, retval will be "failed".
	 */
	EXPORT_FUNCTION_TYPE RTC_getOutPort(const int* handle,
										const char* Name,
										int* retval);
	/**
	 * RTC_create
	 * create RTC object.
	 *  -retval: return value for scilab process.
	 * if success, instance_name will be set to retval.
	 * if error, retval will be "failed".
	 */
	EXPORT_FUNCTION_TYPE RTC_getInPort(const int* handle,
										const char* Name,
										int* retval);

	/**
	 * RTC_getInstanceName
	 * create RTC object.
	 *  -retval: return value for scilab process.
	 * if success, instance_name will be set to retval.
	 * if error, retval will be "failed".
	 */
	EXPORT_FUNCTION_TYPE RTC_getInstanceName(const int* handle,
										char* retval);



	/**
	 * RTC_create
	 * create RTC object.
	 *  -retval: return value for scilab process.
	 * if success, instance_name will be set to retval.
	 * if error, retval will be "failed".
	 */
	EXPORT_FUNCTION_TYPE RTC_getOutPortType(const int* handle,
										char* retval);
	/**
	 * RTC_create
	 * create RTC object.
	 *  -retval: return value for scilab process.
	 * if success, instance_name will be set to retval.
	 * if error, retval will be "failed".
	 */
	EXPORT_FUNCTION_TYPE RTC_getInPortType(const int* handle,
											char* retval);


	/**
	 * RTC_deletePortByName
	 * delete Port to RTC object.
	 *  -instanceName: instance_name of RT component.
	 *  -Name: name of DataPort
	 *  -retval: return value for scilab process.
	 * if success, *retval = 0, if error, retval will be no-zero value.
	 */
	EXPORT_FUNCTION_TYPE RTC_deleteOutPort(const int* handle,
											const int* ahandle,
													 int* retval);


	/**
	 * RTC_deletePortByName
	 * delete Port to RTC object.
	 *  -instanceName: instance_name of RT component.
	 *  -Name: name of DataPort
	 *  -retval: return value for scilab process.
	 * if success, *retval = 0, if error, retval will be no-zero value.
	 */
EXPORT_FUNCTION_TYPE RTC_deleteInPort(const int* handle,
									  const int* ahandle,
										   int* retval);

	/**
	 * RTC_isAlive
	 * check if RTC instance is alive or not.
	 *  -instanceName: instance_name of RT component.
	 *  -retval: return value for scilab process.
	 * if alive, *retval = non-zero (TRUE) , if error, retval is zero (FALSE).
	 */
	EXPORT_FUNCTION_TYPE RTC_isAlive(const int* handle, int* retval);

	/**
	 * RTC_writePort**
	 *  -portName : name of DataPort
	 *  -arg: data
	 *  -length: data size.
	 *  -retval: return value.
	 * If success, *retval is positive value (written size).
	 * if failed, *retval is negative.
	 */
	EXPORT_FUNCTION_TYPE RTC_writePortDouble(const int* handle,
													double* arg,
													const int* length,
													int* retval);
	EXPORT_FUNCTION_TYPE RTC_writePortFloat( const int* handle,
													float* arg, 
													const int* length, 
													int* retval);
	EXPORT_FUNCTION_TYPE RTC_writePortLong(  const int* handle,
													int* arg,
													const int* length,
													int* retval);
	EXPORT_FUNCTION_TYPE RTC_writePortBoolean(  const int* handle,
													int* arg,
													const int* length,
													int* retval);
	/**
	 * RTC_pollInPort
	 * check the data buffer
	 *  -portName : name of DataPort
	 *  -retval: return value.
	 * If buffer has data, *retval is non zero.
	 * if buffer does not have any data, *retval is zero.
	 * if failed, *retval is zero.
	 */
	EXPORT_FUNCTION_TYPE RTC_pollInPort(const int* handle, int* retval);

	/**
	 * RTC_readInPort
	 * read the data buffer
	 *  -portName : name of DataPort
	 *  -retval: return value.
	 * If success, *retval is written data size
	 * if failed, *retval is negative.
	 */
	EXPORT_FUNCTION_TYPE RTC_readInPort(const int* handle, int* retval);

	/**
	 * RTC_readPort**
	 *  -portName : name of DataPort
	 *  -length: data size.
	 *  -retval: return value.
	 * *retval is read data.
	 */
	EXPORT_FUNCTION_TYPE RTC_readPortDouble(const int* handle, const int* length, double* retval);
	EXPORT_FUNCTION_TYPE RTC_readPortFloat(const int* handle, const int* length, float* retval);
	EXPORT_FUNCTION_TYPE RTC_readPortLong(const int* handle, const int* length, int* retval);
	EXPORT_FUNCTION_TYPE RTC_readPortBoolean(const int* handle, const int* length, int* retval);

#ifdef __cplusplus
};
#endif



#endif


