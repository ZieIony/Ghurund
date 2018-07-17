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
        }

        public EditorTab(EditorPanel panel) {
            Content = panel;
            Header = panel.Title;
        }

        public EditorTab(IDockableControl control) {
            Content = new EditorPanel(control);
            Header = control.Title;
        }

        public override void OnApplyTemplate() {
            base.OnApplyTemplate();

            window = Window.GetWindow(this);

            MenuItem closeItem = GetTemplateChild("closeMenuItem") as MenuItem;
            closeItem.Click += close_Click;
            MenuItem undockItem = GetTemplateChild("undockMenuItem") as MenuItem;
            undockItem.Click += undock_Click;
        }

        private void close_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new WindowActionEventArgs(
                TitleBar.WindowActionEvent,
                WindowAction.Close,
                controls: new DockableControls(Content as EditorPanel)));
        }

        private void undock_Click(object sender, RoutedEventArgs e) {
            RaiseEvent(new WindowActionEventArgs(
                TitleBar.WindowActionEvent,
                WindowAction.Undock,
                controls: new DockableControls(Content as EditorPanel)));
        }

        protected override void OnMouseDown(MouseButtonEventArgs e) {
            base.OnMouseDown(e);

            if (e.Source != this)
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
                    RaiseEvent(new WindowActionEventArgs(TitleBar.WindowActionEvent, WindowAction.Undock, e.GetPosition(this), new DockableControls(panel.Content as IDockableControl)));
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
