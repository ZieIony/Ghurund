#pragma once

#include "control/ToolWindow.h"
#include "tool/PropertyPanel.h"
#include "tool/WidgetHierarchyPanel.h"

#include "ui/style/Theme.h"
#include "ui/control/TextBlock.h"
#include "ui/widget/SplitLayout.h"
#include "ui/widget/VerticalScrollBar.h"
#include "ui/widget/property/PropertyList.h"
#include "ui/LayoutLoader.h"
#include "resource/watcher/FileWatcher.h"
#include "application/Application.h"

using namespace Ghurund;
using namespace Ghurund::UI;

namespace Ghurund::Editor {
    class LayoutEditorTab:public ControlContainer {
        SharedPointer<ToolWindow> propertiesWindow;
        SharedPointer<PropertyPanel> propertiesPanel;
        SharedPointer<ToolWindow> widgetHierarchyWindow;
        SharedPointer<WidgetHierarchyPanel> widgetHierarchyPanel;
        SharedPointer<StackLayout> layoutWorkspace;
        SharedPointer<Button> reloadLayout;
        LayoutLoader layoutLoader;
        FileWatcher fileWatcher;
        ResourceContext& context;
        Application& app;
        std::function<void()> loadCallback;

    public:
        LayoutEditorTab(Application& app, ResourceContext& context, Ghurund::UI::Theme& theme, const FilePath& filePath):app(app), context(context) {
            Name = "editor tab";

            fileWatcher.addFile(filePath, [this, &app](const FilePath& path, const FileChange& change) {
                if (change == FileChange::RENAMED_TO || change == FileChange::MODIFIED) {
                    loadCallback = [this, &app, path]() {
                        File file(path);
                        if (!file.Exists)
                            return;
                        if (file.read() != Status::OK)
                            app.FunctionQueue.post(loadCallback);
                        loadLayout(Buffer(file.Data, file.Size));
                    };

                    app.FunctionQueue.post(loadCallback);
                }
            });

            propertiesPanel = ghnew PropertyPanel(context, theme);
            propertiesWindow = ghnew ToolWindow();
            propertiesWindow->Title = L"Properties";
            propertiesWindow->Content = propertiesPanel;
            propertiesWindow->PreferredSize.width = 200;
            widgetHierarchyPanel = ghnew WidgetHierarchyPanel(context, theme);
            widgetHierarchyWindow = ghnew ToolWindow();
            widgetHierarchyWindow->Title = L"Widget";
            widgetHierarchyWindow->Content = widgetHierarchyPanel;
            widgetHierarchyWindow->PreferredSize.width = 200;

            layoutWorkspace = ghnew StackLayout();
            File file(filePath);
            file.read();
            loadLayout(Buffer(file.Data, file.Size));

            SharedPointer<SplitLayout> widgetHierarchySplit = ghnew SplitLayout();
            widgetHierarchySplit->Orientation = Orientation::HORIZONTAL;
            SharedPointer<SplitLayout> propertiesSplit = ghnew SplitLayout();
            propertiesSplit->Orientation = Orientation::HORIZONTAL;
            widgetHierarchySplit->Child1 = widgetHierarchyWindow;
            widgetHierarchySplit->Child2 = propertiesSplit;
            widgetHierarchySplit->LockedChild = LockedChild::CHILD_1;
            propertiesSplit->Child1 = layoutWorkspace;
            propertiesSplit->Child2 = propertiesWindow;
            propertiesSplit->LockedChild = LockedChild::CHILD_2;
            Child = widgetHierarchySplit;
        }

        void loadLayout(const Buffer& data) {
            PointerList<Control*> controls;
            layoutLoader.load(data, controls);
            layoutWorkspace->Children.clear();
            for (Control* control : controls)
                layoutWorkspace->Children.add(control);
            propertiesPanel->Item = layoutWorkspace;
            layoutWorkspace->invalidate();
        }
    };
}
