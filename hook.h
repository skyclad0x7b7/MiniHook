#define _GNU_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

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
    int _var;
} Variable;
