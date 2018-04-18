using System;
using System.Drawing;
using System.Windows.Forms;

namespace Ghurund.Editor.Control {
    public class VerticalButton : Button {
        private StringFormat format = new StringFormat {
            Alignment = StringAlignment.Center,
            LineAlignment = StringAlignment.Center
        };

        public string VerticalText {
            get; set;
        }

        protected override void OnPaint(PaintEventArgs pevent) {
            base.OnPaint(pevent);

            pevent.Graphics.TranslateTransform(Width, 0);
            pevent.Graphics.RotateTransform(90);

            pevent.Graphics.DrawString(VerticalText, Font, new SolidBrush(ForeColor), new Rectangle(0, 0, Height, Width), format);
        }

        public override Size GetPreferredSize(Size proposedSize) {
            Size textSize = TextRenderer.MeasureText(VerticalText, Font, proposedSize, TextFormatFlags.GlyphOverhangPadding);
            Size size = new Size(textSize.Height + Padding.Vertical + FlatAppearance.BorderSize, textSize.Width + Padding.Horizontal + FlatAppearance.BorderSize);
            Size baseSize = base.GetPreferredSize(proposedSize);
            return new Size(Math.Max(baseSize.Width, size.Width), Math.Max(baseSize.Height, size.Height));
        }

    }
}
