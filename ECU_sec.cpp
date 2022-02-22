/////////////////////////////////////////////////////////////////////
// This is normal C++ code so you can do all C++ stuff like:
// - define and derive classes
// - define and overload functions
// - include headers
// etc.
/////////////////////////////////////////////////////////////////////

#include "canllib.h"

void BatteryState::onMessage()
{
	// look on CAN 1 only
	if (CAN != 1)
		return;

	print("BatteryState received on CAN %d", this->CAN);

	message m(0x456);
	m.setByte(0, this->BS_Count.get());
	m.DLC = 8;
	send(m);
}

