#pragma once

#include "LayoutEditorBinding.h"
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

namespace Ghurund::Editor {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class LayoutEditorTab:public Widget<LayoutEditorBinding> {
        LayoutLoader layoutLoader;
        FileWatcher fileWatcher;
        Application* app = nullptr;
        std::function<void()> loadCallback;

    public:
        /*void loadLayout(const FilePath& filePath) {
            fileWatcher.addFile(filePath, [this](const FilePath& path, const FileChange& change) {
                if (change == FileChange::RENAMED_TO || change == FileChange::MODIFIED) {
                    loadCallback = [this, path]() {
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

            File file(filePath);
            file.read();
            loadLayout(Buffer(file.Data, file.Size));
        }

        void loadLayout(const Buffer& data) {
            PointerList<Control*> controls;
            layoutLoader.load(data, controls);
            Layout->Workspace->Children.clear();
            for (Control* control : controls)
                Layout->Workspace->Children.add(control);
            Layout->Properties->Item = Layout->Workspace;
            Layout->Workspace->invalidate();
        }*/
    };
}
