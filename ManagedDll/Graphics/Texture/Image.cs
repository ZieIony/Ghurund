using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics.Texture {
    public class Image: Resource.Resource {

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

        [Browsable(false)]
        public static Array<ResourceFormat> Formats { get; } = new Array<ResourceFormat>(Image_getFormats(), ptr => new ResourceFormat(ptr));


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Image_getWidth(IntPtr _this);

        public uint Width => Image_getWidth(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Image_getHeight(IntPtr _this);

        public uint Height => Image_getHeight(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Image_getPixelSize(IntPtr _this);

        public uint PixelSize => Image_getPixelSize(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Image_getRowPitch(IntPtr _this);

        public uint RowPitch => Image_getRowPitch(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Image_getData(IntPtr _this);

        public IntPtr Data => Image_getData(NativePtr);


        public WriteableBitmap ToBitmap() {
            WriteableBitmap bitmap = new WriteableBitmap((int)Width, (int)Height, 72, 72, PixelFormats.Bgra32, null);
            bitmap.WritePixels(new System.Windows.Int32Rect(0, 0, (int)Width, (int)Height), Data, (int)(RowPitch * Height), (int)RowPitch);
            return bitmap;
        }
    }
}
