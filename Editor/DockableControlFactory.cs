using System;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor {
    public class DockableControlFactory : IDockableControlFactory {
        public IDockableControl MakeControl(Type type) {
            return EditorKernel.Instance.GetService(type) as IDockableControl;
        }
    }

}
