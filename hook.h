#define _GNU_SOURCE

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <dlfcn.h>

typedef enum _VariableType 
{
    VT_bool = 1,
    VT_char = 2,
    VT_int = 3,
    VT_unsigned_int = 4,
    VT_string = 5,
    VT_buffer = 6
} VariableType;

typedef struct _Variable
{
    VariableType _type;
    int _var;
} Variable;

char *strcpy(char *dest, const char *src);
