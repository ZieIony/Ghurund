using System;
using System.ComponentModel;
using System.Drawing;
using System.Windows.Forms;

namespace Ghurund.Editor.Docking {
    public partial class DockableTabControl : TabControl {
        private bool mouseDown;
        Point downLocation;
        private DockableTabPage selectedTab;

        [DefaultValue(null), Browsable(false)]
        public CollapsedPagesContainer CollapsedPagesContainer { get; set; }

        public DockableTabControl() {
            InitializeComponent();
        }

        protected override void OnMouseDown(MouseEventArgs e) {
            base.OnMouseDown(e);
            mouseDown = true;
            downLocation = e.Location;
            for (int i = 0; i < TabCount; ++i) {
                Rectangle r = GetTabRect(i);
                if (r.Contains(e.Location)) {
                    selectedTab = TabPages[i] as DockableTabPage;
                    break;
                }
            }
        }

        protected override void OnMouseClick(MouseEventArgs e) {
            if (e.Button == MouseButtons.Middle) {
                close();
                return;
            }
            if (e.Button == MouseButtons.Right) {
                for (int i = 0; i < TabCount; ++i) {
                    Rectangle r = GetTabRect(i);
                    if (!r.Contains(e.Location))
                        continue;

                    selectedTab = TabPages[i] as DockableTabPage;

                    ContextMenuStrip menu = new ContextMenuStrip();
                    ToolStripButton closeItem = new ToolStripButton("Close");
                    closeItem.Click += new EventHandler(closeItem_Click);
                    menu.Items.Add(closeItem);
                    ToolStripButton floatItem = new ToolStripButton("Float");
                    floatItem.Click += new EventHandler(floatItem_Click);
                    menu.Items.Add(floatItem);

                    /*if (!(Parent.Parent is RootDockPanel)) {
                        SplitContainer parentSplitContainer = Parent.Parent.Parent as SplitContainer;
                        if (!parentSplitContainer.IsSplitterFixed) {*/
                            ToolStripButton hideItem = new ToolStripButton("Collapse");
                            hideItem.Click += new EventHandler(collapseItem_Click);
                            menu.Items.Add(hideItem);
                        /*}
                    }*/

                    menu.Show(PointToScreen(e.Location));
                    return;
                }
            }
            base.OnMouseClick(e);
        }

        void collapseItem_Click(object sender, EventArgs e) {
            Controls.Remove(selectedTab);
            CollapsedPagesContainer.collapse(selectedTab.Controls[0], selectedTab.Text, DockSide.Left);
        }

        void floatItem_Click(object sender, EventArgs e) {
            doFloat();
        }

        void closeItem_Click(object sender, EventArgs e) {
            close();
        }

        protected override void OnMouseUp(MouseEventArgs e) {
            base.OnMouseUp(e);
            mouseDown = false;
        }

        protected override void OnMouseMove(MouseEventArgs e) {
            base.OnMouseMove(e);
            int dist = (int)Math.Sqrt(Math.Pow(downLocation.X - e.X, 2) + Math.Pow(downLocation.Y - e.Y, 2));
            if (mouseDown && selectedTab != null && dist > 5) {
                Point p = PointToScreen(e.Location);
                DockableWindow window = doFloat();
                p.X -= e.X;
                p.Y -= e.Y;
                window.Location = p;
                window.startDrag();
                mouseDown = false;
            }
        }

        private void close() {
            IDockContainer dockPanel = Parent as IDockContainer;
            dockPanel.undock(selectedTab);
            Refresh();
        }

        private DockableWindow doFloat() {
            DockableWindow window = selectedTab.toWindow();
            window.Size = Size;
            close();
            window.Visible = true;
            selectedTab.Dispose();
            return window;
        }
    }
}
