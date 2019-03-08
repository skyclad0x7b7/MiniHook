#include "hook.h"

/***** Initialize org function *****/
typedef FILE *(*lib_fopen_type)(const char *, const char *);
lib_fopen_type lib_fopen = NULL;

typedef size_t(*lib_fwrite_type)(const void *, size_t, size_t, FILE *);
lib_fwrite_type lib_fwrite = NULL;

typedef size_t(*lib_fread_type)(void *restrict, size_t, size_t, FILE *restrict);
lib_fread_type lib_fread = NULL;

typedef int(*lib_fclose_type)(FILE *);
lib_fclose_type lib_fclose = NULL;

typedef int(*lib_unlink_type)(const char *);
lib_unlink_type lib_unlink = NULL;

typedef int(*lib_remove_type)(const char *);
lib_remove_type lib_remove = NULL;

typedef int(*lib_rename_type)(const char *, const char *);
lib_rename_type lib_rename = NULL;

typedef mode_t(*lib_umask_type)(mode_t);
lib_umask_type lib_umask = NULL;

typedef pid_t(*lib_getpid_type)();
lib_getpid_type lib_getpid = NULL;

typedef pid_t(*lib_fork_type)();
lib_fork_type lib_fork = NULL;


static void con() __attribute__((constructor));
void con()
{
    lib_fopen = (lib_fopen_type)dlsym(RTLD_NEXT, "fopen");
    lib_fwrite = (lib_fwrite_type)dlsym(RTLD_NEXT, "fwrite");
    lib_fread = (lib_fread_type)dlsym(RTLD_NEXT, "fread");
    lib_fclose = (lib_fclose_type)dlsym(RTLD_NEXT, "fclose");
    lib_unlink = (lib_unlink_type)dlsym(RTLD_NEXT, "unlink");
    lib_remove = (lib_remove_type)dlsym(RTLD_NEXT, "remove");
    lib_rename = (lib_rename_type)dlsym(RTLD_NEXT, "rename");
    lib_umask = (lib_umask_type)dlsym(RTLD_NEXT, "umask");
    lib_getpid = (lib_getpid_type)dlsym(RTLD_NEXT, "getpid");
    lib_fork = (lib_fork_type)dlsym(RTLD_NEXT, "fork");
}
/************************************/

void HOOK_MAKE_LOG_STRING(char *buffer, const char *func_name, const unsigned int arg_count, const Variable *args)
{
    char temp[1024] = {0,};
    snprintf(buffer, 1024, "%s(", func_name);

    for (int i = 0; i < arg_count && args != NULL; i++)
    {
        switch(args[i]._type)
        {
        case VT_unsigned_int:
        {
            snprintf(temp, 1024, "%u", (unsigned)(args[i]._var));
            break;
        }
        case VT_string:
        {
            snprintf(temp, 1024, "\"%s\"", (char *)(args[i]._var));
            break;
        }
        case VT_offset:
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

void HOOK_LOG(const LoggingType loggingType, const char *func_name, const unsigned int arg_count, const Variable *args)
{
    char buffer[1024] = {0, };
    HOOK_MAKE_LOG_STRING(buffer, func_name, arg_count, args);
    switch(loggingType)
    {
        case LT_STDOUT:
        {
            printf("%s", buffer);
            break;
        }
        case LT_FILE:
        {
            char filename[256] = {0, };
            snprintf(filename, sizeof(filename), "pid_%d.log", lib_getpid());
            FILE *hFile = lib_fopen(filename, "a");
            if(hFile != NULL)
            {
                lib_fwrite(buffer, sizeof(char), strlen(buffer), hFile);
                lib_fclose(hFile);    
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

size_t fwrite(const void *buffer, size_t size, size_t count, FILE *stream)
{
    Variable args[4] = { 
        { VT_string, (int)buffer },
        { VT_unsigned_int, (int)size },
        { VT_unsigned_int, (int)count },
        { VT_offset, (int)stream }
    };
    HOOK_LOG(LT_FILE, "fwrite", 4, args);
    size_t ret = lib_fwrite(buffer, size, count, stream);
    return ret;
}

size_t fread(void *restrict buffer, size_t size, size_t count, FILE *restrict stream)
{
    Variable args[4] = { 
        { VT_string, (int)buffer },
        { VT_unsigned_int, (int)size },
        { VT_unsigned_int, (int)count },
        { VT_offset, (int)stream }
    };
    HOOK_LOG(LT_FILE, "fread", 4, args);
    size_t ret = lib_fread(buffer, size, count, stream);
    return ret;
}

int fclose(FILE *stream)
{
    Variable args[1] = { 
        { VT_offset, (int)stream }
    };
    HOOK_LOG(LT_FILE, "fclose", 1, args);
    int ret = lib_fclose(stream);
    return ret; 
}

int unlink(const char *filename)
{
    Variable args[1] = { 
        { VT_string, (int)filename }
    };
    HOOK_LOG(LT_FILE, "unlink", 1, args);
    int ret = lib_unlink(filename);
    return ret;
}

int remove(const char *filename)
{
    Variable args[1] = { 
        { VT_string, (int)filename }
    };
    HOOK_LOG(LT_FILE, "remove", 1, args);
    int ret = lib_remove(filename);
    return ret;
}

int rename(const char *oldname, const char *newname)
{
    Variable args[2] = { 
        { VT_string, (int)oldname },
        { VT_string, (int)newname }
    };
    HOOK_LOG(LT_FILE, "remove", 2, args);
    int ret = lib_rename(oldname, newname);
    return ret;
}

mode_t umask(mode_t mode)
{
    Variable args[1] = { 
        { VT_unsigned_int, (int)mode }
    };
    HOOK_LOG(LT_FILE, "umask", 1, args);
    mode_t ret = lib_umask(mode);
    return ret;
}

pid_t getpid()
{
    HOOK_LOG(LT_FILE, "getpid", 0, NULL);
    pid_t ret = lib_getpid();
    return ret;
}

pid_t fork()
{
    HOOK_LOG(LT_FILE, "fork", 0, NULL);
    pid_t ret = lib_fork();
    return ret;
}

