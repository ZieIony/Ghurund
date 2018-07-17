using System.Collections.Generic;
using System.Windows;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Shapes;

namespace Ghurund.Controls.Workspace {
    public partial class HighlightWindow : Window {
        Brush brush;
        Pen pen;
        Rect rectangle = new Rect();

        public DockSpot SelectedSpot { get; private set; }

        public List<DockSpot> DockSpots { get; set; }

        public HighlightWindow() {
            InitializeComponent();

            brush = new SolidColorBrush(Color.FromArgb(0x7f, 0x64, 0x95, 0xed));
            pen = new Pen(brush, 1);
            ShowInTaskbar = false;
        }

        internal void ContinueDocking() {
            DockSpot prevSpot = SelectedSpot;
            Point mousePos = Mouse.GetPosition(this);

            SelectedSpot = null;
            foreach (DockSpot spot in DockSpots) {
                if (spot.Rect.Contains(mousePos)) {
                    SelectedSpot = spot;
                    break;
                }
            }

            if (prevSpot != SelectedSpot)
                InvalidateVisual();
        }

        protected override void OnRenderSizeChanged(SizeChangedInfo sizeInfo) {
            base.OnRenderSizeChanged(sizeInfo);
            rectangle.Size = RenderSize;
        }

        protected override void OnRender(DrawingContext drawingContext) {
            base.OnRender(drawingContext);

            if (SelectedSpot!=null)
                drawingContext.DrawRectangle(brush, pen, SelectedSpot.Rect);
        }
    }
}
