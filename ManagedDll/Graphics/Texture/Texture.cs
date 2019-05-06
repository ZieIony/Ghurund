using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Graphics.Texture {
    public class Texture: Resource.Resource {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Texture_new();

        protected override IntPtr NewObject() => Texture_new();


        public Texture() {
        }

        public Texture(IntPtr ptr) : base(ptr) {
        }
    }
}
