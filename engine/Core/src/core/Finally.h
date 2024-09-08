#pragma once

namespace Ghurund::Core {
	template<typename F>
	class Finally {
	private:
		F f;

	public:
		Finally(F f):f(f) {}

		~Finally() {
			f();
		}
	};
}