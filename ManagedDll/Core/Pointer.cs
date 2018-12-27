using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Core {
    public class Pointer : NativeClass {

        public Pointer() {
        }

        public Pointer(IntPtr ptr) : base(ptr) {
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Pointer_getReferenceCount(IntPtr _this);

        public uint ReferenceCount {
            get => Pointer_getReferenceCount(NativePtr);
        }
    }
}
