using System;
using System.Collections;
using System.Windows;
using System.Windows.Controls;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;

namespace Ghurund.Managed {
    public enum NavigationMode {
        Orbit, Pan, Zoom, Rotate
    }

    public enum CameraMode {
        Top, Side, Front, Default, Custom
    }

    public partial class SceneView: UserControl, IDisposable {

        private Point prevPos;
        private bool pressed = false;
        private float dist = 0;
        private static readonly float MAX_CLICK_DIST = 5;

        private Material invalidMaterial;
        private Scene editorScene;
        private SelectionModel selection;

        private RenderStep editorStep;
        private RenderStep sceneStep;

        public NavigationMode NavigationMode { get; set; }

        public static readonly RoutedEvent SelectionChangedEvent = EventManager.RegisterRoutedEvent("SelectionChanged", RoutingStrategy.Bubble, typeof(RoutedEventHandler), typeof(SceneView));

        public event RoutedEventHandler SelectionChanged {
            add { AddHandler(SelectionChangedEvent, value); }
            remove { RemoveHandler(SelectionChangedEvent, value); }
        }

        private Camera topCamera, sideCamera, frontCamera, defaultCamera, customCamera;

        private CameraMode cameraMode;
        public CameraMode CameraMode {
            get => cameraMode;
            set {
                cameraMode = value;
                switch (cameraMode) {
                    case CameraMode.Default:
                        renderView.Camera = defaultCamera;
                        sceneStep.Camera = defaultCamera;
                        editorStep.Camera = defaultCamera;
                        break;
                    case CameraMode.Front:
                        renderView.Camera = frontCamera;
                        sceneStep.Camera = frontCamera;
                        editorStep.Camera = frontCamera;
                        break;
                    case CameraMode.Side:
                        renderView.Camera = sideCamera;
                        sceneStep.Camera = sideCamera;
                        editorStep.Camera = sideCamera;
                        break;
                    case CameraMode.Top:
                        renderView.Camera = topCamera;
                        sceneStep.Camera = topCamera;
                        editorStep.Camera = topCamera;
                        break;
                    case CameraMode.Custom:
                        renderView.Camera = customCamera;
                        renderView.Camera = customCamera;
                        editorStep.Camera = customCamera;
                        break;
                }
            }
        }

        private Scene scene;
        public Scene Scene {
            get => scene;
            set {
                sceneStep.Entities.Clear();
                value?.AddReference();
                if (scene != null) {
                    removeListeners(new System.Collections.Generic.List<Entity>() { scene });
                    scene.Release();
                }
                scene = value;
                if (scene != null) {
                    sceneStep.Entities.Add(scene);
                    addListeners(new System.Collections.Generic.List<Entity>() { scene });
                }
            }
        }

        private void addListeners(IList list) {
            System.Collections.Generic.List<Entity> entities = new System.Collections.Generic.List<Entity>();
            foreach (Entity e in list)
                entities.Add(e);
            while (entities.Count > 0) {
                Entity entity = entities[0];
                entities.RemoveAt(0);
                entity.PropertyChanged += Entity_PropertyChanged;
                if (entity is Scene) {
                    foreach (Entity e in (entity as Scene).Entities)
                        entities.Add(e);
                    (entity as Scene).Entities.CollectionChanged += Entities_CollectionChanged;
                }
            }
        }

        private void removeListeners(IList list) {
            System.Collections.Generic.List<Entity> entities = new System.Collections.Generic.List<Entity>();
            foreach (Entity e in list)
                entities.Add(e);
            while (entities.Count > 0) {
                Entity entity = entities[0];
                entities.RemoveAt(0);
                entity.PropertyChanged -= Entity_PropertyChanged;
                if (entity is Scene) {
                    foreach (Entity e in (entity as Scene).Entities)
                        entities.Add(e);
                    (entity as Scene).Entities.CollectionChanged -= Entities_CollectionChanged;
                }
            }
        }

        private void Entities_CollectionChanged(object sender, System.Collections.Specialized.NotifyCollectionChangedEventArgs e) {
            if (e.OldItems != null)
                removeListeners(e.OldItems);
            if (e.NewItems != null)
                addListeners(e.NewItems);
        }

        private void Entity_PropertyChanged(object sender, System.ComponentModel.PropertyChangedEventArgs e) {
            Invalidate();
        }

        private Material overrideMaterial;
        public Material OverrideMaterial {
            get => overrideMaterial;
            set {
                value?.AddReference();
                overrideMaterial?.Release();
                overrideMaterial = value;
                sceneStep.OverrideMaterial = overrideMaterial;
            }
        }

        public Renderer Renderer { get => renderView.Renderer; }

        public Camera Camera {
            get => renderView.Camera;
            set {
                value?.AddReference();
                customCamera?.Release();
                customCamera = value;
                CameraMode = CameraMode.Custom;
            }
        }

        public System.Collections.Generic.List<Entity> SelectedEntities {
            get;
            set;
        } = new System.Collections.Generic.List<Entity>();

        public SceneView() {
            InitializeComponent();
        }

        private bool disposed = false;

        ~SceneView() {
            Dispose(false);
        }

        public void Dispose() {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing) {
            if (disposed)
                return;

            Uninit();

            disposed = true;
        }

