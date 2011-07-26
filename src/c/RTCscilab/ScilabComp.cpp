/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : ScilabComp.cpp
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
#include "ScilabComp.h"

/**
 * implementation_id
 * This variable will be used in registering the RTC.
 * The implementation ID will be the identifier which will be used
 * in creating the RTC using RTC::Manager.
 */
char implementation_id[RTCSCILAB_MAXID];

/**
 * type_name
 * This variable will be used in registering the RTC.
 * This type_name will be the default instance name of RTC.
 * The type_name will be defined in the Manager_create function.
 */
char type_name[RTCSCILAB_MAXID];

// Module specification
// <rtc-template block="module_spec">
static const char* scirtc_spec[] =
  {
    "implementation_id", implementation_id,
    "type_name",         type_name,
    "description",       "Scilab Interfacing RTC",
    "version",           "1.0.0",
    "vendor",            "ysuga.net",
    "category",          "Test",
    "activity_type",     "PERIODIC",
    "kind",              "DataFlowComponent",
    "max_instance",      "1",
    "language",          "C++",
    "lang_type",         "compile",
   // "exec_cxt.periodic.rate", "1.0",
    // Configuration variables
    "conf.default.exec_param", "0",
    ""
  };
// </rtc-template>

/*!
 * @brief constructor
 * @param manager Maneger Object
 */
ScilabComp::ScilabComp(RTC::Manager* manager)
    // <rtc-template block="initializer">
  : RTC::DataFlowComponentBase(manager),
    syncFlag(0),  usageCount(0)//, 
//    m_doubleInIn("doubleIn", m_doubleIn),
//    m_doubleOutOut("doubleOut", m_doubleOut)

    // </rtc-template>
{
  // Registration: InPort/OutPort/Service
  // <rtc-template block="registration">
  // Set InPort buffers
 // registerInPort("doubleIn", m_doubleInIn);
  
  // Set OutPort buffer
 // registerOutPort("doubleOut", m_doubleOutOut);
  
  // Set service provider to Ports
  
  // Set service consumers to Ports
  
  // Set CORBA Service Ports
  
  // </rtc-template>

}

/*!
 * @brief destructor
 */
ScilabComp::~ScilabComp()
{
}



RTC::ReturnCode_t ScilabComp::onInitialize()
{
  // <rtc-template block="bind_config">
  // Bind variables and configuration variable
  bindParameter("exec_param", m_exec_param, "0");
  

  activeFlag = 0;//FALSE;

  // </rtc-template>
  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ScilabComp::onFinalize()
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ScilabComp::onStartup(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ScilabComp::onShutdown(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/


RTC::ReturnCode_t ScilabComp::onActivated(RTC::UniqueId ec_id)
{
	SetActive();
	manualDeactivatedFlag = 0;
  return RTC::RTC_OK;
}

RTC::ReturnCode_t ScilabComp::onDeactivated(RTC::UniqueId ec_id)
{
	SetInActive();
    manualDeactivatedFlag = 1;
  return RTC::RTC_OK;
}

int ScilabComp::WaitOnExecuteStart(void) {
	do {
		if(GetUsageCount() == 1) {
			break;
		}
		coil::usleep(0);
		if(manualDeactivatedFlag) {
			return -2;
		}

	}while(1);


	return 0;
}

void ScilabComp::NotifyCalcEnd(void) {
	DecrementUsageCount();
}



RTC::ReturnCode_t ScilabComp::onExecute(RTC::UniqueId ec_id)
{
  //	MessageBoxA(NULL, "ONEXECUTE", "MESSAGE", MB_OK);
	if(IsSynchronize()) {
		IncrementUsageCount();
		do {
			if(GetUsageCount() == 0) {
				break;
			}
			coil::usleep(0);
		}while(1);
	}

  return RTC::RTC_OK;
}

/*
RTC::ReturnCode_t ScilabComp::onAborting(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ScilabComp::onError(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ScilabComp::onReset(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ScilabComp::onStateUpdate(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/

/*
RTC::ReturnCode_t ScilabComp::onRateChanged(RTC::UniqueId ec_id)
{
  return RTC::RTC_OK;
}
*/



extern "C"
{
 
  void ScilabCompInit(RTC::Manager* manager)
  {
    coil::Properties profile(scirtc_spec);
    manager->registerFactory(profile,
                             RTC::Create<ScilabComp>,
                             RTC::Delete<ScilabComp>);
  }
  
};


