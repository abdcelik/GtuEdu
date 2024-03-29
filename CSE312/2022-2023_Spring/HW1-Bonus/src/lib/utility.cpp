#include <lib/utility.h>

using namespace myos::common;

void intToStr(int32_t value, int8_t* str);

void printf(int8_t* str)
{
    static uint16_t* VideoMemory = (uint16_t*)0xb8000;

    static uint8_t x=0,y=0;

    for(int i = 0; str[i] != '\0'; ++i)
    {
        switch(str[i])
        {
            case '\n':
                x = 0;
                y++;
                break;
            default:
                VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | str[i];
                x++;
                break;
        }

        if(x >= 80)
        {
            x = 0;
            y++;
        }

        if(y >= 25)
        {
            for(y = 0; y < 25; y++)
                for(x = 0; x < 80; x++)
                    VideoMemory[80*y+x] = (VideoMemory[80*y+x] & 0xFF00) | ' ';
            x = 0;
            y = 0;
        }
    }
}

void printfHex(uint8_t key)
{
    char* foo = "00";
    char* hex = "0123456789ABCDEF";
    foo[0] = hex[(key >> 4) & 0xF];
    foo[1] = hex[key & 0xF];
    printf(foo);
}

/*
    You must give true parameter values
    Prints given formatted message to screen
*/
void print(const int8_t* format, uint8_t num_args, int32_t args[])
{
    const uint16_t size = 512;
    const uint8_t intBuffSize = 16;
    uint16_t index = 0;
    uint8_t argsIndex = 0;

    int8_t buffer[size];
    int8_t intBuffer[intBuffSize];
    
    for(uint16_t i = 0 ; i < size ; ++i)
        buffer[i] = 0;

    for(uint16_t i = 0 ; format[i] != 0 ; ++i)
    {
        switch(format[i])
        {
            case '%':
                ++i; // skipping %d

                intToStr(args[argsIndex++], intBuffer);

                for(uint8_t j = 0 ; intBuffer[j] != 0 ; ++j)
                    buffer[index++] = intBuffer[j];

                break;
            default:
                buffer[index++] = format[i];
                break;
        }
    }

    printf(buffer);
}

// Buffer size must be 16
// Fills buffer as character from given integer
void intToStr(int32_t value, int8_t* str)
{
    int32_t i = 0, j = 0;
    int8_t temp;
    
    if (value < 0)
    {
        str[0] = '-';
        i = 1;
        value = -value;
    }

    do
    {
        str[i++] = (value % 10) + '0';
        value /= 10;
    } while (value);

    str[i] = '\0';

    if (str[0] == '-')
        j = 1;

    for (--i; j < i; ++j, --i)
    {
        temp = str[j];
        str[j] = str[i];
        str[i] = temp;
    }
}

void printUint(uint32_t var)
{
    int8_t buff[16];

    for(uint32_t i = 0 ; i < 16 ; ++i)
        buff[i] = 0;

    intToStr(var, buff);
    printf(buff);
}

uint32_t rand()
{
    uint32_t randomSeed = 0;

    __asm__ volatile("rdtsc" : "=a" (randomSeed));
    randomSeed = randomSeed * 1103515245 + 12345;

    return randomSeed;
}

uint32_t stoi(int8_t* buffer)
{
    uint32_t value = 0;

    for (uint32_t i = 0; buffer[i] != '\0'; ++i)
    {
        value *= 10;
        value += buffer[i] - '0';
    }

    return value;
}

uint32_t readUint32_t(int8_t* message)
{
    const uint8_t size = 5;
    int8_t buffer[size];

    for (uint8_t i = 0 ; i < size ; ++i)
        buffer[i] = 0;
    
    printf(message);
    
    if (read(STDIN, buffer, size - 1) == -1)
    {
        printf("ERROR! Reading input from user is failed!\n");
        exit(exit_failure);
    }

    return stoi(buffer);
}