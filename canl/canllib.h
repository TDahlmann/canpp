/*
 * The MIT License (MIT)
 *
 * Copyright (c) 2016 Thomas Dahlmann <tomydahl@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 */

#ifndef _CANLLIB_H
#define _CANLLIB_H

/*-----------------------------------------------------------------------------------------------
    Includes
  -----------------------------------------------------------------------------------------------*/

#include <Windows.h>

#include <stdio.h>
#ifndef NO_CANL_DATA
#include "canl_data.h"
#include "canl_dynamic.h"
#else
#include "canl_base.h"
#endif

#include "math.h"

/*-----------------------------------------------------------------------------------------------
    Defines and Macros
  -----------------------------------------------------------------------------------------------*/
extern HANDLE hPipe;

/* forward decl. */
class CanlMessage;

#ifndef WINAPI
#define WINAPI  __stdcall
/*#define WINAPI*/
#endif

extern void (*msgRxFuncAll)(message& m);
extern void (*OnStartFunc)(void);
extern void (*OnStopFunc)(void);

// Type definition for the callback function.
typedef int (WINAPI *CallbackFunc)(int);
typedef int (WINAPI *CallbackFuncTxMsg)(int);
typedef void (WINAPI *CanlTxMessageCallback)(CanlMessage*);
typedef void (WINAPI *CanlPrintCallback)(char*);

typedef void (WINAPI *CanlRxMessage)(CanlMessage*);
typedef void (WINAPI *CanlRegisterTxCallback)(CanlTxMessageCallback);
typedef void (WINAPI *CanlRegisterPrintCallback)(CanlPrintCallback);
typedef CanlConfig* (WINAPI *CanlGetConfig)(void);
typedef void (WINAPI *CanlTimerCallback)(void);


#ifdef _CANLLIB_
#define CANLLIBAPI  __declspec(dllexport)
#else
#define CANLLIBAPI  __declspec(dllimport)
#endif /* _CANLLIB_ */

// exported funcs
CANLLIBAPI int WINAPI SampleFunction(CallbackFunc Callback, int, int);
CANLLIBAPI void WINAPI ProcessRxCanMsg(CanlMessage* rxMsg);
CANLLIBAPI void WINAPI RegisterTxCallback(CanlTxMessageCallback callback, CanlMessage* txMsg);
CANLLIBAPI void WINAPI RegisterPrintCallback(CanlPrintCallback callback, char* str);
CANLLIBAPI CanlConfig* WINAPI GetConfig(void);
CANLLIBAPI void WINAPI TimerCallback(void);

// protos
void msgRxInit(void);
void canOut(unsigned long ID, unsigned long DLC, unsigned char *byte);
//void ProcessRxCanMsg(CanlMessage* rxMsg);
void msgRxInit(void);
unsigned int len2dlc(unsigned int len);
unsigned int dlc2len(unsigned int dlc);

#endif /* _CANLLIB_H */
