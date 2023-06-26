#include <cstring>
#include <fstream>
#include "SuperBlock.hpp"

class FAT12
{
	public:
		FAT12(char* argv[])
		{
			int blockSize = std::stoi(argv[1]);

			if (blockSize < 1 || blockSize > 4)
				throw std::string("Block Size should be between (1 - 4) !\n");

			_blockSizeInByte = blockSize * KBYTE;

			_diskName.assign(argv[2]);
			_diskSize = 4 * KBYTE * _blockSizeInByte;
			_disk = new char[_diskSize];
		}

		~FAT12(){

			delete _superBlock;
			_superBlock = nullptr;

			delete _disk;
			_disk = nullptr;
		}

		void initializeDisk()
		{
			_superBlock = new SuperBlock(3 * _blockSizeInByte, BLOCK_COUNT - 4, _blockSizeInByte, _blockSizeInByte);
			memcpy(_disk, _superBlock->toString().c_str(), _blockSizeInByte);

			std::fstream file(_diskName, std::ios::out);

			if (!file.is_open())
				throw std::string("Disk file could't be opened!");
			
			file.write(_disk, _diskSize);
			file.close();
		}
		
	private:
		char* _disk;
		std::string _diskName;
		long int _diskSize;
		long int _blockSizeInByte;

		SuperBlock* _superBlock;

		const int KBYTE = 1024;
		const int BLOCK_COUNT = 4096;
};