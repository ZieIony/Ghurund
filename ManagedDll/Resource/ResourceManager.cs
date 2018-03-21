using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Resource {
    public class ResourceManager : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ResourceManager_new(IntPtr graphics, IntPtr parameterManager);

        public ResourceManager(Graphics.Graphics graphics, Game.ParameterManager parameterManager) {
            NativePtr = ResourceManager_new(graphics.NativePtr, parameterManager.NativePtr);
        }

    }
}
