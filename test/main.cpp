#include<fstream>
#include<iostream>
#include<sstream>
#include<string>

#include <stdio.h>  /* defines FILENAME_MAX */
// #define WINDOWS  /* uncomment this line to use it for windows.*/ 
#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif
#include<iostream>
 
std::string GetCurrentWorkingDir( void ) {
  char buff[FILENAME_MAX];
  GetCurrentDir( buff, FILENAME_MAX );
  std::string current_working_dir(buff);
  return current_working_dir;
}

int main() {
  std::ifstream infile("res/res.txt");
  std::string line;
  while (std::getline(infile, line)) {
    std::cerr << line << std::endl;
    return 0;
  }
  std::cout << "fail" << GetCurrentWorkingDir() << std::endl;
  return 1;
}
