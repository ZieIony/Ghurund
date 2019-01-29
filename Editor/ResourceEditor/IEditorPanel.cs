using Ghurund.Controls.Workspace;

namespace Ghurund.Editor.ResourceEditor {
    public interface IEditorPanel : IDockablePanel {
        bool NeedsSaving { get; }
        bool Save(string fileName = null);
        bool Load(string fileName);
    }
}