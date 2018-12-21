﻿using System;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Resource {
    public abstract class Resource : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Resource_delete(IntPtr _this);

        protected override void DeleteObject() {
            Resource_delete(NativePtr);
        }


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

        [Browsable(false)]
        public string FileName {
            get => Resource_getFileName(NativePtr);
            set => Resource_setFileName(NativePtr, value);
        }


        public override string ToString() {
            return FileName;
        }

    }
}
