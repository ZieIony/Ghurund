using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;

namespace Ghurund.Managed.Graphics {
    public class Camera : Entity {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Camera_new();

        protected override IntPtr NewObject() => Camera_new();


        public Camera() { }

        public Camera(IntPtr ptr) : base(ptr) { }


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
        private static extern void Camera_setPositionDistanceRotation(IntPtr _this, Float3 pos, float dist, float yaw, float pitch, float roll);

        public void SetPositionDistanceRotation(Float3 pos, float dist, float yaw, float pitch, float roll = 0.0f) {
            Camera_setPositionDistanceRotation(NativePtr, pos, dist, yaw, pitch, roll);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_setTargetDistanceOrbit(IntPtr _this, Float3 target, float dist, float yaw, float pitch, float roll);

        public void SetTargetDistanceOrbit(Float3 target, float dist, float yaw, float pitch, float roll = 0.0f) {
            Camera_setTargetDistanceOrbit(NativePtr, target, dist, yaw, pitch, roll);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_setRotation(IntPtr _this, float yaw, float pitch, float roll);

        public void SetRotation(float yaw, float pitch, float roll = 0.0f) {
            Camera_setRotation(NativePtr, yaw, pitch, roll);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_setOrbit(IntPtr _this, float yaw, float pitch, float roll);

        public void SetOrbit(float yaw, float pitch, float roll = 0.0f) {
            Camera_setOrbit(NativePtr, yaw, pitch, roll);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_rotate(IntPtr _this, float yaw, float pitch, float roll);

        public void Rotate(float yaw, float pitch, float roll = 0.0f) {
            Camera_rotate(NativePtr, yaw, pitch, roll);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_orbit(IntPtr _this, float yaw, float pitch, float roll);

        public void Orbit(float yaw, float pitch, float roll = 0.0f) {
            Camera_orbit(NativePtr, yaw, pitch, roll);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_pan(IntPtr _this, float x, float y);

        public void Pan(float x, float y) {
            Camera_pan(NativePtr, x, y);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_zoom(IntPtr _this, float z);

        public void Zoom(float z) {
            Camera_zoom(NativePtr, z);
        }

    }
}
