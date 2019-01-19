using System;
using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;

namespace Ghurund.Controls.PropertyGrid {

    public class PropertyGrid : Control {

        public ObservableCollection<Property> Properties { get; } = new ObservableCollection<Property>();

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
                        var description = info.GetCustomAttribute<DescriptionAttribute>(true);
                        var category = info.GetCustomAttribute<CategoryAttribute>(true);
                        var editorType = info.GetCustomAttribute<EditorAttribute>(true)?.EditorType;
                        Properties.Add(new Property() {
                            DisplayName = info.Name,
                            ValueGetter = () => info.GetValue(selectedObject),
                            ValueSetter = (v) => info.SetValue(selectedObject, v),
                            Category = category?.Category ?? Property.GENERIC_CATEGORY,
                            Description = description?.Description,
                            Editor = editorType != null ? Activator.CreateInstance(editorType, true) as IPropertyEditor : null
                        });
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

        public void Refresh() {
            view.Refresh();
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
