using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Graphics;

namespace Ghurund.Managed.Game {
    public class Level : NativeClass {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Level_new();

        protected override IntPtr NewObject() => Level_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Level_delete(IntPtr _this);

        protected override void DeleteObject() {
            if (ptrOwner)
                Level_delete(NativePtr);
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Level_setCamera(IntPtr _this, IntPtr camera);

        public Camera Camera {
            set {
                Level_setCamera(NativePtr, value.NativePtr);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Level_setScene(IntPtr _this, IntPtr scene);

        public Scene Scene {
            set {
                Level_setScene(NativePtr, value != null ? value.NativePtr : IntPtr.Zero);
            }
        }

    }
}