        public void Init(ResourceManager resourceManager, ResourceContext resourceContext) {
            defaultCamera = new Camera();
            defaultCamera.InitParameters(resourceContext.ParameterManager);
            ResetCamera(CameraMode.Default);
            frontCamera = new Camera();
            frontCamera.InitParameters(resourceContext.ParameterManager);
            ResetCamera(CameraMode.Front);
            sideCamera = new Camera();
            sideCamera.InitParameters(resourceContext.ParameterManager);
            ResetCamera(CameraMode.Side);
            topCamera = new Camera();
            topCamera.InitParameters(resourceContext.ParameterManager);
            ResetCamera(CameraMode.Top);

            renderView.Init(resourceManager, resourceContext);

            editorScene = Scenes.MakeEditor(resourceManager, resourceContext);
            invalidMaterial = Materials.MakeInvalid(resourceManager, resourceContext);

            editorStep = new RenderStep {
                Camera = Camera
            };
            editorStep.Entities.Add(editorScene);
            editorStep.InitParameters(resourceContext.ParameterManager);
            Renderer.Steps.Add(editorStep);

            sceneStep = new RenderStep {
                Camera = Camera
            };
            sceneStep.InvalidMaterial = invalidMaterial;
            sceneStep.InitParameters(resourceContext.ParameterManager);
            Renderer.Steps.Add(sceneStep);

            selection = Models.MakeSelection(resourceManager, resourceContext);
            selection.Visible = false;
            editorScene.Entities.Add(selection);

            CameraMode = CameraMode.Default;    // just to update the current camera
        }

        public void Uninit() {
            renderView.Uninit();

            Scene = null;
            overrideMaterial?.Release();
            overrideMaterial = null;

            editorScene?.Release();
            editorScene = null;
            invalidMaterial?.Release();
            invalidMaterial = null;

            sideCamera?.Release();
            sideCamera = null;
            customCamera?.Release();
            customCamera = null;
            frontCamera?.Release();
            frontCamera = null;
            topCamera?.Release();
            topCamera = null;
            defaultCamera?.Release();
            defaultCamera = null;
        }

        public void Invalidate() {
            renderView.Invalidate();
        }

        public void ResetCamera() => ResetCamera(CameraMode);

        public void ResetCamera(CameraMode cameraMode) {
            switch (cameraMode) {
                case CameraMode.Default:
                    defaultCamera.Perspective = true;
                    defaultCamera.SetPositionTargetUp(new Float3(-400, 400, -400), new Float3(0, 0, 0), new Float3(0, 1, 0));   // TODO: automatic distance to cover the scene
                    break;
                case CameraMode.Front:
                    frontCamera.Perspective = false;
                    frontCamera.SetPositionTargetUp(new Float3(0, 0, -100), new Float3(0, 0, 0), new Float3(0, 1, 0));
                    break;
                case CameraMode.Side:
                    sideCamera.Perspective = false;
                    sideCamera.SetPositionTargetUp(new Float3(100, 0, 0), new Float3(0, 0, 0), new Float3(0, 1, 0));
                    break;
                case CameraMode.Top:
                    topCamera.Perspective = false;
                    topCamera.SetPositionTargetUp(new Float3(0, 100, 0), new Float3(0, 0, 0), new Float3(0, 0, 1));
                    break;
            }
        }

        private void renderView_MouseDown(object sender, System.Windows.Forms.MouseEventArgs e) {
            prevPos = new Point(e.X, e.Y);
            if (e.Button == System.Windows.Forms.MouseButtons.Left) {
                pressed = true;
                dist = 0;
            }
        }

        private void renderView_MouseMove(object sender, System.Windows.Forms.MouseEventArgs e) {
            var pos = new Point(e.X, e.Y);
            if (pressed) {
                var dx = pos.X - prevPos.X;
                var dy = -(pos.Y - prevPos.Y);
                dist += (float)Math.Sqrt(dx * dx + dy * dy);
                if (NavigationMode == NavigationMode.Orbit) {
                    renderView.Camera.Orbit((float)(dx / 5 * Math.PI / 180), (float)(dy / 5 * Math.PI / 180));
                } else if (NavigationMode == NavigationMode.Pan) {
                    renderView.Camera.Pan((float)dx, (float)-dy);
                } else if (NavigationMode == NavigationMode.Zoom) {
                    renderView.Camera.Zoom((float)dy);
                } else {
                    renderView.Camera.Rotate((float)(dx / 5 * Math.PI / 180), (float)(dy / 5 * Math.PI / 180));
                }
                Invalidate();
            }
            prevPos = pos;
        }

        private void renderView_MouseUp(object sender, System.Windows.Forms.MouseEventArgs e) {
            if (e.Button == System.Windows.Forms.MouseButtons.Left) {
                pressed = false;
                if (dist < MAX_CLICK_DIST) {
                    SelectedEntities.Clear();
                    Model model = sceneStep.Pick(new Int2 { X = (int)prevPos.X, Y = (int)prevPos.Y });
                    if (model != null) {
                        SelectedEntities.Add(model);
                        selection.Select(model);
                        selection.Visible = true;
                    } else {
                        selection.Visible = false;
                    }
                    Invalidate();
                    RaiseEvent(new RoutedEventArgs(SelectionChangedEvent, this));
                }
            }
        }

        public void SetMaterial(ResourceContext context, Material material) {
            Scene scene = new Scene();
            Model sphere = Models.MakeSphere(context, material);
            scene.Entities.Add(sphere);
            sphere.Release();
            Scene = scene;
            scene.Release();

            CameraMode = CameraMode.Default;
        }
    }
}
