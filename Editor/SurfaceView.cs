using System.Windows.Forms;
using Ghurund.Managed;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ninject;

namespace Ghurund.Editor {
    public class SurfaceView : UserControl {
        Window window;

        [Inject]
        public Graphics Graphics { get; set; }

        Renderer renderer;
        LevelManager levelManager;
        Level level;
        Camera camera;

        [Inject]
        public ParameterManager ParameterManager { get; set; }

        public SurfaceView() {
            if (!IsInDesignMode(this)) {
                EditorKernel.Instance.Inject(this);

                camera = new Camera();
                camera.initParameters(ParameterManager);
                level = new Level {
                    Camera = camera
                };
                levelManager = new LevelManager {
                    Level = level
                };
                window = new Window();
                window.init(Handle);
                renderer = new Renderer();
                renderer.init(Graphics, window);
            }
        }

        ~SurfaceView() {
            if (!IsInDesignMode(this))
                window.uninit();
        }

        private Scene scene;
        public Scene Scene {
            get => scene;
            set {
                scene = value;
                level.Scene = scene;
            }
        }

        protected override void OnPaint(PaintEventArgs e) {
            base.OnPaint(e);
            if (IsInDesignMode(this)) {
                e.Graphics.Clear(System.Drawing.Color.CornflowerBlue);
            } else {
                CommandList commandList = renderer.startFrame();
                levelManager.draw(commandList, ParameterManager);
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
