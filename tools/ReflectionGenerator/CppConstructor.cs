namespace ReflectionGenerator {
    public class CppConstructor {
        public string name;

        public override string ToString() {
            return $@"static const auto CONSTRUCTOR = Constructor<{name}>();";
        }

    }
}