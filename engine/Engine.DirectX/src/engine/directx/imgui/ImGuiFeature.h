#pragma once

#include "ImGuiDescriptorHeapAllocator.h"

#include "core/feature/Feature.h"
#include "engine/directx/DxGraphics.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class ImGuiFeature:public Feature {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ImGuiFeature::GET_TYPE();
#pragma endregion

	private:
		DxGraphics& graphics;

	protected:
		virtual CoroutineTask<void> onInit() override;

		virtual void onDeinit() override;

	public:
		ImGuiFeature(DxGraphics& graphics):graphics(graphics) {}
	};
}
