#pragma once
#include <functional>
#include <iostream>
#include <vector>
using namespace std;

enum class ElementType
{
    SRC,
    AND_GATE,
    OR_GATE,
    NOT_GATE
};

class LogicGate;

using LogicGateRef = std::reference_wrapper<LogicGate>;

class LogicGate
{
  public:
    LogicGate(bool init_value = false);
    LogicGate(ElementType type);
    bool signal () const;
    LogicGate& operator>> (LogicGate&);

  private:
    bool value;
    ElementType type;
    vector<LogicGateRef> inputs = {};
    vector<LogicGateRef> outputs = {};
};