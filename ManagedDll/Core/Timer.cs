using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Core {

    public class Timer: NativeClass {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Timer_new();

        protected override IntPtr NewObject() => Timer_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern float Timer_getTime(IntPtr _this);

        public float Time {
            get => Timer_getTime(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool Timer_isPaused(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Timer_setPaused(IntPtr _this, bool paused);

        public bool Paused {
            get => Timer_isPaused(NativePtr);
            set => Timer_setPaused(NativePtr, value);
        }
    }
}
