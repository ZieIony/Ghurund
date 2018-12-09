using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Resource {
    public class ResourceContext : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ResourceContext_new(IntPtr graphics, IntPtr audio, IntPtr parameterManager);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void ResourceContext_delete(IntPtr _this);

        protected override void DeleteObject() => ResourceContext_delete(NativePtr);


        public ResourceContext(Graphics.Graphics graphics, Audio.Audio audio, Game.ParameterManager parameterManager) {
            NativePtr = ResourceContext_new(graphics.NativePtr, audio.NativePtr, parameterManager.NativePtr);
        }
    }
}
