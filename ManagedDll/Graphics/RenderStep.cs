using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Graphics {
    public class RenderStep : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr RenderStep_new();

        protected override IntPtr NewObject() => RenderStep_new();


        public RenderStep() {
        }

        public RenderStep(IntPtr ptr) : base(ptr) {
        }
    }
}
