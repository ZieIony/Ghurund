using System;
using System.Drawing;
using System.Windows.Forms;

namespace Ghurund.Editor.Docking {
    public partial class DockableTabPage : TabPage {
        public DockableTabPage() {
            InitializeComponent();
            Dock = DockStyle.Fill;
        }

        public DockableTabPage(System.Windows.Forms.Control content, string text) {
            InitializeComponent();
            Text = text;
            Controls.Add(content);
        }

        private RootDockPanel dockPanel;
        public RootDockPanel RootPanel {
            get { return dockPanel; }
            set {
                dockPanel = value ?? throw new NullReferenceException();
            }
        }

        public DockableWindow toWindow() {
            return new DockableWindow(Text, Controls[0]) {
                DockPanel = RootPanel
            };
        }

        public Image Icon { get; set; }
    }
}
