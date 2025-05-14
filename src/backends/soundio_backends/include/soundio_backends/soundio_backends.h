#pragma once


namespace resonance_core
{

class BackendFactory;

}

namespace soundio_backends
{

void register_backends(resonance_core::BackendFactory& factory);

}
