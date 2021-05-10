/////////////////////////////////////////////////////////////////////
// This is normal C++ code so you can do all C++ stuff like:
// - define and derive classes
// - define and overload functions
// - include headers
// etc.
/////////////////////////////////////////////////////////////////////

#include "canllib.h"

void BMS_07::onMessage()
{
    print("BMS_07 received on CAN %d", this->CAN);

    message m(0x456);
    m.setByte(0, this->BMS_07_BZ.get());
    m.DLC = 8;
    send(m);
}


