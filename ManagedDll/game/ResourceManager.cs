using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Game {
    public class ParameterManager : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ParameterManager_new(IntPtr graphics);

        public ParameterManager(Graphics.Graphics graphics) {
            NativePtr = ParameterManager_new(graphics.NativePtr);
        }

    }
}
