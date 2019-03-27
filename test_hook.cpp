#include "hook.h"

lib_fopen_type lib_fopen = NULL;
lib_getpid_type lib_getpid = NULL;

using namespace Mini;

static void con() __attribute__((constructor));
void con()
{
    lib_fopen = (lib_fopen_type)dlsym(RTLD_NEXT, "fopen");
    lib_getpid = (lib_getpid_type)dlsym(RTLD_NEXT, "getpid");
}

 /* ========================================================== */

FILE *fopen(const char *filename, const char *mode)
{
    Variable args[2] = { 
        Variable(VariableType::VT_char_array, (PTR_TYPE)filename),
        Variable(VariableType::VT_char_array, (PTR_TYPE)mode)
    };
    Logger::instance().log(MakeLogString("fopen", 2, args) + "\n");

    FILE *ret = lib_fopen(filename, mode);
    return ret;
}

pid_t getpid()
{
    Logger::instance().log(MakeLogString("getpid", 0, NULL));
    pid_t ret = lib_getpid();
    return ret;
}
