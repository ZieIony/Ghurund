using System;
using System.Windows;
using System.Windows.Media.Imaging;
using Ghurund.Controls.PropertyGrid;
using Ghurund.Controls.Workspace;
using Ghurund.Editor.ResourceEditor;
using Ghurund.Managed;
using Ghurund.Managed.Audio;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Graphics.Shader;
using Ghurund.Managed.Resource;
using Ghurund.Managed.Script;
using Microsoft.Win32;

namespace Ghurund.Editor {
    public class RoutedFileOpenedEventArgs: RoutedEventArgs {
        public string Path { get; }

        public RoutedFileOpenedEventArgs(string path, RoutedEvent fileOpenedEvent) : base(fileOpenedEvent) {
            Path = path;
        }
    }

    public delegate void RoutedFileOpenedEventHandler(object sender, RoutedFileOpenedEventArgs e);

    public partial class MainWindow {

        public static readonly RoutedEvent FileOpenedEvent = EventManager.RegisterRoutedEvent("FileOpened", RoutingStrategy.Bubble, typeof(RoutedFileOpenedEventHandler), typeof(MainWindow));

        public object Scripts { get; private set; }

        public event RoutedFileOpenedEventHandler FileOpened {
            add { AddHandler(FileOpenedEvent, value); }
            remove { RemoveHandler(FileOpenedEvent, value); }
        }

        private void fileOpenedHandler(object sender, RoutedFileOpenedEventArgs e) {
            openFile(e.Path);
        }

        private void valueEditedHandler(object sender, RoutedValueEditedEventEventArgs e) {
            editResource(e.Value);
        }

        private void openFile(bool defaultToProject = false) {
            OpenFileDialog openFileDialog = new OpenFileDialog {
                Filter = "All (*.*)|*.*|Projects (*.project)|*.project|" 
                + makeFilter("Images", Managed.Graphics.Texture.Image.Formats)
                + "|" + makeFilter("Sounds", Sound.Formats)
                + "|" + makeFilter("Scenes", Scene.Formats)
                + "|" + makeFilter("Shaders", Shader.Formats),
                FilterIndex = defaultToProject ? 1 : 0
            };
            if (openFileDialog.ShowDialog() == true)
                openFile(openFileDialog.FileName);
        }

        private void editResource(Value value) {
            IDocumentPanel editorPanel = null;
            Resource resource = value.Getter() as Resource;

            if (value.Type == typeof(Managed.Graphics.Texture.Image)) {
                /*editorPanel = new ImageEditorPanel() {
                    Image = resource as Managed.Graphics.Texture.Image
                };*/
            } else if (value.Type == typeof(Material)) {
                editorPanel = new MaterialEditorPanel() {
                    Material = resource as Material
                };
            } else if (value.Type == typeof(Sound)) {
                editorPanel = new SoundEditorPanel() {
                    Sound = resource as Sound
                };
            } else if (value.Type == typeof(Script)) {
                if (resource == null)
                    resource = Managed.Script.Scripts.MakeEmpty(value.Owner as Entity);
                editorPanel = new ScriptEditorPanel() {
                    Script = resource as Script
                };
                value.Setter(resource);
            } else {
                MessageBox.Show(this, "GhurundEngine is unable to open files of that type.", "Unknown format", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }

            openPanel(this, editorPanel);

            if (resource.FileName != null)
                Settings.AddRecentFile(resource.FileName);
        }

        private void openFile(string path) {
            IDocumentPanel editorPanel;

            if (path.EndsWith("jpg") || path.EndsWith("jpeg") || path.EndsWith("png")) {
                editorPanel = new ImageEditorPanel();
            } else if (path.EndsWith("scene")) {
                editorPanel = new SceneEditorPanel();
            } else if (path.EndsWith("hlsl") || path.EndsWith("material")) {
                editorPanel = new MaterialEditorPanel();
            } else if (path.EndsWith("wav")) {
                editorPanel = new SoundEditorPanel();
            } else if (path.EndsWith("script")) {
                editorPanel = new ScriptEditorPanel();
            } else if (path.EndsWith("project")) {
                closeProject();
                openProject(path);
                Settings.AddRecentProject(path);
                return;
            } else {
                MessageBox.Show(this, "GhurundEngine is unable to open files of that type.", "Unknown format", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }

            if (!editorPanel.Load(path)) {
                MessageBox.Show(this, "There was an error while reading the file. Please make sure that the file is correct, all dependencies are available and its format matches the extension. More information can be found in the logs.", "Error while reading the file", MessageBoxButton.OK, MessageBoxImage.Error);
                return;
            }
            openPanel(this, editorPanel);

            Settings.AddRecentFile(path);
        }
    }
}
