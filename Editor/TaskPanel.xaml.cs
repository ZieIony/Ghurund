using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Editor {
    public partial class TaskPanel : UserControl {

        public static readonly RoutedEvent TaskAddedEvent = EventManager.RegisterRoutedEvent("TaskAdded", RoutingStrategy.Bubble, typeof(RoutedTaskEventHandler), typeof(TaskPanel));

        public event RoutedTaskEventHandler TaskAdded {
            add { AddHandler(TaskAddedEvent, value); }
            remove { RemoveHandler(TaskAddedEvent, value); }
        }

        public static readonly RoutedEvent TaskFinishedEvent = EventManager.RegisterRoutedEvent("TaskFinished", RoutingStrategy.Bubble, typeof(RoutedTaskEventHandler), typeof(TaskPanel));

        public event RoutedTaskEventHandler TaskFinished {
            add { AddHandler(TaskFinishedEvent, value); }
            remove { RemoveHandler(TaskFinishedEvent, value); }
        }

        public TaskPanel() {
            InitializeComponent();
        }
    }
}
