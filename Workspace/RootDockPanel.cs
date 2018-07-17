using System.Collections.Generic;
using System.Windows;

namespace Ghurund.Controls.Workspace {
    public class RootDockPanel : DockPanel {
        public override List<DockSpot> DockSpots {
            get {
                if (splitContainer == null && (tabControl == null || !tabControl.HasItems)) {
                    List<DockSpot> list = new List<DockSpot>();
                    Point p = PointToScreen(new Point());
                    list.Add(new DockSpot(new Rect(p.X, p.Y, ActualWidth, ActualHeight),
                        new Rect(p.X, p.Y, Width, Height), DockSide.Center, this));
                    return list;
                } else if (splitContainer == null) {
                    return base.DockSpots;
                } else {
                    List<DockSpot> list = new List<DockSpot>();
                    Point p = PointToScreen(new Point());
                    int spotWidth = 20;
                    int spotHeight = 20;

                    list.Add(new DockSpot(new Rect(p.X, p.Y, spotWidth, ActualHeight),
                        new Rect(p.X, p.Y, ActualWidth, ActualHeight), DockSide.Left, this));
                    list.Add(new DockSpot(new Rect(ActualWidth - spotWidth + p.X, p.Y, spotWidth, ActualHeight),
                        new Rect(p.X, p.Y, ActualWidth, ActualHeight), DockSide.Right, this));
                    list.Add(new DockSpot(new Rect(p.X, p.Y, ActualWidth, spotHeight),
                        new Rect(p.X, p.Y, ActualWidth, ActualHeight), DockSide.Top, this));
                    list.Add(new DockSpot(new Rect(p.X, p.Y + ActualHeight - spotHeight, ActualWidth, spotHeight),
                        new Rect(p.X, p.Y, ActualWidth, ActualHeight), DockSide.Bottom, this));

                    DockPanel child1 = splitContainer.Panel1 as DockPanel;
                    DockPanel child2 = splitContainer.Panel2 as DockPanel;
                    list.AddRange(child1.DockSpots);
                    list.AddRange(child2.DockSpots);

                    return list;
                }
            }
        }

    }
}
