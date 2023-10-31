#include <Graph_lib/Graph.h>
#include <Graph_lib/Simple_window.h>
#include <iostream>
#include <polygon/poly.h>
#include <vector2d/vector2d.h>
using namespace std;
using namespace Graph_lib;

using output = reference_wrapper<Element>;

class Operation;

class Element
{
  public:
    Element(bool n_is_inverted = false, const vector<output>& n_outputs = {})
        : is_inverted(n_is_inverted), outputs(n_outputs)
    {
    }

    void set_inverter (bool new_state) { is_inverted = new_state; }

    bool get_inverter () const { return is_inverted; }

    const vector<output> get_outputs () const { return outputs; }

    bool get_output () const { return out; }

    operator bool () const { return out; }

    Element& operator>> (Operation& rhs);

  protected:
    virtual void calc () = 0;
    bool out = false;

  private:
    bool is_inverted;
    vector<output> outputs;
};

class Source : public Element
{
  public:
    Source(bool value, bool is_inverted = false, const vector<output>& outputs = {}) : Element(is_inverted, outputs)
    {
        out = value;
    }

    void set_output (bool value) { out = value; }

    Source& operator= (bool value)
    {
        out = value;
        return *this;
    }
};

int main (void)
{
    cout << "Hello world";
    return 0;
}