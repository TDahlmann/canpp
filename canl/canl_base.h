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

#ifndef _CANL_BASE_H
#define _CANL_BASE_H

/*-----------------------------------------------------------------------------------------------
    Defines and Macros
  -----------------------------------------------------------------------------------------------*/

// consts
#define MAX_MSG_LEN 64
#define EARLY_PRINT_BUFFER_SIZE 10000
#define PRINT_BUFFER_SIZE 10000

// can fd
#define CANL_MSG_FLAG_BRS 0x00010000;
#define CANL_MSG_FLAG_FDF 0x00020000;

/* forward decl. */
class CanlMessage;
class signal;
class message;

void send(message& m);
void print( const char *format , ... );

/* Canl cnonfig */
typedef unsigned long canpr_timecount_t;
typedef struct _CanlConfig
{
	int timerUsed;
	canpr_timecount_t timerCount;
	int numTimers;
	int channel;
} CanlConfig;

/* Timers */
#define TIMER_EXPIRE_COUNT_MULT 1000 // 1 ms timer for seconds
#define TIMER_MUX_NUM 1000
class Timer
{
public:
	void init(void) {m_active = 0; m_expireCount = 0; m_timerFunc = NULL; m_expireCountMult = TIMER_EXPIRE_COUNT_MULT;};
	Timer() {init();}; 
	Timer(void (*timerFunc)(void));

    canpr_timecount_t m_expireCountMult;
	int m_active;
	canpr_timecount_t m_expireCount;
	void (*m_timerFunc)(void);
};

void setTimer(Timer& timer, canpr_timecount_t  expireTime);
void cancelTimer(Timer& timer);

class MsTimer : public Timer
{
public:
    MsTimer();
    MsTimer(void (*timerFunc)(void));
};

/* can byte */

class CanByte
{
public:
    unsigned char m_byte;

    unsigned char & operator=(unsigned char byte);
    unsigned char & operator=(signal& sig);


};

/* Base class for CAN messages */
class message
{
public:
    
    message();
    message(unsigned long id);

    // can msg handling
    void onMessage(void) {};    
    void rxFunc(CanlMessage *rxMsg);    
    //void OutputMessage(message& m);
    void saveBytes(void);

    // codec funcs
    //unsigned char & byte(int ix);
    void bufferToSignals(void);
    void signalsToBuffer(void);
    void setByte(int ix, unsigned char byte);
    unsigned char getByte(int ix);
    
    unsigned long ID;
    unsigned short DLC;
    unsigned char CAN;
    unsigned char FDF;
    unsigned char BRS;
    

    unsigned char byteArr[MAX_MSG_LEN];
    bool lastByteArrayValid;
    unsigned char byteArrLast[MAX_MSG_LEN];

    // sigs
    int numSignals;
    signal *rootSignal;

};

/* Base class for CAN signals */
class signal 
{
public:
    // constructors
    signal();
    signal(const signal &s2) {raw = s2.raw;}; 
    signal(const unsigned long r) {raw = r;}; 
    signal(unsigned long startBit, unsigned long bitLength, unsigned long m_startByte, unsigned char m_startByteMask,unsigned long m_stopByte, unsigned char m_stopByteMask, unsigned long m_shiftDown, double factor, double offset, double min,double max);
         
    // operators
    signal& operator=(unsigned long raw);
    signal& operator=(const signal& sig);
    bool changed(void);
    bool updated(void);

    // set get
    void setRaw(unsigned long);
    void set(unsigned long);
    unsigned long getRaw(void);
    unsigned long get(void);
    void setPhys(double);
    double getPhys(void);
    
    // conversions
    // can to vals
    inline unsigned long getRawValue(unsigned char* buf);    
    inline double getDoublePhysValue(unsigned long rawVal);
    inline long getIntPhysValue(unsigned long rawVal);
	// vals to can
	unsigned long physToRawValue(double physVal);
	void rawToCanBuffer(unsigned char* buf, unsigned long rawVal);    

    // misc
    //void OnSignalUpdate(void);
    
    // parent
    message* parent;

    // signal chain next
    signal* next;

    enum SIGVALUES
    {
        INIT = 8,
        VAL1,
    };

    unsigned long raw;
    double phys;
    
    // params
    bool m_isMuxer;
    long muxVal; // -1 no mux val

    // bit params
    unsigned long m_startBit;
    unsigned long m_bitLength;

    // byte params
    unsigned long m_startByte;
    unsigned char m_startByteMask;
    unsigned long m_stopByte;
    unsigned char m_stopByteMask;
    unsigned long m_shiftDown;
	bool m_bigEndian; // Motorola flag = big end.
    
	// sig value
    double m_factor;
    double m_offset;
    double m_min;
    double m_max;
	bool m_isSigned;
	bool m_isFloat;
	int m_prec;    
    
};

/* adaptions */
#define variables
#define on void
#define byte(x) byteArr[x % MAX_MSG_LEN]

typedef unsigned char byte;
/* CAN RX */
#define CANL_RX_CAN_ARRAY_SIZE 10000
typedef struct _CanRx
{
	unsigned long canId;
	void (*msgRxFunc)(CanlMessage*);
} CanRx;


/* externs */
extern int canNumberMsgs;
extern CanRx canRxArray[];

/* Canl message */
class CanlMessage
{
public:    
	CanlMessage()
	{
		canId = 0;
		dlc = 8;
		ch = 0;
		flags = 0;
		buf = NULL;
	}
    unsigned long canId;
    unsigned short dlc;
	unsigned int flags;
    unsigned char ch;
    unsigned char *buf;
};


#endif /* _CANL_BASE_H */
