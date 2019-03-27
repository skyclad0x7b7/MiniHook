#ifndef __LOGGER_H__
#define __LOGGER_H__

#include <stdio.h>
#include <fstream>
#include <string>
#include <string.h>
#include "libc_func.h"

const char *const LOG_PATH = "./logs";

namespace Mini
{

class Logger
{
public:
    static Logger& instance()
    {
        if(_instance == NULL)
            _instance = new Logger();
        return *_instance;
    }

    void reopen_logfile();
    void log(const std::string&);
private:
    Logger();
    ~Logger();

    pid_t _pid;
    char _filename[256];
    std::ofstream _ofs;
    static Logger *_instance;
};

} // namespace Mini

#endif // __LOGGER_H__