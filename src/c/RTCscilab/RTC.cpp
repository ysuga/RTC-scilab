/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : RTC.cpp
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
#include "ScilabComp.h"

//#include "RTCInterface.h"
#include "GlobalUtility.h"

#include "RTCSciOutPort.h"
#include "RTCSciInPort.h"

#define MAX_SCILAB_COMP 64

/**
 * Global variable to map object in which RTC objects are stored.
 * Key value is name (std::string) of the CorbaNaming service.
 */
ScilabComp* g_CompMap[MAX_SCILAB_COMP] = {0, };

int g_CompMapCounter = 0;
/**
 * Global function for getting the pointer to CorbaNaming object.
 *   -address: IP address of corba naming object.
 * If success, the corba naming address will be return.
 * If error, NULL pointer.
 */
inline ScilabComp* GetComponent(int handle) {
	if(handle >= MAX_SCILAB_COMP || handle < 0) return NULL;
	return g_CompMap[handle];
}


typedef std::map<std::string, RTCSciOutPortBase*> OutPortMap;
typedef std::map<std::string, RTCSciInPortBase*> InPortMap;

typedef std::pair<std::string, RTCSciOutPortBase*> OutPortPair;
typedef std::pair<std::string, RTCSciInPortBase*> InPortPair;

#define MAX_PORT 128



RTCSciOutPortBase* g_OutPortMap[MAX_PORT] = {0, };
int g_OutPortCounter = 0;

RTCSciInPortBase*  g_InPortMap[MAX_PORT] = {0, };
int g_InPortCounter = 0;

inline RTCSciOutPortBase* GetSciOutPort(const int h) {
	int handle = h % 1000;
	if(handle < 0 || handle >= MAX_PORT) return NULL;
	return g_OutPortMap[handle];
}

inline RTCSciInPortBase* GetSciInPort(const int h) {
	int handle = h % 1000;
	if(handle < 0 || handle >= MAX_PORT) return NULL;
	return g_InPortMap[handle];
}

/**
 * Clean up local memory
 */
void CleanUpSciPorts() {
	for(int i = 0;i < MAX_PORT;i++) {
		delete g_OutPortMap[i];
		g_OutPortMap[i] = NULL;
		delete g_InPortMap[i];
		g_InPortMap[i] = NULL;
	}
}

/**
 * RTC_create
 * create RTC object.
 *  -retval: return value for scilab process.
 * if success, instance_name will be set to retval.
 * if error, retval will be "failed".
 */
EXPORT_FUNCTION_TYPE RTC_create(int *retval)
{
	ScilabComp* pComp = (ScilabComp*)g_pManager->createComponent(implementation_id);
	if(pComp == NULL) {
		*retval =  -1;
	}
	g_CompMap[g_CompMapCounter] = pComp;
	*retval = g_CompMapCounter;
	g_CompMapCounter++;
}

/**
 * RTC_create
 * create RTC object.
 *  -retval: return value for scilab process.
 * if success, instance_name will be set to retval.
 * if error, retval will be "failed".
 */
EXPORT_FUNCTION_TYPE RTC_getInstanceName(const int *handle, char* retval) {
	ScilabComp* pComp = GetComponent(*handle);
	if(pComp == NULL) {
		strcpy(retval, "NULL");
		return;
	}

	
	std::string instanceName = pComp->getInstanceName();
	strcpy(retval, instanceName.c_str());
}


/**
 * RTC_destroy
 * exit & destroy RTC object.
 *  -instanceName: instance_name of RT component.
 *  -retval: return value for scilab process.
 * if success, *retval = 0, if error, retval will be no-zero value.
 */
EXPORT_FUNCTION_TYPE RTC_destroy(const int* handle,  int* retval)
{
	ScilabComp *comp = GetComponent(*handle);
	if(comp == NULL) {
		*retval = -1; return;
	}

	comp->exit();
	//g_pManager->deleteComponent(comp);
	g_CompMap[*handle] = NULL;
	*retval = 0;
}


/**
 * RTC_wait
 * wait for RTC object is executing.
 *  -instanceName: instance_name of RT component.
 *  -retval: return value for scilab process.
 * if success, *retval = 0, if error, retval will be no-zero value.
 */
EXPORT_FUNCTION_TYPE RTC_wait(const int* handle,  int* retval)
{
	ScilabComp *comp = GetComponent(*handle);
	if(comp == NULL) {
		*retval = -1; return;
	}
	//	MessageBoxA(NULL, "WAIT", "MESSAGE", MB_OK);
	
	*retval = 	comp->WaitOnExecuteStart();
}

