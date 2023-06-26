#ifndef _DRIVER_H_
#define _DRIVER_H_

#include <common/types.h>

namespace myos
{
    namespace drivers
    {
        class Driver
        {
            public:
                Driver();
                ~Driver();
                
                virtual void Activate();
                virtual myos::common::int32_t Reset();
                virtual void Deactivate();
        };

        class DriverManager
        {
            private:
                Driver* drivers[265];
                myos::common::int32_t numDrivers;
                
            public:
                DriverManager();
                void AddDriver(Driver*);
                void ActivateAll();
        };
    }
}
    
#endif