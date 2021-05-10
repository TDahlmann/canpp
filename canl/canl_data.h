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
#include "canl_base.h"

class BatteryUsage : public message
{
public:
    BatteryUsage(unsigned long id) : message (id) {};
    BatteryUsage();

    void onMessage(void);
    signal BU_CRC;
    signal BU_Count;
    signal BU_Current;
    signal BU_Volatage;
};

class LockAttempts : public message
{
public:
    LockAttempts(unsigned long id) : message (id) {};
    LockAttempts();

    void onMessage(void);
    signal LA_Attempts;
    signal LA_CRC;
    signal LA_Count;
};

class RadarControl : public message
{
public:
    RadarControl(unsigned long id) : message (id) {};
    RadarControl();

    void onMessage(void);
    signal RC_Accerlation;
    signal RC_CRC;
    signal RC_Count;
    signal RC_RadarRange;
    signal RC_SIG_1;
    signal RC_SIG_2;
    signal RC_SIG_3;
    signal RC_SIG_4;
    signal RC_SIG_6;
};

class BatteryState : public message
{
public:
    BatteryState(unsigned long id) : message (id) {};
    BatteryState();

    void onMessage(void);
    signal BS_CRC;
    signal BS_Charging_Enable;
    signal BS_Count;
    signal BS_Energy;
    signal BS_Power;
    signal BS_Resistance;
    signal BS_Sig1;
    signal BS_Sig2;
    signal BS_Sig3;
    signal BS_Sig5;
    signal BS_Sig6;
};

