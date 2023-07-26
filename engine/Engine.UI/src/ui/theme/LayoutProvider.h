#pragma once

#include "core/Provider.h"

namespace Ghurund::UI {
	class Control;

	class LayoutProvider:public Ghurund::Core::Provider<Control*> {};
}