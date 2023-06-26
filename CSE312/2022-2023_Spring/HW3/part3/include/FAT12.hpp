#include <fstream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <iterator>
#include <map>
#include <sstream>
#include <algorithm>
#include <bits/stdc++.h>
#include "Directory.hpp"
#include "SuperBlock.hpp"

#define KBYTE 1024

class FAT12
{
	enum CommandCode {eDir, eMkdir, eRmdir, eDumpe2fs, eWrite, eRead, eDel, cError};

	public:
		FAT12(int args, char* argv[])
		{
			if (checkParameters(args, argv) == false)
				throw std::string("Wrong command line argument! Check the command table!\nUsage: ./fileSystemOper fileSystem.data operation parameters\n");

			_diskName.assign(argv[1]);
			_command.assign(argv[2]);

			rootDir = new Directory(std::to_string(0), "\\");
			DAT[rootDir->dirName] = 0;

			currentDir = new Directory();
			currentDir = rootDir;

			NUM_OF_FILES = 0;
			NUM_OF_DIRECTORIES = 1;

			mount();	// Read disk image file
			loadDisk();
		}

		~FAT12()
		{
			delete _superBlock;
			_superBlock = nullptr;

			delete _disk;
			_disk = nullptr;
		}

		void mount()
		{
			_diskSize = getFileSize();
			_disk = new char[_diskSize];

			std::fstream file(_diskName, std::ios::in);

			if (!file.is_open())
				throw std::string("Disk file could't be opened!");

			file.read(_disk, _diskSize);
			file.close();
		}

		void unmount()
		{
			std::fstream file(_diskName, std::ios::out);

			if (!file.is_open())
				throw std::string("Disk file could't be opened!");

			file.write(_disk, _diskSize);
			file.close();
		}

		void loadDisk()
		{
			char buffer[KBYTE];

			readByte(0, buffer, 1024);

			std::string sbuffer(buffer);
			std::vector<std::string> tokens = split(sbuffer);

			_superBlock = new SuperBlock(std::stoi(tokens[0]), std::stoi(tokens[1]), std::stoi(tokens[2]), std::stoi(tokens[3]));
			_blockSizeInByte = _superBlock->blockSizeInByte;
		}

		void readByte(int block, char* buffer, int size)
		{
			memcpy(buffer, _disk + (block * _blockSizeInByte), size);
		}

		void writeByte(int block, const char* buffer, int size)
		{
			memcpy(_disk + (block * _blockSizeInByte), buffer, size);
		}

		void command(char* argv[])
		{
			switch(hashIt(_command))
			{
				case eDir:
					dir(argv);
					break;
				case eMkdir:
					mkdir(argv);
					break;
				case eRmdir:
					rmdir(argv);
					break;
				case eDumpe2fs:
					dumpe2fs();
					break;
				case eWrite:
					cwrite(argv);
					break;
				case eRead:
					cread(argv);
					break;
				case eDel:
					del(argv);
					break;
				default:
					throw std::string("Undefined command!\n");
			}
		}	

		void dir(char* argv[])
		{
			std::map<std::string, int>::iterator it;

			if (it == DAT.end())
				throw std::string("dir: cannot find such directory!\n");

			std::cout << "\\" << std::endl;
		}

		void mkdir(char* argv[])
		{
			std::string args(argv[3]);
			std::replace(args.begin(), args.end(), '\\', ' ');
			std::vector<std::string> tokens = split(args);
			std::map<std::string, int>::iterator it;

			for (unsigned int i = 0 ; i < tokens.size() - 1 ; ++i)
			{
				it = DAT.find(tokens[i]);

				if (it == DAT.end())
					throw std::string("mkdir: cannot create directory \n");
			}

			++NUM_OF_DIRECTORIES;

			Directory newDirect;

			newDirect.dirNum.assign(std::to_string(NUM_OF_DIRECTORIES));
			newDirect.dirName.assign(tokens[tokens.size()-1]);

			DAT[newDirect.dirName] = NUM_OF_DIRECTORIES;

			currentDir->dirs.push_back(&newDirect);
		}

		void rmdir(char* argv[])
		{
			std::cout << "rmdir : not implemented !" << std::endl;
		}

		void dumpe2fs()
		{
			std::cout << "NUMBER OF FREE BLOCKS : " << _superBlock->numberOfFreeBlock << std::endl;
			std::cout << "NUMBER OF DIRECTORIES : " << NUM_OF_DIRECTORIES <<std::endl;
			std::cout << "NUM OF FILES : " << NUM_OF_FILES << std::endl;
			std::cout << "BLOCK SIZE : " << _superBlock->blockSizeInByte <<  std::endl;
		}

		void cwrite(char* argv[])
		{
			std::cout << "write : not implemented !" << std::endl;
		}

		void cread(char* argv[])
		{
			std::cout << "read : not implemented !" << std::endl;
		}

		void del(char* argv[])
		{
			std::cout << "del : not implemented !" << std::endl;
		}

	private:
		std::string _diskName;
		std::string _command;

		int NUM_OF_FILES;
		int NUM_OF_DIRECTORIES;

		char* _disk;
		long int _diskSize;
		long int _blockSizeInByte;

		SuperBlock* _superBlock;

		//bitset<disksize> freeblocks(0);

		Directory* rootDir;
		Directory* currentDir;
		std::map<std::string, int> FAT;
		std::map<std::string, int> DAT;

		const int BLOCK_COUNT = 4096;

		bool checkParameters(int argc, char* argv[])
		{
			if (argc < 3)
				return false;

			switch(hashIt(argv[2]))
			{
				case eDumpe2fs:
					if (argc != 3)
						return false;
					break;
				case eDir:
				case eMkdir:
				case eRmdir:
				case eDel:
					if (argc != 4)
						return false;
					break;
				case eWrite:
				case eRead:
					if (argc != 5)
						return false;
					break;
				default:
					return false;
			}

			return true;
		}

		int getFileSize()
		{
			std::streampos begin, end;
			std::ifstream file(_diskName, std::ios::binary);

			if (!file.is_open())
				throw std::string("Disk file could't be opened!");

			begin = file.tellg();
			file.seekg (0, std::ios::end);

			end = file.tellg();
			file.close();

			return end - begin;
		}

		std::vector<std::string> split(std::string str)
		{
			std::istringstream buf(str);
			std::istream_iterator<std::string> beg(buf), end;

			std::vector<std::string> tokens(beg, end);

			return tokens;
		}

		CommandCode hashIt(std::string const& str)
		{
			if (!str.compare("dir")) 		return eDir;
			if (!str.compare("mkdir")) 		return eMkdir;
			if (!str.compare("rmdir")) 		return eRmdir;
			if (!str.compare("dumpe2fs")) 	return eDumpe2fs;
			if (!str.compare("write")) 		return eWrite;
			if (!str.compare("read")) 		return eRead;
			if (!str.compare("del")) 		return eDel;

			return cError;
		}
};