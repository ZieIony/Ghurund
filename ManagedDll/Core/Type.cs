using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Core {
    public class Type : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Type_delete(IntPtr _this);

        protected override void DeleteObject() {
            if(ptrOwner)
                Type_delete(NativePtr);
        }

        public Type(IntPtr ptr) : base(ptr) { }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(CharStrMarshaler))]
        private static extern string Type_getName(IntPtr _this);

        public string Name => Type_getName(NativePtr);

        public override string ToString() {
            return Name;
        }
    }
}