/**
 * RTC_notify
 * wait for RTC object is executing.
 *  -instanceName: instance_name of RT component.
 *  -retval: return value for scilab process.
 * if success, *retval = 0, if error, retval will be no-zero value.
 */
EXPORT_FUNCTION_TYPE RTC_notify(const int* handle,  int* retval)
{
	ScilabComp *comp = GetComponent(*handle);
	if(comp == NULL) {
		*retval = -1; return;
	}

	comp->NotifyCalcEnd();
	*retval = 0;
}


/**
 * RTC_notify
 * wait for RTC object is executing.
 *  -instanceName: instance_name of RT component.
 *  -retval: return value for scilab process.
 * if success, *retval = 0, if error, retval will be no-zero value.
 */
EXPORT_FUNCTION_TYPE RTC_startSync(const int* handle,  int* retval)
{
	ScilabComp* comp = GetComponent(*handle);
	if(comp == NULL) {
		*retval = -1; return;
	}

	comp->StartSynchronize();
	*retval = 0;
}


/**
 * RTC_stopSync
 * wait for RTC object is executing.
 *  -instanceName: instance_name of RT component.
 *  -retval: return value for scilab process.
 * if success, *retval = 0, if error, retval will be no-zero value.
 */
EXPORT_FUNCTION_TYPE RTC_stopSync(const int* handle,  int* retval)
{
	ScilabComp *comp = GetComponent(*handle);
	if(comp == NULL) {
		*retval = -1; return;
	}

	comp->StopSynchronize();
	*retval = 0;
}



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
												int* retval)
{
	ConvertDmyStr(Name);
	
	ScilabComp *comp = GetComponent(*handle);
	if(comp == NULL) {
		*retval = -1; return;
	}

	std::string typeCode = Type; // To use operator==
	RTCSciOutPortBase* pPort = NULL;
	int offset = 0;

	try {
		if(typeCode == "TimedLong") {
			pPort = new RTCSciOutPort<TimedLong, long>(Name);
			offset = 1000;
		} else if(typeCode == "TimedLongSeq") {
			pPort = new RTCSciSeqOutPort<TimedLongSeq, long>(Name);
			offset = 1000;
		} else if(typeCode == "TimedFloat") {
			pPort = new RTCSciOutPort<TimedFloat, float>(Name);
			offset = 2000;
		} else if(typeCode == "TimedFloatSeq") {
			pPort = new RTCSciSeqOutPort<TimedFloatSeq, float>(Name);
			offset = 2000;
		} else if(typeCode == "TimedDouble") {
			pPort = new RTCSciOutPort<TimedDouble, double>(Name);
			offset = 3000;
		} else if(typeCode == "TimedDoubleSeq") {
			pPort = new RTCSciSeqOutPort<TimedDoubleSeq, double>(Name);
			offset = 3000;
		} else if(typeCode == "TimedBoolean") {
			pPort = new RTCSciOutPort<TimedBoolean, long>(Name);
			offset = 4000;
		} else if(typeCode == "TimedBooleanSeq") {
			pPort = new RTCSciSeqOutPort<TimedBooleanSeq, long>(Name);
			offset = 4000;
		} else {
			err("Unknown type code %s.", typeCode.c_str());
			*retval = -2; return;
		}

		pPort->SetScilabComp(comp);
		pPort->SetOwnerHandle(*handle);
		comp->addOutPort(Name, *pPort);
		g_OutPortMap[g_OutPortCounter] = pPort;
		*retval = g_OutPortCounter + offset;
		pPort->SetSelfHandle(*retval);

		g_OutPortCounter++;
	} catch (...) {
		err("Unknown exception was thrown.");
		*retval = -3;
	}
}

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
											   int* retval)
{
	ConvertDmyStr(Name);

	ScilabComp *comp = GetComponent(*handle);
	if(comp == NULL) {
		*retval = -1; return;
	}

	std::string typeCode = Type;
	RTCSciInPortBase* pPort = NULL;
	int offset;
	try {
		if(typeCode == "TimedLong") {
			pPort = new RTCSciInPort<TimedLong, long>(Name);
			offset = 1000;
		} else if(typeCode == "TimedLongSeq") {
			pPort = new RTCSciSeqInPort<TimedLongSeq, long>(Name);
			offset = 1000;
		} else if(typeCode == "TimedFloat") {
			pPort = new RTCSciInPort<TimedFloat, float>(Name);
			offset = 2000;
		} else if(typeCode == "TimedFloatSeq") {
			pPort = new RTCSciSeqInPort<TimedFloatSeq, float>(Name);
			offset = 2000;
		} else if(typeCode == "TimedDouble") {
			pPort = new RTCSciInPort<TimedDouble, double>(Name);
			offset = 3000;
		} else if(typeCode == "TimedDoubleSeq") {
			pPort = new RTCSciSeqInPort<TimedDoubleSeq, double>(Name);
			offset = 3000;
		} else if(typeCode == "TimedBoolean") {
			pPort = new RTCSciInPort<TimedBoolean, long>(Name);
			offset = 4000;
		} else if(typeCode == "TimedBooleanSeq") {
			pPort = new RTCSciSeqInPort<TimedBooleanSeq, long>(Name);
			offset = 4000;
		} else {
			err("Unknown type code %s.", typeCode.c_str());
			*retval = -2; return;
		}

		pPort->SetScilabComp(comp);
		pPort->SetOwnerHandle(*handle);
		comp->addInPort(Name, *pPort);
		g_InPortMap[g_InPortCounter] = pPort;
		
		*retval = g_InPortCounter + offset;
		pPort->SetSelfHandle(*retval);
		g_InPortCounter++;
	} catch (...) {
		err("Unknown exception was thrown.");
		*retval = -3;
	}
}

