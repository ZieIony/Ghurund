using System;
using System.Windows.Forms;
using Ghurund.Managed.Application;
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

        public Camera Camera { get; }

        [Inject]
        public ParameterManager ParameterManager { get; set; }

        public SurfaceView() {
            if (!IsInDesignMode(this)) {
                EditorKernel.Instance.Inject(this);

                Camera = new Camera();
                Camera.InitParameters(ParameterManager);
                level = new Level {
                    Camera = Camera
                };
                levelManager = new LevelManager {
                    Level = level
                };
                window = new Window();
                window.Init(Handle);
                window.InitParameters(ParameterManager);
                renderer = new Renderer();
                renderer.Init(Graphics, window);
            }
        }

        ~SurfaceView() {
            if (!IsInDesignMode(this))
                window.Uninit();
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
                CommandList commandList = renderer.StartFrame();
                levelManager.draw(commandList, ParameterManager);
                renderer.FinishFrame();
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

        protected override void OnSizeChanged(EventArgs e) {
            base.OnSizeChanged(e);
            Camera.SetScreenSize((uint)Width, (uint)Height);
            window.UpdateSize();
            renderer.Resize((uint)Width, (uint)Height);
            window.UpdateParameters();
        }
    }
}
