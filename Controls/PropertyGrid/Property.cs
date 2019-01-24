using System;
using System.ComponentModel;
using System.Reflection;

namespace Ghurund.Controls.PropertyGrid {
    public class Value {
        public delegate object ValueGetterDelegate();
        public delegate void ValueSetterDelegate(object obj);

        public IPropertyEditor Editor { get; set; }
        public ValueGetterDelegate Getter { get; set; }
        public ValueSetterDelegate Setter { get; set; }
    }

    public class Property : INotifyPropertyChanged {
        internal static readonly string GENERIC_CATEGORY = "Generic";

        private PropertyChangedEventHandler propertyChangedHandler;
        private INotifyPropertyChanged notificationSource;

        public Property(INotifyPropertyChanged notificationSource) {
            this.notificationSource = notificationSource;
                propertyChangedHandler = new PropertyChangedEventHandler(Property_PropertyChanged);
            notificationSource.PropertyChanged += propertyChangedHandler;
        }

        public Property(object owner, PropertyInfo info) {
            var description = info.GetCustomAttribute<DescriptionAttribute>(true);
            var category = info.GetCustomAttribute<CategoryAttribute>(true);
            var editorType = info.GetCustomAttribute<EditorAttribute>(true)?.EditorType;
            Category = category?.Category ?? Property.GENERIC_CATEGORY;
            DisplayName = info.Name;
            Description = description?.Description;
            Value.Editor = editorType != null ? Activator.CreateInstance(editorType, true) as IPropertyEditor : null;
            Value.Getter = () => info.GetValue(owner);
            Value.Setter = (v) => info.SetValue(owner, v);
            if (owner is INotifyPropertyChanged) {
                notificationSource = owner as INotifyPropertyChanged;
                propertyChangedHandler = new PropertyChangedEventHandler(Property_PropertyChanged);
                notificationSource.PropertyChanged += propertyChangedHandler;
            }
        }

        ~Property() {
            if (notificationSource != null)
                notificationSource.PropertyChanged -= propertyChangedHandler;
        }

        private void Property_PropertyChanged(object sender, PropertyChangedEventArgs e) {
            PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Value"));
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public string Category { get; set; } = GENERIC_CATEGORY;
        public string DisplayName { get; set; }
        public string Description { get; set; }
        public Value Value { get; } = new Value();
    }
}
