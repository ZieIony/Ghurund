#include "ghedxpch.h"
#include "ImGuiFeature.h"

#define IMGUI_IMPLEMENTATION
#include <imgui/misc/single_file/imgui_single_file.h>

namespace Ghurund::Engine::DirectX {
	const Ghurund::Core::Type& ImGuiFeature::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ImGuiFeature>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	CoroutineTask<void> ImGuiFeature::onInit() {
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // IF using Docking Branch

		co_return;
	}
	
	void ImGuiFeature::onDeinit() {
		ImGui::DestroyContext();
	}
}
