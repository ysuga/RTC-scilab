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
#include "GlobalUtility.h"



RTObjectStruct *RTObjectMap[MAX_RT_OBJECT] = {0, };

int RTObjectCounter = 0;

/** RTObjet_create
 * create RT component reference.
 *  -address: IP address of naming service.
 *  -componentName: name of component. this should include naming context.
 *  -retval : return value for scilab process.
 * *retval will be...
 *  success: RTC_OK(0)
 *  error  : Non-zero vlaue.
 */
EXPORT_FUNCTION_TYPE RTObject_create(const int *CorbaNamingID, const char* componentName, int* retval)
{
	RTObjectMap[RTObjectCounter] = new RTObjectStruct();
	RTObjectMap[RTObjectCounter]->namingID = *CorbaNamingID;
	RTObjectMap[RTObjectCounter]->componentName = componentName;
	*retval = RTObjectCounter;
	RTObjectCounter++;
}

/** RTObjet_destroy
 * destroy RT component reference.
 *  -address: IP address of naming service.
 *  -componentName: name of component. this should include naming context.
 *  -retval : return value for scilab process.
 * *retval will be...
 *  success: RTC_OK(0)
 *  error  : Non-zero vlaue.
 */
EXPORT_FUNCTION_TYPE RTObject_destroy(const int *componentID, int* retval)
{
	delete RTObjectMap[*componentID];
	RTObjectMap[*componentID] = NULL;
	*retval = 0;
}


/** RTObjet_activate
 * activate RT component.
 *  -address: IP address of naming service.
 *  -componentName: name of component. this should include naming context.
 *  -retval : return value for scilab process.
 * *retval will be...
 *  success: RTC_OK(0)
 *  error  : Non-zero vlaue.
 */
EXPORT_FUNCTION_TYPE RTObject_activate(const int *Handle, int* retval)
{
	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer failed.");
		*retval = -1; return;
	}
	corbaConsumer.setObject(object);
	
	RTC::ExecutionContextList_var ec = corbaConsumer->get_owned_contexts();
	*retval = ec[0]->activate_component(RTC::RTObject::_duplicate(corbaConsumer._ptr()));
}

/** RTObjet_deactivate
 * deactivate RT component.
 *  -address: IP address of naming service.
 *  -componentName: name of component. this should include naming context.
 *  -retval : return value for scilab process.
 * *retval will be...
 *  success: RTObjet_OK(0)
 *  error  : Non-zero vlaue.
 */
EXPORT_FUNCTION_TYPE RTObject_deactivate(const int *Handle, int* retval)
{
	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer");
		*retval = -1; return;
	}
	corbaConsumer.setObject(object);

	RTC::ExecutionContextList_var ec = corbaConsumer->get_owned_contexts();
	*retval = ec[0]->deactivate_component(RTC::RTObject::_duplicate(corbaConsumer._ptr()));
}


/** RTObjet_reset
 * reset RT component.
 *  -address: IP address of naming service.
 *  -componentName: name of component. this should include naming context.
 *  -retval : return value for scilab process.
 * *retval will be...
 *  success: RTObjet_OK(0)
 *  error  : Non-zero vlaue.
 */
EXPORT_FUNCTION_TYPE RTObject_reset(const int *Handle, int* retval)
{
	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer failed.");
		*retval = -1; return;
	}
	corbaConsumer.setObject(object);

	RTC::ExecutionContextList_var ec = corbaConsumer->get_owned_contexts();
	*retval = ec[0]->reset_component(RTC::RTObject::_duplicate(corbaConsumer._ptr()));
}


/** RTObjet_exit
 * deactivate RT component.
 *  -address: IP address of naming service.
 *  -componentName: name of component. this should include naming context.
 *  -retval : return value for scilab process.
 * *retval will be...
 *  success: RTObjet_OK(0)
 *  error  : Non-zero vlaue.
 */
