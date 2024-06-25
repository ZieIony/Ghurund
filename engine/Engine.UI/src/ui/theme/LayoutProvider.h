#pragma once

#include "core/Provider.h"
#include "core/SharedPointer.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
	class LayoutProvider:public Ghurund::Core::Provider<Ghurund::Core::SharedPointer<Control>> {};
}