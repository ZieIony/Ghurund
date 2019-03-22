using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Ghurund.Managed.Core;

namespace Ghurund.Managed.Resource {
    public abstract class Resource: Pointer {

        public Resource() {
        }

        public Resource(IntPtr ptr) : base(ptr) {
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Status Resource_load(IntPtr _this, IntPtr manager, IntPtr context, [MarshalAs(UnmanagedType.LPWStr)] string fileName);

        public virtual Status Load(ResourceManager resourceManager, ResourceContext context, string fileName) {
            return Resource_load(NativePtr, resourceManager.NativePtr, context.NativePtr, fileName);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Status Resource_save(IntPtr _this, IntPtr manager, [MarshalAs(UnmanagedType.LPWStr)] string fileName);

        public virtual Status Save(ResourceManager resourceManager, string fileName) {
            return Resource_save(NativePtr, resourceManager.NativePtr, fileName);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Resource_getDefaultFormat(IntPtr _this);

        [Browsable(false)]
        public ResourceFormat DefaultFormat { get => new ResourceFormat(Resource_getDefaultFormat(NativePtr)); }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))]
        private static extern string Resource_getFileName(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Resource_setFileName(IntPtr _this, [MarshalAs(UnmanagedType.LPWStr)] string fileName);

        [Category("Common")]
        [Description("The name of the file this resource was saved to. Inline resources and newly created ones don't have a file name.")]
        public string FileName {
            get => Resource_getFileName(NativePtr);
            set => Resource_setFileName(NativePtr, value);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool Resource_isValid(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Resource_setValid(IntPtr _this, bool valid);

        [Browsable(false)]
        public bool Valid {
            get => Resource_isValid(NativePtr);
            set => Resource_setValid(NativePtr, value);
        }


        public override string ToString() {
            return FileName != null ? FileName.Substring(FileName.LastIndexOf("\\") + 1) : "[unnamed " + GetType().Name + "]";
        }

    }
}
