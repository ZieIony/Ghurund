using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Resource {
    public class ResourceFormat : NativeClass {
        static ResourceFormat() {
            Values = new ResourceFormat[ResourceFormat_getValueCount()];
            IntPtr arrayPtr = ResourceFormat_getValues();
            for (int i = 0; i < Values.Length; i++)
                Values[i] = new ResourceFormat(NativeArrays.getArrayItem(arrayPtr, i));
        }

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

        public static ResourceFormat[] Values { get; }
    }
}