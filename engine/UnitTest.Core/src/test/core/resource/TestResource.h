#pragma once

#include "core/resource/Resource.h"

namespace UnitTest {
	class TestResource:public Ghurund::Core::Resource {
	public:
		Ghurund::Core::AString text;
	};
}