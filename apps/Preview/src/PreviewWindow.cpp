#include "PreviewWindow.h"

#include "ThemeApplication.h"

#include "core/Colors.h"
#include "core/io/File.h"
#include "engine/directx/DxGraphicsFeature.h"
#include "ui/directx/shader/DxUIShaderProvider.h"
#include "ui/directx/text/DxTextMeshFactory.h"
#include "ui/material/ControlMaterialInputs.h"

namespace Preview {
	PreviewWindow::PreviewWindow(
		Ghurund::Core::Application& app,
		DxRenderer& renderer,
		ThemeApplication& themeApp
	):GameWindow(app), themeApp(themeApp) {
		closed += DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER;
		Renderer = &renderer;
		BackgroundColor = &Colors::LIGHT_SKY_BLUE;
	}

	void PreviewWindow::init() {
		previewLayout.set((PreviewLayout*)Application.ResourceManager.load<Control>(FilePath(L"apps/Preview/res/layout.xml"), DirectoryPath(), ResourceFormat::AUTO, LoadOption::DONT_CACHE));

		DxGraphicsFeature* graphicsFeature = Application.Features.get<DxGraphicsFeature>();
		auto commandList = makeIntrusive<CommandList>();
		commandList->init(graphicsFeature->Graphics, graphicsFeature->Graphics.DirectQueue);

		textMeshFactory = makeShared<DxTextMeshFactory>(graphicsFeature->MemoryManager);
		textureFactory = makeShared<DxTextureFactory>(graphicsFeature->Graphics, commandList.ref());
		uiContext = makeShared<DxUIContext>(*this, graphicsFeature->MemoryManager, textMeshFactory.ref(), textureFactory.ref());
		uiLayer.set(ghnew UILayer());
		uiLayer->init(uiContext.ref());
		uiLayer->Theme = &themeApp.CurrentTheme;
		uiLayer->Content = previewLayout.get();
		Layers.add(uiLayer.get());

		DxUIShaderProvider shaderProvider(Application.ResourceManager);
		UIMaterialProvider materialProvider(shaderProvider, graphicsFeature->MemoryManager);
		basicMaterial = IntrusivePointer<UIMaterial>(materialProvider.makeControl());
		ControlMaterialInputs params(basicMaterial.ref());
		params.BackgroundColor = Colors::ALICE_BLUE;
		previewLayout->Material = basicMaterial.get();

		previewLayout->themeChanged += [this](PreviewLayout& previewLayout, const ThemeType type) {
			Application.FunctionQueue.post([&, type] {
				themeApp.ThemeType = type;
				previewLayout.Theme = &themeApp.CurrentTheme;
			});
			return true;
		};

		previewLayout->colorChanged += [this](PreviewLayout& previewLayout, const uint32_t color) {
			Application.FunctionQueue.post([&, color] {
				themeApp.PrimaryColor = color;
				previewLayout.dispatchThemeChanged();
			});
			return true;
		};

#ifdef _DEBUG
		sizeChanged += [&](Window& window) {
			Logger::print(LogType::INFO, _T("\n"));
			Logger::print(LogType::INFO, previewLayout->printTree().Data);
			Logger::print(LogType::INFO, _T("\n"));
			previewLayout->validate();
			return true;
		};
#endif
		DragDropEnabled = true;
		dropped += [this](Ghurund::Core::Window& window, const Array<FilePath*>& files) {
			fileWatcher.clearFiles();
			FilePath& path = *files[0];
			postLoadCallback(path);
			watchFile(path);
			return true;
		};
	}

	void PreviewWindow::postLoadCallback(const FilePath& path) {
		loadCallback = [this, path] {
			File file(path);
			if (!file.Exists)
				return;
			/*if (file.read() == Status::OK) {
				if (path.Extension == L"xml") {
					loadLayout(file);
				} else {
					loadDrawable(file);
				}
			} else {
				Application.FunctionQueue.post(loadCallback);
			}*/
		};

		Application.FunctionQueue.post(loadCallback);
	}
}
