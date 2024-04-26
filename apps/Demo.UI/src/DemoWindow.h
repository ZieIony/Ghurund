#include "core/application/Application.h"

#include "application/UIApplicationWindow.h"
#include <ui/UIDebugTools.h>
#include <ui/adapter/AdapterLayout.h>
#include <ColorListAdapter.h>
#include <ui/layout/VerticalLayoutManager.h>

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class DemoWindow:public UIApplicationWindow {
	private:
		SharedPointer<Control> demoLayout;

	public:
		DemoWindow(Ghurund::Core::Application& app, Renderer& renderer):UIApplicationWindow(app, renderer) {
			Style = WindowStyle{
			 .hasMinimizeButton = true,
			 .hasMaximizeButton = true,
			 .hasTitle = true,
			 .borderStyle = WindowBorderStyle::RESIZE,
			 .showOnTaskbar = true
			};
		}

		~DemoWindow() {
			UIDebugTools::uninit();
		}

		virtual void init(WindowManager& windowManager) override {
			__super::init(windowManager);

			UIDebugTools::init(UILayer.Context);
			UIDebugTools::drawConstraints = true;

			demoLayout.set(Application.ResourceManager.load<Control>(
				FilePath(L"apps/Demo.UI/res/layout.xml"),
				DirectoryPath(),
				ResourceFormat::AUTO,
				LoadOption::DONT_CACHE
			));
			Content = demoLayout.get();

			sizeChanged += [&](Window& window) {
				Logger::print(LogType::INFO, _T("\n"));
				Logger::print(LogType::INFO, demoLayout->printTree().Data);
				Logger::print(LogType::INFO, _T("\n"));
				demoLayout->validate();
				return true;
			};

			AdapterLayout* adapterLayout = (AdapterLayout*)demoLayout->find("adapterLayout");
			auto layoutManager = std::make_unique<VerticalAdapterLayoutManager>();
			layoutManager->Spacing = 8;
			layoutManager->adapterLayout = adapterLayout;
			adapterLayout->LayoutManager = std::move(layoutManager);
			adapterLayout->ItemAdapter = std::make_unique<ColorListAdapter>(List<Color>({
				Color(0xffff0000),
				Color(0xff00ff00),
				Color(0xffffff00),
				Color(0xff00ffff),
				Color(0xffff00ff),
				Color(0xff00ff7f),
				Color(0xffff7f00),
				Color(0xff7fff00),
				Color(0xffff7f7f),
				Color(0xff7fff7f),
				Color(0xff0000ff)
				}));

			AdapterLayout* adapterLayout2 = (AdapterLayout*)demoLayout->find("adapterLayout2");
			auto layoutManager2 = std::make_unique<VerticalAdapterLayoutManager>();
			layoutManager2->Spacing = 8;
			layoutManager2->adapterLayout = adapterLayout2;
			adapterLayout2->LayoutManager = std::move(layoutManager2);
			adapterLayout2->ItemAdapter = std::make_unique<ColorListAdapter>(List<Color>({
				Color(0xffff0000),
				Color(0xff00ff00),
				Color(0xffffff00),
				Color(0xff00ffff),
				Color(0xffff00ff),
				Color(0xff00ff7f),
				Color(0xffff7f00),
				Color(0xff7fff00),
				Color(0xffff7f7f),
				Color(0xff7fff7f),
				Color(0xff0000ff)
				}));
		}
	};
}