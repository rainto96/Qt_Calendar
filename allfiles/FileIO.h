#ifndef FILEIO_H
#define FILEIO_H

#include "date.h"
class FileIO
{
	private:
	public:
        static void writeToFile(Date* dates,char* dir);
		static void readFromFile(Date* dates,char* dir,int howmany);
};
#endif
