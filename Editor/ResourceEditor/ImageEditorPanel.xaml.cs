using System;
using System.Collections.Generic;
using System.IO;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml.Serialization;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor.ResourceEditor {

    public interface IImageEditor : IDocumentPanel {
    }

    public partial class ImageEditorPanel : UserControl, IImageEditor, IStateControl {

        private List<object> selectedItems = new List<object>();
        public List<object> SelectedItems {
            get => selectedItems;
            set {
                // nothing, this editor doesn't support selection change
            }
        }

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
                selectedItems.Clear();
                imageView.Source = null;
                Title = new Title("");
                image = value;
                if (image != null) {
                    Title = new Title(image.UriSource.ToString().Substring(image.UriSource.ToString().LastIndexOfAny(new char[] { '\\', '/' }) + 1), image.UriSource.ToString());
                    imageView.Source = image;
                    //selectedItems.Add(image);
                }
            }
        }

        public ImageSource Icon { get; }
        public Control Control { get => this; }
        public Title Title { get; private set; }
        public bool NeedsSaving => false;

        public void SaveState(Stream stream) {
            XmlSerializer serializer = new XmlSerializer(typeof(string));
            serializer.Serialize(stream, Image?.UriSource.ToString());
        }

        public void RestoreState(Stream stream) {
            XmlSerializer serializer = new XmlSerializer(typeof(string));
            string uriPath = serializer.Deserialize(stream) as string;
            Uri uri = new Uri(uriPath);
            if (!File.Exists(uri.LocalPath))
                return; // TODO: error handling
            Load(uri.LocalPath);
        }

        public bool Save(string fileName = null) {
            return false;
        }

        public bool Load(string fileName) {
            var bitmapImage = new BitmapImage(new Uri(fileName));
            bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
            Image = bitmapImage;
            return true;
        }
    }
}
