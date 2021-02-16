using System.Collections.Generic;
using System.IO;
using System.Linq;

namespace BindingGenerator
{
    class Program
    {
        static void Main(string[] args)
        {
            string input = args.Length > 0 ? new DirectoryInfo(args[0]).FullName : Directory.GetCurrentDirectory();
            string output = args.Length > 1 ? new DirectoryInfo(args[1]).FullName : input;
            new Generator().generateBindings(getFiles(input), input, output);
        }

        static List<string> getFiles(string path)
        {
            List<string> files = new List<string>();
            List<string> directories = new List<string>();
            directories.Add(path);
            while (directories.Count > 0)
            {
                string dir = directories[0];
                directories.RemoveAt(0);
                directories.AddRange(Directory.GetDirectories(dir));
                files.AddRange(Directory.GetFiles(dir));
            }

            return files.Where(it => it.EndsWith(".xml")).ToList().ConvertAll(it => Path.Combine(path, it));
        }
    }
}