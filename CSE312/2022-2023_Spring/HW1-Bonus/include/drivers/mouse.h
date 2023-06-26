#ifndef _MOUSE_H_
#define _MOUSE_H_

#include <common/types.h>
#include <drivers/driver.h>
#include <hardwarecommunication/port.h>
#include <hardwarecommunication/interrupts.h>
#include <lib/utility.h>

namespace myos
{
    namespace drivers
    {
        class MouseDriver : public myos::hardwarecommunication::InterruptHandler, public Driver
        {
                myos::hardwarecommunication::Port8Bit dataport;
                myos::hardwarecommunication::Port8Bit commandport;
                myos::common::uint8_t buffer[3];
                myos::common::uint8_t offset;
                myos::common::uint8_t buttons;

            public:
                MouseDriver(myos::hardwarecommunication::InterruptManager* manager);
                ~MouseDriver();
                virtual myos::common::uint32_t HandleInterrupt(myos::common::uint32_t esp);
                virtual void Activate();
        };
    }
}
    
#endif