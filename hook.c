#include "hook.h"

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

void HOOK_LOG(bool write_on_file, const char *func_name, const unsigned int arg_count, const Variable *args)
{
    char buffer[1024] = {0, };
    HOOK_MAKE_LOG_STRING(buffer, func_name, arg_count, args);
    char buffer2[1024] = {0, };
    lib_strcpy(buffer2, buffer);
    if (write_on_file)
    {
        FILE *hFile = fopen("log.txt", "a");
        if(hFile != NULL)
        {
            fwrite(buffer2, sizeof(char), strlen(buffer2), hFile);
            fclose(hFile);    
        }
    }
    else
        printf("%s", buffer2);
}

/***** Initialize org function *****/
typedef char *(*lib_strcpy_type)(char *, const char *);
lib_strcpy_type lib_strcpy = NULL;

static void con() __attribute__((constructor));
void con()
{
    lib_strcpy = (lib_strcpy_type)dlsym(RTLD_NEXT, "strcpy");
}
/************************************/


char *strcpy(char *dest, const char *src) 
{
    // =======================================
    Variable args[2] = { 
        { VT_buffer, (int)dest },
        { VT_string, (int)src }
    };
    HOOK_LOG(true, "strcpy", 2, args);
    // Before Org Function

    char *ret = lib_strcpy(dest, src);

    // After Org Function
    return ret;
}
