#ifndef _COMMON_H_
#define _COMMON_H_

namespace myos
{
    namespace common
    {
        typedef char                     int8_t;
        typedef unsigned char           uint8_t;
        typedef short                   int16_t;
        typedef unsigned short         uint16_t;
        typedef int                     int32_t;
        typedef unsigned int           uint32_t;
        typedef long long int           int64_t;
        typedef unsigned long long int uint64_t;
    
        typedef const char*              string;

        typedef unsigned int pid_t;
        typedef unsigned int size_t;
        typedef int ssize_t;
    }
}
    
#endif