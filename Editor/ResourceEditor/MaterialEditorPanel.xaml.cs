using System;
using System.IO;
using System.Windows.Controls;
using System.Windows.Documents;
using System.Windows.Media;
using Ghurund.Controls.Workspace;
using Ghurund.Managed;
using Ghurund.Managed.Core;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Graphics.Shader;
using Ghurund.Managed.Resource;
using Ninject;

namespace Ghurund.Editor.ResourceEditor {
    public interface IMaterialEditor : IDockableControl {
        Material Material { get; set; }
    }

    public enum SampleModel {
        Cube, Sphere, Plane, Custom
    }

    public partial class MaterialEditorPanel : UserControl, IMaterialEditor, IStateControl {

        [Inject]
        public ResourceManager ResourceManager { get; set; }

        [Inject]
        public ResourceContext ResourceContext { get; set; }

        public SampleModel SampleModel { get; set; } = SampleModel.Cube;

        private Material material;
        public Material Material {
            get => material;
            set {
                material = value;
                Title = new Title(material.FileName.Substring(material.FileName.LastIndexOfAny(new char[] { '\\', '/' }) + 1), material.FileName);
                shaderCode.Text = material.Shader.SourceCode;

                setupScene();
            }
        }

        public ImageSource Icon { get; }
        public Control Control { get => this; }
        public Title Title { get; private set; }

        public MaterialEditorPanel() {
            InitializeComponent();

            EditorKernel.Instance.Inject(this);

            cameraPicker.Items.Add(CameraMode.Default);
            cameraPicker.Items.Add(CameraMode.Side);
            cameraPicker.Items.Add(CameraMode.Front);
            cameraPicker.Items.Add(CameraMode.Top);
            cameraPicker.SelectedValue = CameraMode.Default;

            preview.Init(ResourceManager, ResourceContext);
            preview.Renderer.ClearColor = 0xff7f7f7f;

            modelPicker.SelectedValue = SampleModel.Cube;
        }

        public object Save() {
            return material.FileName;
        }

        public void Restore(object state) {
            if (state != null) {
                string uri = state as string;
                if (!File.Exists(uri))
                    return; // TODO: error handling
                /*var bitmapImage = new BitmapImage(new Uri(uri));
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                Image = bitmapImage;*/
            }
        }

        #region IDisposable Support
        private bool disposedValue = false; // To detect redundant calls

        protected virtual void Dispose(bool disposing) {
            if (!disposedValue) {
                if (disposing) {
                    preview.Uninit();
                    if (Material != null)
                        Material.Dispose();
                }

                // TODO: free unmanaged resources (unmanaged objects) and override a finalizer below.
                // TODO: set large fields to null.

                disposedValue = true;
            }
        }

        // TODO: override a finalizer only if Dispose(bool disposing) above has code to free unmanaged resources.
        // ~MaterialEditorPanel() {
        //   // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
        //   Dispose(false);
        // }

        // This code added to correctly implement the disposable pattern.
        public void Dispose() {
            // Do not change this code. Put cleanup code in Dispose(bool disposing) above.
            Dispose(true);
            // TODO: uncomment the following line if the finalizer is overridden above.
            // GC.SuppressFinalize(this);
        }
        #endregion

        private void Model_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            if (material != null)
                setupScene();
        }

        private void setupScene() {
            Scene scene = new Scene();
            TransformedEntity model = null;
            switch (modelPicker.SelectedValue) {
                case SampleModel.Sphere:
                    model = Models.MakeSphere(ResourceContext, material);
                    break;
                case SampleModel.Plane:
                    model = Models.MakePlane(ResourceContext, material);
                    break;
                case SampleModel.Custom:
                    break;
                default:
                    model = Models.MakeCube(ResourceContext, material);
                    break;
            }
            model.Scale = new Float3(50, 50, 50);
            scene.Entities.Add(model);
            model.Dispose();
            model = null;
            preview.Scene = scene;
            scene.Dispose();
            scene = null;

            preview.Refresh();
        }

        private void ShaderCode_GotFocus(object sender, System.Windows.RoutedEventArgs e) {
        }

        private void ResetCamera_Click(object sender, System.Windows.RoutedEventArgs e) {
            preview.ResetCamera();
            preview.Refresh();
        }

        private void Camera_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            preview.CameraMode = ((CameraMode?)cameraPicker.SelectedValue) ?? CameraMode.Default;
            preview.Refresh();
        }

        private void Build_Click(object sender, System.Windows.RoutedEventArgs e) {
            Shader shader = Material.Shader;
            shader.SourceCode = shaderCode.Text;
            string output = shader.Compile();
            if (output != null) {
                foreach (string line in output.Split('\n'))
                    Logger.Log(line);
            }
            shader.Build(ResourceContext);
            shader.Dispose();
            preview.Refresh();
        }
    }
}
