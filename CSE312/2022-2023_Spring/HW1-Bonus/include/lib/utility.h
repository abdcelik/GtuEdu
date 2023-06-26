#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <common/types.h>
#include <lib/unixapi.h>

void printf(myos::common::int8_t* str);
void printfHex(myos::common::uint8_t key);
void print(const myos::common::int8_t* format, myos::common::uint8_t num_args, myos::common::int32_t args[]);
void printUint(myos::common::uint32_t var);
myos::common::uint32_t rand();
myos::common::uint32_t stoi(myos::common::int8_t* buffer);
myos::common::uint32_t readUint32_t(myos::common::int8_t* message);

#endif