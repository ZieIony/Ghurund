using System.Collections.ObjectModel;
using System.ComponentModel;
using System.Reflection;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Input;
using System.Windows.Media;

namespace Ghurund.Controls {
    public class Property {
        internal static readonly string GENERIC_CATEGORY = "Generic";

        public string Category { get; set; } = GENERIC_CATEGORY;
        public string DisplayName { get; set; }
        public string Description { get; set; }
        public object Value { get; set; }
    }

    public class PropertyGrid : Control {
        public ObservableCollection<Property> Properties {
            get { return (ObservableCollection<Property>)GetValue(PropertiesProperty); }
            set { SetValue(PropertiesProperty, value); }
        }

        public static readonly DependencyProperty PropertiesProperty =
            DependencyProperty.Register("Properties", typeof(ObservableCollection<Property>), typeof(PropertyGrid), new PropertyMetadata(null));

        private object selectedObject;
        public object SelectedObject {
            get {
                return selectedObject;
            }
            set {
                selectedObject = value;
                Properties.Clear();
                var properties = selectedObject.GetType().GetProperties();
                foreach (PropertyInfo info in properties) {
                    var browsable = info.GetCustomAttribute<BrowsableAttribute>(true);
                    if (browsable != null && !browsable.Browsable)
                        continue;
                    var description = info.GetCustomAttribute<DescriptionAttribute>(true);
                    var category = info.GetCustomAttribute<CategoryAttribute>(true);
                    Properties.Add(new Property() {
                        DisplayName = info.Name,
                        Value = info.GetValue(selectedObject),
                        Category = category?.Category ?? Property.GENERIC_CATEGORY,
                        Description = description?.Description
                    });
                }
            }
        }

        static PropertyGrid() {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(PropertyGrid), new FrameworkPropertyMetadata(typeof(PropertyGrid)));
        }

        public PropertyGrid() {
            Properties = new ObservableCollection<Property>();
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

            var view = CollectionViewSource.GetDefaultView(Properties);
            if (view.GroupDescriptions.Count == 0)
                view.GroupDescriptions.Add(new PropertyGroupDescription("Category"));

            if (view.SortDescriptions.Count == 0) {
                view.SortDescriptions.Add(new SortDescription("Category", ListSortDirection.Ascending));
                view.SortDescriptions.Add(new SortDescription("DisplayName", ListSortDirection.Ascending));
            }
        }
    }
}
