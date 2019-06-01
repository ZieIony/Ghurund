using Ghurund.Managed.Script;
using System;
using System.Runtime.InteropServices;

namespace Ghurund.Managed.Resource {
    public class ResourceContext: NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ResourceContext_new(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Graphics.Graphics graphics,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Audio.Audio audio,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Game.ParameterManager parameterManager,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ScriptEngine scriptEngine,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Physics.Physics physics,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ResourceManager resourceManager);


        public Graphics.Graphics Graphics { get; set; }

        public Audio.Audio Audio { get; set; }

        public Game.ParameterManager ParameterManager { get; set; }

        public ScriptEngine ScriptEngine { get; set; }

        public Physics.Physics Physics { get; set; }

        public ResourceManager ResourceManager { get; set; }

        public ResourceContext(Graphics.Graphics graphics, Audio.Audio audio, Game.ParameterManager parameterManager, ScriptEngine scriptEngine, Physics.Physics physics, ResourceManager resourceManager) {
            NativePtr = ResourceContext_new(graphics, audio, parameterManager, scriptEngine, physics, resourceManager);
            Graphics = graphics;
            Audio = audio;
            ParameterManager = parameterManager;
            ScriptEngine = scriptEngine;
            Physics = physics;
            ResourceManager = resourceManager;
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr ResourceContext_init(IntPtr _this);

        public void Init() => ResourceContext_init(NativePtr);
    }
}
