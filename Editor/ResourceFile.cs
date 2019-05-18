using System;
using System.ComponentModel;
using System.Drawing;
using System.IO;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media.Imaging;
using Ghurund.Managed;
using Ghurund.Managed.Editor;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Graphics.Mesh;
using Ghurund.Managed.Resource;
using Microsoft.WindowsAPICodePack.Shell;

namespace Ghurund.Editor {
    public class ResourceFile: INotifyPropertyChanged {

        public event PropertyChangedEventHandler PropertyChanged;

        // This method is called by the Set accessor of each property.
        // The CallerMemberName attribute that is applied to the optional propertyName
        // parameter causes the property name of the caller to be substituted as an argument.
        private void NotifyPropertyChanged([CallerMemberName] string propertyName = "") {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs(propertyName));
        }

        public string Path { get; set; }
        public string Name { get; set; }
        public string Size => Length / 1024 + "kB";
        public long Length { get; set; }
        public string Modified { get; set; }
        public bool Exists { get; set; }

        private BitmapSource thumbnail;
        public BitmapSource Thumbnail {
            get => thumbnail;
            set {
                thumbnail = value;
                NotifyPropertyChanged();
            }
        }

        public ResourceFile(string path, ResourceManager resourceManager, ResourceContext resourceContext, ThumbnailRenderer thumbnailRenderer)
            : this(new FileInfo(path), resourceManager, resourceContext, thumbnailRenderer) {
        }

        public ResourceFile(FileInfo file, ResourceManager resourceManager, ResourceContext resourceContext, ThumbnailRenderer thumbnailRenderer) {
            Path = file.FullName;
            Name = file.Name;
            Exists = file.Exists;
            if (file.Exists) {
                Length = file.Length;
                Modified = file.LastWriteTime.ToShortDateString();

                string thumbnailPath = file.FullName + ".thumbnail";
                if (File.Exists(thumbnailPath) && File.GetLastWriteTimeUtc(thumbnailPath).CompareTo(File.GetLastWriteTimeUtc(Path)) > 0) {
                    Thumbnail = new BitmapImage(new Uri(thumbnailPath));
                } else {
                    if (Name.EndsWith(".scene")) {
                        generateThumbnailEntity(new Scene(), resourceManager, resourceContext, thumbnailRenderer, thumbnailPath);
                    } else if (Name.EndsWith(".model")) {
                        generateThumbnailEntity(new Model(), resourceManager, resourceContext, thumbnailRenderer, thumbnailPath);
                    } else if (Name.EndsWith(".mesh")) {
                        generateThumbnailMesh(resourceManager, resourceContext, thumbnailRenderer, thumbnailPath);
                    } else {
                        loadThumbnail();
                    }
                }
            }
        }

        private async void generateThumbnailEntity(Entity entity, ResourceManager resourceManager, ResourceContext resourceContext, ThumbnailRenderer thumbnailRenderer, string thumbnailPath) {
            await Application.Current.Dispatcher.InvokeAsync(() => {
                if (Path == null || !File.Exists(Path)) { // TODO: error handling
                    Thumbnail = null;
                    return;
                }

                if (entity.Load(resourceManager, resourceContext, Path) != Status.OK) {
                    Thumbnail = null;
                    return;
                }

                Thumbnail = thumbnailRenderer.Render(entity).ToBitmap();

                BitmapEncoder encoder = new PngBitmapEncoder();
                encoder.Frames.Add(BitmapFrame.Create(Thumbnail));

                using (var fileStream = new FileStream(thumbnailPath, FileMode.Create)) {
                    encoder.Save(fileStream);
                }
            });
        }

        private async void generateThumbnailMesh(ResourceManager resourceManager, ResourceContext resourceContext, ThumbnailRenderer thumbnailRenderer, string thumbnailPath) {
            await Application.Current.Dispatcher.InvokeAsync(() => {
                if (Path == null || !File.Exists(Path)) { // TODO: error handling
                    Thumbnail = null;
                    return;
                }

                Mesh mesh = new Mesh();
                if (mesh.Load(resourceManager, resourceContext, Path) != Status.OK) {
                    mesh.Release();
                    Thumbnail = null;
                    return;
                }

                Thumbnail = thumbnailRenderer.Render(mesh).ToBitmap();

                BitmapEncoder encoder = new PngBitmapEncoder();
                encoder.Frames.Add(BitmapFrame.Create(Thumbnail));

                using (var fileStream = new FileStream(thumbnailPath, FileMode.Create)) {
                    encoder.Save(fileStream);
                }
            });
        }

        private async void loadThumbnail() {
            await Application.Current.Dispatcher.InvokeAsync(() => {
                if (Path == null || !File.Exists(Path)) { // TODO: error handling
                    Thumbnail = null;
                    return;
                }

                ShellFile shellFile = ShellFile.FromFilePath(Path);
                Thumbnail = shellFile.Thumbnail.BitmapSource;
            });
        }
    }
}
