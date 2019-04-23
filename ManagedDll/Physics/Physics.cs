using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Physics {
    public class Physics: NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Physics_new();

        protected override IntPtr NewObject() => Physics_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Physics_init(IntPtr _this);

        public void Init() => Physics_init(NativePtr);
    }
}
