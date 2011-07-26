/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : RTC-scilab.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */
#ifndef RTCSCILAB_HEADER_INCLUDED
#define RTCSCILAB_HEADER_INCLUDED




/**
 * Linkage definition.
 */
#ifdef WIN32
#define EXPORT_FUNCTION_TYPE __declspec(dllexport) void __cdecl
#else
#define EXPORT_FUNCTION_TYPE void
#endif


#include "Manager.h"
#include "CorbaNaming.h"
#include "Connection.h"

#include "Configuration.h"

#include "RTC.h"
#include "RTObject.h"
#include "Port.h"




#endif

