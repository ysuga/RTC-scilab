/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : Connection.h
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

#define MAX_CONNECTION 128

RTC::ConnectorProfile* g_ConnectorProfiles[MAX_CONNECTION] = {0, };

int ConnectionCount = 0;
/**
 * Connection_create
 *
 *  -address: IP address of Naming Service
 *  -connectorID: identifier of connector to be created.
 *  -connectorName: name of connector to be created.
 *  -compA: name of component A
 *  -portNameA: name of componentA's port
 *  -compB: name of component B
 *  -portNameB: name of componentB's port
 *  -retval: return value for scilab process.
 *  if success, *retval = 0, if error, non-zero value.
 */
EXPORT_FUNCTION_TYPE Connection_create(
									   const char* connectorID,
									   const char* connectorName, 
									   const int* HandleA,
									   const int* HandleB,
									   int* retval)
{
	
	RTC::PortService_ptr pPortA = GetPort(*HandleA);
	if(pPortA == NULL) {
		*retval = -1;
		return;
	}

	RTC::PortService_ptr pPortB = GetPort(*HandleB);
	if(pPortB == NULL) {
		*retval = -1;
		return;
	}


	// 接続のためのコネクションプロファイルを作成
	RTC::ConnectorProfile* prof = new RTC::ConnectorProfile();
	prof->connector_id = CORBA::string_dup(connectorID);
	prof->name = CORBA::string_dup(connectorName);
	prof->ports.length(2);
	prof->ports[0] = pPortA;//getNamedPort(corbaConsumerA->get_ports(), portNameA);//(*plistA)[indexA];
	prof->ports[1] = pPortB;// getNamedPort(corbaConsumerB->get_ports(), portNameB);//(*plistB)[indexB];
	
	// 接続のプロパティを追加
	CORBA_SeqUtil::push_back(prof->properties,
		   NVUtil::newNV("dataport.interface_type",
				 "corba_cdr"));
	CORBA_SeqUtil::push_back(prof->properties,
		   NVUtil::newNV("dataport.dataflow_type",
				 "push"));
	CORBA_SeqUtil::push_back(prof->properties,
		   NVUtil::newNV("dataport.subscription_type",
				 "flush"));

	if(prof->ports[0]->connect(*prof) != RTC::RTC_OK) {
		*retval = -2;
		return;
	}

	*retval = ConnectionCount;
	g_ConnectorProfiles[ConnectionCount] = prof;
	ConnectionCount++;
}

EXPORT_FUNCTION_TYPE Connection_destroy(const int* Handle,
									   int* retval)
{
	if(g_ConnectorProfiles[*Handle] == NULL) {*retval =  -1; return;}

	RTC::ConnectorProfile *prof = g_ConnectorProfiles[*Handle];

	prof->ports[0]->disconnect(prof->connector_id);

	*retval = 0;
}