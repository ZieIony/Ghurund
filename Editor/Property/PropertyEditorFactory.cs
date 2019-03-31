using Ghurund.Controls.PropertyGrid;
using Ghurund.Managed;
using Ghurund.Managed.Resource;
using System;
using System.Collections.Generic;

namespace Ghurund.Editor.Property {
    class PropertyEditorFactory: IPropertyEditorFactory {
        private static readonly Dictionary<Type, Type> DEFAULT_EDITOR_TYPES = new Dictionary<Type, Type> {
            {typeof(bool), typeof(BooleanPropertyEditor) },
            {typeof(int), typeof(IntPropertyEditor) },
            {typeof(float), typeof(FloatPropertyEditor) },
            {typeof(string), typeof(TextPropertyEditor) },
            {typeof(Float3), typeof(Float3PropertyEditor) },
            {typeof(Color), typeof(ColorPropertyEditor) },
            {typeof(Resource), typeof(ResourcePropertyEditor) }
        };

        public Type GetEditorType(Type propertyType) {
            if (propertyType.IsEnum) {
                return typeof(EnumPropertyEditor);
            } else {
                foreach (Type t in DEFAULT_EDITOR_TYPES.Keys) {
                    if (t.IsAssignableFrom(propertyType))
                        return DEFAULT_EDITOR_TYPES[t];
                }
                return null;
            }
        }
    }
}
