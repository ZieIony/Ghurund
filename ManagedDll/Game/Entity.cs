using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Game {

    public abstract class Entity : Resource.Resource {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_delete(IntPtr _this);

        protected override void DeleteObject() => Entity_delete(NativePtr);


        public delegate void EntityChangeEventHandler(Object sender);
        public event EntityChangeEventHandler AfterChanged;

        public Entity() {
            Parameters = new ParameterArray(Entity_getParameters(NativePtr));
        }

        public Entity(IntPtr ptr) : base(ptr) {
            Parameters = new ParameterArray(Entity_getParameters(NativePtr));
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Entity_getType(IntPtr _this);

        [Category("Common")]
        [Description("Different types have different functions and can contain different children.")]
        public Core.Type Type => new Core.Type(Entity_getType(NativePtr));


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        [return: MarshalAs(UnmanagedType.CustomMarshaler, MarshalTypeRef = typeof(WCharStrMarshaler))]
        private static extern String Entity_getName(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_setName(IntPtr _this, [MarshalAs(UnmanagedType.LPWStr)] String name);

        [Category("Common")]
        [Description("This name will appear in scene explorer and in shaders.")]
        public String Name {
            get {
                return Entity_getName(NativePtr);
            }
            set {
                Entity_setName(NativePtr, value);
                AfterChanged?.Invoke(this);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern IntPtr Entity_getParameters(IntPtr _this);

        [Browsable(false)]
        public ParameterArray Parameters {
            get; internal set;
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Entity_initParameters(IntPtr _this, IntPtr parameterManager);

        public void InitParameters(ParameterManager manager) {
            Entity_initParameters(NativePtr, manager.NativePtr);
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        public static extern void Entity_updateParameters(IntPtr _this);

        public void UpdateParameters() {
            Entity_updateParameters(NativePtr);
        }
    }

    public class EntityList : List<Entity> {

        public EntityList(IntPtr ptr) : base(ptr) {
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr Entity_getType(IntPtr _this);

        protected override Entity MakeItem(IntPtr p) {
            var type = new Core.Type(Entity_getType(p));
            switch (type.Name.ToLower()) {
                case "camera":
                    return new Camera(p);
                case "light":
                    return new Light(p);
                case "model":
                    return new Model(p);
            }
            return null;    // TODO: should Entity be abstract?
        }
    }

    public class TransformedEntity : Entity {

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 TransformedObject_getPosition(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void TransformedObject_setPosition(IntPtr _this, Float3 position);

        [Category("Transformation")]
        [Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Position {
            get {
                return TransformedObject_getPosition(NativePtr);
            }
            set {
                TransformedObject_setPosition(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 TransformedObject_getRotation(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void TransformedObject_setRotation(IntPtr _this, Float3 rotation);

        [Category("Transformation")]
        [Description("Euler angles in radians. Maybe I should use degrees instead?")]
        [Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Rotation {
            get {
                return TransformedObject_getRotation(NativePtr);
            }
            set {
                TransformedObject_setRotation(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 TransformedObject_getScale(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void TransformedObject_setScale(IntPtr _this, Float3 scale);

        [Category("Transformation")]
        [Description("Each value has to be > 0. For 100% scale use value = 1.0.")]
        [Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Scale {
            get {
                return TransformedObject_getScale(NativePtr);
            }
            set {
                TransformedObject_setScale(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr TransformedEntity_getFormats();

        public static ResourceFormatArray Formats { get; } = new ResourceFormatArray(TransformedEntity_getFormats());

    }
}
