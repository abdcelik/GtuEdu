#include <drivers/keyboard.h>

using namespace myos;
using namespace myos::common;
using namespace myos::drivers;
using namespace myos::hardwarecommunication;

KeyboardEventHandler::KeyboardEventHandler() {}

KeyboardEventHandler::~KeyboardEventHandler() {}

void KeyboardEventHandler::OnKeyDown(int8_t) {}

void KeyboardEventHandler::OnKeyUp(int8_t) {}

PrintfKeyboardEventHandler::PrintfKeyboardEventHandler() {}

PrintfKeyboardEventHandler::~PrintfKeyboardEventHandler() {}

void PrintfKeyboardEventHandler::OnKeyDown(int8_t c)
{
    int8_t* foo = " ";
    foo[0] = c;
    printf(foo);
}

KeyboardDriver::KeyboardDriver(InterruptManager* manager, KeyboardEventHandler *handler)
    : InterruptHandler(manager, 0x21), dataport(0x60), commandport(0x64)
{
    this->handler = handler;
}

KeyboardDriver::~KeyboardDriver() {}

void KeyboardDriver::Activate()
{
    while(commandport.Read() & 0x1)
        dataport.Read();
    
    commandport.Write(0xae); // activate interrupts
    commandport.Write(0x20); // command 0x20 = read controller command byte
    uint8_t status = (dataport.Read() | 1) & ~0x10;
    commandport.Write(0x60); // command 0x60 = set controller command byte
    dataport.Write(status);
    dataport.Write(0xf4);
}

uint32_t KeyboardDriver::HandleInterrupt(uint32_t esp)
{
    uint8_t key = dataport.Read();
    
    if(handler == 0 || key >= 0x80)
        return esp;

    switch(key)
    {
        case 0x02:
            interruptManager->tableManager->AddCurrentProcessBuffer('1');
            handler->OnKeyDown('1');
            break;

        case 0x03:
            interruptManager->tableManager->AddCurrentProcessBuffer('2');
            handler->OnKeyDown('2');
            break;

        case 0x04:
            interruptManager->tableManager->AddCurrentProcessBuffer('3');
            handler->OnKeyDown('3');
            break;

        case 0x05:
            interruptManager->tableManager->AddCurrentProcessBuffer('4');
            handler->OnKeyDown('4');
            break;

        case 0x06:
            interruptManager->tableManager->AddCurrentProcessBuffer('5');
            handler->OnKeyDown('5');
            break;

        case 0x07:
            interruptManager->tableManager->AddCurrentProcessBuffer('6');
            handler->OnKeyDown('6');
            break;

        case 0x08:
            interruptManager->tableManager->AddCurrentProcessBuffer('7');
            handler->OnKeyDown('7');
            break;

        case 0x09:
            interruptManager->tableManager->AddCurrentProcessBuffer('8');
            handler->OnKeyDown('8');
            break;

        case 0x0A:
            interruptManager->tableManager->AddCurrentProcessBuffer('9');
            handler->OnKeyDown('9');
            break;

        case 0x0B:
            interruptManager->tableManager->AddCurrentProcessBuffer('0');
            handler->OnKeyDown('0');
            break;

        case 0x1C:
            interruptManager->tableManager->AddCurrentProcessBuffer('\n');
            handler->OnKeyDown('\n');
            break;

        case 0x1E:
            esp = (uint32_t)interruptManager->tableManager->Schedule((CPUState*)esp);
            break;
            
        default:
            break;
    }

    return esp;
}