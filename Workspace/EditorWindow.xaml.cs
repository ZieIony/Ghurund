using System.Windows;

namespace Ghurund.Controls.Workspace {
    public partial class EditorWindow : Window {
        private readonly WorkspacePanel workspacePanel;
        private readonly IDockablePanel[] controls;

        public EditorWindow() {
            InitializeComponent();
        }

        public EditorWindow(WorkspacePanel workspacePanel, IDockablePanel control) : this(workspacePanel, new DockableGroup(control)) { }

        public EditorWindow(WorkspacePanel workspacePanel, DockableGroup controls) : this() {
            foreach (IDockablePanel control in controls.Panels)
                tabControl.Items.Add(new EditorTab(control));

            this.workspacePanel = workspacePanel;
            this.controls = controls.Panels;
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
                workspacePanel.dock(new DockableGroup(controls, new Size(ActualWidth, ActualHeight)));
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
