#include "logic_gate.h"
#include <iostream>
#include <vector>
using namespace std;

LogicGate::LogicGate(bool init_value) : value(init_value) {}

LogicGate::LogicGate(ElementType init_type) : type(init_type) {}

bool LogicGate::signal() const
{
    bool tmp_value;
    switch (type)
    {
    case ElementType::SRC:
        return value;
    case ElementType::AND_GATE:
    {
        tmp_value = true;
        for (const LogicGate& in : inputs)
            tmp_value *= in.signal();
        return tmp_value;
    }
    case ElementType::OR_GATE:
    {
        tmp_value = false;
        for (const LogicGate& in : inputs)
            tmp_value += in.signal();
        return tmp_value;
    }
    case ElementType::NOT_GATE:
        return !value;
    default:
        throw runtime_error("Unknown type of logic gate");
    }
}

LogicGate& LogicGate::operator>> (LogicGate& new_connection)
{
    if (new_connection.type == ElementType::SRC)
        throw runtime_error("Trying to use source gate as output");
    outputs.emplace_back(new_connection);
    new_connection.inputs.emplace_back(*this);
    return new_connection;
}
