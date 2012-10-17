/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : ScilabComp.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */

#ifndef SCILABCOMP_H
#define SCILABCOMP_H

/**
#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>
*/

#include "coil/TimeMeasure.h"
// Service implementation headers
// <rtc-template block="service_impl_h">

// </rtc-template>

// Service Consumer stub headers
// <rtc-template block="consumer_stub_h">

// </rtc-template>

using namespace RTC;

/*!
 * @class ScilabComp
 * @brief ScilabComp Interfacing RTC
 *
 */
class ScilabComp
  : public RTC::DataFlowComponentBase
{
 public:
  /*!
   * @brief constructor
   * @param manager Maneger Object
   */
  ScilabComp(RTC::Manager* manager);

  /*!
   * @brief destructor
   */
  ~ScilabComp();

  // <rtc-template block="public_attribute">
  
  // </rtc-template>

  // <rtc-template block="public_operation">
  
  // </rtc-template>


  RTC::ReturnCode_t initialize() throw(CORBA::SystemException) {
  //  RTC::Properties dummy_prop;
  //  setProperties(dummy_prop); // ★これを呼ぶとインスタンス名が正しく上書きされる
  
	  return DataFlowComponentBase::initialize();
  }



  /*!
   *
   * The initialize action (on CREATED->ALIVE transition)
   * formaer rtc_init_entry() 
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onInitialize();

  /***
   *
   * The finalize action (on ALIVE->END transition)
   * formaer rtc_exiting_entry()
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onFinalize();

  /***
   *
   * The startup action when ExecutionContext startup
   * former rtc_starting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStartup(RTC::UniqueId ec_id);

  /***
   *
   * The shutdown action when ExecutionContext stop
   * former rtc_stopping_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onShutdown(RTC::UniqueId ec_id);

  /***
   *
   * The activated action (Active state entry action)
   * former rtc_active_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onActivated(RTC::UniqueId ec_id);

  /***
   *
   * The deactivated action (Active state exit action)
   * former rtc_active_exit()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onDeactivated(RTC::UniqueId ec_id);

  /***
   *
   * The execution action that is invoked periodically
   * former rtc_active_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
   virtual RTC::ReturnCode_t onExecute(RTC::UniqueId ec_id);

  /***
   *
   * The aborting action when main logic error occurred.
   * former rtc_aborting_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onAborting(RTC::UniqueId ec_id);

  /***
   *
   * The error action in ERROR state
   * former rtc_error_do()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onError(RTC::UniqueId ec_id);

  /***
   *
   * The reset action that is invoked resetting
   * This is same but different the former rtc_init_entry()
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onReset(RTC::UniqueId ec_id);
  
  /***
   *
   * The state update action that is invoked after onExecute() action
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onStateUpdate(RTC::UniqueId ec_id);

  /***
   *
   * The action that is invoked when execution context's rate is changed
   * no corresponding operation exists in OpenRTm-aist-0.2.0
   *
   * @param ec_id target ExecutionContext Id
   *
   * @return RTC::ReturnCode_t
   * 
   * 
   */
  // virtual RTC::ReturnCode_t onRateChanged(RTC::UniqueId ec_id);


 protected:
  // <rtc-template block="protected_attribute">
  
  // </rtc-template>

  // <rtc-template block="protected_operation">
  
  // </rtc-template>

  // Configuration variable declaration
  // <rtc-template block="config_declare">
  /*!
   * 
   * - Name:  exec_param
   * - DefaultValue: 0
   */
  int m_exec_param;
  // </rtc-template>


  // CORBA Port declaration
  // <rtc-template block="corbaport_declare">
  
  // </rtc-template>

  // Service declaration
  // <rtc-template block="service_declare">
  
  // </rtc-template>

  // Consumer declaration
  // <rtc-template block="consumer_declare">
  
  // </rtc-template>

 private:
  // <rtc-template block="private_attribute">
  
  // </rtc-template>

  // <rtc-template block="private_operation">
  
  // </rtc-template>

	 int activeFlag;
	  void SetActive() {
		  activeFlag = 1;
	  }

	  void SetInActive() {
		  activeFlag = 0;
	  }

 public:
	  int isActive() {
		  return activeFlag;
	  }

	  int manualDeactivatedFlag;
	  int isManuallyDeactivated() {
		  return manualDeactivatedFlag;
	  }

   typedef coil::Guard<coil::Mutex> Guard;

private:
	int syncFlag;
	coil::Mutex m_executeMutex;
	int usageCount;
public:
	void IncrementUsageCount(void) {
		Guard myGuard(m_executeMutex);
		usageCount++;
	}

	void DecrementUsageCount(void) {
		Guard myGuard(m_executeMutex);
		usageCount--;
	}

	int GetUsageCount(void) {
		Guard myGuard(m_executeMutex);
		return usageCount;
	}

	int WaitOnExecuteStart(void);
	void NotifyCalcEnd(void);

	void StartSynchronize(void) {
		syncFlag = 1;
		manualDeactivatedFlag = 0;
	}

	void StopSynchronize(void) {
		syncFlag = 0;
	}

	int IsSynchronize(void) {
		return syncFlag;
	}



	coil::TimeMeasure m_WaitIntervalMeasure;
	coil::TimeValue   m_Interval;
};


extern "C"
{
   void ScilabCompInit(RTC::Manager* manager);


};

#endif // SCILAB_H
