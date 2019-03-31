using System;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor {
    public class DockableControlFactory : IDockablePanelFactory {
        public IDockablePanel MakePanel(Type type) {
            return EditorKernel.GetService(type) as IDockablePanel;
        }
    }

}
