#pragma once

#include <functional>
#include <vector>


namespace resonance_core
{

class AbstractDepender
{
private:
  std::vector<std::function<void()>> m_deconstruction_callbacks;

public:
  void
    subscribe_to_deconstruction(std::function<void()> callback);

  virtual
    ~AbstractDepender();
};

}

