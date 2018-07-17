using System;
using System.ComponentModel;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;

namespace Ghurund.Controls.Workspace {
    public class PeekButton : Button {
        static PeekButton() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(PeekButton), new FrameworkPropertyMetadata(typeof(PeekButton)));
        }

        [Bindable(true)]
        public Brush SelectionBrush {
            get { return (Brush)GetValue(SelectionBrushProperty); }
            set { SetValue(SelectionBrushProperty, value); }
        }

        public static readonly DependencyProperty SelectionBrushProperty =
            DependencyProperty.Register("SelectionBrush", typeof(Brush), typeof(PeekButton), new PropertyMetadata(null));

        [Bindable(true)]
        public String Text {
            get { return (String)GetValue(TextProperty); }
            set { SetValue(TextProperty, value); }
        }

        public static readonly DependencyProperty TextProperty =
            DependencyProperty.Register("Text", typeof(String), typeof(PeekButton), new PropertyMetadata(null));

        [Bindable(true)]
        public ImageSource Icon {
            get { return (ImageSource)GetValue(IconProperty); }
            set { SetValue(IconProperty, value); }
        }

        public static readonly DependencyProperty IconProperty =
            DependencyProperty.Register("Icon", typeof(ImageSource), typeof(PeekButton), new PropertyMetadata(null));

        [Bindable(true)]
        public Orientation Orientation {
            get { return (Orientation)GetValue(OrientationProperty); }
            set { SetValue(OrientationProperty, value); }
        }

        private static readonly DependencyProperty OrientationProperty =
            DependencyProperty.Register("Orientation", typeof(Orientation), typeof(PeekButton), new PropertyMetadata(null));
    }
}
