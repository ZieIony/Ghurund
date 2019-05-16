using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Controls.Workspace {
    public partial class TitleBar: Control {

        public static readonly RoutedEvent WindowActionEvent = EventManager.RegisterRoutedEvent("WindowAction", RoutingStrategy.Bubble, typeof(WindowActionEventHandler), typeof(TitleBar));

        public event WindowActionEventHandler WindowAction {
            add { AddHandler(WindowActionEvent, value); }
            remove { RemoveHandler(WindowActionEvent, value); }
        }

        public static readonly RoutedEvent WindowDraggedEvent = EventManager.RegisterRoutedEvent("WindowDragged", RoutingStrategy.Bubble, typeof(WindowEventHandler), typeof(TitleBar));

        public event WindowEventHandler WindowDragged {
            add { AddHandler(WindowDraggedEvent, value); }
            remove { RemoveHandler(WindowDraggedEvent, value); }
        }

        public static readonly RoutedEvent WindowDroppedEvent = EventManager.RegisterRoutedEvent("WindowDropped", RoutingStrategy.Bubble, typeof(WindowEventHandler), typeof(TitleBar));

        public event WindowEventHandler WindowDropped {
            add { AddHandler(WindowDroppedEvent, value); }
            remove { RemoveHandler(WindowDroppedEvent, value); }
        }

        private void minimizeButton_Click(object sender, RoutedEventArgs e) {
            if (HandleWindowActions) {
                windowAction(Workspace.WindowAction.Minimize);
            } else {
                RaiseEvent(new WindowActionEventArgs(WindowActionEvent, Workspace.WindowAction.Minimize, new Point()));
            }
        }

        private void maximizeButton_Click(object sender, RoutedEventArgs e) {
            if (HandleWindowActions) {
                windowAction(Workspace.WindowAction.Maximize);
            } else {
                RaiseEvent(new WindowActionEventArgs(WindowActionEvent, Workspace.WindowAction.Maximize, new Point()));
            }
        }

        private void closeButton_Click(object sender, RoutedEventArgs e) {
            if (HandleWindowActions) {
                windowAction(Workspace.WindowAction.Close);
            } else {
                RaiseEvent(new WindowActionEventArgs(WindowActionEvent, Workspace.WindowAction.Close, new Point()));
            }
        }

        private void undockButton_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new WindowActionEventArgs(WindowActionEvent, Workspace.WindowAction.Undock, new Point()));
        }

    }
}