EXPORT_FUNCTION_TYPE RTC_getOutPort(const int* handle,
										const char* Name,
										int* retval)
{
	*retval = -1;
	ConvertDmyStr(Name);

	for(int i = 0;i < ::g_OutPortCounter;i++) {
		if(g_OutPortMap[i] != NULL) {
			if(g_OutPortMap[i]->GetName()==Name && g_OutPortMap[i]->GetOwnerHandle()==*handle) {
				*retval = g_OutPortMap[i]->GetSelfHandle();
				return;
			}
		}
	}
}

EXPORT_FUNCTION_TYPE RTC_getInPort(const int* handle,
										const char* Name,
										int* retval)
{
	*retval = -1;
	ConvertDmyStr(Name);

	for(int i = 0;i < ::g_InPortCounter;i++) {
		if(g_InPortMap[i] != NULL) {
			if(g_InPortMap[i]->GetName()==Name && g_InPortMap[i]->GetOwnerHandle()==*handle) {
				*retval = g_InPortMap[i]->GetSelfHandle();
				return;
			}
		}
	}
}

EXPORT_FUNCTION_TYPE RTC_getOutPortType(const int* handle,
										char* retval)
{
	RTCSciOutPortBase* port = ::GetSciOutPort(*handle);
	if(port != NULL) {
		std::string& typeCode = port->GetTypeCode();
		strcpy(retval, typeCode.c_str());
	}
}


EXPORT_FUNCTION_TYPE RTC_getInPortType(const int* handle,
										char* retval)
{
	RTCSciInPortBase* port = ::GetSciInPort(*handle);
	if(port != NULL) {
		std::string& typeCode = port->GetTypeCode();
		strcpy(retval, typeCode.c_str());
	}

}

/**
 * RTC_isAlive
 * check if RTC instance is alive or not.
 *  -instanceName: instance_name of RT component.
 *  -retval: return value for scilab process.
 * if alive, *retval = non-zero (TRUE) , if error, retval is zero (FALSE).
 */
EXPORT_FUNCTION_TYPE RTC_isAlive(const int* handle, int* retval)
{
	if(GetComponent(*handle) != NULL) {
	  *retval = 1;//TRUE;
	} else {
	  *retval = 0;//FALSE;
	}
}

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
										   int* retval)
{
	RTCSciInPortBase* pPort = GetSciInPort(*ahandle);
	if(pPort == NULL) {
		*retval = -1;return;
	}

	ScilabComp *comp = GetComponent(*handle);
	if(comp == NULL) {
		*retval = -2;return;
	}
	
	comp->deletePort(pPort->GetPort());

	delete g_InPortMap[*handle];
	g_InPortMap[*handle] = NULL;
	*retval= 0;
}


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
										   int* retval)
{
	RTCSciOutPortBase* pPort = GetSciOutPort(*ahandle);
	if(pPort == NULL) {
		*retval = -1;return;
	}

	ScilabComp *comp = GetComponent(*handle);
	if(comp == NULL) {
		*retval = -2;return;
	}
	
	comp->deletePort(pPort->GetPort());

	delete g_OutPortMap[*handle];
	g_OutPortMap[*handle] = NULL;
	*retval= 0;
}


/**
 * RTC_writePort**
 *  -portName : name of DataPort
 *  -arg: data
 *  -length: data size.
 *  -retval: return value.
 * If success, *retval is positive value (written size).
 * if failed, *retval is negative.
 */
EXPORT_FUNCTION_TYPE RTC_writePortDouble(const int* handle ,
												double* arg,
												const int* length, 
												int* retval)
{

	RTCSciOutPortBase* pPort = GetSciOutPort(*handle);
	if(pPort == NULL) {
		*retval = -1; return;
	}
	*retval = pPort->Write(arg, *length);
}

