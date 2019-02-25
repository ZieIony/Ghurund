using System;
using System.Drawing;
using System.Windows.Forms;
using Ghurund.Managed.Application;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed {
    public class RenderView : UserControl, IDisposable {

        Window window;

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
            Refresh();
        }

        private bool disposed = false;

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
            Renderer = new Renderer();
            Renderer.Init(window, resourceManager, resourceContext);
            Renderer.ClearColor = 0xff7f7f7f;
        }

        public void Uninit() {
            Renderer?.Dispose();
            Renderer = null;
            window?.Dispose();
            window = null;
            Camera?.Dispose();
            Camera = null;

            ParameterManager = null;
            Graphics = null;
        }

        public Bitmap GrabFrame() {
            Bitmap bitmap = new Bitmap(Width, Height);
            DrawToBitmap(bitmap, Bounds);
            return bitmap;
        }

        protected override void OnPaint(PaintEventArgs e) {
            base.OnPaint(e);
            if (IsInDesignMode(this)) {
                e.Graphics.Clear(Color.CornflowerBlue);
            } else if (Renderer != null) {
                Renderer.Render();
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
            if (Camera != null)
                Camera.SetScreenSize((uint)Width, (uint)Height);
            window.UpdateSize();
            Renderer.Resize((uint)Width, (uint)Height);
            window.UpdateParameters();
        }
    }
}
