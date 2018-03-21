using System.Windows.Forms;
using Ghurund.Editor.Utils;
using Ghurund.Managed;
using Ghurund.Managed.Graphics;

namespace Ghurund.Editor {
    public partial class SurfaceView : UserControl {
        Window window;
        Graphics graphics;
        Renderer renderer;

        public SurfaceView() {
            InitializeComponent();
        }

        ~SurfaceView() {
            if (!this.IsInDesignMode())
                window.uninit();
        }

        private void SurfaceView_Paint(object sender, PaintEventArgs e) {
            if (this.IsInDesignMode()) {
                e.Graphics.Clear(System.Drawing.Color.CornflowerBlue);
            } else {
                renderer.startFrame();
                renderer.finishFrame();
            }
        }

        private void SurfaceView_Load(object sender, System.EventArgs e) {
            if (!this.IsInDesignMode()) {
                window = new Window();
                window.init(Handle);
                graphics = new Graphics();
                graphics.init();
                renderer = new Renderer();
                renderer.init(graphics, window);
            }
        }
    }
}
