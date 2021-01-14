#ifndef MY_SERVER_HANDLER
#define MY_SERVER_HANDLER

#include <string>

unsigned int __stdcall ClientTread(void*);
bool parseCMD(char*, std::string&, std::string&);
int CreateUser(std::string, std::string&);
int LogInUser(std::string, std::string&, bool&);
bool GetMsg(std::string, std::string&, bool);
void NewLog(std::vector<std::string>);

#endif

