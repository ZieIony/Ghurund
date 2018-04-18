using System;
using System.Collections.Generic;
using System.Windows.Forms;
using Ghurund.Editor.Control;

namespace Ghurund.Editor.Docking {
    public class PeekPanel : FlowLayoutPanel {
        private ResizeGrip resizeGrip;
        private Panel peekedContainer;
        private Panel closePeek;

        private Dictionary<Button, System.Windows.Forms.Control> controls = new Dictionary<Button, System.Windows.Forms.Control>();

        public PeekPanel() {
            AutoSize = true;
            AutoSizeMode = AutoSizeMode.GrowAndShrink;

            closePeek = new TransparentPanel {
                Dock = DockStyle.Fill
            };
            closePeek.Click += ClosePeek_Click;

            DockChanged += PeekPanel_DockChanged;
        }

        private void PeekPanel_DockChanged(object sender, EventArgs e) {
            resizeGrip = new ResizeGrip();
            peekedContainer = new Panel {
                Dock = Dock
            };

            switch (Dock) {
                case DockStyle.Top:
                    resizeGrip.Height = 5;
                    resizeGrip.Dock = DockStyle.Bottom;
                    resizeGrip.Cursor = Cursors.SizeNS;
                    break;
                case DockStyle.Bottom:
                    resizeGrip.Height = 5;
                    resizeGrip.Dock = DockStyle.Top;
                    resizeGrip.Cursor = Cursors.SizeNS;
                    break;
                case DockStyle.Left:
                    resizeGrip.Width = 5;
                    resizeGrip.Dock = DockStyle.Right;
                    resizeGrip.Cursor = Cursors.SizeWE;
                    break;
                case DockStyle.Right:
                    resizeGrip.Width = 5;
                    resizeGrip.Dock = DockStyle.Left;
                    resizeGrip.Cursor = Cursors.SizeWE;
                    break;
            }

            peekedContainer.Controls.Add(resizeGrip);
        }

        public void add(System.Windows.Forms.Control control, string text) {
            VerticalButton button = new VerticalButton {
                AutoSize = true,
                AutoSizeMode = AutoSizeMode.GrowAndShrink,
                VerticalText = text
            };
            button.Click += Button_Click;
            Controls.Add(button);
            controls.Add(button, control);
            Visible = true;
        }

        private void Button_Click(object sender, EventArgs e) => peek(controls[sender as Button]);

        private void peek(System.Windows.Forms.Control control) {
            control.Dock = DockStyle.Fill;
            peekedContainer.Width = 250;
            peekedContainer.Controls.Add(control);
            control.BringToFront();

            Parent.Controls.Add(peekedContainer);
            peekedContainer.BringToFront();
            Parent.Controls.Add(closePeek);
            closePeek.BringToFront();
            Parent.Refresh();
        }

        private void ClosePeek_Click(object sender, EventArgs e) {
            foreach (System.Windows.Forms.Control c in peekedContainer.Controls) {
                if (c != resizeGrip) {
                    peekedContainer.Controls.Remove(c);
                    break;
                }
            }
            peekedContainer.Parent = null;
            closePeek.Parent = null;
        }

    }
}
