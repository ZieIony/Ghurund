using System.Windows;

namespace Ghurund.Editor {
    public class EditorTask {
    }

    public class RoutedTaskEventArgs : RoutedEventArgs {
        public EditorTask Task { get; set; }

        public RoutedTaskEventArgs(RoutedEvent routedEvent, EditorTask task) : base(routedEvent) {
            Task = task;
        }
    }

    public delegate void RoutedTaskEventHandler(object sender, RoutedTaskEventArgs args);
}
