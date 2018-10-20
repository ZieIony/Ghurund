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


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_setPositionTargetUp(IntPtr _this, Float3 pos, Float3 target, Float3 up);

        public void SetPositionTargetUp(Float3 pos, Float3 target, Float3 up) {
            Camera_setPositionTargetUp(NativePtr, pos, target, up);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_setPositionDirectionUp(IntPtr _this, Float3 pos, Float3 dir, Float3 up);

        public void SetPositionDirectionUp(Float3 pos, Float3 dir, Float3 up) {
            Camera_setPositionDirectionUp(NativePtr, pos, dir, up);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_rotate(IntPtr _this, float yaw, float pitch, float roll);

        public void Rotate(float yaw, float pitch, float roll) {
            Camera_rotate(NativePtr, yaw, pitch, roll);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_orbit(IntPtr _this, float yaw, float pitch, float roll);

        public void Orbit(float yaw, float pitch, float roll) {
            Camera_orbit(NativePtr, yaw, pitch, roll);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_pan(IntPtr _this, Float3 pan);

        public void Pan(Float3 pan) {
            Camera_pan(NativePtr, pan);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_setRotation(IntPtr _this, float yaw, float pitch, float roll);

        public void SetRotation(float yaw, float pitch, float roll) {
            Camera_setRotation(NativePtr, yaw, pitch, roll);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_setOrbit(IntPtr _this, float yaw, float pitch, float roll);

        public void SetOrbit(float yaw, float pitch, float roll) {
            Camera_setOrbit(NativePtr, yaw, pitch, roll);
        }

    }
}
