#include "core/application/Application.h"

#include "PreviewLayout.h"
#include "ui/direct2d/application/UIApplicationWindow.h"

namespace Preview {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;
	using namespace Ghurund::UI::Direct2D;

	class PreviewWindow :public Ghurund::UI::Direct2D::UIApplicationWindow {
	private:
		IntrusivePointer<PreviewLayout> previewLayout;
		FileWatcher fileWatcher;
		std::function<void()> loadCallback;
		ThemeApplication& themeApp;

	public:
		PreviewWindow(Ghurund::Core::Application& app, Renderer& renderer, ThemeApplication& themeApp);

		virtual void init() override;

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