EXPORT_FUNCTION_TYPE RTObject_exit(const int *Handle, int* retval)
{
	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer failed.");
		*retval = -1; return;
	}
	corbaConsumer.setObject(object);

	RTC::ExecutionContextList_var ec = corbaConsumer->get_owned_contexts();
	*retval = ec[0]->remove_component(RTC::RTObject::_duplicate(corbaConsumer._ptr()));
	corbaConsumer->exit();


}


/** RTObjet_reset
 * reset RT component.
 *  -address: IP address of naming service.
 *  -componentName: name of component. this should include naming context.
 *  -retval : return value for scilab process.
 * If success, *retval will be...
 *  "active", "error", "inactive", "created", and "unknown".
 *  if failed to find RTC, *retval is "failed".
 */
EXPORT_FUNCTION_TYPE RTObject_getCurrentState(const int *Handle,
										 char* retval)
{
	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer failed.");
		*retval = -1; return;
	}
	corbaConsumer.setObject(object);

	RTC::ExecutionContextList_var ec = corbaConsumer->get_owned_contexts();
	RTC::LifeCycleState ret = ec[0]->get_component_state(RTC::RTObject::_duplicate(corbaConsumer._ptr()));
	if(ret == RTC::ACTIVE_STATE) strcpy(retval, "active");
	else if(ret == RTC::CREATED_STATE) strcpy(retval, "created");
	else if(ret == RTC::INACTIVE_STATE) strcpy(retval, "inactive");
	else if(ret == RTC::ERROR_STATE) strcpy(retval, "error");
	else strcpy(retval, "unknown");
}


/** RTObjet_getPortNameList
 * Get RTC's ports name list.
 *  -address: IP address of naming service.
 *  -componentName: name of component. this should include naming context.
 *  -retval : return value for scilab process.
 * If success, *retval will be the names of RTC-posts. Each name is separated by space.
 *  The retval will be recognized by scilab process.
 *  if failed to find RTC, *retval is "failed".
 */
EXPORT_FUNCTION_TYPE RTObject_getPortNameList(const int *Handle,
										 char* retval)
{
	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer ");
		strcpy(retval, "failed"); return;
	}
	corbaConsumer.setObject(object);

	RTC::PortServiceList *plist = corbaConsumer->get_ports();
	int length = plist->length();
	
	std::string str;
	for(unsigned int i = 0;i < plist->length();i++) {
		str += (std::string)((*plist)[i]->get_port_profile()->name) + RTCSCILAB_DELIMITER;
	}
	strcpy(retval, str.c_str());
}

/** RTObjet_getConfSetNameList
 * Get RTC's configuration_set name list.
 *  -address: IP address of naming service.
 *  -componentName: name of component. this should include naming context.
 *  -retval : return value for scilab process.
 * If success, *retval will be the names of RTC-configuration_sets. Each name is separated by space.
 *  The retval will be recognized by scilab process.
 *  if failed to find RTC, *retval is "failed".
 */
EXPORT_FUNCTION_TYPE RTObject_getConfSetNameList(const int *Handle, 
											char* retval)
{
	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer failed.");
		strcpy(retval, "failed"); return;
	}
	corbaConsumer.setObject(object);

	SDOPackage::Configuration_ptr pConf = corbaConsumer->get_configuration();
	SDOPackage::ConfigurationSetList *pConfSetList = pConf->get_configuration_sets();
	std::string str;
	for(unsigned int i = 0;i < pConfSetList->length();i++) {
		str += (std::string)((*pConfSetList)[i].id) + RTCSCILAB_DELIMITER ;
	}
	strcpy(retval, str.c_str());
}

EXPORT_FUNCTION_TYPE RTObject_getInstanceName(const int *Handle, 
											char* retval)
{
	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer failed.");
		strcpy(retval, "failed"); return;
	}
	corbaConsumer.setObject(object);

	std::string str;
	str = corbaConsumer->get_component_profile()->instance_name;

	strcpy(retval, str.c_str());
}

