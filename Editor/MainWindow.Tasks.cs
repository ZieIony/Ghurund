using System;
using System.ComponentModel;
using System.Reactive.Linq;
using System.Windows;

namespace Ghurund.Editor {
    public partial class MainWindow {

        private void initTasks() {
            AddHandler(TaskPanel.TaskAddedEvent, new RoutedTaskEventHandler(taskPanel_TaskAdded));
        }

        private void taskPanel_TaskAdded(object sender, RoutedTaskEventArgs args) {
        }
    }
}
