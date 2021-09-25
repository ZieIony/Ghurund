using System;
using System.Collections.Generic;
using System.IO;
using System.Text.RegularExpressions;

namespace ReflectionGenerator {
    class ReflectionGenerator {
        private const string IDENTIFIER_PATTERN = @"[a-zA-Z_][a-zA-Z_0-9]*";

        private const string NAMESPACE_PATTERN = $@"{IDENTIFIER_PATTERN}(?:\:\:{IDENTIFIER_PATTERN})*";
        private const string NAMESPACE_CONTENT_PATTERN = $@"(?<identation> *)namespace (?<namespace>{NAMESPACE_PATTERN}) *\{{(?<content>(.*\n)*?)\k<identation>\}}";

        private const string TEMPLATE_PARAM_PATTERN = $@"(?:typename|class|auto) +{IDENTIFIER_PATTERN}(?:\.\.\.)?";
        private const string TEMPLATE_DECL_PATTERN = $@"template *\< *{TEMPLATE_PARAM_PATTERN} *(?:, *{TEMPLATE_PARAM_PATTERN} *)*\>";

        private const string TYPE_PATTERN = $@"(?:(?:{NAMESPACE_PATTERN})?\:\:)?{IDENTIFIER_PATTERN}(?: *\< *{IDENTIFIER_PATTERN}(?: *, *{IDENTIFIER_PATTERN})? *\>)?";
        private const string TYPE_EXTEND_PATTERN = $@"(?:public |protected |private )? *?{TYPE_PATTERN}";
        private const string TYPE_DECL_PATTERN = $@"(?:{TEMPLATE_DECL_PATTERN}\n? *)?(?:class|struct|__interface) +(?<typeName>{IDENTIFIER_PATTERN})(?: *: *{TYPE_EXTEND_PATTERN}(?: *, *{TYPE_EXTEND_PATTERN})?)?";
        private const string TYPE_CONTENT_PATTERN = $@"(?<identation2> *){TYPE_DECL_PATTERN} *{{(?<content>(.*\n)*?)\k<identation2>}};";

        private const string TYPE_VARIANT_PATTERN = $@"(?:const *|volatile *)*{TYPE_PATTERN} *?[\&\*]*";
        private const string PROPERTY_PATTERN = $@"__declspec *\( *property *\( *get *= *(?<getter>{IDENTIFIER_PATTERN}) *(?:, *put *= *(?<setter>{IDENTIFIER_PATTERN}) *)?\) *\) *(?<propertyType>{TYPE_VARIANT_PATTERN}) *(?<propertyName>{IDENTIFIER_PATTERN}) *\;";

        private const string METHOD_PARAM_PATTERN = $@"{TYPE_VARIANT_PATTERN} *{IDENTIFIER_PATTERN}";
        private const string METHOD_PATTERN = $@"(?:static |const |inline |virtual ) *?{TYPE_VARIANT_PATTERN}(?<methodName>{IDENTIFIER_PATTERN}) *\( *(?<parameters>{METHOD_PARAM_PATTERN}?(, *{METHOD_PARAM_PATTERN})*) *\) *(?:const|override)? *(?:;|{{)";

        private static string GetConstructorPattern(string name) {
            return $@"(?: |\n){name} *\( *(?<parameters>{METHOD_PARAM_PATTERN}?(, *{METHOD_PARAM_PATTERN})*) *\)";
        }

        public static void Generate(FileInfo file, DirectoryInfo outFolder, List<FileInfo> generatedFiles) {
            var stream = file.OpenText();
            var content = stream.ReadToEnd();
            stream.Close();
            if (content.Contains("GH_GENERATE_REFLECTION")) {
                Console.WriteLine("processing file: " + file.FullName);
                FindNamespaces(outFolder, generatedFiles, content);
            }
            if (Regex.IsMatch(content, "reflection_[a-z0-9_]{10,}")) {
                /*string preprocessedContent = PreprocessNamespaces(outFolder, generatedFiles, content);
                StreamWriter preprocessedStream = file.CreateText();
                preprocessedStream.Write(preprocessedContent);
                preprocessedStream.Close();
                Console.WriteLine(file);*/
            }
        }

        private static void FindNamespaces(DirectoryInfo generated, List<FileInfo> generatedFiles, string fileContent) {
            var matches = Regex.Matches(fileContent, NAMESPACE_CONTENT_PATTERN);
            foreach (Match match in matches) {
                string namespaceContent = match.Groups["content"].Value;
                if (namespaceContent.Contains("GH_GENERATE_REFLECTION")) {
                    string namespaceName = match.Groups["namespace"].Value;
                    Console.WriteLine("namespace found: " + namespaceName);
                    List<CppType> reflectionTypes = FindReflectionTypes(namespaceName, namespaceContent);
                    /*TypesWithReflection types = PreprocessTypes(generated, generatedFiles, namespaceName, namespaceContentGroup.Value);
                    StringWriter stringWriter = new StringWriter();
                    foreach (string inc in types.guid)
                        stringWriter.WriteLine($"#include \"{inc}.h\"\r\n");
                    return string.Format("{0}{1}{2}{3}",
                        stringWriter.ToString(),
                        match.Value.Substring(0, namespaceContentGroup.Index - match.Index),
                        types.content,
                        match.Value.Substring(namespaceContentGroup.Index - match.Index + namespaceContentGroup.Length));*/
                }
            };
        }

