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

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern int ResourceFormat_getValueCount();

        public static ResourceFormatNativeArray Values { get; } = new ResourceFormatNativeArray(ResourceFormat_getValues(), ResourceFormat_getValueCount());
    }

    public class ResourceFormatArray : Array<ResourceFormat> {
        public ResourceFormatArray(IntPtr ptr) : base(ptr) {
        }

        protected override ResourceFormat MakeItem(IntPtr p) {
            return new ResourceFormat(p);
        }
    }

    public class ResourceFormatNativeArray : NativeArray<ResourceFormat> {
        public ResourceFormatNativeArray(IntPtr ptr, int size) : base(ptr, size) {
        }

        protected override ResourceFormat MakeItem(IntPtr p) {
            return new ResourceFormat(p);
        }
    }
}