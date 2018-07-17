using System.Windows;

namespace Ghurund.Controls.Workspace {
    public partial class EditorWindow : Window {
        private readonly WorkspacePanel workspacePanel;
        private readonly IDockableControl[] controls;

        public EditorWindow() {
            InitializeComponent();
        }

        public EditorWindow(WorkspacePanel workspacePanel, IDockableControl control) : this(workspacePanel, new DockableControls(control)) { }

        public EditorWindow(WorkspacePanel workspacePanel, DockableControls controls) : this() {
            foreach (IDockableControl control in controls.Controls)
                tabControl.Items.Add(new EditorTab(control));

            this.workspacePanel = workspacePanel;
            this.controls = controls.Controls;
            Owner = GetWindow(workspacePanel);

            Width = controls.SuggestedSize.Width;
            Height = controls.SuggestedSize.Height;

            AddHandler(TitleBar.WindowDraggedEvent, new WindowEventHandler(titleBar_WindowDragged));
            AddHandler(TitleBar.WindowDroppedEvent, new WindowEventHandler(titleBar_WindowDropped));
            AddHandler(TitleBar.WindowActionEvent, new WindowActionEventHandler(titleBar_WindowAction));
        }

        private void titleBar_WindowDragged(object sender, WindowEventArgs args) {
            Left = args.Left;
            Top = args.Top;

            workspacePanel.ContinueDocking();
        }

        private void titleBar_WindowDropped(object sender, WindowEventArgs args) {
            if (workspacePanel.FinishDocking()) {
                Close();
                tabControl.Items.Clear();
                workspacePanel.dock(new DockableControls(controls, new Size(ActualWidth, ActualHeight)));
            }
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

        public void StartDrag() {
            var titleBar = Extensions.FindVisualChildByName<TitleBar>(this, "titleBar");
            titleBar.StartDrag();
        }

    }
}
