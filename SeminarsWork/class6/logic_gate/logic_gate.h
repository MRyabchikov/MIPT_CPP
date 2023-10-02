#pragma once
#include <iostream>
#include <vector>
using namespace std;

const char source_gate = 'S';
const char and_gate = 'A';
const char or_gate = 'O';
const char xor_gate = 'X';

class LogicGate
{
  public:
    LogicGate(const char ntype = source_gate, bool nvalue = false, bool nis_inverted = false,
              void (*ncallback)(LogicGate&) = nullptr);
    operator bool () const;
    void operator~();
    LogicGate& operator>> (LogicGate&);
    LogicGate& operator= (bool value);

  private:
    vector<LogicGate*> input_gates;
    vector<LogicGate*> output_gates;
    bool is_part_of_a_cycle () const;
    void find_all_connected_gates (vector<LogicGate*> connections) const;
    const char type;
    bool value;
    bool is_inverted;
    void (*callback)(LogicGate&);
};

LogicGate::LogicGate(const char ntype, bool nvalue, bool nis_inverted, void (*ncallback)(LogicGate&))
    : type(ntype), value(nvalue), is_inverted(nis_inverted), callback(ncallback)
{
}

LogicGate::operator bool () const
{
    switch (type)
    {
    case source_gate:
        return value;
    case and_gate:
        for (int i = 0; i < int(input_gates.size()); i++)
            if (input_gates[i]->value == false)
                return false;
        return true;
    case or_gate:
        for (int i = 0; i < int(input_gates.size()); i++)
            if (input_gates[i]->value == true)
                return true;
        return false;
    case xor_gate:
    {
        if (input_gates.size() == 0)
            throw runtime_error("Xor gate has no input_gates");
        bool nvalue = input_gates[0]->value;
        for (int i = 1; i < int(input_gates.size()); i++)
            nvalue = (value == input_gates[i]->value) ? false : true;
        return value;
    }
    default:
        throw runtime_error("Unknown gate kind");
        return false;
    }
}

void LogicGate::operator~() { is_inverted = !is_inverted; }

LogicGate& LogicGate::operator>> (LogicGate& output)
{
    output_gates.push_back(&output);
    output.input_gates.push_back(this);
    return output;
}

LogicGate& LogicGate::operator= (bool new_value)
{
    if (value != new_value)
    {
        value = new_value;
        callback(*this);
        for (int i = 0; i < int(output_gates.size()); i++)
            *output_gates[i] = bool(output_gates[i]);
    }
    return *this;
}

void LogicGate::find_all_connected_gates(vector<LogicGate*> connections) const
{
    for (int i = 0; i < int(output_gates.size()); i++)
    {
        for (int j = 0; j < int(connections.size()); j++)
            if (connections[j] == output_gates[i])
                throw runtime_error("Cycle found");
        connections.push_back(output_gates[i]);
        output_gates[i]->find_all_connected_gates(connections);
    }
}
