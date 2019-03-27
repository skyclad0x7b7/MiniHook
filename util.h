#ifndef __UTIL_H__
#define __UTIL_H__

#include <stdio.h>
#include <string>

#include "variable.h"

namespace Mini
{

std::string MakeLogString(const char *, int, Variable *);

}

#endif // __UTIL_H__