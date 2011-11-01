/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : Port.cpp
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


RTPortStruct *RTPortMap[MAX_RT_DATAPORT] = {0, };

int RTPortCounter = 0;

EXPORT_FUNCTION_TYPE Port_create(const int *Handle, const char* portName, int* retval)
{
	ConvertDmyStr(portName);

	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer failed.");
		*retval = -1; return;
	}
	corbaConsumer.setObject(object);

	if(getNamedPort(corbaConsumer->get_ports(), portName) == NULL) {
		*retval= -1;
		return;
	}

	RTPortMap[RTPortCounter] = new RTPortStruct();
	RTPortMap[RTPortCounter]->Name = portName;
	RTPortMap[RTPortCounter]->RTObjectId = *Handle;
	*retval = RTPortCounter;
	RTPortCounter++;
}

EXPORT_FUNCTION_TYPE Port_destroy(const int* Handle, int* retval)
{
	delete RTPortMap[*Handle];
	RTPortMap[*Handle] = NULL;
	*retval = 0;
}

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
									 char* retval)
{
	RTC::PortService_ptr pPort = GetPort(*Handle);
	if(pPort == NULL) {
		strcpy(retval, "NULL");
		return;
	}

	RTC::PortProfile* pPortProfile = pPort->get_port_profile();

	std::string str;
	coil::Properties props = NVUtil::toProperties(pPortProfile->properties);
	for(int j = 0;j < props.size();j++) {
		str += pPortProfile->properties[j].name;
		str += RTCSCILAB_DELIMITER;
		str += props[((std::string)pPortProfile->properties[j].name).c_str()];
		str += RTCSCILAB_DELIMITER;
	}
	strcpy(retval, str.c_str());
	return;
}


EXPORT_FUNCTION_TYPE Port_getName(const int *Handle,
									 char* retval)
{
	RTPortStruct* pPort = GetRTPort(*Handle);
	if(pPort == NULL) {
		strcpy(retval, "NULL");
		return;
	}

	strcpy(retval, pPort->Name.c_str());
}

