using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Resources;
using System.Xml;
using System.Xml.Serialization;
using Ghurund.Controls.Workspace;
using Ghurund.Managed;
using Ghurund.Managed.Core;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Graphics.Shader;
using Ghurund.Managed.Resource;
using Microsoft.Win32;
using Ninject;

namespace Ghurund.Editor.ResourceEditor {
    public interface IMaterialEditor: IDocumentPanel {
        Material Material { get; set; }
    }

    public enum SampleModel {
        Cube, Sphere, Plane, Custom
    }

    public partial class MaterialEditorPanel: UserControl, IMaterialEditor, IStateControl {

        private System.Collections.Generic.List<object> selectedItems = new System.Collections.Generic.List<object>();
        public System.Collections.Generic.List<object> SelectedItems {
            get => selectedItems;
            set {
                // nothing, this editor doesn't support selection change
            }
        }

        [Inject]
        public ResourceContext ResourceContext { get; set; }

        public SampleModel SampleModel { get; set; } = SampleModel.Cube;

        private Material material;
        public Material Material {
            get => material;
            set {
                if (material == value)
                    return;

                material?.Release();
                selectedItems.Clear();
                material = value;
                if (material != null) {
                    material.AddReference();
                    Title = new Title(material.ToString().Substring(material.ToString().LastIndexOfAny(new char[] { '\\', '/' }) + 1), material.ToString());
                    shaderCode.Text = material.Shader.SourceCode;

                    setupScene();

                    propertyGrid.AddParameters(material.Parameters, "Material");
                    selectedItems.Add(material);
                }
            }
        }

        public ImageSource Icon { get; }
        public Control Control { get => this; }
        public Title Title { get; private set; }
        public bool NeedsSaving => false;

        public MaterialEditorPanel() {
            InitializeComponent();

            EditorKernel.Inject(this);

            preview.Init(ResourceContext);

            cameraPicker.Items.Add(CameraMode.Default);
            cameraPicker.Items.Add(CameraMode.Side);
            cameraPicker.Items.Add(CameraMode.Front);
            cameraPicker.Items.Add(CameraMode.Top);
            cameraPicker.SelectedValue = CameraMode.Default;

            modelPicker.SelectedValue = SampleModel.Cube;

            Uri uri = new Uri("pack://application:,,,/Resources/languages/HLSL.xshd", UriKind.Absolute);
            StreamResourceInfo info = Application.GetResourceStream(uri);
            Stream xshd_stream = info.Stream;
            XmlTextReader xshd_reader = new XmlTextReader(xshd_stream);
            shaderCode.SyntaxHighlighting = ICSharpCode.AvalonEdit.Highlighting.Xshd.HighlightingLoader.Load(xshd_reader, ICSharpCode.AvalonEdit.Highlighting.HighlightingManager.Instance);
            xshd_reader.Close();
            xshd_stream.Close();
        }

        public bool Save(string fileName = null) {
            if (fileName == null && material.FileName == null) {
                SaveFileDialog saveFileDialog = new SaveFileDialog();
                var result = saveFileDialog.ShowDialog();
                if (!result.GetValueOrDefault(false))
                    return false;
                fileName = saveFileDialog.FileName;
            }
            return material.Save(ResourceContext, fileName) == Status.OK;
        }

        public bool Load(string fileName) {
            var material = new Material();
            if (Shader.Formats.Any(format => fileName.EndsWith(format.Extension))) {
                var shader = new Shader();
                if (shader.Load(ResourceContext, fileName) != Status.OK) {
                    if (fileName.EndsWith("shader")) {  // TODO: pass only if it's a compilation error
                        material.Release();
                        shader.Release();
                        return false;
                    }
                }
                material.Shader = shader;
                material.Valid = true;
                Material = material;
                material.Release();
                shader.Release();
            } else {
                if (material.Load(ResourceContext, fileName) != Status.OK) {
                    material.Release();
                    return false;
                }
                Material = material;
                material.Release();
            }
            return true;
        }

        public void SaveState(Stream stream) {
            XmlSerializer serializer = new XmlSerializer(typeof(string));
            serializer.Serialize(stream, material.FileName);
        }

        public void RestoreState(Stream stream) {
            XmlSerializer serializer = new XmlSerializer(typeof(string));
            string fileName = serializer.Deserialize(stream) as string;
            if (!File.Exists(fileName))
                return; // TODO: error handling
            Load(fileName);
        }

        #region IDisposable Support
        private bool disposedValue = false; // To detect redundant calls

        protected virtual void Dispose(bool disposing) {
            if (!disposedValue) {
                if (disposing) {
                    preview.Uninit();
                    if (Material != null)
                        Material.Release();
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
            if (material == null || modelPicker.SelectedValue == null)
                return;

            Scene scene = new Scene();
            Model model = null;
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
            model.Release();
            preview.Scene = scene;
            scene.Release();

            preview.ShowPlane = false;
        }

        private void ResetCamera_Click(object sender, RoutedEventArgs e) {
            preview.ResetCamera();
            preview.Invalidate();
        }

        private void Camera_SelectionChanged(object sender, SelectionChangedEventArgs e) {
            preview.CameraMode = ((CameraMode?)cameraPicker.SelectedValue) ?? CameraMode.Default;
            preview.Invalidate();
        }

        private void Build_Click(object sender, RoutedEventArgs e) {
            var parameters = new System.Collections.Generic.List<Parameter>(material.Parameters.Filter(p => p != null));
            foreach (Parameter p in parameters)
                p.AddReference();

            Shader shader = Material.Shader;
            shader.SourceCode = shaderCode.Text;
            string output = shader.Compile();
            if (output != null) {
                foreach (string line in output.Split('\n'))
                    Logger.Log(LogType.ERROR, line);
            }
            shader.Build(ResourceContext);
            Material.InitParameters(ResourceContext.ParameterManager);
            var parameters2 = Material.Parameters;
            foreach (Parameter p2 in parameters2) {
                if (p2 == null)
                    continue;
                foreach (Parameter p in parameters) {
                    if (p2.Name == p.Name && p2.Type == p.Type) {
                        p2.Value = p.Value;
                        break;
                    }
                }
            }
            foreach (Parameter p in parameters)
                p.Release();
            propertyGrid.Properties.Clear();
            propertyGrid.AddParameters(material.Parameters, "Material");
            preview.Invalidate();
        }

        private void ShowPlane_Click(object sender, RoutedEventArgs e) {
            preview.ShowPlane = showPlane.IsChecked.Value;
        }

        private void ShaderCode_MouseUp(object sender, System.Windows.Input.MouseButtonEventArgs e) {
            var line = shaderCode.Document.GetLineByOffset(shaderCode.CaretOffset);
            status.Text = "[" + line.LineNumber + ":" + (shaderCode.CaretOffset - line.Offset) + "]";
        }
    }
}
