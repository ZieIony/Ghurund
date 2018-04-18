using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace Ghurund.Editor.Docking {
    public partial class ChildDockPanel : UserControl, IDockContainer {

        int prevSplitterDistance;

        public Orientation orientation = Orientation.Horizontal;

        [DefaultValue(null), Browsable(false)]
        public RootDockPanel RootPanel { get; set; } = null;

        private CollapsedPagesContainer pagesContainer;
        [DefaultValue(null), Browsable(false)]
        public CollapsedPagesContainer CollapsedPagesContainer {
            get {
                return pagesContainer;
            }
            set {
                pagesContainer = value;
                tabControl.CollapsedPagesContainer = value;
            }
        }

        public ChildDockPanel() {
            InitializeComponent();

            Dock = DockStyle.Fill;
        }

        public void getDockSpots(List<DockSpot> list) {
            if (SplitContainer == null) {
                Point p = PointToScreen(Location);
                list.Add(new DockSpot(new Rectangle(p.X + Size.Width / 6, p.Y, Size.Width / 6, Size.Height),
                    new Rectangle(p.X, p.Y, Size.Width / 2, Size.Height), DockSide.Left, this));
                list.Add(new DockSpot(new Rectangle(p.X + Size.Width * 4 / 6, p.Y, Size.Width / 6, Size.Height),
                    new Rectangle(p.X + Size.Width / 2, p.Y, Size.Width / 2, Size.Height), DockSide.Right, this));
                list.Add(new DockSpot(new Rectangle(p.X, p.Y + Size.Height / 6, Size.Width, Size.Height / 6),
                    new Rectangle(p.X, p.Y, Size.Width, Size.Height / 2), DockSide.Top, this));
                list.Add(new DockSpot(new Rectangle(p.X, p.Y + Size.Height * 4 / 6, Size.Width, Size.Height / 6),
                    new Rectangle(p.X, p.Y + Size.Height / 2, Size.Width, Size.Height / 2), DockSide.Bottom, this));
                list.Add(new DockSpot(new Rectangle(p.X + Size.Width * 2 / 6, p.Y + Size.Height * 2 / 6, Size.Width * 2 / 6, Size.Height * 2 / 6),
                    new Rectangle(p.X, p.Y, Size.Width, Size.Height), DockSide.Center, this));
            } else {
                ChildDockPanel child1 = SplitContainer.Panel1.Controls[0] as ChildDockPanel;
                ChildDockPanel child2 = SplitContainer.Panel2.Controls[0] as ChildDockPanel;
                child1.getDockSpots(list);
                child2.getDockSpots(list);
            }
        }

        #region IDockContainer Members

        public void dock(System.Windows.Forms.Control control) {
            DockableTabPage tabPage = new DockableTabPage();
            tabPage.Text = control.Text;
            tabPage.Controls.Add(control);
            dock(tabPage);
        }
        public void dock(DockableTabPage control) {
            tabControl.TabPages.Add(control);
            control.RootPanel = RootPanel;
        }

        public void dock(System.Windows.Forms.Control control, DockSide side) {
            DockableTabPage tabPage = new DockableTabPage();
            tabPage.Text = control.Text;
            tabPage.Controls.Add(control);
            dock(tabPage, side);
        }
        public void dock(DockableTabPage control, DockSide side) {
            if (side == DockSide.Center) {
                tabControl.TabPages.Add(control);
            } else {    // split container is null
                SplitContainer = new SplitContainer();
                SplitContainer.Dock = DockStyle.Fill;
                Controls.Remove(tabControl);
                RootPanel.DockPanels.Remove(this);

                ChildDockPanel child1 = new ChildDockPanel();
                child1.CollapsedPagesContainer = CollapsedPagesContainer;
                child1.RootPanel = RootPanel;
                RootPanel.DockPanels.Add(child1);
                ChildDockPanel child2 = new ChildDockPanel();
                child2.CollapsedPagesContainer = CollapsedPagesContainer;
                child2.RootPanel = RootPanel;
                RootPanel.DockPanels.Add(child2);
                if (side == DockSide.Left || side == DockSide.Top) {
                    SplitContainer.Panel1.Controls.Add(child1);
                    SplitContainer.Panel2.Controls.Add(child2);
                } else {
                    SplitContainer.Panel1.Controls.Add(child2);
                    SplitContainer.Panel2.Controls.Add(child1);
                }
                if (side == DockSide.Top || side == DockSide.Bottom) {
                    SplitContainer.Orientation = Orientation.Horizontal;
                    //splitContainer.SplitterDistance = Height / 2;
                    child1.orientation = Orientation.Horizontal;
                    child2.orientation = Orientation.Horizontal;
                } else {
                    //splitContainer.SplitterDistance = Width / 2;
                    child1.orientation = Orientation.Vertical;
                    child2.orientation = Orientation.Vertical;
                }

                child1.dock(control);
                child2.Controls.Clear();
                child2.Controls.Add(tabControl);
                child2.TabControl = tabControl;

                Controls.Add(SplitContainer);
                tabControl = null;
            }
            control.RootPanel = RootPanel;
        }

        public void undock(DockableTabPage control) {
            tabControl.TabPages.Remove(control);
            if (tabControl.TabCount == 0) {
                if (!(Parent is RootDockPanel)) {
                    IDockContainer childDockPanel = Parent.Parent.Parent as IDockContainer;
                    Parent.Controls.Remove(this);
                    childDockPanel.flatten();
                }
            }
        }

        public void flatten() {
            Controls.Remove(SplitContainer);
            if (SplitContainer.Panel1.Controls.Count > 0) {
                Controls.Add(SplitContainer.Panel1.Controls[0].Controls[0]);    // add child DockableTabControl to this
                RootPanel.DockPanels.Remove(SplitContainer.Panel1.Controls[0] as ChildDockPanel);
            }
            if (SplitContainer.Panel2.Controls.Count > 0) {
                Controls.Add(SplitContainer.Panel2.Controls[0].Controls[0]);    // add child DockableTabControl to this
                RootPanel.DockPanels.Remove(SplitContainer.Panel2.Controls[0] as ChildDockPanel);
            }
            if (Controls[0] is SplitContainer) {
                SplitContainer = Controls[0] as SplitContainer;
                tabControl = null;
            } else {
                SplitContainer = null;
                tabControl = Controls[0] as DockableTabControl;
            }
            RootPanel.DockPanels.Add(this);
        }

        #endregion

        public SplitContainer SplitContainer { get; set; } = null;

        public DockableTabControl TabControl {
            get {
                return tabControl;
            }
            set {
                tabControl = value;
            }
        }
    }
}
