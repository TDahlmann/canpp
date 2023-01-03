/*
* The MIT License (MIT)
*
* Copyright(c) 2016 Thomas Dahlmann <tomydahl@gmail.com>
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this softwareand associated documentation files(the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
* copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions :
*
* The above copyright noticeand this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
* THE SOFTWARE.
*
*/
#include "canllib.h"

extern Timer* g_timerArray[];
extern CanlConfig g_canlConfig;

BatteryState rxMsg_BatteryState;

/* BatteryState (0x190) */
void msgRxFunc_BatteryState(CanlMessage *rxMsg)
{
    rxMsg_BatteryState.rxFunc(rxMsg);
    rxMsg_BatteryState.onMessage();
    rxMsg_BatteryState.saveBytes();
}

void msgRxInit(void)
{
    int ix = 0;

    /* BatteryState (0x190) */
    canRxArray[ix].canId = 0x190;
    canRxArray[ix].msgRxFunc = msgRxFunc_BatteryState;
    ix++;

    OnStartFunc = NULL;
    OnStopFunc = NULL;
    msgRxFuncAll = NULL;

    OnKeyFunc = NULL;

    OnCommandFunc = NULL;

    g_canlConfig.timerUsed = 0;
    g_canlConfig.numTimers = 0;


    canNumberMsgs = ix;
}