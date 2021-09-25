using System.Collections.Generic;

namespace ReflectionGenerator {
    public class CppType {
        public string name, supertype;
        public bool isTemplate, isAbstract;
        public List<CppConstructor> constructors;
        public List<CppMethod> methods;
        public List<CppProperty> properties;
    }
}