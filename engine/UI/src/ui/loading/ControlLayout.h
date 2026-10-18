#pragma once

#include "core/resource/Resource.h"
#include <ui/control/Control.h>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class ControlLayout:public Resource {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ControlLayout::GET_TYPE();
#pragma endregion

	public:
		IntrusivePointer<Control> control;

#pragma region formats
	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const override {
			return ControlLayout::FORMATS;
		}

	public:
		static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);

		inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };

		static const inline uint32_t VERSION = 0;
#pragma endregion
	};
}
