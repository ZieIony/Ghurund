using Ghurund.Managed.Collection;
using Ghurund.Managed.Game;
using System;
using System.ComponentModel;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Graphics {
    public class RenderStep: NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr RenderStep_new();

        protected override IntPtr NewObject() => RenderStep_new();


        public RenderStep() {
            Entities = new PointerList<Entity>(RenderStep_getEntities(NativePtr), p => Game.Entities.MakeEntity(p));
        }

        public RenderStep(IntPtr ptr) : base(ptr) {
            Entities = new PointerList<Entity>(RenderStep_getEntities(NativePtr), p => Game.Entities.MakeEntity(p));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr RenderStep_getEntities(IntPtr _this);

        [Browsable(false)]
        public PointerList<Entity> Entities {
            get; internal set;
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void RenderStep_setCamera(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Camera camera);

        public Camera Camera {
            set => RenderStep_setCamera(NativePtr, value);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void RenderStep_initParameters(IntPtr _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ParameterManager parameterManager);

        public void InitParameters(ParameterManager manager) {
            RenderStep_initParameters(NativePtr, manager);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr RenderStep_pick(IntPtr _this, Int2 mousePos);

        public Model Pick(Int2 mousePos) {
            IntPtr modelPtr = RenderStep_pick(NativePtr, mousePos);
            if (modelPtr == IntPtr.Zero)
                return null;
            return new Model(modelPtr);
        }

    }
}
