#include "PreviewWindow.h"

#include "ThemeApplication.h"

namespace Preview {
	void PreviewWindow::init(WindowManager& windowManager) {
		__super::init(windowManager);

		Ghurund::UI::Direct2D::Graphics2D& graphics2d = Application.Features.get<Ghurund::UI::Direct2D::Graphics2D>();

		UILayer* uiLayer = ghnew UILayer(graphics2d, *this, Application.ResourceManager);

		previewLayout.set(Application.ResourceManager.load<PreviewLayout>(FilePath(L"apps/Preview/res/layout.xml"), nullptr, LoadOption::DONT_CACHE));
		//previewLayout->Theme = &themeApp.CurrentTheme;
		uiLayer->Root.Child = previewLayout.get();
		/*previewLayout->themeChanged += [this](PreviewLayout& previewLayout, const ThemeType type) {
			themeApp.ThemeType = type;
			previewLayout.Theme = &themeApp.CurrentTheme;
			return true;
			};
		previewLayout->colorChanged += [this](PreviewLayout& previewLayout, const uint32_t color) {
			themeApp.PrimaryColor = color;
			return true;
			};

		sizeChanged += [&](Window& window) {
			Logger::print(LogType::INFO, _T("\n"));
			Logger::print(LogType::INFO, previewLayout->printTree().Data);
			Logger::print(LogType::INFO, _T("\n"));
			return true;
			};

		DragDropEnabled = true;
		dropped += [this](Ghurund::Core::Window& window, const Array<FilePath*>& files) {
			fileWatcher.clearFiles();
			FilePath& path = *files[0];
			postLoadCallback(path);
			watchFile(path);
			return true;
			};*/

		Layers.add(std::unique_ptr<UILayer>(uiLayer));
	}

	void PreviewWindow::postLoadCallback(const FilePath& path) {
		loadCallback = [this, path]() {
			File file(path);
			if (!file.Exists)
				return;
			if (file.read() == Status::OK) {
				if (path.Extension == L"xml") {
					loadLayout(file);
				} else {
					loadDrawable(file);
				}
			} else {
				Application.FunctionQueue.post(loadCallback);
			}
			};

		Application.FunctionQueue.post(loadCallback);
	}
}
