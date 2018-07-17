using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;

namespace Ghurund.Managed.Graphics {
    public class Camera : Entity {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Camera_new();

        protected override void newObject() => NativePtr = Camera_new();

        public Camera() { }

        public Camera(IntPtr ptr) : base(ptr) { }
    }
}
