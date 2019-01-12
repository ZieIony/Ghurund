using System;
using System.ComponentModel;
using System.IO;
using System.Runtime.CompilerServices;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Media.Imaging;
using Microsoft.WindowsAPICodePack.Shell;

namespace Ghurund.Editor {
    public class ResourceFile : INotifyPropertyChanged {

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
            get => thumbnail; private set {
                thumbnail = value;
                NotifyPropertyChanged();
            }
        }

        public ResourceFile(string path) : this(new FileInfo(path)) {
        }

        public ResourceFile(FileInfo file) {
            Path = file.FullName;
            Name = file.Name;
            Exists = file.Exists;
            if (file.Exists) {
                Length = file.Length;
                Modified = file.LastWriteTime.ToShortDateString();

                loadThumbnail();
            }
        }

        private async void loadThumbnail() {
            await Application.Current.Dispatcher.InvokeAsync(() => {
                if (Path == null || !File.Exists(Path)) // TODO: error handling
                    Thumbnail = null;
                ShellFile shellFile = ShellFile.FromFilePath(Path);
                Thumbnail = shellFile.Thumbnail.BitmapSource;
            });
        }
    }
}
