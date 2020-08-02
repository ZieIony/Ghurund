using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Ghurund.Managed.Game;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Graphics {
    public class Camera : Entity {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Camera_new();

        protected override IntPtr NewObject() => Camera_new();


        public Camera() { }

        public Camera(IntPtr ptr) : base(ptr) { }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Camera_getTarget(IntPtr _this);

        public Float3 Target {
            get => Camera_getTarget(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Camera_getDirection(IntPtr _this);

        public Float3 Direction {
            get => Camera_getDirection(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 Camera_getUp(IntPtr _this);

        public Float3 Up {
            get => Camera_getUp(NativePtr);
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
        private static extern void Camera_setPositionDirectionDistanceUp(IntPtr _this, Float3 pos, Float3 dir, float dist, Float3 up);

        public void SetPositionDirectionDistanceUp(Float3 pos, Float3 dir, float dist, Float3 up) {
            Camera_setPositionDirectionDistanceUp(NativePtr, pos, dir, dist, up);
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


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Camera_getFormats();

        [Browsable(false)]
        public static Array<ResourceFormat> Formats { get; } = new Array<ResourceFormat>(Camera_getFormats(), ptr => new ResourceFormat(ptr));


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern bool Camera_getPerspective(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Camera_setPerspective(IntPtr _this, bool pers);

        public bool Perspective {
            get => Camera_getPerspective(NativePtr);
            set => Camera_setPerspective(NativePtr, value);
        }

    }
}
