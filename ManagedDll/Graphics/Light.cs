using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics {
    public class Light : Entity {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Light_new();

        protected override IntPtr NewObject() => Light_new();

        public Light() { }

        public Light(IntPtr ptr) : base(ptr) { }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Light_getFormats();

        public static ResourceFormatArray Formats { get; } = new ResourceFormatArray(Light_getFormats());

    }
}
