using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics.Mesh {
    public class Mesh : Resource.Resource {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Mesh_new();

        protected override IntPtr NewObject() => Mesh_new();


        public Mesh() {
        }

        public Mesh(IntPtr ptr) : base(ptr) { }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Mesh_getFormats();

        public static ResourceFormatArray Formats { get; } = new ResourceFormatArray(Mesh_getFormats());
    }
}