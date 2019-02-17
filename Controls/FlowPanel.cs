using System;
using System.Windows;
using System.Windows.Controls;

namespace Ghurund.Controls {
    public class FlowPanel : Panel {
        protected override Size MeasureOverride(Size availableSize) {
            Size size = new Size(0, 0);

            foreach (UIElement child in Children) {
                child.Measure(availableSize);
                size.Width = Math.Max(size.Width, child.DesiredSize.Width);
                size.Height = Math.Max(size.Height, child.DesiredSize.Height);
            }

            size.Width = double.IsPositiveInfinity(availableSize.Width) ?
               size.Width : availableSize.Width;

            return size;
        }

        protected override Size ArrangeOverride(Size finalSize) {
            double x = 0, y = 0, maxY = 0;
            foreach (UIElement child in InternalChildren) {
                if (x > 0 && x + child.DesiredSize.Width > finalSize.Width) {
                    x = 0;
                    y = maxY;
                }
                if (InternalChildren.IndexOf(child) == InternalChildren.Count - 1) {
                    child.Arrange(new Rect(x, y, finalSize.Width - x, child.DesiredSize.Height));
                } else {
                    child.Arrange(new Rect(x, y, child.DesiredSize.Width, child.DesiredSize.Height));
                }
                x += child.DesiredSize.Width;
                maxY = Math.Max(maxY, y + child.DesiredSize.Height);
            }
            return new Size(finalSize.Width, maxY);
        }
    }
}