/**
 * RTC_writePort**
 *  -portName : name of DataPort
 *  -arg: data
 *  -length: data size.
 *  -retval: return value.
 * If success, *retval is positive value (written size).
 * if failed, *retval is negative.
 */
EXPORT_FUNCTION_TYPE RTC_writePortFloat(const int *handle,
											   float* arg,
											   const int* length,
											   int* retval)
{
	RTCSciOutPortBase* pPort = GetSciOutPort(*handle);
	if(pPort == NULL) {
		*retval = -1; return;
	}
	*retval = pPort->Write(arg, *length);
}

/**
 * RTC_writePort**
 *  -portName : name of DataPort
 *  -arg: data
 *  -length: data size.
 *  -retval: return value.
 * If success, *retval is positive value (written size).
 * if failed, *retval is negative.
 */
EXPORT_FUNCTION_TYPE RTC_writePortLong(const int* handle,
											  int* arg,
											  const int* length,
											  int* retval)
{
	RTCSciOutPortBase* pPort = GetSciOutPort(*handle);
	if(pPort == NULL) {
		*retval = -1; return;
	}
	*retval = pPort->Write(arg, *length);
}

/**
 * RTC_writePort**
 *  -portName : name of DataPort
 *  -arg: data
 *  -length: data size.
 *  -retval: return value.
 * If success, *retval is positive value (written size).
 * if failed, *retval is negative.
 */
EXPORT_FUNCTION_TYPE RTC_writePortBoolean(const int* handle,
											  int* arg,
											  const int* length,
											  int* retval)
{
	RTCSciOutPortBase* pPort = GetSciOutPort(*handle);
	if(pPort == NULL) {
		*retval = -1; return;
	}
	*retval = pPort->Write(arg, *length);
}



/**
 * RTC_pollInPort
 * check the data buffer
 *  -portName : name of DataPort
 *  -retval: return value.
 * If buffer has data, *retval is non zero.
 * if buffer does not have any data, *retval is zero.
 * if failed, *retval is zero.
 */
EXPORT_FUNCTION_TYPE RTC_pollInPort(const int* handle , int* retval)
{
	RTCSciInPortBase* pPort = GetSciInPort(*handle);
	if(pPort == NULL) {
		*retval = 0; return;
	}
	*retval = pPort->Poll();
}

/**
 * RTC_readInPort
 * read the data buffer
 *  -portName : name of DataPort
 *  -retval: return value.
 * If success, *retval is written data size
 * if failed, *retval is negative.
 */
EXPORT_FUNCTION_TYPE RTC_readInPort(const int* handle, int* retval)
{
	RTCSciInPortBase* pPort = GetSciInPort(*handle);
	if(pPort == NULL) {
		*retval = -1; return;
	}
	*retval = pPort->Read();
}

/**
 * RTC_readPort**
 *  -portName : name of DataPort
 *  -length: data size.
 *  -retval: return value.
 * *retval is read data.
 */
EXPORT_FUNCTION_TYPE RTC_readPortDouble(const int* handle, const int* length, double* retval)
{
	RTCSciInPortBase* pPort = GetSciInPort(*handle);
	if(pPort == NULL) {
		*retval = -1; return;
	}
	pPort->Get(retval, *length);
}

/**
 * RTC_readPort**
 *  -portName : name of DataPort
 *  -length: data size.
 *  -retval: return value.
 * *retval is read data.
 */
EXPORT_FUNCTION_TYPE RTC_readPortFloat(const int* handle, const int* length, float* retval)
{
	RTCSciInPortBase* pPort = GetSciInPort(*handle);
	if(pPort == NULL) {
		*retval = -1; return;
	}
	pPort->Get(retval, *length);
}

/**
 * RTC_readPort**
 *  -portName : name of DataPort
 *  -length: data size.
 *  -retval: return value.
 * *retval is read data.
 */
EXPORT_FUNCTION_TYPE RTC_readPortLong(const int* handle, const int* length, int* retval)
{
	RTCSciInPortBase* pPort = GetSciInPort(*handle);
	if(pPort == NULL) {
		*retval = -1; return;
	}
	pPort->Get(retval, *length);
}

/**
 * RTC_readPort**
 *  -portName : name of DataPort
 *  -length: data size.
 *  -retval: return value.
 * *retval is read data.
 */
EXPORT_FUNCTION_TYPE RTC_readPortBoolean(const int* handle, const int* length, int* retval)
{
	RTCSciInPortBase* pPort = GetSciInPort(*handle);
	if(pPort == NULL) {
		*retval = -1; return;
	}
	pPort->Get(retval, *length);
}
