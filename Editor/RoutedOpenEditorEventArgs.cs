using System.Windows;

namespace Ghurund.Editor {
    public class RoutedEditorOpenedEventArgs : RoutedEventArgs {
        public object EditedResource { get; }

        public RoutedEditorOpenedEventArgs(object editedResource, RoutedEvent editorOpenedEvent) : base(editorOpenedEvent) {
            EditedResource = editedResource;
        }
    }

    public delegate void RoutedEditorOpenedEventHandler(object sender, RoutedEditorOpenedEventArgs e);
}