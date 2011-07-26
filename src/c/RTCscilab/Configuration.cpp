/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : Configuration.cpp
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
													  char* confNameList)
{
	ConvertDmyStr(confSetName);
	info("ConfigurationSet_getConfNameList(%s, %s, %s)", address, componentName, confSetName);

	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer (addr=%s, name=%s) failed.", address, componentName);
		strcpy(confNameList, "failed");return;
	}
	corbaConsumer.setObject(object);


	SDOPackage::Configuration_ptr pConf = corbaConsumer->get_configuration();
	SDOPackage::ConfigurationSetList *pConfSetList = pConf->get_configuration_sets();
	for(unsigned int i = 0;i < pConfSetList->length();i++) {
		info("persing confset(%s)", (*pConfSetList)[i].id);
		if( ((std::string)((*pConfSetList)[i].id)) == confSetName ){
			std::string str;
			coil::Properties props = NVUtil::toProperties((*pConfSetList)[i].configuration_data);
			for(int j = 0;j < props.size();j++) {
				str += (*pConfSetList)[i].configuration_data[j].name;
				str += RTCSCILAB_DELIMITER;
				str += RTCSCILAB_DMYSTR + props[((std::string)(*pConfSetList)[i].configuration_data[j].name).c_str()];
				str += RTCSCILAB_DELIMITER;
				// Memo: 2010/02/28
				// The RTCSCILAB_DMYSTR is strictly needed because the property allows empty value.
				// if empty value is passed to scilab, error occurs.
				// This error occurs because I use space to separate values and names of property.
				// I guess if I use "," or ";" for delimiter, the error will be erased.
			}
			strcpy(confNameList, str.c_str());
			info("match.");
			return;
		}
	}

	strcpy(confNameList, "failed");
}



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
EXPORT_FUNCTION_TYPE Configuration_configure(const int *Handle,
											 const char* confSetName,
											 const char* confName, 
											 const char* confValue,
										     int* retval)
{
	ConvertDmyStr(confSetName);
	ConvertDmyStr(confName);
	ConvertDmyStr(confValue);

	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer (addr=%s, name=%s) failed.", address, componentName);
		*retval = -1; return;
	}
	corbaConsumer.setObject(object);

	SDOPackage::Configuration_ptr pConf = corbaConsumer->get_configuration();
	SDOPackage::ConfigurationSetList *pConfSetList = pConf->get_configuration_sets();
	for(unsigned int i = 0;i < pConfSetList->length();i++) {
		if( ((std::string)((*pConfSetList)[i].id)) == confSetName ){
			SDOPackage::ConfigurationSet* pConfSet = pConf->get_configuration_set(confSetName);
			std::string str;
			coil::Properties props = NVUtil::toProperties(pConfSet->configuration_data);
			for(int j = 0;j < props.size();j++) {
				if( ((std::string)(pConfSet->configuration_data[j].name)) == confName) {
					//props.removeNode(confName);
					props.setProperty(confName, confValue);
					RTC::NVList list;
					NVUtil::copyFromProperties(list, props);

					pConfSet->configuration_data = list;
					pConf->set_configuration_set_values(*pConfSet);
					pConf->activate_configuration_set(confSetName);
					*retval = 0;return;
				}
			}
		}
	}

	err("Failed to find configuration(%s) in RTC(%s)", confName, componentName);
	*retval = -2;
}

/** Configuration_getValue
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
EXPORT_FUNCTION_TYPE Configuration_getValue(const int *Handle,
											   const char* confSetName,
											   const char* confName,
											   char* retval)
{
	ConvertDmyStr(confSetName);
	ConvertDmyStr(confName);

	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	CORBA::Object_ptr object;
	if((object=Resolve(*Handle)) == 0) {
		err("Resolving Corba Consumer (addr=%s, name=%s) failed.", address, componentName);
		strcpy(retval, "failed"); return;
	}
	corbaConsumer.setObject(object);

	strcpy(retval, "");

	SDOPackage::Configuration_ptr pConf = corbaConsumer->get_configuration();
	SDOPackage::ConfigurationSetList *pConfSetList = pConf->get_configuration_sets();

	for(unsigned int i = 0;i < pConfSetList->length();i++) {
		if ( (std::string)((*pConfSetList)[i].id) == confSetName ) {
			coil::Properties props = NVUtil::toProperties((*pConfSetList)[i].configuration_data);
			for(int j = 0;j < props.size();j++) {
				if( ((std::string)(*pConfSetList)[i].configuration_data[j].name) == confName) {
					std::string strbuf = RTCSCILAB_DMYSTR + props[((std::string)(*pConfSetList)[i].configuration_data[j].name).c_str()];
				
					strcpy(retval, strbuf.c_str());
					return;
				}
			}
		}
	}
}
