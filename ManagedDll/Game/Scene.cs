using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Game {
    public class Scene : Entity {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Scene_new();

        protected override void newObject() => NativePtr = Scene_new();
    }
}
