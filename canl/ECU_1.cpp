/////////////////////////////////////////////////////////////////////
// This is normal C++ code so you can do all C++ stuff like:
// - define and derive classes
// - define and overload functions
// - include headers
// - use math.h functions like sin(), sqrt(), pow(), log10() ...
// etc.
/////////////////////////////////////////////////////////////////////

#include "canllib.h"


// global variables
int counter = 0;
unsigned int stromRaw; 
unsigned char byteVal;
unsigned int canId;

// timer based on seconds
Timer myTimer(onMyTimer);
// timer based on mili seconds
MsTimer myMsTimer(onMyMsTimer);

////////////////////////////////////////
// start function (optionally)
////////////////////////////////////////
void onStart()
{
    print("onStart() called\n");
    // start 1 second timer
    setTimer(myTimer, 1);
    // start 100 ms timer
    setTimer(myMsTimer, 100);
}

////////////////////////////////////////
// stop function  (optionally)
////////////////////////////////////////
void onStop()
{
    print("onStop() called\n");
}
 
////////////////////////////////////////
// message RX handler for message ACC_06
////////////////////////////////////////
void ACC_06::onMessage()
{
    // define message BMS_01
    BMS_01 m;

    ////////////////////////////////////
    // signal assignments
    // note: "this->" can be omitted
    ////////////////////////////////////

    // set signal raw value by "="
    m.BMS_01_BZ = counter;

    // set signal physical value
    m.BMS_IstSpannung.setPhys(20.5 / counter );

    // set signal raw value from RX message by "="
    m.BMS_01_CRC = this->ACC_06_CRC;

    // set signal raw value from RX message by set()
    stromRaw = this->ACC_Sollbeschleunigung_02.getRaw();
    m.BMS_IstStrom_02.setRaw(stromRaw); // also: set()
    
    // set message byte at index 6 from RX message
    byteVal = this->getByte(5);
    m.setByte(6, byteVal); // also: m.byte(6) = byte 

    ////////////////////////////////////
    // send on CAN
    ////////////////////////////////////

    // output BMS_01 on default channel
    send(m);

    // send message with CAN ID 0x123 on channel 2  
    message m2(0x123);
    m2.CAN = 2;
    m2.DLC = 8;
    send(m2);
   
    // print in can++ print window
    print("Received message with Id = %x", this->ID);

    // handle counter variable
    counter = counter + 1;
    if (counter == 16)
        counter = 0;   
}


/////////////////////////////////////////////////////////////////////
// signal change handler for signal BMS_01::BMS_01_BZ
/////////////////////////////////////////////////////////////////////
void BMS_01::onMessage()
{
    // @BMS_01::BMS_01_BZ changed code here:
    if (BMS_01_BZ.changed())
    {
        print("New BZ = %d", BMS_01_BZ.getRaw());
    }

}

/////////////////////////////////////////////////////////////////////
// Following function may be defined to be called for all RX messages
// (except messages which are handeled by onMessage() like above).
// If not needed just remove it.
/////////////////////////////////////////////////////////////////////
void onAllMessages(message &m)
{
    canId = m.ID;
}

/////////////////////////////////////////////////////////////////////
// timer handlers
/////////////////////////////////////////////////////////////////////
void onMyTimer()
{
    print("1 sec timer");

    BMS_07 m;

    m.BMS_07_BZ = counter;
    send(m);    

    // restart timer for peridoc occurrence           
    setTimer(myTimer, 1);
}

void onMyMsTimer()
{
    Airbag_09 m1;
	
    m1.Airbag_09_BZ = counter;
    send(m1);

    // restart timer for peridoc occurrence      
    setTimer(myMsTimer, 100);
}

