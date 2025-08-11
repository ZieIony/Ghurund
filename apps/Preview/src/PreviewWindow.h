#include "core/application/Application.h"

#include "PreviewLayout.h"
#include "engine/application/GameWindow.h"
#include <engine/directx/DxRenderer.h>
#include <ui/direct2d/D2DUILayer.h>

namespace Preview {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;
	using namespace Ghurund::Engine::DirectX;

	class PreviewWindow :public Ghurund::Engine::GameWindow {
	private:
		WindowStyle PREVIEW_WINDOW_STYLE = WindowStyle{
			.hasMinimizeButton = true,
			.hasMaximizeButton = false,
			.hasTitle = true,
			.borderStyle = WindowBorderStyle::RESIZE,
			.showOnTaskbar = true,
		};

		IntrusivePointer<PreviewLayout> previewLayout;
		FileWatcher fileWatcher;
		std::function<void()> loadCallback;
		ThemeApplication& themeApp;
		Ghurund::UI::Direct2D::D2DUILayer* uiLayer = nullptr;

	public:
		PreviewWindow(
			NotNull<Ghurund::Core::Application> app,
			NotNull<DxRenderer> renderer,
			NotNull<ThemeApplication> themeApp
		);

		void init();

		void uninit() {
			if (uiLayer) {
				uiLayer->release();
				uiLayer = nullptr;
			}
		}

		void postLoadCallback(const FilePath& path);

		void loadLayout(const File& file) {
			/*IntrusivePointer<ControlGroup> layout(Application.ResourceManager.load<ControlGroup>(file, nullptr, LoadOption::DONT_CACHE));
			previewLayout->Container->Children.clear();
			for (Control* control : layout->Children)
				previewLayout->Container->Children.add(control);
			previewLayout->Container->requestLayout();*/
		}

		void loadDrawable(const File& file) {
			/*auto image = makeIntrusive<Bitmap>();
			MemoryInputStream stream(data.Data, data.Size);
			DirectoryPath baseDir(L".");
			image->load(app->ResourceContext, baseDir, stream);
			auto drawableView = makeIntrusive<DrawableView>();
			drawableView->Image = ghnew BitmapDrawable(image);
			binding->Container->Children = { drawableView };
			binding->Container->requestLayout();*/
		}

		void watchFile(FilePath& filePath) {
			fileWatcher.addFile(filePath, [this](const FilePath& path, const FileChange& change) {
				if (change == FileChange::RENAMED_TO || change == FileChange::MODIFIED)
					postLoadCallback(path);
				});
		}
	};
}