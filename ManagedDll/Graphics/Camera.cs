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


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_initParameters(IntPtr _this, IntPtr parameterManager);

        public void InitParameters(ParameterManager parameterManager) {
            Camera_initParameters(NativePtr, parameterManager.NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_setScreenSize(IntPtr _this, uint width, uint height);

        public void SetScreenSize(uint width, uint height) {
            Camera_setScreenSize(NativePtr, width, height);
        }
    }
}
