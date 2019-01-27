﻿using System;
using System.Runtime.InteropServices;
using Ghurund.Managed.Application;
using Ghurund.Managed.Game;

namespace Ghurund.Managed.Graphics {
    public class Renderer : NativeClass {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_new();

        protected override IntPtr NewObject() => Renderer_new();


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_init(IntPtr nativeRenderer, IntPtr graphics, IntPtr window);

        public void Init(Graphics graphics, Window window) {
            Renderer_init(NativePtr, graphics.NativePtr, window.NativePtr);
            Statistics = new RenderingStatistics(Renderer_getStatistics(NativePtr));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_startFrame(IntPtr nativeRenderer);

        public CommandList StartFrame() {
            return new CommandList(Renderer_startFrame(NativePtr));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_finishFrame(IntPtr nativeRenderer);

        public void FinishFrame() {
            Renderer_finishFrame(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_uninit(IntPtr nativeRenderer);

        public void Uninit() {
            Renderer_uninit(NativePtr);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_resize(IntPtr nativeRenderer, uint width, uint height);

        public void Resize(uint width, uint height) {
            Renderer_resize(NativePtr, width, height);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Renderer_draw(
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Renderer _this,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Camera camera,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Entity entity,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] ParameterManager parameterManager,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material overrideMaterial,
            [MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(NativeClassMarshaler))] Material invalidMaterial);

        public void Draw(Camera camera, Entity entity, ParameterManager parameterManager, Material overrideMaterial, Material invalidMaterial) {
            Renderer_draw(this, camera, entity, parameterManager, overrideMaterial, invalidMaterial);
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_setClearColor(IntPtr renderer, uint color);

        public uint ClearColor {
            set {
                Renderer_setClearColor(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Renderer_getStatistics(IntPtr renderer);

        public RenderingStatistics Statistics { get; private set; }
    }
}
