#pragma once
#include <iostream>

#ifdef ENABLE_TRACING
#define TRACE(name)                                                                                                    \
    Tracer a_tracer_obj { name, __FILE__, __LINE__ }
#else
#define TRACE(name)
#endif

#define TRACE_FUNC TRACE(__func__)

class Tracer
{
  public:
    Tracer(const std::string name, const std::string file, int line);
    ~Tracer();

  private:
    std::string s;
    static int counter;
    std::string indent () const;
};