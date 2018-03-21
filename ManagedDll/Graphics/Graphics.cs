using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Graphics {
    public class Graphics : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Graphics_new();

        public Graphics() {
            NativePtr = Graphics_new();
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Graphics_init(IntPtr _this);

        public void init() {
            Graphics_init(NativePtr);
        }
    }
}
