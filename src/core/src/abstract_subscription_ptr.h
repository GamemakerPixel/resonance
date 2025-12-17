#pragma once

#include <memory>


namespace resonance_core
{

class AbstractDepender;

// Will act as a shared ptr to an object until all objects passed as dependers of the
// object are deconstructed (they will notify this ptr when that happens, it will keep
// a reference count). After this, it will act as a weak ptr. It will not act as a
// shared ptr until it has subscribed to at least one depender.
template <typename T>
class AbstractSubscriptionPtr
{
private:
  std::shared_ptr<T> m_shared = nullptr;
  const std::weak_ptr<T> m_weak;
  int m_living_depender_count = 0;

public:
  // Note that ownership of the object isn't taken until subscribe_to_depender is called
  // at least once.
  AbstractSubscriptionPtr(std::shared_ptr<T> object);

  void
    subscribe_to_depender(AbstractDepender& depender);

  std::weak_ptr<T>
    get_object() const;

private:
  void
    on_depender_deconstructed();
};


class NullDependeeException: public std::logic_error
{
public:
  NullDependeeException(const std::string& message)
  : std::logic_error(message) {}
};


class DependeeExpiredException: public std::runtime_error
{
public:
  DependeeExpiredException(const std::string& message)
  : std::runtime_error(message) {}
};

}

