using System;
using System.Drawing;
using System.Threading.Tasks;
using System.Windows.Forms;
using Ghurund.Managed.Application;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed {
    public class RenderView: UserControl, IDisposable {

        private readonly uint FRAME_COUNT = 3;

        Window window;
        SwapChain swapChain;

        public Graphics.Graphics Graphics { get; private set; }

        public ParameterManager ParameterManager { get; private set; }

        public Renderer Renderer { get; private set; }

        private Camera camera;
        public Camera Camera {
            get => camera;
            set {
                value?.AddReference();
                if (Camera != null) {
                    camera.Release();
                    camera.PropertyChanged -= Camera_PropertyChanged;
                }
                camera = value;
                if (Camera != null) {
                    camera.SetScreenSize((uint)Width, (uint)Height);
                    camera.PropertyChanged += Camera_PropertyChanged;
                }
            }
        }

        private void Camera_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e) {
            Invalidate();
        }

        private bool disposed = false;

        public RenderView() {
            //SetStyle(ControlStyles.OptimizedDoubleBuffer, true);
            SetStyle(ControlStyles.UserPaint, true);
            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
        }

        ~RenderView() {
            Dispose(false);
        }

        public new void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected new virtual void Dispose(bool disposing) {
            if (disposed)
                return;

            Uninit();

            disposed = true;
        }

        public void Init(ResourceManager resourceManager, ResourceContext resourceContext) {
            Graphics = resourceContext.Graphics;
            ParameterManager = resourceContext.ParameterManager;

            window = new Window();
            window.Init(Handle);
            window.InitParameters(ParameterManager);
            swapChain = new SwapChain();
            swapChain.Init(Graphics, window, FRAME_COUNT);
            Renderer = new Renderer();
            Renderer.Init(resourceManager, resourceContext);
            Renderer.ClearColor = 0xff7f7f7f;
        }

        public void Uninit() {
            swapChain?.Dispose();
            swapChain = null;
            Renderer?.Dispose();
            Renderer = null;
            window?.Dispose();
            window = null;
            Camera?.Dispose();
            Camera = null;

            ParameterManager = null;
            Graphics = null;
        }

        protected override void OnPaint(PaintEventArgs e) {
            //base.OnPaint(e);
            if (IsInDesignMode(this)) {
                e.Graphics.Clear(System.Drawing.Color.CornflowerBlue);
            } else if (Renderer != null) {
                Renderer.Render(swapChain.GetFrame());
                swapChain.Present();
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
            UpdateSize();
        }

        protected void UpdateSize() {
            if (window == null)
                return;
            if (Camera != null)
                Camera.SetScreenSize((uint)Width, (uint)Height);
            window.UpdateSize();
            swapChain.Resize((uint)Width, (uint)Height);
            window.UpdateParameters();
        }
    }
}
