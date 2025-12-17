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


template class resonance_core::AbstractSubscriptionPtr<AudioBackend>;
template class resonance_core::AbstractSubscriptionPtr<AudioOutputDevice>;
