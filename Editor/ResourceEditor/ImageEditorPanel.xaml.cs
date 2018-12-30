using System;
using System.IO;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor.ResourceEditor {

    public interface IImageEditor : IDockableControl {
    }

    public partial class ImageEditorPanel : UserControl, IImageEditor, IStateControl {

        private bool disposed = false;

        public ImageEditorPanel() {
            InitializeComponent();
        }

        ~ImageEditorPanel() {
            Dispose(false);
        }

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing) {
            if (disposed)
                return;

            disposed = true;
        }

        private BitmapImage image;
        public BitmapImage Image {
            get => image;
            set {
                image = value;
                Title = new Title(image.UriSource.ToString().Substring(image.UriSource.ToString().LastIndexOfAny(new char[] { '\\', '/' }) + 1), image.UriSource.ToString());
                imageView.Source = image;
            }
        }

        public ImageSource Icon { get; }
        public Control Control { get => this; }
        public Title Title { get; private set; }

        public object Save() {
            return Image?.UriSource.ToString();
        }

        public void Restore(object state) {
            if (state != null) {
                string uri = state as string;
                if (!File.Exists(uri))
                    return; // TODO: error handling
                var bitmapImage = new BitmapImage(new Uri(uri));
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                Image = bitmapImage;
            }
        }
    }
}
