#include "core/application/Application.h"

#include "PreviewLayout.h"
#include "engine/application/GameWindow.h"
#include <engine/directx/DxRenderer.h>
#include <ui/UILayer.h>
#include <ui/directx/DxUIContext.h>
#include <ui/directx/text/DxTextMeshFactory.h>
#include <engine/directx/texture/DxTextureFactory.h>

namespace Preview {
	using namespace Ghurund;
	using namespace Ghurund::Core;
	using namespace Ghurund::UI;
	using namespace Ghurund::UI::DirectX;
	using namespace Ghurund::Engine::DirectX;

	class PreviewWindow :public Ghurund::Engine::GameWindow {
	private:
		IntrusivePointer<Control> previewLayout;
		FileWatcher fileWatcher;
		std::function<void()> loadCallback;
		ThemeApplication& themeApp;
		SharedPointer<DxTextMeshFactory> textMeshFactory;
		SharedPointer<DxTextureFactory> textureFactory;
		SharedPointer<DxUIContext> uiContext;
		IntrusivePointer<UILayer> uiLayer;
		IntrusivePointer<IMaterial> basicMaterial;

	public:
		PreviewWindow(
			Ghurund::Core::Application& app,
			DxRenderer& renderer,
			ThemeApplication& themeApp
		);

		void init();

		void uninit() {
			uiLayer.set(nullptr);
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