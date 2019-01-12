using System.IO;
using System.Windows.Media.Imaging;
using Microsoft.WindowsAPICodePack.Shell;

namespace Ghurund.Editor {
    public class ResourceFile {

        public string Path { get; set; }
        public string Name { get; set; }
        public string Size => Length / 1024 + "kB";
        public long Length { get; set; }
        public string Modified { get; set; }

        public BitmapSource Thumbnail {
            get {
                if (Path == null || !File.Exists(Path))   // TODO: error handling
                    return null;
                ShellFile shellFile = ShellFile.FromFilePath(Path);
                return shellFile.Thumbnail.Bitmap.ToBitmapSource();
            }
        }

        public ResourceFile() { }

        public ResourceFile(string path) : this(new FileInfo(path)) {
        }

        public ResourceFile(FileInfo file) {
            Path = file.FullName;
            Name = file.Name;
            Length = file.Length;
            Modified = file.LastWriteTime.ToShortDateString();
        }
    }
}
