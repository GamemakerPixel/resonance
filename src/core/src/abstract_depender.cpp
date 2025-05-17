#include "core/abstract_depender.h"

#include <functional>
#include <vector>

using namespace resonance_core;


void
  AbstractDepender::subscribe_to_deconstruction(std::function<void()> callback)
{
  m_deconstruction_callbacks.push_back(callback);
}


AbstractDepender::~AbstractDepender()
{
  for (std::function<void()> callback: m_deconstruction_callbacks)
  {
    callback();
  }
}
