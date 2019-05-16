using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace Ghurund.Controls.Workspace {
    public partial class TitleBar: Control {

        private Point mousePos;
        private double left, top;
        private bool lmbDown, dragging;

        public bool DragWindow { get; set; } = true;

        [Bindable(true)]
        public string Title {
            get { return (string)GetValue(TitleProperty); }
            set { SetValue(TitleProperty, value); }
        }

        public static readonly DependencyProperty TitleProperty =
            DependencyProperty.Register("Title", typeof(string), typeof(TitleBar), new PropertyMetadata(null));

        public bool PanelFocused {
            get { return (bool)GetValue(PanelFocusedProperty); }
            set { SetValue(PanelFocusedProperty, value); }
        }

        public static readonly DependencyProperty PanelFocusedProperty =
            DependencyProperty.Register("PanelFocused", typeof(bool), typeof(TitleBar), new PropertyMetadata(null));

        [Bindable(true)]
        public ImageSource Icon {
            get { return (ImageSource)GetValue(IconProperty); }
            set { SetValue(IconProperty, value); }
        }

        public static readonly DependencyProperty IconProperty =
            DependencyProperty.Register("Icon", typeof(ImageSource), typeof(TitleBar), new PropertyMetadata(null));

        public Brush IconColor {
            get { return (Brush)GetValue(IconColorProperty); }
            set { SetValue(IconColorProperty, value); }
        }

        public static readonly DependencyProperty IconColorProperty =
            DependencyProperty.Register("IconColor", typeof(Brush), typeof(TitleBar), new PropertyMetadata(null));
        
        public Visibility MinimizeButtonVisibility {
            get { return (Visibility)GetValue(MinimizeButtonVisibilityProperty); }
            set { SetValue(MinimizeButtonVisibilityProperty, value); }
        }

        public static readonly DependencyProperty MinimizeButtonVisibilityProperty =
            DependencyProperty.Register("MinimizeButtonVisibility", typeof(Visibility), typeof(TitleBar), new PropertyMetadata(null));

        public Visibility MaximizeButtonVisibility {
            get { return (Visibility)GetValue(MaximizeButtonVisibilityProperty); }
            set { SetValue(MaximizeButtonVisibilityProperty, value); }
        }

        public static readonly DependencyProperty MaximizeButtonVisibilityProperty =
            DependencyProperty.Register("MaximizeButtonVisibility", typeof(Visibility), typeof(TitleBar), new PropertyMetadata(null));

        public bool HandleWindowActions {
            get { return (bool)GetValue(HandleWindowActionsProperty); }
            set { SetValue(HandleWindowActionsProperty, value); }
        }

        public static readonly DependencyProperty HandleWindowActionsProperty =
            DependencyProperty.Register("HandleWindowActions", typeof(bool), typeof(TitleBar), new PropertyMetadata(null));

        public bool HandleWindowDragging {
            get { return (bool)GetValue(HandleWindowDraggingProperty); }
            set { SetValue(HandleWindowDraggingProperty, value); }
        }

        public static readonly DependencyProperty HandleWindowDraggingProperty =
            DependencyProperty.Register("HandleWindowDragging", typeof(bool), typeof(TitleBar), new PropertyMetadata(null));


        static TitleBar() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(TitleBar), new FrameworkPropertyMetadata(typeof(TitleBar)));
        }

        public override void OnApplyTemplate() {
            base.OnApplyTemplate();
            
            var closeButton = GetTemplateChild("closeButton") as Button;
            closeButton.Click += closeButton_Click;
            var maximizeButton = GetTemplateChild("maximizeButton") as Button;
            maximizeButton.Click += maximizeButton_Click;
            var minimizeButton = GetTemplateChild("minimizeButton") as Button;
            minimizeButton.Click += minimizeButton_Click;

            MenuItem closeItem = GetTemplateChild("closeMenuItem") as MenuItem;
            closeItem.Click += closeButton_Click;
            MenuItem undockItem = GetTemplateChild("undockMenuItem") as MenuItem;
            undockItem.Click += undockButton_Click;
        }

        protected override void OnMouseDown(MouseButtonEventArgs e) {
            base.OnMouseDown(e);

            if (e.ChangedButton != MouseButton.Left)
                return;

            mouseDown();

            e.Handled = true;
        }

        public void StartDrag() {
            mouseDown();
            dragging = true;
        }

        private void mouseDown() {
            mousePos = PointToScreen(Mouse.GetPosition(this));
            var window = Window.GetWindow(this);
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
                    RaiseEvent(new WindowActionEventArgs(WindowActionEvent, Workspace.WindowAction.Undock, e.GetPosition(this)));
                }

                if (dragging) {
                    if (HandleWindowDragging) {
                        windowDragged(left + pos.X - mousePos.X, top + pos.Y - mousePos.Y);
                    } else {
                        RaiseEvent(new WindowEventArgs(WindowDraggedEvent, left + pos.X - mousePos.X, top + pos.Y - mousePos.Y));
                    }
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

            var pos = PointToScreen(e.GetPosition(this));
            RaiseEvent(new WindowEventArgs(WindowDroppedEvent, left + pos.X - mousePos.X, top + pos.Y - mousePos.Y));

            e.Handled = true;
        }

        private void windowDragged(double left, double top) {
            Window.GetWindow(this).Left = left;
            Window.GetWindow(this).Top = top;
        }

        private void windowAction(WindowAction action) {
            if (action == Workspace.WindowAction.Close) {
                Window.GetWindow(this).Close();
            } else if (action == Workspace.WindowAction.Maximize) {
                Window.GetWindow(this).WindowState = (Window.GetWindow(this).WindowState == WindowState.Normal) ? WindowState.Maximized : WindowState.Normal;
            } else if (action == Workspace.WindowAction.Minimize) {
                Window.GetWindow(this).WindowState = WindowState.Minimized;
            }
        }
    }
}
