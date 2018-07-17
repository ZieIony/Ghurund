using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Controls.Workspace {
    public class SplitPanel : Control {

        public Orientation Orientation {
            get { return (Orientation)GetValue(OrientationProperty); }
            set { SetValue(OrientationProperty, value); }
        }

        public static readonly DependencyProperty OrientationProperty =
            DependencyProperty.Register("Orientation", typeof(Orientation), typeof(SplitPanel), new PropertyMetadata(Orientation.Horizontal));

        public Control Panel1 {
            get { return (Control)GetValue(Panel1Property); }
            set { SetValue(Panel1Property, value); }
        }

        public static readonly DependencyProperty Panel1Property =
            DependencyProperty.Register("Panel1", typeof(Control), typeof(SplitPanel), new PropertyMetadata(null));

        public GridLength Panel1Size {
            get { return (GridLength)GetValue(Panel1SizeProperty); }
            set { SetValue(Panel1SizeProperty, value); }
        }

        public static readonly DependencyProperty Panel1SizeProperty =
            DependencyProperty.Register("Panel1Size", typeof(GridLength), typeof(SplitPanel), new PropertyMetadata(null));

        public Control Panel2 {
            get { return (Control)GetValue(Panel2Property); }
            set { SetValue(Panel2Property, value); }
        }

        public static readonly DependencyProperty Panel2Property =
            DependencyProperty.Register("Panel2", typeof(Control), typeof(SplitPanel), new PropertyMetadata(null));

        public GridLength Panel2Size {
            get { return (GridLength)GetValue(Panel2SizeProperty); }
            set { SetValue(Panel2SizeProperty, value); }
        }

        public static readonly DependencyProperty Panel2SizeProperty =
            DependencyProperty.Register("Panel2Size", typeof(GridLength), typeof(SplitPanel), new PropertyMetadata(null));


        static SplitPanel() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SplitPanel), new FrameworkPropertyMetadata(typeof(SplitPanel)));
        }

        public override void OnApplyTemplate() {
            base.OnApplyTemplate();
        }
    }
}
