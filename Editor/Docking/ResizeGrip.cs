using System.Drawing;
using System.Windows.Forms;

namespace Ghurund.Editor.Docking {
    public class ResizeGrip : UserControl {
        private Point prevLocation;

        public ResizeGrip() {
            MouseDown += ResizeGrip_MouseDown;
            MouseMove += ResizeGrip_MouseMove;
            MouseUp += ResizeGrip_MouseUp;

            BackColor = ProfessionalColors.GripDark;
        }

        private void ResizeGrip_MouseDown(object sender, MouseEventArgs e) {
            if (e.Button != MouseButtons.Left)
                return;

            Capture = true;
            prevLocation = MousePosition;
        }

        private void ResizeGrip_MouseMove(object sender, MouseEventArgs e) {
            if (!Capture)
                return;

            Point currentLocation = MousePosition;
            if (Dock == DockStyle.Top || Dock == DockStyle.Bottom) {
                Parent.Height += currentLocation.Y - prevLocation.Y;
            } else {
                Parent.Width += currentLocation.X - prevLocation.X;
            }
            prevLocation = currentLocation;
            Parent.Refresh();
        }

        private void ResizeGrip_MouseUp(object sender, MouseEventArgs e) {
            Capture = false;
        }
    }
}
