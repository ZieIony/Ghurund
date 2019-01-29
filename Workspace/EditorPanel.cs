using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Input;
using System.Windows.Media;

namespace Ghurund.Controls.Workspace {
    public class EditorPanel : ContentControl {

        public Title Title {
            get { return (Title)GetValue(TitleProperty); }
            set { SetValue(TitleProperty, value); }
        }

        public static readonly DependencyProperty TitleProperty =
            DependencyProperty.Register("Title", typeof(Title), typeof(EditorPanel), new PropertyMetadata(null));

        public ImageSource Icon {
            get { return (ImageSource)GetValue(IconProperty); }
            set {
                SetValue(IconProperty, value);
            }
        }

        public static readonly DependencyProperty IconProperty =
            DependencyProperty.Register("Icon", typeof(ImageSource), typeof(EditorPanel), new PropertyMetadata(null));

        public bool PanelFocused {
            get => (bool)GetValue(PanelFocusedProperty);
            set => SetValue(PanelFocusedProperty, value);
        }

        public static readonly DependencyProperty PanelFocusedProperty =
            DependencyProperty.Register("PanelFocused", typeof(bool), typeof(EditorPanel), new PropertyMetadata(null));

        static EditorPanel() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(EditorPanel), new FrameworkPropertyMetadata(typeof(EditorPanel)));
        }

        public EditorPanel() {
        }

        public EditorPanel(IDockablePanel control) {
            control.Control.Width = double.NaN;
            control.Control.Height = double.NaN;
            Content = control.Control;
            Title = control.Title;
            Icon = control.Icon;
        }

        protected override void OnPreviewMouseDown(MouseButtonEventArgs e) {
            base.OnPreviewMouseDown(e);
            RaiseEvent(new PanelActionEventArgs(this, WorkspacePanel.PanelFocusedEvent));
        }
    }
}
