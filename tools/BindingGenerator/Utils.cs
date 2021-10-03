using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text.RegularExpressions;

namespace BindingGenerator {

    public static class Utils {
        public static Arguments ParseArguments(string[] args) {
            var pattern = @"-?-(?<name>[a-zA-Z0-9_]+)=(['""`])(?<value>.+?)(\1)";
            var dictionary = new Dictionary<string, string>();
            foreach (string arg in args) {
                var match = Regex.Match(arg, pattern);
                if (match.Success) {
                    dictionary.Add(match.Groups["name"].Value, match.Groups["value"].Value);
                }
            }
            return new Arguments(dictionary);
        }

        public static FileInfo[] GetFiles(DirectoryInfo input, string extension) {
            var extensionWithDot = extension.StartsWith(".") ? extension : "." + extension;
            List<string> files = new List<string>();
            List<string> directories = new List<string> { input.FullName };

            while (directories.Count > 0) {
                string dir = directories[0];
                directories.RemoveAt(0);
                directories.AddRange(Directory.GetDirectories(dir));
                files.AddRange(Directory.GetFiles(dir));
            }

            return files.Where(it => it.EndsWith(extensionWithDot)).Select(it => new FileInfo(Path.Combine(input.FullName, it))).ToArray();
        }

        public static string GetNameWithoutExtension(this FileInfo fileInfo) {
            return Path.GetFileNameWithoutExtension(fileInfo.FullName);
        }
    }
}
