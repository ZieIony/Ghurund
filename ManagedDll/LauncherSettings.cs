using Ghurund.Managed.Resource;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Drawing.Design;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.Windows.Forms.Design;

namespace Ghurund.Managed {
    public class LauncherSettings : IResource {
        public class LauncherSettingsData {
            private List<WindowSize> windowSizes = new List<WindowSize>();

            [Category("Graphics")]
            [Description("The list of screen resolutions handled by the application.")]
            public List<WindowSize> WindowSizes { get => windowSizes; }

            [Category("Graphics")]
            public bool DefaultWindowed { get; set; }

            [Category("Global")]
            [Description("This path should be relative to the launcher.")]
            [Editor(typeof(FileNameEditor), typeof(UITypeEditor))]
            public string PathToExe { get; set; }

            [Category("Global")]
            [Description("The name of the application. This name will be used as the launcher's title.")]
            public string Name { get; set; }

            [Category("Global")]
            [Description("This path should be relative to the launcher.")]
            [Editor(typeof(FileNameEditor), typeof(UITypeEditor))]
            public string PathToImage { get; set; }
        }

        public LauncherSettings() {
            FileName = "unnamed settings." + DefaultExtension;
            Data = new LauncherSettingsData();
        }

        public LauncherSettingsData Data { get; private set; }

        public string FileName { get; set; }
        public string DefaultExtension { get => "stn"; }

        public bool load(ResourceManager resourceManager, string fileName) {
            FileName = fileName;
            // Open the file containing the data that you want to deserialize.
            FileStream fs = new FileStream(FileName, FileMode.Open);
            try {
                BinaryFormatter formatter = new BinaryFormatter();

                // Deserialize the hashtable from the file and 
                // assign the reference to the local variable.
                Data = (LauncherSettingsData)formatter.Deserialize(fs);
                return true;
            } catch (SerializationException) {
                return false;
            } finally {
                fs.Close();
            }

        }

        public bool save(ResourceManager resourceManager, string fileName) {
            FileName = fileName;
            FileStream fs = new FileStream(FileName, FileMode.Create);

            // Construct a BinaryFormatter and use it to serialize the data to the stream.
            BinaryFormatter formatter = new BinaryFormatter();
            try {
                formatter.Serialize(fs, Data);
                return true;
            } catch (SerializationException) {
                return false;
            } finally {
                fs.Close();
            };
        }

        public string getExtension() {
            throw new NotImplementedException();
        }
    }
}
