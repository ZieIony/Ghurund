using System.ComponentModel;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;

namespace Ghurund.Controls.PropertyGrid {

    public class PropertyGrid : Control {

        public ObservableNotifyCollection<Property> Properties { get; } = new ObservableNotifyCollection<Property>();

        private ICollectionView view;


        public string Filter {
            get { return (string)GetValue(FilterProperty); }
            set { SetValue(FilterProperty, value); }
        }

        public static readonly DependencyProperty FilterProperty =
            DependencyProperty.Register("Filter", typeof(string), typeof(PropertyGrid), new PropertyMetadata(null));


        private object selectedObject;
        public object SelectedObject {
            get {
                return selectedObject;
            }
            set {
                selectedObject = value;
                Properties.Clear();
                if (selectedObject != null) {
                    var properties = selectedObject.GetType().GetProperties();
                    foreach (PropertyInfo info in properties) {
                        var browsable = info.GetCustomAttribute<BrowsableAttribute>(true);
                        if (browsable != null && !browsable.Browsable)
                            continue;
                        Properties.Add(new Property(selectedObject, info));
                    }
                }
            }
        }

        static PropertyGrid() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(PropertyGrid), new FrameworkPropertyMetadata(typeof(PropertyGrid)));
        }

        public PropertyGrid() {
            view = CollectionViewSource.GetDefaultView(Properties);
        }

        protected override void OnPropertyChanged(DependencyPropertyChangedEventArgs e) {
            base.OnPropertyChanged(e);
            if (e.Property == FilterProperty)
                view.Refresh();
        }

        private void DockPanel_IsKeyboardFocusWithinChanged(object sender, DependencyPropertyChangedEventArgs e) {
            var element = (FrameworkElement)sender;
            if (element.IsKeyboardFocusWithin) {
                Visual cur = element;
                while (cur != null && !(cur is ListBoxItem))
                    cur = (Visual)VisualTreeHelper.GetParent(cur);
                ((ListBoxItem)cur).IsSelected = true;
            }
        }

        private void DockPanel_MouseDown(object sender, MouseEventArgs e) {
            ((FrameworkElement)sender).MoveFocus(new TraversalRequest(FocusNavigationDirection.First));
        }

        public override void OnApplyTemplate() {
            base.OnApplyTemplate();

            if (view.GroupDescriptions.Count == 0)
                view.GroupDescriptions.Add(new PropertyGroupDescription("Category"));

            if (view.SortDescriptions.Count == 0) {
                view.SortDescriptions.Add(new SortDescription("Category", ListSortDirection.Ascending));
                view.SortDescriptions.Add(new SortDescription("DisplayName", ListSortDirection.Ascending));
            }

            view.Filter = obj => string.IsNullOrEmpty(Filter) ? true : (obj as Property).DisplayName.ToLower().Contains(Filter);

            var listBox = GetTemplateChild("listBox") as ListBox;
            listBox.ItemsSource = view;
        }
    }
}
