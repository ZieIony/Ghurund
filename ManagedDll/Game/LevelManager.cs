using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Graphics;

namespace Ghurund.Managed.Game {
    public class LevelManager : NativeClass {
        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr LevelManager_new();

        protected override IntPtr NewObject() => LevelManager_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void LevelManager_delete(IntPtr _this);

        protected override void DeleteObject() => LevelManager_delete(NativePtr);


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void LevelManager_setLevel(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Level level);

        public Level Level {
            set {
                LevelManager_setLevel(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void LevelManager_draw(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] CommandList commandList);

        public void Draw(CommandList commandList) {
            LevelManager_draw(NativePtr, commandList);
        }
    }
}
