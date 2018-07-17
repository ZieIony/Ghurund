using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Ghurund.Controls.Workspace {
    public class WorkspacePanel : Control {
        private HighlightWindow highlightWindow = new HighlightWindow();
        private DockPanel rootDockPanel;
        private PeekPanel peekPanel;

        static WorkspacePanel() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(WorkspacePanel), new FrameworkPropertyMetadata(typeof(WorkspacePanel)));
        }

        public override void OnApplyTemplate() {
            base.OnApplyTemplate();
            rootDockPanel = GetTemplateChild("rootDockPanel") as DockPanel;
            peekPanel = GetTemplateChild("peekPanel") as PeekPanel;

            AddHandler(TitleBar.WindowActionEvent, new WindowActionEventHandler(titleBar_WindowAction));
        }

        private void titleBar_WindowAction(object sender, WindowActionEventArgs args) {
            rootDockPanel.flatten();
            if (args.Action == WindowAction.Undock) {
                var window = new EditorWindow(this, args.Controls);
                var mousePos = PointToScreen(Mouse.GetPosition(this));
                if (args.Location != null) {
                    var location = args.Location.Value;
                    window.Left = mousePos.X - location.X;
                    window.Top = mousePos.Y - location.Y;
                    window.Show();
                    window.StartDrag();
                } else {
                    window.Show();
                }
            } else if (args.Action == WindowAction.Minimize) {
                peekPanel.Add(args.Controls, PeekSide.Left);
            }

            args.Handled = true;
        }

        internal void StartDocking() {
            var window = Window.GetWindow(this);
            var workspacePos = PointToScreen(new Point());

            highlightWindow.Owner = window;
            highlightWindow.Left = workspacePos.X;
            highlightWindow.Top = workspacePos.Y;
            highlightWindow.Width = ActualWidth;
            highlightWindow.Height = ActualHeight;
            highlightWindow.DockSpots = rootDockPanel.DockSpots;
            foreach (DockSpot spot in highlightWindow.DockSpots)
                spot.Rect = new Rect(PointFromScreen(spot.Rect.Location), spot.Rect.Size);
            highlightWindow.Show();
        }

        internal void ContinueDocking() {
            if (!highlightWindow.IsVisible)
                StartDocking();
            highlightWindow.ContinueDocking();
        }

        internal bool FinishDocking() {
            highlightWindow.Hide();

            return (highlightWindow.SelectedSpot != null);
        }

        internal void dock(DockableControls controls) {
            Window.GetWindow(this).Activate();
            highlightWindow.SelectedSpot.DockPanel.Dock(controls, highlightWindow.SelectedSpot.Side);
        }

        public void Dock(DockableControls controls) {
            rootDockPanel.Dock(controls, DockSide.Center);
        }

        public WorkspaceState Save() {
            WorkspaceState state = new WorkspaceState();
            rootDockPanel.Save(state.dockState);
            peekPanel.Save(state.peekState);
            return state;
        }

        public void Restore(WorkspaceState state, IDockableControlFactory factory) {
            if (state == null)
                return;
            rootDockPanel.Restore(state.dockState, factory);
            peekPanel.Restore(state.peekState, factory);
        }
    }
}
