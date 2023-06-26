#include <drivers/mouse.h>

using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;

MouseDriver::MouseDriver(InterruptManager* manager) 
    : InterruptHandler(manager, 0x2C), dataport(0x60), commandport(0x64) {}

MouseDriver::~MouseDriver() {}
    
void MouseDriver::Activate()
{
    offset = 0;
    buttons = 0;
    
    commandport.Write(0xA8);
    commandport.Write(0x20); // command 0x60 = read controller command byte
    uint8_t status = dataport.Read() | 2;
    commandport.Write(0x60); // command 0x60 = set controller command byte
    dataport.Write(status);

    commandport.Write(0xD4);
    dataport.Write(0xF4);
    dataport.Read();        
}
    
uint32_t MouseDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t status = commandport.Read();

    if (!(status & 0x20))
        return esp;

    buffer[offset] = dataport.Read();
    offset = (offset + 1) % 3;

    if(offset == 0)
    {
        for(uint8_t i = 0; i < 3; i++)
            if((buffer[0] & (0x1<<i)) != (buttons & (0x1<<i)))
                if(buttons & (0x1<<i))
                    esp = (uint32_t)interruptManager->tableManager->Schedule((CPUState*)esp);

        buttons = buffer[0];
    }
    
    return esp;
}