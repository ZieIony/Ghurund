namespace ReflectionGenerator {
    public class CppProperty {
        public CppType ownerType;
        public string type, name, getter, setter;

        public override string ToString() {
            var getterType = $@"{(type.Contains("const") ? type.Substring("const ".Length) : type)}({ownerType.name}::*)()";
            var setterType = $@"void({ownerType.name}::*)({type})";
            var propertyType = setter.Length > 0 ? "Property" : "ReadOnlyProperty";
            return $@"static auto PROPERTY_{name.ToUpper()} = Ghurund::{propertyType}<{ownerType.name}, {type}>(""{type}"", ""{name}"", ({getterType})&{getter + (setter.Length > 0 ? $@", ({setterType})&{setter}" : "")});";
        }
    }
}