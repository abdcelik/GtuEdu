#include <drivers/driver.h>

using namespace myos::common;
using namespace myos::drivers;
 
Driver::Driver() {}

Driver::~Driver() {}
        
void Driver::Activate() {}

int32_t Driver::Reset()
{
    return 0;
}

void Driver::Deactivate() {}

DriverManager::DriverManager()
{
    numDrivers = 0;
}

void DriverManager::AddDriver(Driver* drv)
{
    drivers[numDrivers++] = drv;
}

void DriverManager::ActivateAll()
{
    for(int32_t i = 0; i < numDrivers; ++i)
        drivers[i]->Activate();
}