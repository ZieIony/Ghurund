using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Core {
    public class Type : NativeClass {
        public Type(IntPtr ptr) : base(ptr) { }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))]
        private static extern String Type_getName(IntPtr _this);

        public String Name => Type_getName(NativePtr);

        public override string ToString() {
            return Name;
        }
    }
}
