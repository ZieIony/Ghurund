using System.Windows.Forms;

namespace Ghurund.Editor.Control {
    public class SystemButton : Button {
        public CaptionButton Caption { get; set; } = CaptionButton.Close;

        protected override void OnPaintBackground(PaintEventArgs e) {
            //base.OnPaintBackground(e);
        }

        protected override void OnPaint(PaintEventArgs pevent) {
            ControlPaint.DrawCaptionButton(pevent.Graphics, 0, 0, Width, Height, Caption, ButtonState.Flat);
        }
    }
}
