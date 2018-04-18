using System;
using System.Windows.Forms;
using System.Runtime.InteropServices;

namespace Ghurund.Editor.Docking {
    public partial class DockableWindow : Form {
        public const int WM_NCLBUTTONDOWN = 0xA1;
        public const int HT_CAPTION = 0x2;

        [DllImportAttribute("user32.dll")]
        public static extern int SendMessage(IntPtr hWnd,
                         int Msg, int wParam, int lParam);
        [DllImportAttribute("user32.dll")]
        public static extern bool ReleaseCapture();

        public DockableWindow() {
            InitializeComponent();
        }
        public DockableWindow(String title, System.Windows.Forms.Control content) {
            InitializeComponent();
            Text = title;
            Controls.Clear();
            Controls.Add(content);
        }

        public RootDockPanel DockPanel { get; set; }

        public new System.Windows.Forms.Control.ControlCollection Controls {
            get {
                return contentPanel.Controls;
            }
        }

        public void startDrag() {
            ReleaseCapture();
            SendMessage(Handle, WM_NCLBUTTONDOWN, HT_CAPTION, 0);
        }

        public DockableTabPage toPanel() {
            return new DockableTabPage(Controls[0], Text) {
                RootPanel = DockPanel
            };
        }

        private int WM_ENTERSIZEMOVE = 0x231;
        private int WM_EXITSIZEMOVE = 0x232;
        private int WM_MOVING = 0x0216;

        protected override void WndProc(ref Message m) {
            base.WndProc(ref m);
            if (m.Msg == WM_ENTERSIZEMOVE) {
                DockPanel.startDock();
            } else if (m.Msg == WM_MOVING) {
                DockPanel.dockingMsg(ref m);
            } else if (m.Msg == WM_EXITSIZEMOVE) {
                if (DockPanel.canDock()) {
                    DockPanel.dock(toPanel());
                    Dispose();
                }
                DockPanel.finishDock();
            }
        }
    }
}
