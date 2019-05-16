using System;
using System.Collections.Generic;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Controls.Primitives;
using System.Windows.Interop;
using System.Windows.Media.Imaging;

namespace Ghurund.Editor {
    public static class Extensions {
        [System.Runtime.InteropServices.DllImport("gdi32.dll")]
        public static extern bool DeleteObject(IntPtr hObject);

        public static BitmapSource ToBitmapSource(this Bitmap source) {
            var hBitmap = source.GetHbitmap();
            var result = System.Windows.Interop.Imaging.CreateBitmapSourceFromHBitmap(hBitmap, IntPtr.Zero, Int32Rect.Empty, BitmapSizeOptions.FromEmptyOptions());

            DeleteObject(hBitmap);

            return result;
        }

        public static BitmapImage ToBitmapImage(this Bitmap bitmap) {
            BitmapImage bitmapImage = new BitmapImage();
            using (MemoryStream memory = new MemoryStream()) {
                bitmap.Save(memory, ImageFormat.Png);
                memory.Position = 0;
                bitmapImage.BeginInit();
                bitmapImage.StreamSource = memory;
                bitmapImage.CacheOption = BitmapCacheOption.OnLoad;
                bitmapImage.EndInit();
            }
            return bitmapImage;
        }

        public static IEnumerable<T> Filter<T>(this IEnumerable<T> source, Func<T, bool> predicate) => source.Where(predicate);
        public static IEnumerable<T2> Map<T, T2>(this IEnumerable<T> source, Func<T, T2> predicate) => source.Select(predicate);

        public static void ForEach<T>(this IEnumerable<T> source, Action<T> action) {
            foreach (T item in source)
                action(item);
        }

        public static bool Any<T>(this IEnumerable<T> source, Func<T, bool> predicate) {
            foreach (T item in source)
                if (predicate(item))
                    return true;
            return false;
        }
    }
}
