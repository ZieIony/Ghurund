using System;
using System.Windows;
using System.Windows.Input;
using Ghurund.Managed;
using Ghurund.Managed.Audio;
using Ghurund.Managed.Core;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Graphics.Shader;
using Ghurund.Managed.Physics;
using Ghurund.Managed.Resource;
using Ghurund.Managed.Script;

namespace Ghurund.Preview {
    public partial class MainWindow : Window {
        readonly Logger.LogCallback callback;

        readonly Graphics graphics;
        readonly ParameterManager parameterManager;
        readonly Audio audio;
        readonly ScriptEngine scriptEngine;
        readonly ResourceContext resourceContext;
        readonly ResourceManager resourceManager;
        readonly Physics physics;
        readonly Timer timer;

        Scene scene;

        public MainWindow() {
            InitializeComponent();

            string[] args = Environment.GetCommandLineArgs();
            if (args.Length < 2) {
                MessageBox.Show("you have to open a scene, a mesh, a model, a material or a shader");
                Application.Current.Shutdown();
                return;
            }

            callback = new Logger.LogCallback(log);
            Logger.Init(callback);

            string filePath = args[1];

            graphics = new Graphics();
            graphics.Init();
            audio = new Audio();
            parameterManager = new ParameterManager();
            timer = new Timer();
            scriptEngine = new ScriptEngine();
            scriptEngine.Init(timer);
            physics = new Physics();
            physics.Init();

            resourceManager = new ResourceManager();
            resourceContext = new ResourceContext(graphics, audio, parameterManager, scriptEngine, physics);
            sceneView.Init(resourceManager, resourceContext);

            loadFile(filePath);
        }

        private void loadFile(string filePath) {
            scene = new Scene();
            if (filePath.EndsWith("scene")) {
                scene.Load(resourceManager, resourceContext, filePath);
            } else if (filePath.EndsWith("hlsl")) {
                Shader shader = new Shader();
                shader.Load(resourceManager, resourceContext, filePath);
                Material material = new Material {
                    Shader = shader,
                    Valid = true
                };
                shader.Release();
                Model model = Models.MakeCube(resourceContext, material);
                model.Scale = new Float3(50, 50, 50);
                material.Release();
                scene.Entities.Add(model);
                model.Release();
            }
            sceneView.Scene = scene;
        }

        private void log(string log) {
            Console.WriteLine(log);
        }

        protected override void OnClosed(EventArgs e) {
            base.OnClosed(e);

            scene.Release();

            sceneView.Dispose();

            resourceManager.Dispose();
            resourceContext.Dispose();

            timer.Dispose();
            graphics.Dispose();
            audio.Dispose();
            parameterManager.Dispose();
            scriptEngine.Dispose();
            physics.Dispose();

            Graphics.reportLiveObjects();
        }

        protected override void OnKeyUp(KeyEventArgs e) {
            base.OnKeyUp(e);

            if (e.Key == Key.P)
                sceneView.Camera.Perspective = !sceneView.Camera.Perspective;
        }
    }
}
