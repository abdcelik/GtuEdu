#include <list>

class Directory
{
	public:
		class Entry
		{
			std::string _fileName;
			std::string _ext;
			std::string _attr;
			std::string _time;
			std::string _date;
			std::string _firstBlock;
			std::string _size;
		};

		std::string dirNum;
		std::string dirName;
		std::list<Entry*> files;
		std::list<Directory*> dirs;

		Directory() {}

		Directory(std::string dirNum, std::string dirName)
		{
			this->dirNum.assign(dirNum);
			this->dirName.assign(dirName);
		}

		~Directory()
		{
			files.clear();
			dirs.clear();
		}

		Directory& operator=(const Directory& other)
		{
			dirNum.assign(other.dirNum);
			dirName.assign(other.dirName);

			files = other.files;
			dirs = other.dirs;

			return *this;
		}
};