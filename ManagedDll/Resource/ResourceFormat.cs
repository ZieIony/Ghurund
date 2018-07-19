using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Resource {
    public class ResourceFormat : NativeClass {
        public ResourceFormat(IntPtr ptr) : base(ptr) {
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))]
        private static extern String ResourceFormat_getExtension(IntPtr _this);

        public String Extension { get => ResourceFormat_getExtension(NativePtr); }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ResourceFormat_getValues();

        public static ResourceFormatArray Values { get; } = new ResourceFormatArray(ResourceFormat_getValues());
    }

    public class ResourceFormatArray : NativeArray<ResourceFormat> {
        public ResourceFormatArray(IntPtr ptr) : base(ptr) {
        }

        protected override ResourceFormat MakeItem(IntPtr p) {
            return new ResourceFormat(p);
        }
    }
}