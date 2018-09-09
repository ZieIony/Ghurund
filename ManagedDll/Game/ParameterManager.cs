using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Game {
    public class ParameterManager : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ParameterManager_new();

        protected override void newObject() => NativePtr = ParameterManager_new();

    }
}
