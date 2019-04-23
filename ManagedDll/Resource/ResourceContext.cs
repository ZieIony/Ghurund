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
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Physics.Physics physics);


        public Graphics.Graphics Graphics { get; set; }

        public Audio.Audio Audio { get; set; }

        public Game.ParameterManager ParameterManager { get; set; }

        public ScriptEngine ScriptEngine { get; set; }

        public Physics.Physics Physics { get; set; }

        public ResourceContext(Graphics.Graphics graphics, Audio.Audio audio, Game.ParameterManager parameterManager, ScriptEngine scriptEngine, Physics.Physics physics) {
            NativePtr = ResourceContext_new(graphics, audio, parameterManager, scriptEngine, physics);
            Graphics = graphics;
            Audio = audio;
            ParameterManager = parameterManager;
            ScriptEngine = scriptEngine;
            Physics = physics;
        }
    }
}
