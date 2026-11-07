#include "ghedxpch.h"
#include "ImGuiSystem.h"

#include <engine/directx/rendering/DxRenderingContext.h>

#include <imgui/backends/imgui_impl_win32.h>
#include <imgui/backends/imgui_impl_win32.cpp>
#include <imgui/backends/imgui_impl_dx12.h>
#include <imgui/backends/imgui_impl_dx12.cpp>

namespace Ghurund::Engine::DirectX {
	void ImGuiSystem::onInit() {
		// Setup Platform/Renderer backends
		ImGui_ImplDX12_InitInfo init_info = {};
		init_info.Device = graphics.Device;
		init_info.CommandQueue = graphics.DirectQueue;
		init_info.NumFramesInFlight = 3;
		init_info.RTVFormat = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB; // Or your render target format.

		allocator.init(graphics.Device);
		// Allocating SRV descriptors (for textures) is up to the application, so we provide callbacks.
		// The example_win32_directx12/main.cpp application include a simple free-list based allocator.
		init_info.UserData = &allocator;
		init_info.SrvDescriptorHeap = allocator.getHeap();
		init_info.SrvDescriptorAllocFn = [](
			ImGui_ImplDX12_InitInfo* info,
			D3D12_CPU_DESCRIPTOR_HANDLE* out_cpu_handle,
			D3D12_GPU_DESCRIPTOR_HANDLE* out_gpu_handle
			) {
			return ((ImGuiDescriptorHeapAllocator*)info->UserData)->alloc(out_cpu_handle, out_gpu_handle);
		};
		init_info.SrvDescriptorFreeFn = [](
			ImGui_ImplDX12_InitInfo* info,
			D3D12_CPU_DESCRIPTOR_HANDLE cpu_handle,
			D3D12_GPU_DESCRIPTOR_HANDLE gpu_handle
			) {
			return ((ImGuiDescriptorHeapAllocator*)info->UserData)->free(cpu_handle, gpu_handle);
		};

		ImGui_ImplDX12_Init(&init_info);

		for (size_t i = 0; i < commandLists.Size; i++) {
			commandLists[i].set(ghnew DxGraphicsCommandList());
			commandLists[i]->init(graphics, graphics.DirectQueue);
		}
	}

	void ImGuiSystem::onDeinit() {
		allocator.deinit();
		for (size_t i = 0; i < commandLists.Size; i++)
			commandLists[i].set(nullptr);
		ImGui_ImplDX12_Shutdown();
	}
	
	void ImGuiSystem::initWindow(SystemWindow& window) {
		ImGui_ImplWin32_Init(window.Handle);
	}

	void ImGuiSystem::deinitWindow() {
		ImGui_ImplWin32_Shutdown();
	}

	void ImGuiSystem::beginFrame() {
		ImGui_ImplDX12_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();
		bool open = true;
		ImGui::ShowDemoWindow(&open);
	}

	void ImGuiSystem::finishFrame(CommandList& commandList) {
		ImGui::Render();
		auto heap = allocator.getHeap();
		commandLists[index]->get()->SetDescriptorHeaps(1, &heap);
		ImGui_ImplDX12_RenderDrawData(ImGui::GetDrawData(), commandList.get());
	}

	void ImGuiSystem::queueDraw(RenderingContext& renderingContext) {
		((DxRenderingContext&)renderingContext).startFrame(commandLists[index].ref());

		beginFrame();
		finishFrame(commandLists[index].ref());

		commandLists[index]->finish();

		index = (index + 1) % commandLists.Size;
	}
}
