using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics.Texture {
    public class Image : Resource.Resource {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Image_new();

        protected override IntPtr NewObject() => Image_new();


        public Image() {
            FileName = "unnamed image.jpg";
        }

        public Image(IntPtr ptr) : base(ptr) {
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Image_getFormats();

        public static ResourceFormatArray Formats { get; } = new ResourceFormatArray(Image_getFormats());
    }
}
