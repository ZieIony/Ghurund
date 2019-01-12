using System.Windows;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor {
    public enum EditorAction {
        NewProject, OpenFile
    }

    public class RoutedActionPerformedEventArgs : RoutedEventArgs {
        public EditorAction Action { get; }

        public RoutedActionPerformedEventArgs(EditorAction action, RoutedEvent ActionPerformedEvent) : base(ActionPerformedEvent) {
            Action = action;
        }
    }

    public delegate void RoutedActionPerformedEventHandler(object sender, RoutedActionPerformedEventArgs e);

    public partial class MainWindow {

        public static readonly RoutedEvent ActionPerformedEvent = EventManager.RegisterRoutedEvent("ActionPerformed", RoutingStrategy.Bubble, typeof(RoutedActionPerformedEventHandler), typeof(MainWindow));

        public event RoutedActionPerformedEventHandler ActionPerformed {
            add { AddHandler(ActionPerformedEvent, value); }
            remove { RemoveHandler(ActionPerformedEvent, value); }
        }

        private void actionPerformedHandler(object sender, RoutedActionPerformedEventArgs e) {
            if (e.Action == EditorAction.OpenFile) {
                openFile();
            } else if (e.Action == EditorAction.NewProject) {
                newProject();
            }
        }

        private void titleBar_WindowDragged(object sender, WindowEventArgs args) {
            Left = args.Left;
            Top = args.Top;
        }
    }
}
