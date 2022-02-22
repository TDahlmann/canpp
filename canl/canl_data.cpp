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



BatteryUsage::BatteryUsage() : message()
{
    ID = 0xc8;
    DLC = 8;
    FDF = 0;
    BRS = 0;

    rootSignal = &BU_CRC;
    
    // BU_CRC
    BU_CRC.m_isMuxer = 0;
    BU_CRC.muxVal = -1;
    BU_CRC.m_startBit = 0;
    BU_CRC.m_bitLength = 8;
    BU_CRC.m_bigEndian = 0;
    BU_CRC.m_startByte = 0;
    BU_CRC.m_startByteMask = 0xff;
    BU_CRC.m_stopByte = 0;
    BU_CRC.m_stopByteMask = 0xff;
    BU_CRC.m_shiftDown = 0;
    BU_CRC.m_factor = 1.000000;
    BU_CRC.m_offset = 0.000000;
    BU_CRC.m_min = 0.000000;
    BU_CRC.m_max = 255.000000;
    BU_CRC.m_isFloat = 0;
    BU_CRC.m_prec = 0;
    BU_CRC.m_startVal = 0;
    BU_CRC.parent = this;
    BU_CRC.next = &BU_Count;
    
    // BU_Count
    BU_Count.m_isMuxer = 0;
    BU_Count.muxVal = -1;
    BU_Count.m_startBit = 8;
    BU_Count.m_bitLength = 4;
    BU_Count.m_bigEndian = 0;
    BU_Count.m_startByte = 1;
    BU_Count.m_startByteMask = 0xff;
    BU_Count.m_stopByte = 1;
    BU_Count.m_stopByteMask = 0xf;
    BU_Count.m_shiftDown = 0;
    BU_Count.m_factor = 1.000000;
    BU_Count.m_offset = 0.000000;
    BU_Count.m_min = 0.000000;
    BU_Count.m_max = 15.000000;
    BU_Count.m_isFloat = 0;
    BU_Count.m_prec = 0;
    BU_Count.m_startVal = 0;
    BU_Count.parent = this;
    BU_Count.next = &BU_Current;
    
    // BU_Current
    BU_Current.m_isMuxer = 0;
    BU_Current.muxVal = -1;
    BU_Current.m_startBit = 12;
    BU_Current.m_bitLength = 12;
    BU_Current.m_bigEndian = 0;
    BU_Current.m_startByte = 1;
    BU_Current.m_startByteMask = 0xf0;
    BU_Current.m_stopByte = 2;
    BU_Current.m_stopByteMask = 0xff;
    BU_Current.m_shiftDown = 4;
    BU_Current.m_factor = 1.000000;
    BU_Current.m_offset = -2047.000000;
    BU_Current.m_min = -2047.000000;
    BU_Current.m_max = 2046.000000;
    BU_Current.m_isFloat = 0;
    BU_Current.m_prec = 0;
    BU_Current.m_startVal = 0;
    BU_Current.parent = this;
    BU_Current.next = &BU_Volatage;
    
    // BU_Volatage
    BU_Volatage.m_isMuxer = 0;
    BU_Volatage.muxVal = -1;
    BU_Volatage.m_startBit = 24;
    BU_Volatage.m_bitLength = 12;
    BU_Volatage.m_bigEndian = 0;
    BU_Volatage.m_startByte = 3;
    BU_Volatage.m_startByteMask = 0xff;
    BU_Volatage.m_stopByte = 4;
    BU_Volatage.m_stopByteMask = 0xf;
    BU_Volatage.m_shiftDown = 0;
    BU_Volatage.m_factor = 0.250000;
    BU_Volatage.m_offset = 0.000000;
    BU_Volatage.m_min = 0.000000;
    BU_Volatage.m_max = 1023.250000;
    BU_Volatage.m_isFloat = 1;
    BU_Volatage.m_prec = 2;
    BU_Volatage.m_startVal = 0;
    BU_Volatage.parent = this;
    BU_Volatage.next = NULL;

    applySignalsStartValue();
}


