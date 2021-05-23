using System;
using System.Collections.Generic;
using System.IO;
using Utils;

namespace ReflectionGenerator {

    class Program {
        static void Main(string[] args) {
            var arguments = Utils.Utils.ParseArguments(args);
            var input = new DirectoryInfo(arguments["input"] ?? Directory.GetCurrentDirectory());
            var output = new DirectoryInfo(arguments["output"] ?? Directory.GetCurrentDirectory());

            var files = Utils.Utils.GetFiles(input, "h");

            var generatedFiles = new List<FileInfo>();
            if (output.Exists) {
                generatedFiles.AddRange(Utils.Utils.GetFiles(output, "h"));
            } else {
                output.Create();
            }

            Console.WriteLine("Generating reflection");
            foreach (FileInfo file in files)
                ReflectionGenerator.Generate(file, output, generatedFiles);
            Console.WriteLine("Done");
        }
    }
}