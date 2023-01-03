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
unsigned int currentRaw; 
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
// actions triggered by key press in
// CAN++ main window  (optionally)
////////////////////////////////////////
void onKey(char key)
{
	if (key == 'a')
	{
		message m(0xaa);
		m.DLC = 8;
		send(m);
	}
	else if (key == 'b')
	{
		message m(0xbb);
		m.DLC = 8;
		send(m);
	}
}

///////////////////////////////////////////////////////////////////////////////
// Actions triggered by a command received by can++ in server mode (optionally)
// Thus this command was sent from a client program. Example usages:
// - start a test function
// - set a global variable to switch behaviour
// - send a CAN message provided by command string <cmd>
// ...
////////////////////////////////////////
void onCommand(char* cmd, int len)
{
	print("Command received: %s", cmd);
}

////////////////////////////////////////
// message RX handler for message RadarControl
////////////////////////////////////////
void RadarControl::onMessage()
{
	// look on CAN 1 only
	if (CAN != 1)
		return;

	// define message BatteryUsage
	BatteryUsage m;

	////////////////////////////////////
	// signal assignments
	// note: "this->" can be omitted
	////////////////////////////////////

	// set signal raw value by "="
	m.BU_Count = counter;

	// set signal physical value
	m.BU_Volatage.setPhys(20.5 / counter );

	// set signal raw value from RX message by "="
	m.BU_CRC = this->RC_CRC;

	// set signal raw value from RX message by set()
	currentRaw = this->RC_Accerlation.getRaw();
	m.BU_Current.setRaw(currentRaw); // also: set()
	
	// set message byte at index 6 from RX message
	byteVal = this->getByte(5);
	m.setByte(6, byteVal); // also: m.byte(6) = byte 

	////////////////////////////////////
	// send on CAN
	////////////////////////////////////

	// output BatteryUsage on default channel
	send(m);

	// send message with CAN ID 0x123 on channel 2  
	message m2(0x123);
	m2.CAN = 2;
	m2.DLC = 8;
	send(m2);
   
	// print in can++ print window
	//print("Received message with Id = %x", this->ID);

	// handle counter variable
	counter = counter + 1;
	if (counter == 16)
		counter = 0;   
}


/////////////////////////////////////////////////////////////////////
// signal change handler for signal BatteryUsage::BatteryUsage_Count
/////////////////////////////////////////////////////////////////////
void BatteryUsage::onMessage()
{
	// @BatteryUsage::BatteryUsage_Count changed code here:
	if (BU_Count.changed())
	{
		//print("New BU_Count = %d", BU_Count.getRaw());
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

	BatteryState m;

	m.BS_Count = counter;
	send(m);	

	// restart timer for peridoc occurrence		   
	setTimer(myTimer, 1);
}

void onMyMsTimer()
{
	LockAttempts m1;
	
	m1.LA_Count = counter;
	send(m1);

	// restart timer for peridoc occurrence	  
	setTimer(myMsTimer, 100);
}

