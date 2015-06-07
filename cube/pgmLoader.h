#ifndef _PGMLOADER_H_
#define _PGMLOADER_H_

#include <string>

class pgmLoader
{
  public:
    static unsigned char* loadPGM(std::string filename, int& width, int& height);
};
#endif