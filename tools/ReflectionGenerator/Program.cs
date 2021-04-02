using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace ReflectionGenerator {

    class Program {
        static void Main(string[] args) {
            if (args.Length < 2)
                return;

            string path = args[0];
            if (File.Exists(path))
                return;
            var files = getHeaders(path);

            string outFolder = args[1];
            var generatedFiles = new List<string>();
            if (Directory.Exists(outFolder)) {
                generatedFiles.AddRange(getHeaders(outFolder));
            } else {
                Directory.CreateDirectory(outFolder);
            }

            Console.WriteLine("Generating reflection");
            foreach (string file in files)
                ReflectionGenerator.generate(file, outFolder, generatedFiles);
            Console.WriteLine("Done");
        }
        private static List<string> getHeaders(string path) {
            var dirs = new List<string> { path };
            var files = new List<string>();
            while (dirs.Count > 0) {
                var currentPath = dirs[0];
                dirs.RemoveAt(0);
                files.AddRange(Directory.GetFiles(currentPath));
                dirs.AddRange(Directory.GetDirectories(currentPath));
            }
            return files.Where(file => file.EndsWith(".h")).ToList();
        }
    }
}