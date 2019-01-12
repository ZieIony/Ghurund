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
    public class RoutedFileOpenedEventArgs : RoutedEventArgs {
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
            IDockableControl panel = null;

            if (path.EndsWith("jpg") || path.EndsWith("jpeg") || path.EndsWith("png")) {
                BitmapImage image = new BitmapImage(new Uri(path));
                panel = new ImageEditorPanel {
                    Image = image
                };
                openPanel(this, panel);
            } else if (path.EndsWith("scene")) {
                var scene = new Scene();
                if (Status.OK == scene.Load(ResourceManager, ResourceContext, path)) {
                    panel = new SceneEditorPanel {
                        Scene = scene
                    };
                    SceneExplorer.Scene = scene;
                    openPanel(this, panel);
                } else {
                    MessageBox.Show(this, "There was an error while reading the file. Please make sure that the file is correct, all dependencies are available and its format matches the extension. More information can be found in the logs.", "Error while reading the file", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }
            } else if (path.EndsWith("project")) {
                closeProject();
                openProject(path);
            } else if (path.EndsWith("hlsl")) {
                var material = new Material();
                var shader = new Shader();
                if (Status.OK == shader.Load(ResourceManager, ResourceContext, path)) {
                    material.Shader = shader;
                    material.Valid = true;
                    panel = new MaterialEditorPanel() {
                        Material = material
                    };
                    openPanel(this, panel);
                } else {
                    MessageBox.Show(this, "There was an error while reading the file. Please make sure that the file is correct, all dependencies are available and its format matches the extension. More information can be found in the logs.", "Error while reading the file", MessageBoxButton.OK, MessageBoxImage.Error);
                    return;
                }
            } else {
                MessageBox.Show(this, "GhurundEngine is unable to open files of that type.", "Unknown format", MessageBoxButton.OK, MessageBoxImage.Information);
                return;
            }

            Settings.AddRecentFile(path);
        }
    }
}
