using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;

namespace Ghurund.Controls.Workspace {
    public class EditorTab : TabItem {

        Point mousePos;
        double left, top;
        private bool lmbDown, dragging;
        private Window window;

        static EditorTab() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(EditorTab), new FrameworkPropertyMetadata(typeof(EditorTab)));
        }

        public EditorTab() {
            Style = FindResource("Workspace.TabItem") as Style;
        }

        public EditorTab(EditorPanel panel) {
            Style = FindResource("Workspace.TabItem") as Style;
            Content = panel;
            Header = panel.Title;
        }

        public EditorTab(IDockablePanel control) {
            Style = FindResource("Workspace.TabItem") as Style;
            Content = new EditorPanel(control);
            Header = control.Title?.Short ?? "";
        }

        public override void OnApplyTemplate() {
            base.OnApplyTemplate();

            window = Window.GetWindow(this);

            MenuItem minimizeItem = GetTemplateChild("minimizeMenuItem") as MenuItem;
            minimizeItem.Click += minimize_Click;
            MenuItem maximizeItem = GetTemplateChild("maximizeMenuItem") as MenuItem;
            maximizeItem.Click += maximize_Click;

            MenuItem minimizeToLeftItem = GetTemplateChild("minimizeToLeftMenuItem") as MenuItem;
            minimizeToLeftItem.Click += minimizeToLeft_Click;
            MenuItem minimizeToTopItem = GetTemplateChild("minimizeToTopMenuItem") as MenuItem;
            minimizeToTopItem.Click += minimizeToTop_Click;
            MenuItem minimizeToRightItem = GetTemplateChild("minimizeToRightMenuItem") as MenuItem;
            minimizeToRightItem.Click += minimizeToRight_Click;
            MenuItem minimizeToBottomItem = GetTemplateChild("minimizeToBottomMenuItem") as MenuItem;
            minimizeToBottomItem.Click += minimizeToBottom_Click;

            MenuItem closeItem = GetTemplateChild("closeMenuItem") as MenuItem;
            closeItem.Click += close_Click;
            MenuItem undockItem = GetTemplateChild("undockMenuItem") as MenuItem;
            undockItem.Click += undock_Click;
        }

        private void minimize_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new WindowActionEventArgs(
                TitleBar.WindowActionEvent,
                WindowAction.Minimize,
                controls: new DockableGroup(Content as EditorPanel)));
        }

        private void maximize_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new WindowActionEventArgs(
                TitleBar.WindowActionEvent,
                WindowAction.Maximize,
                controls: new DockableGroup(Content as EditorPanel)));
        }


        private void minimizeToLeft_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new WindowActionEventArgs(
                TitleBar.WindowActionEvent,
                WindowAction.Minimize,
                controls: new DockableGroup(Content as EditorPanel),
                side: PeekSide.Left));
        }

        private void minimizeToTop_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new WindowActionEventArgs(
                TitleBar.WindowActionEvent,
                WindowAction.Minimize,
                controls: new DockableGroup(Content as EditorPanel),
                side: PeekSide.Top));
        }

        private void minimizeToRight_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new WindowActionEventArgs(
                TitleBar.WindowActionEvent,
                WindowAction.Minimize,
                controls: new DockableGroup(Content as EditorPanel),
                side: PeekSide.Right));
        }

        private void minimizeToBottom_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new WindowActionEventArgs(
                TitleBar.WindowActionEvent,
                WindowAction.Minimize,
                controls: new DockableGroup(Content as EditorPanel),
                side: PeekSide.Bottom));
        }


        private void close_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new WindowActionEventArgs(
                TitleBar.WindowActionEvent,
                WindowAction.Close,
                controls: new DockableGroup(Content as EditorPanel)));
        }

        private void undock_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new WindowActionEventArgs(
                TitleBar.WindowActionEvent,
                WindowAction.Undock,
                controls: new DockableGroup(Content as EditorPanel)));
        }

        protected override void OnMouseDown(MouseButtonEventArgs e) {
            base.OnMouseDown(e);

            if (e.Source != this)
                return;
            if (e.ChangedButton != MouseButton.Left)
                return;

            mousePos = PointToScreen(e.GetPosition(this));
            left = window.Left;
            top = window.Top;
            CaptureMouse();
            lmbDown = true;
        }

        protected override void OnMouseMove(MouseEventArgs e) {
            base.OnMouseMove(e);

            if (!lmbDown)
                return;

            try {
                var pos = PointToScreen(e.GetPosition(this));
                if (!dragging &&
                    (Math.Abs(pos.X - mousePos.X) >= SystemParameters.MinimumHorizontalDragDistance ||
                    Math.Abs(pos.Y - mousePos.Y) >= SystemParameters.MinimumVerticalDragDistance)) {

                    dragging = true;
                    var panel = Content as EditorPanel;
                    RaiseEvent(new WindowActionEventArgs(TitleBar.WindowActionEvent, WindowAction.Undock, e.GetPosition(this), new DockableGroup(panel.Content as IDockablePanel)));
                }

            } catch (Exception) {
                lmbDown = false;
                dragging = false;
            }

            e.Handled = true;
        }

        protected override void OnMouseUp(MouseButtonEventArgs e) {
            base.OnMouseUp(e);

            ReleaseMouseCapture();
            lmbDown = false;
            dragging = false;
        }
    }
}
