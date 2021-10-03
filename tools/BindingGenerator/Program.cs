using System.IO;

namespace BindingGenerator {
    class Program {
        static void Main(string[] args) {
            var arguments = BindingGenerator.Utils.ParseArguments(args);
            var input = new DirectoryInfo(arguments["input"] ?? Directory.GetCurrentDirectory());
            var output = new DirectoryInfo(arguments["output"] ?? Directory.GetCurrentDirectory());

            var files = BindingGenerator.Utils.GetFiles(input, "xml");
            new Generator().generateBindings(files, output);
        }
    }
}