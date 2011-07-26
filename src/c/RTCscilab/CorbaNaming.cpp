/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : CorbaNaming.cpp
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

#define MAX_CORBA_NAMING_OBJECT 64

/**
 * Global variable / Map class object in which CorbaNaming objects are stored.
 * Key value is counter value of created CorbaNaming object.
 */
RTC::CorbaNaming* g_CorbaNamingMap[MAX_CORBA_NAMING_OBJECT] = {0, };


/**
 * Global variable / Counter value of created CorbaNaming object. 
 * This value must be incremented just after creation of CorbaNaming object.
 * This value is never decremented.
 */

int g_CorbaNamingCounter = 0;

/**
 * Global function for getting the pointer to CorbaNaming object.
 *   -address: IP address of corba naming object.
 * If success, the corba naming address will be return.
 * If error, NULL pointer.
 */
RTC::CorbaNaming* GetCorbaNaming(int id) {
	if(id < MAX_CORBA_NAMING_OBJECT) {
		return g_CorbaNamingMap[id];
	}
	return NULL;
}


/**
 * CorbaNaming_create
 *  -address : IP address of Naming server
 *  -id      : return value for rtc-scilab. 
 * If success, *id is the number of naming service object.
 * If error, *id is negative value.
 */
EXPORT_FUNCTION_TYPE CorbaNaming_create(const char* address, int* ret)
{
	if(!g_pCorbaORB) {
		*ret = -1; return;
	}

	try {
		g_CorbaNamingMap[g_CorbaNamingCounter] = new RTC::CorbaNaming(g_pCorbaORB, address);
		if(g_CorbaNamingMap[g_CorbaNamingCounter] == NULL) {
			err("Can not create CorbaNaming object.");
			*ret = -2; return;
		}
		
		*ret = g_CorbaNamingCounter;
		g_CorbaNamingCounter++;
	} catch(...) {
		err("CorbaNaming_create: unknown exception.");
		*ret = -3; return;
	}
}

/**
 * CorbaNaming_destroy
 *  -address : IP address of Naming server.
 *  -ret     : return value for scilab.
 * Before calling this, the CorbaNaming object should be created by calling
 *  CorbaNaming_create function.
 * If success, *ret will be 0. If error, negative value.
 */
EXPORT_FUNCTION_TYPE CorbaNaming_destroy(int* id, int* ret)
{
	try {
		RTC::CorbaNaming* pNaming = GetCorbaNaming(*id);
		if(pNaming == NULL) {
			*ret = -1;
		} else {
			delete pNaming;
			g_CorbaNamingMap[*id] = NULL;
			*ret = 0;
		}
	} catch(...) {
		err("CorbaNaming_destroy: unknown exception.");
		*ret = -1;
	}
}

/**
 * CorbaNaming_destroyAll
 *  -ret     : return value for scilab.
 * If success, *ret will be 0. If error, negative value.
 */
EXPORT_FUNCTION_TYPE CorbaNaming_destroyAll(int* retval)
{
	for(int i = 0;i < MAX_CORBA_NAMING_OBJECT;i++) {
		delete g_CorbaNamingMap[i];
		g_CorbaNamingMap[i] = NULL;
	}
}

/**
 * NamingResolveHelper function.
 * This function is recursively called to resolve the naming context of Corba Components.
 * This is defined in the following section.
 */
static void NamingResolveHelper(CosNaming::NamingContext_ptr pNamingContext, std::string preposition, std::vector<std::string> *stringArray);

/**
 * CorbaNaming_getRTCNameList
 *  -address : IP address of CorbaNaming object. 
 *  -componentName: RT-Component name list. Each name is separated by 
 *    the space. The scilab function will be re-recognize the strings.
 */
EXPORT_FUNCTION_TYPE CorbaNaming_getRTCNameList(int* id, char* componentName)
{
	RTC::CorbaNaming* pNaming = ::GetCorbaNaming(*id);
	if(pNaming == NULL) {
		strcpy(componentName, "failed");
		return;
	}

	try {
		std::vector<std::string> stringArray;
		NamingResolveHelper(pNaming->getRootContext(), std::string(""), &stringArray);

		std::string str;
		for(unsigned int i = 0;i < stringArray.size();i++) {
			str += stringArray[i] + RTCSCILAB_DELIMITER;
		}
		strcpy(componentName, str.c_str());
	} catch(...) {
		err("CorbaNaming_getRTCNameList: unknown exception.");
		strcpy(componentName, "failed");
	}
}


/**
 * NamingResolveHelper function.
 * This function is recursively called to resolve the naming context of Corba Components.
 *
 */
static void NamingResolveHelper(CosNaming::NamingContext_ptr pNamingContext, std::string preposition, std::vector<std::string> *stringArray) {
	CosNaming::BindingList_var blist;
	CosNaming::BindingIterator_var bitr;
	pNamingContext->list(64, blist, bitr);
	for(unsigned int i = 0;i < blist->length();i++) {
		CosNaming::Name name = blist[i].binding_name;
		//		if(blist[i].binding_type == CosNaming::BindingType::ncontext) {
		if(blist[i].binding_type == CosNaming::ncontext) {
			CORBA::Object_ptr object = pNamingContext->resolve(name);
			CosNaming::NamingContext_ptr newContext = CosNaming::NamingContext::_narrow(object);
			std::string preposition2 = preposition + (std::string)(name[0].id) + "." + (std::string)(name[0].kind) + "/";
			NamingResolveHelper(newContext, preposition2, stringArray);
		} else {
			std::string strbuf(preposition + (std::string)(name[0].id) + "." + (std::string)(name[0].kind));
			stringArray->push_back( strbuf);
		}
	}
}