LockAttempts::LockAttempts() : message()
{
    ID = 0x12c;
    DLC = 8;
    FDF = 0;
    BRS = 0;

    rootSignal = &LA_Attempts;
    
    // LA_Attempts
    LA_Attempts.m_isMuxer = 0;
    LA_Attempts.muxVal = -1;
    LA_Attempts.m_startBit = 63;
    LA_Attempts.m_bitLength = 1;
    LA_Attempts.m_bigEndian = 0;
    LA_Attempts.m_startByte = 7;
    LA_Attempts.m_startByteMask = 0x80;
    LA_Attempts.m_stopByte = 7;
    LA_Attempts.m_stopByteMask = 0xff;
    LA_Attempts.m_shiftDown = 7;
    LA_Attempts.m_factor = 1.000000;
    LA_Attempts.m_offset = 0.000000;
    LA_Attempts.m_min = 0.000000;
    LA_Attempts.m_max = 1.000000;
    LA_Attempts.m_isFloat = 0;
    LA_Attempts.m_prec = 0;
    LA_Attempts.m_startVal = 0;
    LA_Attempts.parent = this;
    LA_Attempts.next = &LA_CRC;
    
    // LA_CRC
    LA_CRC.m_isMuxer = 0;
    LA_CRC.muxVal = -1;
    LA_CRC.m_startBit = 0;
    LA_CRC.m_bitLength = 8;
    LA_CRC.m_bigEndian = 0;
    LA_CRC.m_startByte = 0;
    LA_CRC.m_startByteMask = 0xff;
    LA_CRC.m_stopByte = 0;
    LA_CRC.m_stopByteMask = 0xff;
    LA_CRC.m_shiftDown = 0;
    LA_CRC.m_factor = 1.000000;
    LA_CRC.m_offset = 0.000000;
    LA_CRC.m_min = 0.000000;
    LA_CRC.m_max = 255.000000;
    LA_CRC.m_isFloat = 0;
    LA_CRC.m_prec = 0;
    LA_CRC.m_startVal = 0;
    LA_CRC.parent = this;
    LA_CRC.next = &LA_Count;
    
    // LA_Count
    LA_Count.m_isMuxer = 0;
    LA_Count.muxVal = -1;
    LA_Count.m_startBit = 8;
    LA_Count.m_bitLength = 4;
    LA_Count.m_bigEndian = 0;
    LA_Count.m_startByte = 1;
    LA_Count.m_startByteMask = 0xff;
    LA_Count.m_stopByte = 1;
    LA_Count.m_stopByteMask = 0xf;
    LA_Count.m_shiftDown = 0;
    LA_Count.m_factor = 1.000000;
    LA_Count.m_offset = 0.000000;
    LA_Count.m_min = 0.000000;
    LA_Count.m_max = 15.000000;
    LA_Count.m_isFloat = 0;
    LA_Count.m_prec = 0;
    LA_Count.m_startVal = 0;
    LA_Count.parent = this;
    LA_Count.next = NULL;

    applySignalsStartValue();
}


