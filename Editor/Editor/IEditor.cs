using Ghurund.Managed.Resource;
using System;

namespace Ghurund.Editor {
    public interface IEditor {
        bool WasSaved { get; }
        IResource Document { get; set; }

        void newDocument();
        bool saveAs(string fileName);
        bool load(string fileName);
        bool save();

        event EventHandler DocumentChanged;
    }
}