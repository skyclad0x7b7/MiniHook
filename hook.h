#define _GNU_SOURCE

#include <dlfcn.h>
#include <pthread.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#ifdef _X64
typedef uint64_t PTR_TYPE;
#else
typedef uint32_t PTR_TYPE;
#endif

typedef enum _LoggingType
{
    LT_STDOUT = 1,
    LT_FILE = 2
} LoggingType;

typedef enum _VariableType 
{
    VT_bool = 1,
    VT_char,
    VT_int,
    VT_unsigned_int,
    VT_string,
    VT_buffer,
    VT_offset
} VariableType;

typedef struct _Variable
{
    VariableType _type;
    PTR_TYPE _var;
} Variable;
