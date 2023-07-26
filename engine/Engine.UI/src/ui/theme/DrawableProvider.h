#pragma once

#include "core/Provider.h"

namespace Ghurund::UI {
	class Drawable;

	class DrawableProvider:public Ghurund::Core::Provider<Drawable*> {};
}