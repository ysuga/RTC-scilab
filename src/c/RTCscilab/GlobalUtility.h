/**
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */
#pragma once


/**
 * std::map is used to store datas.
 */
#include <map>

/**
 * For debuggin.
 * Caution! This uses C99 Extention macro.
 */
#ifdef _DEBUG
#include <stdio.h>
#define dbg(format, ...) do{fprintf(stderr, __FILE__ ":DBG:" format "\n" , __VA_ARGS__); }while(0)
#else
#define dbg(format, ...)
#endif

/**
 * For debuggin.
 * Caution! This uses C99 Extention macro.
 */
#ifdef _DEBUG
#include <stdio.h>
#define err(format, ...) do{fprintf(stderr, __FILE__ ":ERR:" format "\n" , __VA_ARGS__); }while(0)
#else
#define err(format, ...)
#endif


/**
 * For debuggin.
 * Caution! This uses C99 Extention macro.
 */
#ifdef _DEBUG
#include <stdio.h>
#define info(format, ...) do{fprintf(stderr, __FILE__ ":INFO:" format "\n" , __VA_ARGS__); }while(0)
#else
#define info(format, ...)
#endif


/**
 * RTCSCILAB_DMYSTR is for converting the string argument to non-specialized keword.
 * In scilab DLL loading mechanism, "out" is specialized keyword when calling the 
 * exported function. But in using RT middleware, the "out" is commonly used as a
 * name of DataPort. 
 * RTCSCILAB_DMYSTR is added on the head of the string type argument to avoid from
 * matching specialized keyword.
 *
 */
#define RTCSCILAB_DMYSTR "___"

/**
 * RTCSCILAB_DMYSTR_LENGTH is used in ConvertDmyStr macro.
 * See below.
 */
#define RTCSCILAB_DMYSTR_LENGTH 3

/**
 * ConvertDmyStr macro erases RTCSCILAB_DMYSTR from the string type argument 
 */
#define ConvertDmyStr(x) x = x + RTCSCILAB_DMYSTR_LENGTH


/**
 * This number is used as the string length of implementation_id and type_name.
 * See ScilabComp.cpp
 */
#define RTCSCILAB_MAXID 64

/**
 * This value should be used when returning string list to scilab process.
 * I think the delimiter should be ";" or "," rather than space. 2010/02/28
 */
#define RTCSCILAB_DELIMITER " "




/**
 * implementation_id
 * This variable will be used in registering the RTC (See ScilabComp.cpp).
 * The implementation ID will be the identifier which will be used
 * in creating the RTC using RTC::Manager.
 */
extern char implementation_id[];

/**
 * type_name
 * This variable will be used in registering the RTC (See ScilabComp.cpp).
 * This type_name will be the default instance name of RTC.
 * The type_name will be defined in the Manager_create function.
 */
extern char type_name[];



/**
 * Global Pointer to Manager object.
 * This will be used to create RT Components.
 */
extern RTC::Manager *g_pManager;

/**
 * Global pointer to ORB object.
 * This will be used to create Corba Naming Service object.
 */
extern CORBA::ORB_ptr g_pCorbaORB;


typedef std::map<std::string, RTC::CorbaNaming*> NamingMap;
/**
 * Global variable to map object in which CorbaNaming objects are stored.
 * Key value is IP-address (std::string) of the CorbaNaming service.
 */
extern RTC::CorbaNaming* g_CorbaNamingMap[];



/**
 * Global function for getting the pointer to CorbaNaming object.
 *   -address: IP address of corba naming object.
 * If success, the corba naming address will be return.
 * If error, NULL pointer.
 */
RTC::CorbaNaming* GetCorbaNaming(int id);


class ScilabComp;

//typedef std::map<std::string, ScilabComp*> CompMap;
/**
 * Global variable to map object in which ScilabComp objects are stored.
 * Key value is name (std::string) of the CorbaNaming service.
 */
extern ScilabComp* g_CompMap[];

/**
 * Global function for getting the pointer to CorbaNaming object.
 *   -address: IP address of corba naming object.
 * If success, the corba naming address will be return.
 * If error, NULL pointer.
 */
ScilabComp* GetComponent(const char* name);



#define MAX_RT_OBJECT 128

struct RTObjectStruct {
	int namingID;
	std::string componentName;
};


extern RTObjectStruct *RTObjectMap[MAX_RT_OBJECT];

/**
 * Resolve
 * Utility function for resolving RT component by name.
 *  -address : IP address of naming service.
 *  -name    : name of RTC.
 * If success, non-zero value (ponter to CorbaConsumer object).
 * If error, zero.
 */
inline CORBA::Object_ptr Resolve(const int rtObjectId) {
	if(RTObjectMap[rtObjectId] == NULL) return NULL;

	RTC::CorbaNaming* pNaming = GetCorbaNaming(RTObjectMap[rtObjectId]->namingID);
	if(pNaming == NULL) {
		return NULL;
	}

	return pNaming->resolve(RTObjectMap[rtObjectId]->componentName.c_str());
}

inline RTC::PortService_ptr getNamedPort(RTC::PortServiceList* plist,
								    const char *portName)
{
	
	for(unsigned int i = 0;i < plist->length();i++) {
		RTC::PortProfile* pPortProfile = (*plist)[i]->get_port_profile();
		if(strcmp(portName, ((std::string)(pPortProfile->name)).c_str()) == 0) {
			return (*plist)[i];
		}
	}
	return NULL;
}


struct RTPortStruct {
	int RTObjectId;
	std::string Name;
};

#define MAX_RT_DATAPORT 128

extern RTPortStruct* RTPortMap[MAX_RT_DATAPORT];

inline RTC::PortService_ptr GetPort(const int portId) {
	if(portId >= MAX_RT_DATAPORT) return NULL;

	if(RTPortMap[portId] == NULL) return NULL;

	CORBA::Object_ptr rtObj = Resolve(RTPortMap[portId]->RTObjectId);
	if(rtObj == NULL) return NULL;

	RTC::CorbaConsumer<RTC::RTObject> corbaConsumer;
	corbaConsumer.setObject(rtObj);

	return getNamedPort(corbaConsumer->get_ports(), RTPortMap[portId]->Name.c_str());
}

inline RTPortStruct* GetRTPort(const int portId) {
	if(portId >= MAX_RT_DATAPORT) return NULL;

	if(RTPortMap[portId] == NULL) return NULL;

	return RTPortMap[portId];
}


/**
 * utility function for cleanup local memory
 */
void CleanUpSciPorts();
