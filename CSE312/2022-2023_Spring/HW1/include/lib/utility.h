#ifndef _UTILITY_H_
#define _UTILITY_H_

#include <common/types.h>

using namespace myos::common;

void printf(char* str);
void printfHex(uint8_t key);
void print(const char* format, uint8_t num_args, int32_t args[]);
void printUint(uint32_t var);

#endif