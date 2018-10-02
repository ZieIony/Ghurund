using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor.ResourceEditor {

    public interface IImageEditor : IDockableControl {
    }

    public partial class ImageEditorPanel : UserControl, IImageEditor, IStateControl {

        public ImageEditorPanel() {
            InitializeComponent();
        }

        private BitmapImage image;
        public BitmapImage Image {
            get => image;
            set {
                image = value;
                imageView.Source = image;
            }
        }

        public ImageSource Icon { get; }
        public Control Control { get => this; }
        public string Title { get => Image != null ? Image.UriSource.ToString() : ""; }

        public object Save() {
            return Image?.UriSource.ToString();
        }

        public void Restore(object state) {
            if (state != null) {
                string uri = state as string;
                Image = new BitmapImage() {
                    CacheOption = BitmapCacheOption.OnLoad,
                    UriSource = new System.Uri(uri)
                };
            }
        }
    }
}
