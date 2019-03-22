#ifndef __LOGGER_H__
#define __LOGGER_H__

#include "libc_func.h"

namespace Mini
{

class Logger
{
public:
    static Logger& instance(bool forceInit = false)
	{
        if(forceInit)
            Destroy();

        if(_instance == nullptr)
        {
            _instance = new Logger();
        }
        return *_instance;
    }

    static void Destroy()
    {
        if(_instance != nullptr)
        {
            delete _instance;
            _instance = nullptr;
        }
    }

private:
    Logger();
    ~Logger();

    static Logger *_instance;
};

} // namespace Mini

#endif // __LOGGER_H__