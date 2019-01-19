using System;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Core {
    public class Pointer : NativeClass {

        public Pointer() {
        }

        public Pointer(IntPtr ptr) : base(ptr) {
            Pointer_addReference(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Pointer_addReference(IntPtr _this);

        public void AddReference() {
            Pointer_addReference(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Pointer_release(IntPtr _this);

        public void Release() {
            Pointer_release(NativePtr);
        }

        protected override void DeleteObject() {
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern uint Pointer_getReferenceCount(IntPtr _this);

        [Browsable(false)]
        public uint ReferenceCount {
            get => Pointer_getReferenceCount(NativePtr);
        }
    }
}
