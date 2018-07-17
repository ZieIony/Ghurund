using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;

namespace Ghurund.Managed.Game {
    public class Target : Entity {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Target_new();

        protected override void newObject() => NativePtr = Target_new();

        public Target() { }

        public Target(IntPtr ptr) : base(ptr) { }
    }
}
