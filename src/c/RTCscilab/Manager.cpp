/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : Manager.cpp
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
 * Global pointer to ORB object.
 * This will be used to create Corba Naming Service object.
 */
CORBA::ORB_ptr g_pCorbaORB = NULL;


/**
 * Global Pointer to Manager object.
 * This will be used to create RT Components.
 */
RTC::Manager* g_pManager = NULL;


/**
 * MyModuleInit
 *  manager : RTC::Manager class object.
 * This is for registering the ScilabComp Component to the Manager
 * which will be created in this process.
 */
static void MyModuleInit(RTC::Manager* manager)
{
	ScilabCompInit(manager);
}


/**
 * Manager_create
 *   -managername -- identifier of ScilabComp component.
 *
 * Manager object is created. The pointer to the object
 * is stored in the global variable g_pManager.
 * The argument will be used as the default instance name 
 * of the RTC which will be created by the Manager.
 */
EXPORT_FUNCTION_TYPE Manager_create(char* managername, char* pathrtcconf)
{
  //	printf("Manager_create is called!\n\n");

	if(!g_pManager) {
		static int argc = 3;
		static char* argv[] = {"RTC-Sci.dll", "-f", pathrtcconf};

		strcpy(implementation_id, managername);
		strcpy(type_name, managername);

		g_pManager = RTC::Manager::init(argc, argv);
		g_pManager->init(argc, argv);
		g_pManager->setModuleInitProc(MyModuleInit);
		g_pManager = &(RTC::Manager::instance());
		g_pManager->activateManager();
		g_pManager->runManager(true);
		g_pCorbaORB = g_pManager->getORB();
	}
}


/**
 * Manager_destroy
 * Manager object is destroyed.
 */
EXPORT_FUNCTION_TYPE Manager_destroy(void)
{
	if(g_pManager) {	
		g_pManager->shutdown();
		g_pManager = NULL;
	}
}
