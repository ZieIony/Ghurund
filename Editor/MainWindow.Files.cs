using System;
using System.Windows;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ghurund.Editor.ResourceEditor;
using Ghurund.Managed;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Graphics.Shader;
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

        public event RoutedFileOpenedEventHandler FileOpened {
            add { AddHandler(FileOpenedEvent, value); }
            remove { RemoveHandler(FileOpenedEvent, value); }
        }

        private void fileOpenedHandler(object sender, RoutedFileOpenedEventArgs e) {
            openFile(e.Path);
        }

        private void openFile(bool defaultToProject = false) {
            OpenFileDialog openFileDialog = new OpenFileDialog {
                Filter = "All (*.*)|*.*|Projects (*.project)|*.project|" + makeFilter("Images", Managed.Graphics.Texture.Image.Formats) + "|" + makeFilter("Scenes", Scene.Formats) + "|" + makeFilter("Shaders", Shader.Formats),
                FilterIndex = defaultToProject ? 1 : 0
            };
            if (openFileDialog.ShowDialog() == true)
                openFile(openFileDialog.FileName);
        }

        private void openFile(string path) {
            IDocumentPanel editorPanel = null;

            if (path.EndsWith("jpg") || path.EndsWith("jpeg") || path.EndsWith("png")) {
                editorPanel = new ImageEditorPanel();
            } else if (path.EndsWith("scene")) {
                editorPanel = new SceneEditorPanel();
            } else if (path.EndsWith("hlsl") || path.EndsWith("material")) {
                editorPanel = new MaterialEditorPanel();
            } else if (path.EndsWith("script")) {
                //editorPanel = new ScriptEditorPanel();
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
