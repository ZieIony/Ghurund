using System.Windows.Forms;
using Ghurund.Managed;
using Ghurund.Managed.Graphics;

namespace Ghurund.Editor {
    public class SurfaceView : UserControl {
        Window window;
        Graphics graphics;
        Renderer renderer;

        public SurfaceView() {
            if (!IsInDesignMode(this)) {
                window = new Window();
                window.init(Handle);
                graphics = new Graphics();
                graphics.init();
                renderer = new Renderer();
                renderer.init(graphics, window);
            }
        }

        ~SurfaceView() {
            if (!IsInDesignMode(this))
                window.uninit();
        }

        protected override void OnPaint(PaintEventArgs e) {
            base.OnPaint(e);
            if (IsInDesignMode(this)) {
                e.Graphics.Clear(System.Drawing.Color.CornflowerBlue);
            } else {
                renderer.startFrame();
                renderer.finishFrame();
            }
        }

        public bool IsInDesignMode(Control control) {
            return ResolveDesignMode(control);
        }

        private bool ResolveDesignMode(Control control) {
            System.Reflection.PropertyInfo designModeProperty = control.GetType().GetProperty(
                "DesignMode",
                System.Reflection.BindingFlags.Instance
                | System.Reflection.BindingFlags.NonPublic);

            bool designMode = (bool)designModeProperty.GetValue(control, null);

            if (control.Parent != null)
                designMode |= ResolveDesignMode(control.Parent);

            return designMode;
        }
    }
}
