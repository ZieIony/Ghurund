#pragma once

#include "core/collection/Map.h"

#include "Control.h"

#include <functional>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class ControlPool {
	private:
		Map<std::reference_wrapper<Type>, List<Control*>> typePool;
		Map<FilePath, List<Control*>> resPool;

	public:
		template<class T>
		T* makeControl() {

		}

		template<class T>
		T* makeControl(const FilePath& path) {
			auto it& = resPool.find(path);
			if (it == resPool.end()) {
				Control* control;
				resPool.put(path, control);
				control->addReference();
				return control;
			} else {
				Control* control = *it;
				if (control->ReferenceCount == 1) {
					control->addReference();
					return control;
				} else {
					return (T*)control->clone();
				}
			}
		}
	};
}