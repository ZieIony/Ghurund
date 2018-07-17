using System;
using System.IO;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Xml.Serialization;

namespace Ghurund.Controls.Workspace {
    public static class Extensions {
        public static T FindVisualChildByName<T>(this DependencyObject parent, string name) where T : DependencyObject {
            for (int i = 0; i < VisualTreeHelper.GetChildrenCount(parent); i++) {
                var child = VisualTreeHelper.GetChild(parent, i);
                string controlName = child.GetValue(Control.NameProperty) as string;
                if (controlName == name) {
                    return child as T;
                } else {
                    T result = FindVisualChildByName<T>(child, name);
                    if (result != null)
                        return result;
                }
            }

            return null;
        }

        public static void WriteToBinaryFile<T>(this T objectToWrite, string filePath) {
            using (Stream stream = File.Open(filePath, FileMode.Create)) {
                var binaryFormatter = new XmlSerializer(typeof(T));
                binaryFormatter.Serialize(stream, objectToWrite);
            }
        }

        public static T ReadFromBinaryFile<T>(string filePath) {
            try {
                using (Stream stream = File.Open(filePath, FileMode.Open)) {
                    var binaryFormatter = new XmlSerializer(typeof(T));
                    return (T)binaryFormatter.Deserialize(stream);
                }
            }catch(Exception) {
                return default(T);
            }
        }
    }
}
