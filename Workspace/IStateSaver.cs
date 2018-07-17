using System;

namespace Ghurund.Controls.Workspace {
    public interface IDockableControlFactory {
        IDockableControl MakeControl(Type type);
    }
}
