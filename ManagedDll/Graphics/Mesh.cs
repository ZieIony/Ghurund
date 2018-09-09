using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Graphics {
    public class Mesh:Resource.Resource {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Mesh_new();

        protected override void newObject() => NativePtr = Mesh_new();


        public Mesh() { }

        public Mesh(IntPtr ptr) : base(ptr) { }

    }
}