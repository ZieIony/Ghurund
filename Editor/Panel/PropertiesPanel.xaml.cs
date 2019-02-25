using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Controls.Workspace;

namespace Ghurund.Editor {
    public interface IPropertiesPanel : IToolPanel {
        object SelectedObject { get; set; }
    }

    public partial class PropertiesPanel : UserControl, IPropertiesPanel {

        private List<object> selectedItems = new List<object>();
        public List<object> SelectedItems {
            get => selectedItems;
            set {
                selectedItems = value;
                if (selectedItems == null)
                    return;
                SelectedObject = selectedItems[selectedItems.Count - 1];
            }
        }

        public static readonly RoutedEvent SelectionChangedEvent = EventManager.RegisterRoutedEvent("SelectionChanged", RoutingStrategy.Bubble, typeof(RoutedSelectionChangedEventHandler), typeof(IPropertiesPanel));

        public event RoutedSelectionChangedEventHandler SelectionChanged {
            add { AddHandler(SelectionChangedEvent, value); }
            remove { RemoveHandler(SelectionChangedEvent, value); }
        }

        private bool disposed = false;

        public PropertiesPanel() {
            InitializeComponent();

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

        public ImageSource Icon { get; } = new BitmapImage(new Uri("pack://application:,,,/Resources/properties32.png", UriKind.Absolute));
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
