using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Audio {
    public class Audio : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Audio_new();

        public Audio() {
            NativePtr = Audio_new();
            init();
        }

        ~Audio() {
            uninit();
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Audio_init(IntPtr _this);

        public void init() => Audio_init(NativePtr);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Audio_uninit(IntPtr _this);

        public void uninit() => Audio_uninit(NativePtr);

    }
}
