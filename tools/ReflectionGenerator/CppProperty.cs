namespace ReflectionGenerator {
    public class CppProperty {
        public CppType ownerType;
        public string type, name, getter, setter;

        public override string ToString() {
            var getterType = $@"{(type.Contains("const") ? type.Substring("const ".Length) : type)}({ownerType.name}::*)()";
            var setterType = $@"void({ownerType.name}::*)({type})";
            return $@"static auto PROPERTY_{name.ToUpper()} = Ghurund::TypedProperty<{ownerType.name}, {type}>(""{type}"", ""{name}"", ({getterType})&{getter + (setter.Length > 0 ? $@", ({setterType})&{setter}" : "")});";
        }
    }
}