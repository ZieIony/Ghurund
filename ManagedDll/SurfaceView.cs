using System;
using System.Windows.Forms;
using Ghurund.Managed.Application;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;

namespace Ghurund.Managed {
    public class SurfaceView : UserControl, IDisposable {
        Window window;

        public Graphics.Graphics Graphics { get; private set; }

        public ParameterManager ParameterManager { get; private set; }

        public Renderer Renderer { get; private set; }

        LevelManager levelManager;
        Level level;
        Camera defaultCamera;

        private Camera camera;
        public Camera Camera {
            get => camera;
            set {
                camera = value ?? defaultCamera;
            }
        }

        private Scene scene;

        public Scene Scene {
            get => scene;
            set {
                scene = value;
                level.Scene = scene;
            }
        }

        public void Init(Graphics.Graphics graphics, ParameterManager parameterManager) {
            Graphics = graphics;
            ParameterManager = parameterManager;

            defaultCamera = new Camera();
            defaultCamera.InitParameters(ParameterManager);
            Camera = defaultCamera;
            level = new Level {
                Camera = Camera
            };
            levelManager = new LevelManager {
                Level = level
            };
            window = new Window();
            window.Init(Handle);
            window.InitParameters(ParameterManager);
            Renderer = new Renderer();
            Renderer.Init(Graphics, window);
        }

        public void Uninit() {
            scene = null;

            Renderer.Dispose();
            Renderer = null;
            window.Dispose();
            window = null;
            levelManager.Dispose();
            levelManager = null;
            level.Dispose();
            level = null;
            Camera.Dispose();
            Camera = null;

            ParameterManager = null;
            Graphics = null;
        }

        protected override void OnPaint(PaintEventArgs e) {
            base.OnPaint(e);
            if (IsInDesignMode(this)) {
                e.Graphics.Clear(System.Drawing.Color.CornflowerBlue);
            } else if (Renderer != null) {
                CommandList commandList = Renderer.StartFrame();
                levelManager.Draw(Renderer, ParameterManager);
                Renderer.FinishFrame();
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
            if (window == null)
                return;
            Camera.SetScreenSize((uint)Width, (uint)Height);
            window.UpdateSize();
            Renderer.Resize((uint)Width, (uint)Height);
            window.UpdateParameters();
        }
    }
}
