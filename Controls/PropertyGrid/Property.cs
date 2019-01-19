namespace Ghurund.Controls.PropertyGrid {
    public class Property {
        internal static readonly string GENERIC_CATEGORY = "Generic";

        public delegate object ValueGetterDelegate();
        public delegate void ValueSetterDelegate(object obj);

        public string Category { get; set; } = GENERIC_CATEGORY;
        public string DisplayName { get; set; }
        public string Description { get; set; }
        public IPropertyEditor Editor { get; set; }
        public ValueGetterDelegate ValueGetter { get; set; }
        public ValueSetterDelegate ValueSetter { get; set; }
    }
}
