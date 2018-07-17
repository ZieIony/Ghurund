using System.Windows;

namespace Ghurund.Controls.Workspace {
    public class ControlEventArgs {
        public IDockableControl[] Controls { get; set; }
    }

    public delegate void ControlEventHandler(object sender, ControlEventArgs args);

    public class RoutedControlEventArgs : RoutedEventArgs {
        public IDockableControl[] Controls { get; set; }

        public RoutedControlEventArgs(RoutedEvent routedEvent, IDockableControl[] controls) : base(routedEvent) {
            Controls = controls;
        }
    }

    public delegate void RoutedControlEventHandler(object sender, RoutedControlEventArgs args);

    public class WindowEventArgs : RoutedEventArgs {
        public double Left { get; }
        public double Top { get; }

        public WindowEventArgs(RoutedEvent routedEvent, double left, double top) : base(routedEvent) {
            Left = left;
            Top = top;
        }
    }

    public delegate void WindowEventHandler(object sender, WindowEventArgs args);

    public enum WindowAction {
        Close, Minimize, Maximize, Undock
    }

    public class WindowActionEventArgs : RoutedEventArgs {

        public WindowAction Action { get; }
        public bool ActionHandled { get; set; } = false;
        public DockableControls Controls { get; set; }
        public Point? Location { get; }

        public WindowActionEventArgs(RoutedEvent routedEvent, WindowAction action, Point? location = null, DockableControls controls = null) : base(routedEvent) {
            Action = action;
            Location = location;
            Controls = controls;
        }

    }

    public delegate void WindowActionEventHandler(object sender, WindowActionEventArgs args);

}