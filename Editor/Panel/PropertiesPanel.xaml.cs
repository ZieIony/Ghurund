using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;
using Ghurund.Editor.Property;

namespace Ghurund.Editor {
    public interface IPropertiesPanel : IToolPanel {
        object SelectedObject { get; set; }
    }

    public partial class PropertiesPanel : UserControl, IPropertiesPanel {

        private readonly List<object> selectedItems = new List<object>();
        public List<object> SelectedItems {
            get => selectedItems;
            set {
                selectedItems.Clear();
                selectedItems.AddRange(value);
                if (selectedItems.Count == 0) {
                    SelectedObject = null;
                } else {
                    SelectedObject = selectedItems[0];
                }
            }
        }

        private bool disposed = false;

        public PropertiesPanel() {
            InitializeComponent();

            propertyGrid.PropertyEditorFactory = new PropertyEditorFactory();

            hint.Visibility = Visibility.Visible;
            content.Visibility = Visibility.Collapsed;
        }

        ~PropertiesPanel() {
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

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/icons/properties32.png", UriKind.Absolute));
        public Control Control { get => this; }
        public Title Title { get; } = new Title("Properties");
        public object SelectedObject {
            get => propertyGrid.SelectedObject;
            set {
                if (propertyGrid.SelectedObject == value)
                    return;

                propertyGrid.SelectedObject = value;
                if (value != null) {
                    hint.Visibility = Visibility.Collapsed;
                    content.Visibility = Visibility.Visible;
                } else {
                    hint.Visibility = Visibility.Visible;
                    content.Visibility = Visibility.Collapsed;
                }
            }
        }
    }
}
