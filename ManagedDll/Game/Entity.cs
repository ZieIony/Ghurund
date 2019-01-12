using System;
using System.ComponentModel;
using System.Runtime.InteropServices;
using Ghurund.Managed.Collection;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed.Game {

    public abstract class Entity : Resource.Resource {

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
        private static extern IntPtr Entity_getParameters(IntPtr _this);

        [Browsable(false)]
        public ParameterArray Parameters {
            get; internal set;
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_initParameters(IntPtr _this, IntPtr parameterManager);

        public void InitParameters(ParameterManager manager) {
            Entity_initParameters(NativePtr, manager.NativePtr);
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void Entity_updateParameters(IntPtr _this);

        public void UpdateParameters() {
            Entity_updateParameters(NativePtr);
        }
    }

    public class EntityList : PointerList<Entity> {

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
                case "transformed entity":
                    return new TransformedEntity(p);
            }
            return null;    // TODO: should Entity be abstract?
        }
    }

    public class TransformedEntity : Entity {

        public TransformedEntity() {
        }

        public TransformedEntity(IntPtr ptr) : base(ptr) {
        }

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 TransformedEntity_getPosition(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void TransformedEntity_setPosition(IntPtr _this, Float3 position);

        [Category("Transformation")]
        [Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Position {
            get {
                return TransformedEntity_getPosition(NativePtr);
            }
            set {
                TransformedEntity_setPosition(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 TransformedEntity_getRotation(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void TransformedEntity_setRotation(IntPtr _this, Float3 rotation);

        [Category("Transformation")]
        [Description("Euler angles in radians. Maybe I should use degrees instead?")]
        [Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Rotation {
            get {
                return TransformedEntity_getRotation(NativePtr);
            }
            set {
                TransformedEntity_setRotation(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern Float3 TransformedEntity_getScale(IntPtr _this);

        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern void TransformedEntity_setScale(IntPtr _this, Float3 scale);

        [Category("Transformation")]
        [Description("Each value has to be > 0. For 100% scale use value = 1.0.")]
        [Editor(typeof(Float3UITypeEditor), typeof(System.Drawing.Design.UITypeEditor))]
        public Float3 Scale {
            get {
                return TransformedEntity_getScale(NativePtr);
            }
            set {
                TransformedEntity_setScale(NativePtr, value);
            }
        }


        [DllImport(@"NativeDll.dll", CallingConvention = CallingConvention.Cdecl)]
        private static extern IntPtr TransformedEntity_getFormats();

        public static ResourceFormatArray Formats { get; } = new ResourceFormatArray(TransformedEntity_getFormats());

    }
}
