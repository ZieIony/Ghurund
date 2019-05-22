using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Ghurund.Controls.Workspace {
    public class WorkspacePanel: Control {
        private HighlightWindow highlightWindow = new HighlightWindow();
        private DockPanel rootDockPanel;
        private PeekPanel peekPanel;
        private EditorPanel focusedPanel;

        public static readonly RoutedEvent PanelFocusedEvent = EventManager.RegisterRoutedEvent("PanelFocused", RoutingStrategy.Bubble, typeof(PanelActionEventHandler), typeof(WorkspacePanel));

        public event PanelActionEventHandler PanelFocused {
            add { AddHandler(PanelFocusedEvent, value); }
            remove { RemoveHandler(PanelFocusedEvent, value); }
        }

        public static readonly RoutedEvent PanelClosedEvent = EventManager.RegisterRoutedEvent("PanelClosed", RoutingStrategy.Bubble, typeof(PanelActionEventHandler), typeof(WorkspacePanel));

        public event PanelActionEventHandler PanelClosed {
            add { AddHandler(PanelClosedEvent, value); }
            remove { RemoveHandler(PanelClosedEvent, value); }
        }

        public static readonly RoutedEvent SelectionChangedEvent = EventManager.RegisterRoutedEvent("SelectionChanged", RoutingStrategy.Bubble, typeof(RoutedSelectionChangedEventHandler), typeof(WorkspacePanel));

        public event RoutedSelectionChangedEventHandler SelectionChanged {
            add { AddHandler(SelectionChangedEvent, value); }
            remove { RemoveHandler(SelectionChangedEvent, value); }
        }

        static WorkspacePanel() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(WorkspacePanel), new FrameworkPropertyMetadata(typeof(WorkspacePanel)));
        }

        public override void OnApplyTemplate() {
            base.OnApplyTemplate();
            rootDockPanel = GetTemplateChild("rootDockPanel") as DockPanel;
            peekPanel = GetTemplateChild("peekPanel") as PeekPanel;

            AddHandler(TitleBar.WindowActionEvent, new WindowActionEventHandler(titleBar_WindowAction));
            AddHandler(PanelFocusedEvent, new PanelActionEventHandler(panelFocused));
        }

        private void panelFocused(object sender, PanelActionEventArgs e) {
            if (focusedPanel == e.Panel) {
                e.Handled = true;
            } else {
                if (focusedPanel != null)
                    focusedPanel.PanelFocused = false;
                focusedPanel = e.Panel;
                focusedPanel.PanelFocused = true;
                if(e.Panel.Content is IToolPanel)
                    RaiseEvent(new RoutedSelectionChangedEventArgs((e.Panel.Content as IToolPanel).SelectedItems, SelectionChangedEvent));
            }
        }

        private void titleBar_WindowAction(object sender, WindowActionEventArgs args) {
            rootDockPanel.flatten();
            if (args.Action == WindowAction.Undock) {
                var window = new EditorWindow(this, args.DockableControls);
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
                if (args.DockableControls == null) {
                    peekPanel.HideContent();
                } else {
                    peekPanel.Add(args.DockableControls, PeekSide.Left);
                }
            } else if (args.Action == WindowAction.Close) {
                if (peekPanel.IsOpen)
                    peekPanel.ClosePeeked();
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

            return highlightWindow.SelectedSpot != null;
        }

        internal void dock(DockableGroup controls) {
            Window.GetWindow(this).Activate();
            highlightWindow.SelectedSpot.DockPanel.Dock(controls, highlightWindow.SelectedSpot.Side);
        }

        public void Dock(DockableGroup controls) {
            rootDockPanel.Dock(controls, DockSide.Center);
        }

        public WorkspaceState Save() {
            WorkspaceState state = new WorkspaceState();
            rootDockPanel.Save(state.dockState);
            peekPanel.Save(state.peekState);
            return state;
        }

        public void Restore(WorkspaceState state, IDockablePanelFactory factory) {
            if (state == null)
                return;
            rootDockPanel.Restore(state.dockState, factory);
            peekPanel.Restore(state.peekState, factory);
        }

        public bool ShowChild(Control control) {
            DependencyObject parent = control.Parent;
            while (parent != null) {
                if (parent == rootDockPanel) {
                    return true;
                } else if (parent is FrameworkElement) {
                    FrameworkElement frameworkElement = parent as FrameworkElement;
                    if (frameworkElement.Parent is TabControl) {
                        TabControl tabControl = frameworkElement.Parent as TabControl;
                        tabControl.SelectedItem = frameworkElement;
                    }
                    parent = frameworkElement.Parent;
                } else {
                    return false;
                }
            }
            return false;
        }

        public void Clear() {
            rootDockPanel.Clear();
        }
    }
}