        private static List<CppType> FindReflectionTypes(string namespaceName, string content) {
            var types = new List<CppType>();
            var matches = Regex.Matches(content, TYPE_CONTENT_PATTERN);
            foreach (Match match in matches) {
                string typeContent = match.Groups["content"].Value;
                if (typeContent.Contains("GH_GENERATE_REFLECTION")) {
                    Console.WriteLine("type found: " + match.Groups["typeName"].Value);
                    var type = new CppType {
                        name = match.Groups["typeName"].Value
                    };
                    type.properties = FindProperties(type, typeContent);
                    type.methods = FindMethods(type, typeContent);
                    type.constructors = FindConstructors(type, typeContent);
                    types.Add(type);
                }
            }
            return types;
        }

        /*private static TypesWithReflection PreprocessTypes(DirectoryInfo generated, List<FileInfo> generatedFiles, string namespaceName, string content) {
            string pattern = @"(?<template>template\<[, a-zA-Z_0-9]+\>\n? *)?class +(?<name>[a-zA-Z_0-9]+) *:?(,? *(?:public|protected|private) *(?<supertype>(?:[a-zA-Z_0-9:]+)(\<[, a-zA-Z_0-9]+\>)?))* *\{(?<content>(?:.*\n)*? *GH_GENERATE_REFLECTION(?:.*\n)*?) *\}\;";

            TypesWithReflection types = new TypesWithReflection();
            types.content = Regex.Replace(content, pattern, (match) => {
                var typeName = match.Groups["name"].Value;
                var type = new CppType {
                    isTemplate = match.Groups["template"].Success,
                    name = typeName,
                    supertype = match.Groups["supertype"].Value,
                    isAbstract = content.Contains(") = 0;") || content.Contains(") const = 0;") || content.Contains(") = 0 {"),
                    hasNoArgsConstructor = content.Contains(" " + typeName + "() {")
                    || content.Contains(" " + typeName + "();")
                    || content.Contains(" " + typeName + "():")
                    || content.Contains(" " + typeName + "() = default")
                    || !content.Contains(" " + typeName + "(")
                };
                string reflectionInclude = match.Groups["reflection"].Value;
                string guid = reflectionInclude;
                if (!generatedFiles.Any(file => file.FullName == Path.Combine(generated.FullName, guid + ".h"))) {
                    //guid = "reflection_" + Guid.NewGuid().ToString().Replace("-", "_");
                    types.guid.Add(guid);
                }
                string classContent = match.Groups["content"].Value;
                List<CppConstructor> constructors = FindConstructors(type, classContent);
                List<CppProperty> properties = FindProperties(type, classContent);
                List<CppMethod> methods = FindMethods(type, classContent);
                string reflection = GenerateReflection(namespaceName, type, constructors, properties, methods);
                using (var writer = new StreamWriter(Path.Combine(generated.FullName, guid + ".h")))
                    writer.Write(reflection);
                return match.Value.Replace(reflectionInclude, guid);
            });
            return types;
        }*/

        private static List<CppProperty> FindProperties(CppType ownerType, string classContent) {
            var properties = new List<CppProperty>();

            MatchCollection matches = Regex.Matches(classContent, PROPERTY_PATTERN);
            foreach (Match match in matches) {
                GroupCollection groups = match.Groups;
                Console.WriteLine($"property found: {groups["propertyType"].Value} {groups["propertyName"].Value}");
                properties.Add(new CppProperty {
                    ownerType = ownerType,
                    getter = groups["getter"].Value,
                    setter = groups["setter"].Value,
                    type = groups["propertyType"].Value,
                    name = groups["propertyName"].Value
                });
            }

            return properties;
        }

        private static List<CppConstructor> FindConstructors(CppType ownerType, string classContent) {
            var constructors = new List<CppConstructor>();

            MatchCollection matches = Regex.Matches(classContent, GetConstructorPattern(ownerType.name));
            foreach (Match match in matches) {
                GroupCollection groups = match.Groups;
                Console.WriteLine($"constructor found: {ownerType.name}({groups["parameters"].Value})");
                constructors.Add(new CppConstructor { name = ownerType.name });
            }

            return constructors;
        }

        private static List<CppMethod> FindMethods(CppType ownerType, string classContent) {
            var methods = new List<CppMethod>();

            MatchCollection matches = Regex.Matches(classContent, METHOD_PATTERN);
            foreach (Match match in matches) {
                GroupCollection groups = match.Groups;
                Console.WriteLine($"method found: {groups["methodName"].Value}({groups["parameters"].Value})");
                methods.Add(new CppMethod { name = groups["methodName"].Value });
            }

            return methods;
        }

        private static string GenerateReflection(
            string namespaceName,
            CppType type,
            List<CppConstructor> constructors,
            List<CppProperty> properties,
            List<CppMethod> methods
        ) {
            StringWriter str = new StringWriter();

            str.WriteLine($@"const Ghurund::Core::Type& {type.name}::GET_TYPE() {{");
            foreach (CppProperty p in properties)
                str.WriteLine($@"{p}");
            foreach (CppConstructor c in constructors)
                str.WriteLine($@"{c}");
            str.WriteLine($@"
static const Ghurund::Core::Type TYPE = TypeBuilder<{type.name}>(""{namespaceName}"", ""{type.name}"")");
            foreach (CppProperty p in properties)
                str.WriteLine($@".withProperty(PROPERTY_{p.name.ToUpper()})");
            if (type.isTemplate)
                str.WriteLine($@".withModifier(TypeModifier::TEMPLATE)");
            if (type.isAbstract)
                str.WriteLine($@".withModifier(TypeModifier::ABSTRACT)");
            if (!type.isAbstract && constructors.Count != 0)
                str.WriteLine($@".withConstructor(CONSTRUCTOR)");
            str.WriteLine($@".withSupertype(__super::GET_TYPE());

return TYPE;
}}");

            return str.ToString();
        }

    }
}