RadarControl::RadarControl() : message()
{
    ID = 0x64;
    DLC = 8;
    FDF = 0;
    BRS = 0;

    rootSignal = &RC_Accerlation;
    
    // RC_Accerlation
    RC_Accerlation.m_isMuxer = 0;
    RC_Accerlation.muxVal = -1;
    RC_Accerlation.m_startBit = 24;
    RC_Accerlation.m_bitLength = 11;
    RC_Accerlation.m_bigEndian = 0;
    RC_Accerlation.m_startByte = 3;
    RC_Accerlation.m_startByteMask = 0xff;
    RC_Accerlation.m_stopByte = 4;
    RC_Accerlation.m_stopByteMask = 0x7;
    RC_Accerlation.m_shiftDown = 0;
    RC_Accerlation.m_factor = 0.005000;
    RC_Accerlation.m_offset = -5.800000;
    RC_Accerlation.m_min = -5.800000;
    RC_Accerlation.m_max = 3.005000;
    RC_Accerlation.m_isFloat = 1;
    RC_Accerlation.m_prec = 3;
    RC_Accerlation.m_startVal = 2046;
    RC_Accerlation.parent = this;
    RC_Accerlation.next = &RC_CRC;
    
    // RC_CRC
    RC_CRC.m_isMuxer = 0;
    RC_CRC.muxVal = -1;
    RC_CRC.m_startBit = 0;
    RC_CRC.m_bitLength = 8;
    RC_CRC.m_bigEndian = 0;
    RC_CRC.m_startByte = 0;
    RC_CRC.m_startByteMask = 0xff;
    RC_CRC.m_stopByte = 0;
    RC_CRC.m_stopByteMask = 0xff;
    RC_CRC.m_shiftDown = 0;
    RC_CRC.m_factor = 1.000000;
    RC_CRC.m_offset = 0.000000;
    RC_CRC.m_min = 0.000000;
    RC_CRC.m_max = 255.000000;
    RC_CRC.m_isFloat = 0;
    RC_CRC.m_prec = 0;
    RC_CRC.m_startVal = 0;
    RC_CRC.parent = this;
    RC_CRC.next = &RC_Count;
    
    // RC_Count
    RC_Count.m_isMuxer = 0;
    RC_Count.muxVal = -1;
    RC_Count.m_startBit = 8;
    RC_Count.m_bitLength = 4;
    RC_Count.m_bigEndian = 0;
    RC_Count.m_startByte = 1;
    RC_Count.m_startByteMask = 0xff;
    RC_Count.m_stopByte = 1;
    RC_Count.m_stopByteMask = 0xf;
    RC_Count.m_shiftDown = 0;
    RC_Count.m_factor = 1.000000;
    RC_Count.m_offset = 0.000000;
    RC_Count.m_min = 0.000000;
    RC_Count.m_max = 15.000000;
    RC_Count.m_isFloat = 0;
    RC_Count.m_prec = 0;
    RC_Count.m_startVal = 0;
    RC_Count.parent = this;
    RC_Count.next = &RC_RadarRange;
    
    // RC_RadarRange
    RC_RadarRange.m_isMuxer = 0;
    RC_RadarRange.muxVal = -1;
    RC_RadarRange.m_startBit = 16;
    RC_RadarRange.m_bitLength = 6;
    RC_RadarRange.m_bigEndian = 0;
    RC_RadarRange.m_startByte = 2;
    RC_RadarRange.m_startByteMask = 0xff;
    RC_RadarRange.m_stopByte = 2;
    RC_RadarRange.m_stopByteMask = 0x3f;
    RC_RadarRange.m_shiftDown = 0;
    RC_RadarRange.m_factor = 0.025000;
    RC_RadarRange.m_offset = 0.000000;
    RC_RadarRange.m_min = 0.000000;
    RC_RadarRange.m_max = 1.300000;
    RC_RadarRange.m_isFloat = 1;
    RC_RadarRange.m_prec = 3;
    RC_RadarRange.m_startVal = 0;
    RC_RadarRange.parent = this;
    RC_RadarRange.next = &RC_SIG_1;
    
    // RC_SIG_1
    RC_SIG_1.m_isMuxer = 0;
    RC_SIG_1.muxVal = -1;
    RC_SIG_1.m_startBit = 12;
    RC_SIG_1.m_bitLength = 1;
    RC_SIG_1.m_bigEndian = 0;
    RC_SIG_1.m_startByte = 1;
    RC_SIG_1.m_startByteMask = 0xf0;
    RC_SIG_1.m_stopByte = 1;
    RC_SIG_1.m_stopByteMask = 0x1f;
    RC_SIG_1.m_shiftDown = 4;
    RC_SIG_1.m_factor = 1.000000;
    RC_SIG_1.m_offset = 0.000000;
    RC_SIG_1.m_min = 0.000000;
    RC_SIG_1.m_max = 1.000000;
    RC_SIG_1.m_isFloat = 0;
    RC_SIG_1.m_prec = 0;
    RC_SIG_1.m_startVal = 0;
    RC_SIG_1.parent = this;
    RC_SIG_1.next = &RC_SIG_2;
    
    // RC_SIG_2
    RC_SIG_2.m_isMuxer = 0;
    RC_SIG_2.muxVal = -1;
    RC_SIG_2.m_startBit = 13;
    RC_SIG_2.m_bitLength = 1;
    RC_SIG_2.m_bigEndian = 0;
    RC_SIG_2.m_startByte = 1;
    RC_SIG_2.m_startByteMask = 0xe0;
    RC_SIG_2.m_stopByte = 1;
    RC_SIG_2.m_stopByteMask = 0x3f;
    RC_SIG_2.m_shiftDown = 5;
    RC_SIG_2.m_factor = 1.000000;
    RC_SIG_2.m_offset = 0.000000;
    RC_SIG_2.m_min = 0.000000;
    RC_SIG_2.m_max = 1.000000;
    RC_SIG_2.m_isFloat = 0;
    RC_SIG_2.m_prec = 0;
    RC_SIG_2.m_startVal = 0;
    RC_SIG_2.parent = this;
    RC_SIG_2.next = &RC_SIG_3;
    
    // RC_SIG_3
    RC_SIG_3.m_isMuxer = 0;
    RC_SIG_3.muxVal = -1;
    RC_SIG_3.m_startBit = 14;
    RC_SIG_3.m_bitLength = 1;
    RC_SIG_3.m_bigEndian = 0;
    RC_SIG_3.m_startByte = 1;
    RC_SIG_3.m_startByteMask = 0xc0;
    RC_SIG_3.m_stopByte = 1;
    RC_SIG_3.m_stopByteMask = 0x7f;
    RC_SIG_3.m_shiftDown = 6;
    RC_SIG_3.m_factor = 1.000000;
    RC_SIG_3.m_offset = 0.000000;
    RC_SIG_3.m_min = 0.000000;
    RC_SIG_3.m_max = 1.000000;
    RC_SIG_3.m_isFloat = 0;
    RC_SIG_3.m_prec = 0;
    RC_SIG_3.m_startVal = 0;
    RC_SIG_3.parent = this;
    RC_SIG_3.next = &RC_SIG_4;
    
    // RC_SIG_4
    RC_SIG_4.m_isMuxer = 0;
    RC_SIG_4.muxVal = -1;
    RC_SIG_4.m_startBit = 15;
    RC_SIG_4.m_bitLength = 1;
    RC_SIG_4.m_bigEndian = 0;
    RC_SIG_4.m_startByte = 1;
    RC_SIG_4.m_startByteMask = 0x80;
    RC_SIG_4.m_stopByte = 1;
    RC_SIG_4.m_stopByteMask = 0xff;
    RC_SIG_4.m_shiftDown = 7;
    RC_SIG_4.m_factor = 1.000000;
    RC_SIG_4.m_offset = 0.000000;
    RC_SIG_4.m_min = 0.000000;
    RC_SIG_4.m_max = 1.000000;
    RC_SIG_4.m_isFloat = 0;
    RC_SIG_4.m_prec = 0;
    RC_SIG_4.m_startVal = 0;
    RC_SIG_4.parent = this;
    RC_SIG_4.next = &RC_SIG_6;
    
    // RC_SIG_6
    RC_SIG_6.m_isMuxer = 0;
    RC_SIG_6.muxVal = -1;
    RC_SIG_6.m_startBit = 22;
    RC_SIG_6.m_bitLength = 2;
    RC_SIG_6.m_bigEndian = 0;
    RC_SIG_6.m_startByte = 2;
    RC_SIG_6.m_startByteMask = 0xc0;
    RC_SIG_6.m_stopByte = 2;
    RC_SIG_6.m_stopByteMask = 0xff;
    RC_SIG_6.m_shiftDown = 6;
    RC_SIG_6.m_factor = 1.000000;
    RC_SIG_6.m_offset = 0.000000;
    RC_SIG_6.m_min = 0.000000;
    RC_SIG_6.m_max = 3.000000;
    RC_SIG_6.m_isFloat = 0;
    RC_SIG_6.m_prec = 0;
    RC_SIG_6.m_startVal = 0;
    RC_SIG_6.parent = this;
    RC_SIG_6.next = NULL;

    applySignalsStartValue();
}


