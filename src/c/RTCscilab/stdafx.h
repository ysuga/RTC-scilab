/**
 * Package  : RTC-scilab.
 *   RTC-scilab is the inter-connecting library between scilab and OpenRTM.
 *
 * File     : stdafx.h
 * Date     : 2010/02/28
 * author   : Yuki Suga (E-mail: ysuga@ysuga.net)
 * copyright: ysuga.net 2010, all rights reserved.
 * URL      : http://www.ysuga.net/rtm/rtc_scilab/index.html
 *
 * This file must be used under the terms of GNU Public License version 3.
 * This source file is licensed as described in the file license.txt, which
 * you should have received as part of this distribution.
 */

// The pre-compiled header mechanizm is indispensable for me
// because I use low spec PC..., Yuki Suga 2010/02/28
#ifndef STDAFX_HEADER_INCLUDED
#define STDAFX_HEADER_INCLUDED

#ifdef WIN32
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>
#endif

#include <stdio.h>


#include <iostream>
#include <rtm/CorbaNaming.h>
#include <rtm/RTObject.h>
#include <rtm/CorbaConsumer.h>

#include <rtm/Manager.h>
#include <rtm/DataFlowComponentBase.h>
#include <rtm/CorbaPort.h>
#include <rtm/DataInPort.h>
#include <rtm/DataOutPort.h>
#include <rtm/idl/BasicDataTypeSkel.h>


#include <assert.h>


// TODO: プログラムに必要な追加ヘッダーをここで参照してください。


#endif


