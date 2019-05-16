using System;
using System.Collections.Generic;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Xml.Serialization;
using Ghurund.Controls.Workspace;
using Ghurund.Managed.Audio;
using Ghurund.Managed.Resource;
using Ninject;

namespace Ghurund.Editor.ResourceEditor {

    public interface ISoundEditor: IDocumentPanel {
    }

    public partial class SoundEditorPanel: UserControl, IImageEditor, IStateControl {

        public List<object> SelectedItems {
            get => null;
            set {
                // nothing, this editor doesn't support selection change
            }
        }

        public event RoutedSelectionChangedEventHandler SelectionChanged;

        [Inject]
        public ResourceManager ResourceManager { get; set; }

        [Inject]
        public ResourceContext ResourceContext { get; set; }

        private bool disposed = false;

        public SoundEditorPanel() {
            InitializeComponent();

            EditorKernel.Inject(this);
        }

        ~SoundEditorPanel() {
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

        private Sound sound;

        public Sound Sound {
            get => sound;
            set {
                sound = value;
                Title = new Title(sound.FileName.Substring(sound.FileName.LastIndexOfAny(new char[] { '\\', '/' }) + 1), sound.FileName);
            }
        }

        public ImageSource Icon { get; }
        public Control Control { get => this; }
        public Title Title { get; private set; }
        public bool NeedsSaving => false;

        public void SaveState(Stream stream) {
            XmlSerializer serializer = new XmlSerializer(typeof(string));
            serializer.Serialize(stream, sound?.FileName);
        }

        public void RestoreState(Stream stream) {
            XmlSerializer serializer = new XmlSerializer(typeof(string));
            string fileName = serializer.Deserialize(stream) as string;
            Uri uri = new Uri(fileName);
            if (!File.Exists(fileName))
                return; // TODO: error handling
            Load(fileName);
        }

        public bool Save(string fileName = null) {
            return false;
        }

        public bool Load(string fileName) {
            Sound sound = new Sound();
            sound.Load(ResourceManager, ResourceContext, fileName);
            Sound = sound;
            return true;
        }

        private void Play_Click(object sender, RoutedEventArgs e) {
            sound.Play();
        }

        private void Pause_Click(object sender, RoutedEventArgs e) {
            sound.Pause();
        }

        private void Stop_Click(object sender, RoutedEventArgs e) {
            sound.Stop();
        }
    }
}
