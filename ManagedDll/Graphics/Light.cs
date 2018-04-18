using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;

namespace Ghurund.Managed.Graphics {
    public class Light : Entity {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Light_new();

        protected override void newObject() => NativePtr = Light_new();

        private static int index = 0;

        public Light() {
            Name = "light" + index++;
        }
    }
}
