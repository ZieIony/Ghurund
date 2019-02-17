using System.Windows;
using Ghurund.Controls.Workspace;
using Ninject;

namespace Ghurund.Editor {
    public partial class SettingsWindow : Window {

        [Inject]
        public EditorSettings Settings { get; set; }

        public SettingsWindow() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            propertyGrid.SelectedObject = Settings;

            ThemeResourceDictionary.ApplyTheme(this, Settings.Theme);

            AddHandler(TitleBar.WindowDraggedEvent, new WindowEventHandler(titleBar_WindowDragged));
            AddHandler(TitleBar.WindowActionEvent, new WindowActionEventHandler(titleBar_WindowAction));
        }

        private void titleBar_WindowDragged(object sender, WindowEventArgs args) {
            Left = args.Left;
            Top = args.Top;
        }

        private void titleBar_WindowAction(object sender, WindowActionEventArgs args) {
            if (args.Action == WindowAction.Close) {
                Close();
            } else if (args.Action == WindowAction.Maximize) {
                WindowState = (WindowState == WindowState.Normal) ? WindowState.Maximized : WindowState.Normal;
            } else if (args.Action == WindowAction.Minimize) {
                WindowState = WindowState.Minimized;
            }
            args.Handled = true;
        }
    }
}
