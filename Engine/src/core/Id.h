#pragma once

#include <atomic>

namespace Ghurund {
	typedef uint32_t id_t;

	template<class T> class IdObject {
	private:
		inline static std::atomic<id_t> CURRENT_ID = 0;

		id_t id = CURRENT_ID++;

	public:
		virtual ~IdObject() = default;

		id_t getId() const {
			return id;
		}

		__declspec(property(get = getId)) id_t Id;
	};
}