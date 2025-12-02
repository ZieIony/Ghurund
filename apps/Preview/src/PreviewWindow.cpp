#include "PreviewWindow.h"

#include "ThemeApplication.h"
#include <ui/directx/material/DxUIShaderProvider.h>
#include <ui/directx/material/DxUIMaterialProvider.h>
#include <ui/material/ControlMaterialParameters.h>
#include "core/Colors.h"

namespace Preview {
	PreviewWindow::PreviewWindow(
		Ghurund::Core::Application& app,
		DxRenderer& renderer,
		ThemeApplication& themeApp
	):GameWindow(app), themeApp(themeApp) {
		Renderer = &renderer;
		BackgroundColor = &Colors::LIGHT_SKY_BLUE;
	}

	void PreviewWindow::init() {
		previewLayout.set(Application.ResourceManager.load<Control>(FilePath(L"apps/Preview/res/layout.xml"), DirectoryPath(), ResourceFormat::AUTO, LoadOption::DONT_CACHE));

		DxGraphics* graphics = Application.Features.get<DxGraphics>();
		auto commandList = makeIntrusive<CommandList>();
		commandList->init(*graphics, graphics->DirectQueue);

		uiContext = makeShared<DxUIContext>(*this, *graphics, commandList.ref());
		uiLayer = ghnew UILayer();
		uiLayer->init(uiContext.ref());
		uiLayer->Theme = &themeApp.CurrentTheme;
		uiLayer->Content = previewLayout.get();
		Layers.add(uiLayer);

		DxUIShaderProvider shaderProvider(Application.ResourceManager);
		DxUIMaterialProvider materialProvider(ParameterManager, shaderProvider);
		basicMaterial = IntrusivePointer<IMaterial>(materialProvider.makeControl());
		ControlMaterialParameters params(basicMaterial.ref());
		params.BackgroundColor = Colors::ALICE_BLUE;
		previewLayout->Material = basicMaterial.get();

		/*previewLayout->themeChanged += [this](PreviewLayout& previewLayout, const ThemeType type) {
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
		};*/

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
