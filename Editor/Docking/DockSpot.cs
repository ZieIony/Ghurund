using System.Drawing;

namespace Ghurund.Editor.Docking {
    public class DockSpot {
        public Rectangle hitRect, drawRect;
        public DockSide side;
        public IDockContainer parent;

        public DockSpot(Rectangle hitRect, Rectangle drawRect, DockSide dockSide, IDockContainer parent) {
            this.hitRect = hitRect;
            this.drawRect = drawRect;
            this.side = dockSide;
            this.parent = parent;
        }
    }
}
