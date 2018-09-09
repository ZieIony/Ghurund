namespace Ghurund.Controls.Workspace {
    public interface IStateControl {
        object Save();

        void Restore(object state);
    }
}