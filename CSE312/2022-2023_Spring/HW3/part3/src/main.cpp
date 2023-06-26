#include "FAT12.hpp"

int main(int argc, char* argv[])
{
	try
    {
        FAT12* fat12 = new FAT12(argc, argv);
        fat12->command(argv);
    }
    catch(std::string e)
    {
    	std::cerr << "Exception: " << e;
    }

    return 0;
}