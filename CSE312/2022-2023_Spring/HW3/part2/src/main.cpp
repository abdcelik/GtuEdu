#include "FAT12.hpp"

int main(int argc, char* argv[])
{
	try
	{
    	if (argc != 3)
       		throw std::string("Wrong command line argument!\nUsage: ./makeFileSystem blockSize fileSystem.dat\n");

        FAT12* fat12 = new FAT12(argv);
        fat12->initializeDisk();
    }
    catch(std::string e)
	{
    	std::cerr << "Exception: " << e;
    }

	return 0;
}