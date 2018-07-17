using System;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace Ghurund.Controls.Workspace {
    public class EditorPanel : ContentControl {

        public String Title {
            get { return (String)GetValue(TitleProperty); }
            set { SetValue(TitleProperty, value); }
        }

        public static readonly DependencyProperty TitleProperty =
            DependencyProperty.Register("Title", typeof(String), typeof(EditorPanel), new PropertyMetadata(null));

        public ImageSource Icon {
            get { return (ImageSource)GetValue(IconProperty); }
            set {
                SetValue(IconProperty, value);
            }
        }

        public static readonly DependencyProperty IconProperty =
            DependencyProperty.Register("Icon", typeof(ImageSource), typeof(EditorPanel), new PropertyMetadata(null));

        static EditorPanel() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(EditorPanel), new FrameworkPropertyMetadata(typeof(EditorPanel)));
        }

        public EditorPanel() {
        }

        public EditorPanel(IDockableControl control) {
            control.Control.Width = double.NaN;
            control.Control.Height = double.NaN;
            Content = control.Control;
            Title = control.Title;
            Icon = control.Icon;
        }

        public EditorPanel(PeekableControl control) {
            control.Control.Width = double.NaN;
            control.Control.Height = double.NaN;
            Content = control.Control;
            Title = control.Title;
            Icon = control.Icon;
        }

    }
}
