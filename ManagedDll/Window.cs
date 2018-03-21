using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed {
    public class Window : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Window_new();

        public Window() {
            NativePtr = Window_new();
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Window_init(IntPtr nativeWindow, IntPtr handle);

        public void init(IntPtr handle) {
            Window_init(NativePtr, handle);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Window_uninit(IntPtr nativeWindow);

        public void uninit() {
            Window_uninit(NativePtr);
        }
    }
}
