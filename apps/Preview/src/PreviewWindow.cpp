#include "PreviewWindow.h"

#include "ThemeApplication.h"

namespace Preview {
	PreviewWindow::PreviewWindow(Ghurund::Core::Application& app, Renderer& renderer, ThemeApplication& themeApp):UIApplicationWindow(app, renderer), themeApp(themeApp) {
		Style = WindowStyle{
			.hasMinimizeButton = true,
			.hasMaximizeButton = false,
			.hasTitle = true,
			.borderStyle = WindowBorderStyle::RESIZE,
			.showOnTaskbar = true,
		};
	}

	void PreviewWindow::init() {
		__super::init();

		previewLayout.set(Application.ResourceManager.load<PreviewLayout>(FilePath(L"apps/Preview/res/layout.xml"), DirectoryPath(), ResourceFormat::AUTO, LoadOption::DONT_CACHE));
		Theme = &themeApp.CurrentTheme;
		Content = previewLayout.get();

		previewLayout->themeChanged += [this](PreviewLayout& previewLayout, const ThemeType type) {
			Application.FunctionQueue.post([&, type]() {
				themeApp.ThemeType = type;
				previewLayout.Theme = &themeApp.CurrentTheme;
			});
			return true;
		};

		previewLayout->colorChanged += [this](PreviewLayout& previewLayout, const uint32_t color) {
			Application.FunctionQueue.post([&, color]() {
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

		Application.FunctionQueue.post(loadCallback);
	}
}
