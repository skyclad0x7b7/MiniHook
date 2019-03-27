#include "variable.h"

namespace Mini
{

Variable::Variable(const VariableType var_type, const PTR_TYPE& data) : _var_type(var_type), _data(data)
{

}

PTR_TYPE Variable::GetData() const
{
    return _data;
}

VariableType Variable::GetVarType() const
{
    return _var_type;
}

std::string Variable::ToString() const
{
    char buf[1024] = { 0, };
    std::string ret = "";
    switch(_var_type)
    {
    case VariableType::VT_bool:
        {
            ret.assign((static_cast<bool>(_data) == true) ? "true" : "false");
            break;
        }
    case VariableType::VT_char:
        {
            snprintf(buf, sizeof(buf), "'%c'", static_cast<char>(_data));
            ret.assign(buf);
            break;
        }
    case VariableType::VT_short:
        {
            snprintf(buf, sizeof(buf), "%d", static_cast<short>(_data));
            ret.assign(buf);
            break;
        }
    case VariableType::VT_int:
        {
            snprintf(buf, sizeof(buf), "%d", static_cast<int>(_data));
            ret.assign(buf);
            break;
        }
    case VariableType::VT_char_array:
        {
            snprintf(buf, sizeof(buf), "\"%s\"", reinterpret_cast<char *>(_data));
            ret.assign(buf);
            break;
        }
    default:
        {
            ret.assign("[Unknwon Type]");
            break;
        }
    }
}

}
