#include "PreviewWindow.h"

#include "ThemeApplication.h"

namespace Preview {
	PreviewWindow::PreviewWindow(
		Ghurund::Core::Application& app,
		DxRenderer& renderer,
		ThemeApplication& themeApp
	):DirectXWindow(app, PREVIEW_WINDOW_STYLE, renderer), themeApp(themeApp) {
	}

	void PreviewWindow::init() {
		__super::init();

		previewLayout.set(Application->ResourceManager->load<PreviewLayout>(FilePath(L"apps/Preview/res/layout.xml"), DirectoryPath(), ResourceFormat::AUTO, LoadOption::DONT_CACHE));

		Ghurund::UI::Direct2D::Graphics2D* graphics2d = Application->Features->get<Ghurund::UI::Direct2D::Graphics2D>();
		uiLayer = ghnew Ghurund::UI::Direct2D::D2DUILayer();
		uiLayer->init(graphics2d, *this, SwapChain);
		uiLayer->Theme = &themeApp.CurrentTheme;
		uiLayer->Content = previewLayout.get();
		Layers.add(uiLayer);

		previewLayout->themeChanged += [this](PreviewLayout& previewLayout, const ThemeType type) {
			Application->FunctionQueue->post([&, type]() {
				themeApp.ThemeType = type;
				previewLayout.Theme = &themeApp.CurrentTheme;
			});
			return true;
		};

		previewLayout->colorChanged += [this](PreviewLayout& previewLayout, const uint32_t color) {
			Application->FunctionQueue->post([&, color]() {
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
		loadCallback = [this, path]() {
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

		Application->FunctionQueue->post(loadCallback);
	}
}
