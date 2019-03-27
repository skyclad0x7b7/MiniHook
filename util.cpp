#include "util.h"

namespace Mini
{

std::string MakeLogString(char *func_name, int argc, Variable *argv)
{
    std::string ret = func_name;
    ret += "(";
    for(int i = 0; i < argc; i++)
        ret += argv[i].ToString();
    ret += ")";
    return ret;
}

}