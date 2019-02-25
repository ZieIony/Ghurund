using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.ComponentModel.DataAnnotations;
using System.Reflection;

namespace Ghurund.Controls.PropertyGrid {
    public class Value {
        public delegate object ValueGetterDelegate();
        public delegate void ValueSetterDelegate(object obj);

        public Type Type { get; set; }
        public IPropertyEditor Editor { get; set; }
        public ValueGetterDelegate Getter { get; set; }
        public ValueSetterDelegate Setter { get; set; }
    }

    public class Property : INotifyPropertyChanged {
        private static readonly string GENERIC_CATEGORY = "Generic";
        private static readonly Dictionary<Type, Type> DEFAULT_EDITOR_TYPES = new Dictionary<Type, Type> {
            {typeof(bool), typeof(BooleanPropertyEditor) },
            {typeof(int), typeof(IntPropertyEditor) },
            {typeof(float), typeof(FloatPropertyEditor) },
            {typeof(string), typeof(TextPropertyEditor) }
        };

        private PropertyChangedEventHandler propertyChangedHandler;
        private INotifyPropertyChanged notificationSource;

        public Property(INotifyPropertyChanged notificationSource) {
            this.notificationSource = notificationSource;
            propertyChangedHandler = new PropertyChangedEventHandler(Property_PropertyChanged);
            notificationSource.PropertyChanged += propertyChangedHandler;
        }

        public Property(object owner, PropertyInfo info) {
            DisplayName = info.Name;
            Description = info.GetCustomAttribute<DescriptionAttribute>(true)?.Description;
            Category = info.GetCustomAttribute<CategoryAttribute>(true)?.Category ?? GENERIC_CATEGORY;

            var editable = info.GetCustomAttribute<EditableAttribute>(true)?.AllowEdit ?? false;
            var editorType = info.GetCustomAttribute<EditorAttribute>(true)?.EditorType ?? (editable ? GetEditorType(info.PropertyType) : null);

            Value.Type = info.PropertyType;
            Value.Editor = editorType != null ? Activator.CreateInstance(editorType, true) as IPropertyEditor : null;
            Value.Getter = () => info.GetValue(owner);
            Value.Setter = (v) => info.SetValue(owner, v);

            if (owner is INotifyPropertyChanged) {
                notificationSource = owner as INotifyPropertyChanged;
                propertyChangedHandler = new PropertyChangedEventHandler(Property_PropertyChanged);
                notificationSource.PropertyChanged += propertyChangedHandler;
            }
        }

        private static Type GetEditorType(Type propertyType) {
            if (propertyType.IsEnum) {
                return typeof(EnumPropertyEditor);
            } else {
                return DEFAULT_EDITOR_TYPES[propertyType];
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
