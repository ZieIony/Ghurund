#pragma once

#include "ImGuiDescriptorHeapAllocator.h"

#include "engine/directx/CommandList.h"
#include "engine/ecs/System.h"
#include "engine/directx/rendering/DxGraphicsCommandList.h"
#include "engine/directx/DxGraphics.h"

#include <imgui.h>

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	class ImGuiSystem:public System {
	private:
		DxGraphics& graphics;
		ImGuiDescriptorHeapAllocator allocator;
		Array<IntrusivePointer<DxGraphicsCommandList>> commandLists = 3;
		size_t index = 0;

	public:
		ImGuiSystem(DxGraphics& graphics):graphics(graphics) {}

		virtual void onInit();

		virtual void onDeinit();

		void initWindow(SystemWindow& window);

		void deinitWindow();

		void beginFrame();

		void finishFrame(CommandList& commandList);

		virtual void queueDraw(RenderingContext& renderingContext);

		bool onWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
			extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
			return ImGui_ImplWin32_WndProcHandler(hWnd, msg, wParam, lParam);
		}
	};
}
