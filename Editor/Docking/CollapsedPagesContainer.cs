using System.Collections.Generic;
using System.Windows.Forms;

namespace Ghurund.Editor.Docking {
    public partial class CollapsedPagesContainer : UserControl, IDockContainer {
        Dictionary<DockSide, PeekPanel> panels = new Dictionary<DockSide, PeekPanel>();

        public CollapsedPagesContainer() {
            InitializeComponent();

            PeekPanel leftPeekPanel = new PeekPanel();
            leftPeekPanel.Dock = DockStyle.Left;
            leftPeekPanel.Visible = false;
            panels.Add(DockSide.Left, leftPeekPanel);
            Controls.Add(leftPeekPanel);

            rootDockPanel1.CollapsedPagesContainer = this;
        }

        public void collapse(System.Windows.Forms.Control control, string text, DockSide side) {
            if (!panels.ContainsKey(side))
                return;
            panels[side].add(control, text);
        }

        /*public void expand(DockableTabPage page) {
            if (!pages.ContainsKey(page))
                return;
            CollapsedPage collapsedPage = pages[page];
            panels[collapsedPage.side].flowLayout.Controls.Remove(collapsedPage.button);
            rootDockPanel1.dock(page, collapsedPage.side);
        }*/

        public void dock(DockableTabPage control, DockSide dockSide = DockSide.Center) => rootDockPanel1.dock(control, dockSide);

        public void dock(System.Windows.Forms.Control control, DockSide dockSide = DockSide.Center) => ((IDockContainer)rootDockPanel1).dock(control, dockSide);

        public void flatten() => rootDockPanel1.flatten();

        public void undock(DockableTabPage control) => rootDockPanel1.undock(control);
    }
}