BatteryState::BatteryState() : message()
{
    ID = 0x190;
    DLC = 8;
    FDF = 0;
    BRS = 0;

    rootSignal = &BS_CRC;
    
    // BS_CRC
    BS_CRC.m_isMuxer = 0;
    BS_CRC.muxVal = -1;
    BS_CRC.m_startBit = 0;
    BS_CRC.m_bitLength = 8;
    BS_CRC.m_bigEndian = 0;
    BS_CRC.m_startByte = 0;
    BS_CRC.m_startByteMask = 0xff;
    BS_CRC.m_stopByte = 0;
    BS_CRC.m_stopByteMask = 0xff;
    BS_CRC.m_shiftDown = 0;
    BS_CRC.m_factor = 1.000000;
    BS_CRC.m_offset = 0.000000;
    BS_CRC.m_min = 0.000000;
    BS_CRC.m_max = 255.000000;
    BS_CRC.m_isFloat = 0;
    BS_CRC.m_prec = 0;
    BS_CRC.m_startVal = 0;
    BS_CRC.parent = this;
    BS_CRC.next = &BS_Charging_Enable;
    
    // BS_Charging_Enable
    BS_Charging_Enable.m_isMuxer = 0;
    BS_Charging_Enable.muxVal = -1;
    BS_Charging_Enable.m_startBit = 23;
    BS_Charging_Enable.m_bitLength = 1;
    BS_Charging_Enable.m_bigEndian = 0;
    BS_Charging_Enable.m_startByte = 2;
    BS_Charging_Enable.m_startByteMask = 0x80;
    BS_Charging_Enable.m_stopByte = 2;
    BS_Charging_Enable.m_stopByteMask = 0xff;
    BS_Charging_Enable.m_shiftDown = 7;
    BS_Charging_Enable.m_factor = 1.000000;
    BS_Charging_Enable.m_offset = 0.000000;
    BS_Charging_Enable.m_min = 0.000000;
    BS_Charging_Enable.m_max = 1.000000;
    BS_Charging_Enable.m_isFloat = 0;
    BS_Charging_Enable.m_prec = 0;
    BS_Charging_Enable.m_startVal = 0;
    BS_Charging_Enable.parent = this;
    BS_Charging_Enable.next = &BS_Count;
    
    // BS_Count
    BS_Count.m_isMuxer = 0;
    BS_Count.muxVal = -1;
    BS_Count.m_startBit = 8;
    BS_Count.m_bitLength = 4;
    BS_Count.m_bigEndian = 0;
    BS_Count.m_startByte = 1;
    BS_Count.m_startByteMask = 0xff;
    BS_Count.m_stopByte = 1;
    BS_Count.m_stopByteMask = 0xf;
    BS_Count.m_shiftDown = 0;
    BS_Count.m_factor = 1.000000;
    BS_Count.m_offset = 0.000000;
    BS_Count.m_min = 0.000000;
    BS_Count.m_max = 15.000000;
    BS_Count.m_isFloat = 0;
    BS_Count.m_prec = 0;
    BS_Count.m_startVal = 0;
    BS_Count.parent = this;
    BS_Count.next = &BS_Energy;
    
    // BS_Energy
    BS_Energy.m_isMuxer = 0;
    BS_Energy.muxVal = -1;
    BS_Energy.m_startBit = 12;
    BS_Energy.m_bitLength = 11;
    BS_Energy.m_bigEndian = 0;
    BS_Energy.m_startByte = 1;
    BS_Energy.m_startByteMask = 0xf0;
    BS_Energy.m_stopByte = 2;
    BS_Energy.m_stopByteMask = 0x7f;
    BS_Energy.m_shiftDown = 4;
    BS_Energy.m_factor = 50.000000;
    BS_Energy.m_offset = 0.000000;
    BS_Energy.m_min = 0.000000;
    BS_Energy.m_max = 102250.000000;
    BS_Energy.m_isFloat = 0;
    BS_Energy.m_prec = 0;
    BS_Energy.m_startVal = 0;
    BS_Energy.parent = this;
    BS_Energy.next = &BS_Power;
    
    // BS_Power
    BS_Power.m_isMuxer = 0;
    BS_Power.muxVal = -1;
    BS_Power.m_startBit = 32;
    BS_Power.m_bitLength = 11;
    BS_Power.m_bigEndian = 0;
    BS_Power.m_startByte = 4;
    BS_Power.m_startByteMask = 0xff;
    BS_Power.m_stopByte = 5;
    BS_Power.m_stopByteMask = 0x7;
    BS_Power.m_shiftDown = 0;
    BS_Power.m_factor = 50.000000;
    BS_Power.m_offset = 0.000000;
    BS_Power.m_min = 0.000000;
    BS_Power.m_max = 102250.000000;
    BS_Power.m_isFloat = 0;
    BS_Power.m_prec = 0;
    BS_Power.m_startVal = 0;
    BS_Power.parent = this;
    BS_Power.next = &BS_Resistance;
    
    // BS_Resistance
    BS_Resistance.m_isMuxer = 0;
    BS_Resistance.muxVal = -1;
    BS_Resistance.m_startBit = 46;
    BS_Resistance.m_bitLength = 12;
    BS_Resistance.m_bigEndian = 0;
    BS_Resistance.m_startByte = 5;
    BS_Resistance.m_startByteMask = 0xc0;
    BS_Resistance.m_stopByte = 7;
    BS_Resistance.m_stopByteMask = 0x3;
    BS_Resistance.m_shiftDown = 6;
    BS_Resistance.m_factor = 5.000000;
    BS_Resistance.m_offset = 0.000000;
    BS_Resistance.m_min = 0.000000;
    BS_Resistance.m_max = 20465.000000;
    BS_Resistance.m_isFloat = 0;
    BS_Resistance.m_prec = 0;
    BS_Resistance.m_startVal = 0;
    BS_Resistance.parent = this;
    BS_Resistance.next = &BS_Sig1;
    
    // BS_Sig1
    BS_Sig1.m_isMuxer = 0;
    BS_Sig1.muxVal = -1;
    BS_Sig1.m_startBit = 24;
    BS_Sig1.m_bitLength = 3;
    BS_Sig1.m_bigEndian = 0;
    BS_Sig1.m_startByte = 3;
    BS_Sig1.m_startByteMask = 0xff;
    BS_Sig1.m_stopByte = 3;
    BS_Sig1.m_stopByteMask = 0x7;
    BS_Sig1.m_shiftDown = 0;
    BS_Sig1.m_factor = 1.000000;
    BS_Sig1.m_offset = 0.000000;
    BS_Sig1.m_min = 0.000000;
    BS_Sig1.m_max = 7.000000;
    BS_Sig1.m_isFloat = 0;
    BS_Sig1.m_prec = 0;
    BS_Sig1.m_startVal = 0;
    BS_Sig1.parent = this;
    BS_Sig1.next = &BS_Sig2;
    
    // BS_Sig2
    BS_Sig2.m_isMuxer = 0;
    BS_Sig2.muxVal = -1;
    BS_Sig2.m_startBit = 27;
    BS_Sig2.m_bitLength = 1;
    BS_Sig2.m_bigEndian = 0;
    BS_Sig2.m_startByte = 3;
    BS_Sig2.m_startByteMask = 0xf8;
    BS_Sig2.m_stopByte = 3;
    BS_Sig2.m_stopByteMask = 0xf;
    BS_Sig2.m_shiftDown = 3;
    BS_Sig2.m_factor = 1.000000;
    BS_Sig2.m_offset = 0.000000;
    BS_Sig2.m_min = 0.000000;
    BS_Sig2.m_max = 1.000000;
    BS_Sig2.m_isFloat = 0;
    BS_Sig2.m_prec = 0;
    BS_Sig2.m_startVal = 0;
    BS_Sig2.parent = this;
    BS_Sig2.next = &BS_Sig3;
    
    // BS_Sig3
    BS_Sig3.m_isMuxer = 0;
    BS_Sig3.muxVal = -1;
    BS_Sig3.m_startBit = 30;
    BS_Sig3.m_bitLength = 2;
    BS_Sig3.m_bigEndian = 0;
    BS_Sig3.m_startByte = 3;
    BS_Sig3.m_startByteMask = 0xc0;
    BS_Sig3.m_stopByte = 3;
    BS_Sig3.m_stopByteMask = 0xff;
    BS_Sig3.m_shiftDown = 6;
    BS_Sig3.m_factor = 1.000000;
    BS_Sig3.m_offset = 0.000000;
    BS_Sig3.m_min = 0.000000;
    BS_Sig3.m_max = 3.000000;
    BS_Sig3.m_isFloat = 0;
    BS_Sig3.m_prec = 0;
    BS_Sig3.m_startVal = 0;
    BS_Sig3.parent = this;
    BS_Sig3.next = &BS_Sig5;
    
    // BS_Sig5
    BS_Sig5.m_isMuxer = 0;
    BS_Sig5.muxVal = -1;
    BS_Sig5.m_startBit = 43;
    BS_Sig5.m_bitLength = 1;
    BS_Sig5.m_bigEndian = 0;
    BS_Sig5.m_startByte = 5;
    BS_Sig5.m_startByteMask = 0xf8;
    BS_Sig5.m_stopByte = 5;
    BS_Sig5.m_stopByteMask = 0xf;
    BS_Sig5.m_shiftDown = 3;
    BS_Sig5.m_factor = 1.000000;
    BS_Sig5.m_offset = 0.000000;
    BS_Sig5.m_min = 0.000000;
    BS_Sig5.m_max = 1.000000;
    BS_Sig5.m_isFloat = 0;
    BS_Sig5.m_prec = 0;
    BS_Sig5.m_startVal = 0;
    BS_Sig5.parent = this;
    BS_Sig5.next = &BS_Sig6;
    
    // BS_Sig6
    BS_Sig6.m_isMuxer = 0;
    BS_Sig6.muxVal = -1;
    BS_Sig6.m_startBit = 44;
    BS_Sig6.m_bitLength = 2;
    BS_Sig6.m_bigEndian = 0;
    BS_Sig6.m_startByte = 5;
    BS_Sig6.m_startByteMask = 0xf0;
    BS_Sig6.m_stopByte = 5;
    BS_Sig6.m_stopByteMask = 0x3f;
    BS_Sig6.m_shiftDown = 4;
    BS_Sig6.m_factor = 1.000000;
    BS_Sig6.m_offset = 0.000000;
    BS_Sig6.m_min = 0.000000;
    BS_Sig6.m_max = 3.000000;
    BS_Sig6.m_isFloat = 0;
    BS_Sig6.m_prec = 0;
    BS_Sig6.m_startVal = 0;
    BS_Sig6.parent = this;
    BS_Sig6.next = NULL;

    applySignalsStartValue();
}
