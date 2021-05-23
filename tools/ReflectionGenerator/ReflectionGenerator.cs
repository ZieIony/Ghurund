using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace ReflectionGenerator {
    class ReflectionGenerator {
        public static void Generate(FileInfo file, DirectoryInfo outFolder, List<FileInfo> generatedFiles) {
            var stream = file.OpenText();
            var content = stream.ReadToEnd();
            stream.Close();
            if (Regex.IsMatch(content, "reflection_[a-z0-9_]{10,}")) {
                string preprocessedContent = PreprocessNamespaces(outFolder, generatedFiles, content);
                StreamWriter preprocessedStream = file.CreateText();
                preprocessedStream.Write(preprocessedContent);
                preprocessedStream.Close();
                Console.WriteLine(file);
            }
        }

        private static string PreprocessNamespaces(DirectoryInfo generated, List<FileInfo> generatedFiles, string fileContent) {
            string pattern = @"( *)namespace *(?<name>[a-zA-Z_0-9\:]+) *\{(?<content>(.*\n)*?)\1\}";
            return Regex.Replace(fileContent, pattern, (match) => {
                string namespaceName = match.Groups["name"].Value;
                Group namespaceContentGroup = match.Groups["content"];
                TypesWithReflection types = PreprocessTypes(generated, generatedFiles, namespaceName, namespaceContentGroup.Value);
                StringWriter stringWriter = new StringWriter();
                foreach (string inc in types.guid)
                    stringWriter.WriteLine($"#include \"{inc}.h\"\r\n");
                return string.Format("{0}{1}{2}{3}",
                    stringWriter.ToString(),
                    match.Value.Substring(0, namespaceContentGroup.Index - match.Index),
                    types.content,
                    match.Value.Substring(namespaceContentGroup.Index - match.Index + namespaceContentGroup.Length));
            });
        }

        private static TypesWithReflection PreprocessTypes(DirectoryInfo generated, List<FileInfo> generatedFiles, string namespaceName, string content) {
            string pattern = @"(?<template>template\<[, a-zA-Z_0-9]+\>\n? *)?class +(?<name>[a-zA-Z_0-9]+) *:?(,? *(?:public|protected|private) *(?<supertype>(?:[a-zA-Z_0-9:]+)(\<[, a-zA-Z_0-9]+\>)?))* *\{(?<content>(?:.*\n)*? *(?<reflection>reflection_[a-z0-9_]{10,})(?:.*\n)*?) *\}\;";

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
                List<CppProperty> properties = FindProperties(type, match.Groups["content"].Value);
                string reflection = GenerateReflection(guid, namespaceName, type, properties);
                using (var writer = new StreamWriter(Path.Combine(generated.FullName, guid + ".h")))
                    writer.Write(reflection);
                return match.Value.Replace(reflectionInclude, guid);
            });
            return types;
        }

        private static List<CppProperty> FindProperties(CppType ownerType, string classContent) {
            Regex rx = new Regex(@"__declspec *\( *property *\( *get *= *(?<getter>[a-zA-Z_0-9]+) *(?:, *put *= *(?<setter>[a-zA-Z_0-9]+) *)?\) *\) *(?<type>(?:const *)?(?:[a-zA-Z_0-9\:]+)[\&\*]?)* *(?<property>[a-zA-Z_0-9]+) *\;", RegexOptions.Compiled | RegexOptions.IgnoreCase);

            MatchCollection matches = rx.Matches(classContent);
            var properties = new List<CppProperty>();

            foreach (Match match in matches) {
                GroupCollection groups = match.Groups;
                properties.Add(new CppProperty {
                    ownerType = ownerType,
                    getter = groups["getter"].Value,
                    setter = groups["setter"].Value,
                    type = groups["type"].Value,
                    name = groups["property"].Value
                });
            }

            return properties;
        }

        private static string GenerateReflection(string guid, string namespaceName, CppType type, List<CppProperty> properties) {
            StringWriter str = new StringWriter();

            str.WriteLine($@"#include ""core/reflection/TypeBuilder.h""
#include ""core/reflection/TypedProperty.h""

#define {guid} protected:\
static const Ghurund::Type& GET_TYPE() {{\");
            foreach (CppProperty p in properties)
                str.WriteLine($@"{p}\");
            if (!type.isAbstract && type.hasNoArgsConstructor)
                str.WriteLine($@"\
static const auto CONSTRUCTOR = Ghurund::NoArgsConstructor<{type.name}>();\");
            str.WriteLine($@"\
static const Ghurund::Type TYPE = Ghurund::TypeBuilder(""{namespaceName}"", ""{type.name}"")\");
            foreach (CppProperty p in properties)
                str.WriteLine($@".withProperty(PROPERTY_{p.name.ToUpper()})\");
            if (type.isTemplate)
                str.WriteLine($@".withModifier(TypeModifier::TEMPLATE)\");
            if (type.isAbstract)
                str.WriteLine($@".withModifier(TypeModifier::ABSTRACT)\");
            if (!type.isAbstract && type.hasNoArgsConstructor)
                str.WriteLine($@".withConstructor(CONSTRUCTOR)\");
            str.WriteLine($@".withSupertype(__super::GET_TYPE());\
\
return TYPE;\
}}\
\
public:\
inline static const Ghurund::Type& TYPE = GET_TYPE();\
\
virtual const Ghurund::Type& getType() const override {{\
return TYPE;\
}}");

            return str.ToString();
        }

    }
}