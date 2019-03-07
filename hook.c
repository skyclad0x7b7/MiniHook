#include "hook.h"

/***** Initialize org function *****/
typedef FILE *(*lib_fopen_type)(const char *, const char *);
lib_fopen_type lib_fopen = NULL;

static void con() __attribute__((constructor));
void con()
{
    lib_fopen = (lib_fopen_type)dlsym(RTLD_NEXT, "fopen");
}
/************************************/

void HOOK_MAKE_LOG_STRING(char *buffer, const char *func_name, const unsigned int arg_count, const Variable *args)
{
    char temp[1024] = {0,};
    snprintf(buffer, 1024, "%s(", func_name);

    for (int i = 0; i < arg_count; i++)
    {
        switch(args[i]._type)
        {
        case VT_string:
        {
            snprintf(temp, 1024, "\"%s\"", (char *)(args[i]._var));
            break;
        }
        case VT_buffer:
        {
            snprintf(temp, 1024, "0x%08x", (unsigned)(args[i]._var));
            break;
        }
        default:
        {
            snprintf(temp, 1024, "[UNKNOWN_TYPE_ERROR]");
            break;
        }
        }
        strcat(buffer, temp);
        if((i+1) != arg_count)
            strcat(buffer, ", ");
    }
    strcat(buffer, ")\n");
}

void HOOK_LOG(LoggingType loggingType, const char *func_name, const unsigned int arg_count, const Variable *args)
{
    char buffer[1024] = {0, };
    HOOK_MAKE_LOG_STRING(buffer, func_name, arg_count, args);
    char buffer2[1024] = {0, };
    switch(loggingType)
    {
        case LT_STDOUT:
        {
            printf("%s", buffer2);
            break;
        }
        case LT_FILE:
        {
            FILE *hFile = lib_fopen("log.txt", "a");
            if(hFile != NULL)
            {
                fwrite(buffer2, sizeof(char), strlen(buffer2), hFile);
                fclose(hFile);    
            }
            break;
        }
    }
}

 /* ========================================================== */

FILE *fopen(const char *filename, const char *mode) 
{
    Variable args[2] = { 
        { VT_string, (int)filename },
        { VT_string, (int)mode }
    };
    HOOK_LOG(LT_FILE, "fopen", 2, args);
    FILE *ret = lib_fopen(filename, mode);
    return ret;
}
