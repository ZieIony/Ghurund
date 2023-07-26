#include "core/application/Application.h"
#include "core/window/WindowClass.h"
#include "ui/Canvas.h"
#include "ui/RootView.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/theme/LightTheme.h"
#include "ui/theme/DarkTheme.h"

#include "ui/direct2d/font/FontLoader.h"
#include "ui/direct2d/image/BitmapLoader.h"
#include "core/image/ImageLoader.h"
#include "ui/direct2d/UIContext.h"
#include <ui/control/ControlGroup.h>

#include "PreviewLayout.h"
#include "application/UIApplicationWindow.h"
#include "ui/UILayer.h"
#include "ui/UIFeature.h"

namespace Preview {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;
	using namespace Ghurund::UI::Direct2D;

	class PreviewWindow :public Ghurund::UIApplicationWindow {
	private:
		SharedPointer<PreviewLayout> previewLayout;
		FileWatcher fileWatcher;
		std::function<void()> loadCallback;
		ThemeApplication& themeApp;

	public:
		PreviewWindow(Ghurund::Core::Application& app, Renderer& renderer, ThemeApplication& themeApp) :UIApplicationWindow(app, renderer), themeApp(themeApp) {
			Style = WindowStyle{
			   .hasMinimizeButton = true,
			   .hasMaximizeButton = true,
			   .hasTitle = true,
			   .borderStyle = WindowBorderStyle::RESIZE,
			   .showOnTaskbar = true
			};
		}

		virtual void init(WindowManager& windowManager) override;

		void postLoadCallback(const FilePath& path);

		void loadLayout(const File& file) {
			SharedPointer<ControlGroup> layout(Application.ResourceManager.load<ControlGroup>(file, nullptr, LoadOption::DONT_CACHE));
			previewLayout->Container->Children.clear();
			for (Control* control : layout->Children)
				previewLayout->Container->Children.add(control);
			previewLayout->Container->invalidate();
		}

		void loadDrawable(const File& file) {
			/*auto image = makeShared<Bitmap>();
			MemoryInputStream stream(data.Data, data.Size);
			DirectoryPath baseDir(L".");
			image->load(app->ResourceContext, baseDir, stream);
			auto drawableView = makeShared<DrawableView>();
			drawableView->Image = ghnew BitmapDrawable(image);
			binding->Container->Children = { drawableView };
			binding->Container->invalidate();*/
		}

		void watchFile(FilePath& filePath) {
			fileWatcher.addFile(filePath, [this](const FilePath& path, const FileChange& change) {
				if (change == FileChange::RENAMED_TO || change == FileChange::MODIFIED)
					postLoadCallback(path);
				});
		}
	};
}