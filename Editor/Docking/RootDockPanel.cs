using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.ComponentModel;

namespace Ghurund.Editor.Docking {
    public partial class RootDockPanel : UserControl, IDockContainer {
		internal static readonly int GWL_EXSTYLE = -20;
		internal static readonly int WS_EX_COMPOSITED = 0x02000000;

		[DllImport("user32")]
		internal static extern int GetWindowLong(IntPtr hWnd, int nIndex);

		[DllImport("user32")]
		internal static extern int SetWindowLong(IntPtr hWnd, int nIndex, int dwNewLong);

		private DockHighlightPanel dockHighlightPanel1;

        private CollapsedPagesContainer pagesContainer;
        [DefaultValue(null), Browsable(false)]
        public CollapsedPagesContainer CollapsedPagesContainer {
            get {
                return pagesContainer;
            }
            set {
                pagesContainer = value;
                childDockPanel.CollapsedPagesContainer = value;
            }
        }

        public RootDockPanel() {
			InitializeComponent();

            dockHighlightPanel1 = new DockHighlightPanel();
			dockHighlightPanel1.ForeColor = Color.CornflowerBlue;

			childDockPanel.RootPanel = this;
			DockPanels.Add(childDockPanel);
		}


		public List<DockSpot> DockSpots { get; set; }
        public List<ChildDockPanel> DockPanels { get; } = new List<ChildDockPanel>();

        public DockSpot[] getDockSpots() {
			DockSpot left = new DockSpot(new Rectangle(0, 0, Size.Width / 6, Size.Height),
				new Rectangle(0, 0, Size.Width / 6, Size.Height), DockSide.Left, this);
			DockSpot right = new DockSpot(new Rectangle(Size.Width * 5 / 6, 0, Size.Width / 6, Size.Height),
				new Rectangle(Size.Width * 5 / 6, 0, Size.Width / 6, Size.Height), DockSide.Right, this);
			DockSpot top = new DockSpot(new Rectangle(0, 0, Size.Width, Size.Height / 6),
				new Rectangle(0, 0, Size.Width, Size.Height / 6), DockSide.Top, this);
			DockSpot bottom = new DockSpot(new Rectangle(0, Size.Height * 5 / 6, Size.Width, Size.Height / 6),
				new Rectangle(0, Size.Height * 5 / 6, Size.Width, Size.Height / 6), DockSide.Bottom, this);
			return new DockSpot[] { left, right, top, bottom };
		}

		public void startDock() {
			List<DockSpot> spots = new List<DockSpot>();
			foreach (System.Windows.Forms.Control c in Controls) {
				if (c is ChildDockPanel) {
					ChildDockPanel childPanel = c as ChildDockPanel;
					childPanel.getDockSpots(spots);
				}
			}
			spots.AddRange(getDockSpots());
            foreach (DockSpot d in spots) {
                d.hitRect.Location = PointToClient(d.hitRect.Location);
                d.drawRect.Location = PointToClient(d.drawRect.Location);
            }
            DockSpots = spots;
			dockHighlightPanel1.DockSpots = spots;
			dockHighlightPanel1.Visible = true;
			dockHighlightPanel1.Location = PointToScreen(Point.Empty);
			dockHighlightPanel1.Size = Size;
		}

		public void finishDock() {
			dockHighlightPanel1.Visible = false;
		}

		public Boolean canDock() {
			return dockHighlightPanel1.SelectedDock != null;
		}

		public void dock(System.Windows.Forms.Control control) {
			DockableTabPage tabPage = new DockableTabPage();
			tabPage.Text = control.Text;
            control.Dock = DockStyle.Fill;
			tabPage.Controls.Add(control);
			dock(tabPage);
		}

		public void dock(DockableTabPage control) {
			if (dockHighlightPanel1.SelectedDock != null) {
				dockHighlightPanel1.SelectedDock.parent.dock(control, dockHighlightPanel1.SelectedDock.side);
			} else {
				childDockPanel.dock(control);
			}
		}

		public void dock(System.Windows.Forms.Control control, DockSide side) {
			DockableTabPage tabPage = new DockableTabPage();
			tabPage.Text = control.Text;
            control.Dock = DockStyle.Fill;
            tabPage.Controls.Add(control);
			dock(tabPage, side);
		}

		public void dock(DockableTabPage control, DockSide side) {
			if (side == DockSide.Center) {
				childDockPanel.dock(control);
			} else {
				SplitContainer splitContainer = new SplitContainer();
				splitContainer.Dock = DockStyle.Fill;
				Controls.Remove(childDockPanel);

				ChildDockPanel child2 = new ChildDockPanel();
                child2.CollapsedPagesContainer = CollapsedPagesContainer;
                child2.RootPanel = this;
				if (side == DockSide.Left || side == DockSide.Top) {
					splitContainer.Panel1.Controls.Add(child2);
					splitContainer.Panel2.Controls.Add(childDockPanel);
				} else {
					splitContainer.Panel1.Controls.Add(childDockPanel);
					splitContainer.Panel2.Controls.Add(child2);
				}
				if (side == DockSide.Top || side == DockSide.Bottom) {
					splitContainer.Orientation = Orientation.Horizontal;
					//splitContainer.SplitterDistance = Height / 2;
					childDockPanel.orientation = Orientation.Horizontal;
					child2.orientation = Orientation.Horizontal;
				} else {
					//splitContainer.SplitterDistance = Width / 2;
					childDockPanel.orientation = Orientation.Vertical;
					child2.orientation = Orientation.Vertical;
				}

				child2.dock(control);
				DockPanels.Add(child2);

				childDockPanel = new ChildDockPanel();
				childDockPanel.RootPanel = this;
				childDockPanel.Controls.Clear();
				childDockPanel.Controls.Add(splitContainer);
				childDockPanel.SplitContainer = splitContainer;
				childDockPanel.TabControl = null;
                childDockPanel.CollapsedPagesContainer = CollapsedPagesContainer;

				Controls.Add(childDockPanel);
			}
			control.RootPanel = this;
		}

		public void undock(DockableTabPage control) {
			// nothing to do here
		}

		public void flatten() {
			// nothing to do here
		}

		internal void dockingMsg(ref Message m) {
			dockHighlightPanel1.dockingMsg(ref m);
		}

	}
}
