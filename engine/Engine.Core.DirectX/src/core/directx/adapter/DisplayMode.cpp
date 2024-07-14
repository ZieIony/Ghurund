#include "ghcdxpch.h"
#include "DisplayMode.h"

#include <type_traits>

namespace Ghurund::Core::DirectX {
	DisplayMode::DisplayMode(DisplayMode&& other) noexcept:
		width(std::move(other.Width)), height(std::move(other.Height)), refreshRate(std::move(other.refreshRate)), format(other.Format) {}
}