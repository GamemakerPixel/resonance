#include "core/abstract_subscription_ptr.h"

#include <memory>

#include "core/abstract_depender.h"
#include "core/audio_backend.h"
#include "core/audio_output_device.h"

using namespace resonance_core;


template<typename T>
AbstractSubscriptionPtr<T>::AbstractSubscriptionPtr(std::shared_ptr<T> object)
  : m_weak(object)
{
  if (!object)
  {
    throw NullDependeeException("Dependee object cannot be null");
  }
}


template<typename T>
void
  AbstractSubscriptionPtr<T>::subscribe_to_depender(AbstractDepender& depender)
{
  if (auto shared = m_weak.lock())
  {
    if (!m_shared)
    {
      m_shared = shared;
    }

    m_living_depender_count++;
    depender.subscribe_to_deconstruction([this]() { on_depender_deconstructed(); });
  }
  else
  {
    throw DependeeExpiredException(
      "Cannot subscribe depender after dependee expired\nMake sure to verify it hasn't "
      "expired by calling get_object().expired() and keep it alive with get_object()"
      ".lock() while adding dependers."
    );
  }
}


template<typename T>
std::weak_ptr<T>
  AbstractSubscriptionPtr<T>::get_object() const
{
  return m_weak;
}


template<typename T>
void
  AbstractSubscriptionPtr<T>::on_depender_deconstructed()
{
  m_living_depender_count--;

  if (m_living_depender_count <= 0)
  {
    m_shared = nullptr;
  }
}


template class AbstractSubscriptionPtr<AudioBackend>;
template class AbstractSubscriptionPtr<AudioOutputDevice>;


/*
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
  std::weak_ptr<T> m_weak;
  int m_living_depender_count = 0;

public:
  // Note that ownership of the object isn't taken until subscribe_to_depender is called
  // at least once.
  AbstractSubscriptionPtr(std::shared_ptr<T> object);

  void
    subscribe_to_depender(AbstractDepender& depender);

  std::weak_ptr<T>
    get_object();

private:
  void
    on_depender_deconstructed();
};
*/
