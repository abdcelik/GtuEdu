#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#include <common/types.h>
#include <drivers/driver.h>
#include <hardwarecommunication/interrupts.h>
#include <hardwarecommunication/port.h>
#include <lib/utility.h>

namespace myos
{
    namespace drivers
    {
        class KeyboardEventHandler
        {
            public:
                KeyboardEventHandler();
                ~KeyboardEventHandler();

                virtual void OnKeyDown(myos::common::int8_t);
                virtual void OnKeyUp(myos::common::int8_t);
        };

        class PrintfKeyboardEventHandler : public KeyboardEventHandler
        {
            public:
                PrintfKeyboardEventHandler();
                ~PrintfKeyboardEventHandler();

                void OnKeyDown(myos::common::int8_t c);
        };

        class KeyboardDriver : public myos::hardwarecommunication::InterruptHandler, public Driver
        {
                myos::hardwarecommunication::Port8Bit dataport;
                myos::hardwarecommunication::Port8Bit commandport;
                KeyboardEventHandler* handler;

            public:
                KeyboardDriver(myos::hardwarecommunication::InterruptManager* manager, KeyboardEventHandler *handler);
                ~KeyboardDriver();
                virtual myos::common::uint32_t HandleInterrupt(myos::common::uint32_t esp);
                virtual void Activate();
        };
    }
}
    
#endif