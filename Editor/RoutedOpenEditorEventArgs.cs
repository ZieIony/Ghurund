using System.Windows;

namespace Ghurund.Editor {
    public class RoutedEditorOpenedEventArgs : RoutedEventArgs {
        public ResourceFile EditedResource { get; }

        public RoutedEditorOpenedEventArgs(ResourceFile editedResource, RoutedEvent editorOpenedEvent) : base(editorOpenedEvent) {
            EditedResource = editedResource;
        }
    }

    public delegate void RoutedEditorOpenedEventHandler(object sender, RoutedEditorOpenedEventArgs e);
}