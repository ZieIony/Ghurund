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
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ScriptEngine scriptEngine);


        public Graphics.Graphics Graphics { get; set; }

        public Audio.Audio Audio { get; set; }

        public Game.ParameterManager ParameterManager { get; set; }

        public ScriptEngine ScriptEngine { get; set; }

        public ResourceContext(Graphics.Graphics graphics, Audio.Audio audio, Game.ParameterManager parameterManager, ScriptEngine scriptEngine) {
            NativePtr = ResourceContext_new(graphics, audio, parameterManager, scriptEngine);
            Graphics = graphics;
            Audio = audio;
            ParameterManager = parameterManager;
            ScriptEngine = scriptEngine;
        }
    }
}
