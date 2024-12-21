#include "DemoWindow.h"

#include "DemoApplication.h"
#include "ui/widget/menu/MenuBar.h"
#include "ui/widget/toolbar/Toolbar.h"
#include "ui/layout/VerticalLayoutManager.h"

namespace Demo {
	DemoWindow::DemoWindow(DemoApplication& app, Renderer& renderer):UIApplicationWindow(app, renderer), app(app) {
		Style = WindowStyle{
			.hasMinimizeButton = true,
			.hasMaximizeButton = true,
			.hasTitle = true,
			.borderStyle = WindowBorderStyle::RESIZE,
			.showOnTaskbar = true
		};
	}
	
	void DemoWindow::init() {
		__super::init();

		UIDebugTools::init(UILayer.Context);
		UIDebugTools::drawConstraints = true;

		demoLayout.set(Application.ResourceManager.load<Control>(
			FilePath(L"apps/Demo.UI/res/layout.xml"),
			DirectoryPath(),
			ResourceFormat::AUTO,
			LoadOption::DONT_CACHE
		));
		Content = demoLayout.get();

#ifdef _DEBUG
		sizeChanged += [&](Window& window) {
			Logger::print(LogType::INFO, _T("\n"));
			Logger::print(LogType::INFO, demoLayout->printTree().Data);
			Logger::print(LogType::INFO, _T("\n"));
			demoLayout->validate();
			return true;
		};
#endif

		auto colors = List<Color>({
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
			});

		auto pasteIcon = IntrusivePointer<Drawable>(app.getDrawableFactory().makeDrawable(FilePath(_T("resources/icons/paste 18.png"))));
		auto buttonImage = IntrusivePointer<Drawable>(app.getDrawableFactory().makeDrawable(FilePath(_T("resources/button.png"))));

		Toolbar* toolbar = (Toolbar*)demoLayout->find("toolbar");
		toolbarItemAdapter = ghnew ToolbarItemAdapter(Application.ResourceManager);
		toolbarItemAdapter->Items = {
			SharedPointer<MenuItem>(ghnew ButtonMenuItem(pasteIcon.get(),{})),
			SharedPointer<MenuItem>(ghnew SeparatorMenuItem())
		};
		toolbar->ItemAdapter = *toolbarItemAdapter;

		MenuBar* menuBar = (MenuBar*)demoLayout->find("menuBar");
		menuBarItemAdapter = ghnew MenuBarItemAdapter(Application.ResourceManager);
		menuBarItemAdapter->Items = {
			SharedPointer<MenuItem>(ghnew ButtonMenuItem(buttonImage.get(),{})),
			SharedPointer<MenuItem>(ghnew SeparatorMenuItem())
		};
		menuBar->ItemAdapter = *menuBarItemAdapter;

		AdapterLayout* adapterLayout = (AdapterLayout*)demoLayout->find("adapterLayout");
		auto layoutManager = std::make_unique<VerticalAdapterLayoutManager>();
		layoutManager->Spacing = 8;
		layoutManager->adapterLayout = adapterLayout;
		adapterLayout->LayoutManager = std::move(layoutManager);
		adapter1 = ghnew ColorListAdapter(colors);
		adapterLayout->ItemAdapter = *adapter1;

		AdapterLayout* adapterLayout2 = (AdapterLayout*)demoLayout->find("adapterLayout2");
		auto layoutManager2 = std::make_unique<VerticalAdapterLayoutManager>();
		layoutManager2->Spacing = 8;
		layoutManager2->adapterLayout = adapterLayout2;
		adapterLayout2->LayoutManager = std::move(layoutManager2);
		adapter2 = ghnew ColorListAdapter(colors);
		adapterLayout2->ItemAdapter = *adapter2;
	}
}
