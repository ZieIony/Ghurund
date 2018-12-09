using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;

namespace Ghurund.Managed.Graphics {
    public class Light : Entity {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Light_new();

        protected override IntPtr NewObject() => Light_new();

        public Light() { }

        public Light(IntPtr ptr) : base(ptr) { }
    }
}
