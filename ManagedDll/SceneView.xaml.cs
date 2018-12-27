using System;
using System.Windows;
using System.Windows.Controls;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;

namespace Ghurund.Managed {
    public enum NavigationMode {
        Orbit, Pan, Zoom, Rotate
    }

    public enum CameraMode {
        Top, Side, Front, Default
    }

    public partial class SceneView : UserControl, IDisposable {

        private Point prevPos;
        private bool pressed = false;
        private Material invalidMaterial;

        public NavigationMode NavigationMode { get; set; }

        private CameraMode cameraMode;
        public CameraMode CameraMode {
            get => cameraMode;
            set {
                cameraMode = value;
                switch (cameraMode) {
                    case CameraMode.Default:
                        //Camera.
                        break;
                    case CameraMode.Front:
                        break;
                    case CameraMode.Side:
                        break;
                    case CameraMode.Top:
                        break;
                }
            }
        }

        public Scene Scene { get => surfaceView.Scene; set => surfaceView.Scene = value; }

        public Renderer Renderer { get => surfaceView.Renderer; }

        public Camera Camera { get => surfaceView.Camera; set => surfaceView.Camera = value; }

        public SceneView() {
            InitializeComponent();
        }

        private bool disposed = false;

        ~SceneView() {
            Dispose(false);
        }

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing) {
            if (disposed)
                return;

            Uninit();

            disposed = true;
        }

        public void Init(Resource.ResourceManager resourceManager, Resource.ResourceContext resourceContext) {
            invalidMaterial = Materials.MakeInvalid(resourceManager, resourceContext);

            surfaceView.Init(resourceContext.Graphics, resourceContext.ParameterManager);
            surfaceView.Renderer.InvalidMaterial = invalidMaterial;
        }

        public void Uninit() {
            surfaceView.Uninit();

            invalidMaterial?.Dispose();
            invalidMaterial = null;
        }

        public void Refresh() {
            surfaceView.Refresh();
        }

        private void surfaceView_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e) {
            prevPos = new Point(e.X, e.Y);
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
                pressed = true;
        }

        private void surfaceView_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e) {
            if (pressed) {
                var pos = new Point(e.X, e.Y);
                var dx = pos.X - prevPos.X;
                var dy = -(pos.Y - prevPos.Y);
                if (NavigationMode == NavigationMode.Orbit) {
                    surfaceView.Camera.Orbit((float)(dx / 5 * Math.PI / 180), (float)(dy / 5 * Math.PI / 180));
                } else if (NavigationMode == NavigationMode.Pan) {
                    surfaceView.Camera.Pan((float)dx, (float)-dy);
                } else if (NavigationMode == NavigationMode.Zoom) {
                    surfaceView.Camera.Zoom((float)dy);
                } else {
                    surfaceView.Camera.Rotate((float)(dx / 5 * Math.PI / 180), (float)(dy / 5 * Math.PI / 180));
                }
                surfaceView.Refresh();
                prevPos = pos;
            }
        }

        private void surfaceView_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e) {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
                pressed = false;
        }
    }
}
