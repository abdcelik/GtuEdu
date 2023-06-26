#include <iostream>
#include <string>

class SuperBlock
{
	public:
		int rootDirLocation = 0;
		int numberOfFreeBlock = 0;
		int blockSizeInByte = 0;
		int fatTableLocation = 0;

		SuperBlock() {}

		SuperBlock(int rootDirLocation, int numberOfFreeBlock, int blockSizeInByte, int fatTableLocation)
			:rootDirLocation(rootDirLocation), numberOfFreeBlock(numberOfFreeBlock), blockSizeInByte(blockSizeInByte), fatTableLocation(fatTableLocation) {}

		~SuperBlock() {}

		std::string toString()	// NOTE
		{
			return "rootDirLocation: "+ std::to_string(rootDirLocation) + " " +
				"freeblockcount: " + std::to_string(numberOfFreeBlock) + " " +  
				"blocksize: " + std::to_string(blockSizeInByte) + " " + 
				"faTableLocation: " + std::to_string(fatTableLocation) + " ";
				"superBlockLocation: " + std::to_string(0);
		}	
};