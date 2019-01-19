using System;

namespace Ghurund.Controls.PropertyGrid {
    [AttributeUsage(AttributeTargets.All, AllowMultiple = true, Inherited = true)]
    public sealed class EditorAttribute : Attribute {
        public EditorAttribute(Type type) {
            EditorType = type;
        }

        public Type EditorType { get; }
    }
}
