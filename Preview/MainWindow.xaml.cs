using System;
using System.Windows;
using System.Windows.Input;
using Ghurund.Managed;
using Ghurund.Managed.Audio;
using Ghurund.Managed.Core;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Graphics.Shader;
using Ghurund.Managed.Resource;

namespace Ghurund.Preview {
    public partial class MainWindow : Window {
        Logger.LogCallback callback;

        Graphics graphics;
        ParameterManager parameterManager;
        Audio audio;
        ResourceContext resourceContext;
        ResourceManager resourceManager;
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
            audio = new Audio();
            parameterManager = new ParameterManager();

            resourceManager = new ResourceManager();
            resourceContext = new ResourceContext(graphics, audio, parameterManager);
            sceneView.Init(resourceManager, resourceContext);

            scene = new Scene();
            if (filePath.EndsWith("scene")) {
                scene.Load(resourceManager, resourceContext, filePath);
            }else if (filePath.EndsWith("hlsl")) {
                Shader shader = new Shader();
                shader.Load(resourceManager, resourceContext, filePath);
                Material material = new Material {
                    Shader = shader,
                    Valid = true
                };
                shader.Dispose();
                shader = null;
                TransformedEntity model = Models.MakeCube(resourceContext, material);
                model.Scale = new Float3(50, 50, 50);
                material.Dispose();
                material = null;
                scene.Entities.Add(model);
                model.Dispose();
                model = null;
            }
            sceneView.Scene = scene;
        }

        private void log(string log) {
            Console.WriteLine(log);
        }

        protected override void OnClosed(EventArgs e) {
            base.OnClosed(e);

            scene.Dispose();

            sceneView.Dispose();

            resourceManager.Dispose();
            resourceContext.Dispose();

            graphics.Dispose();
            audio.Dispose();
            parameterManager.Dispose();

            Graphics.reportLiveObjects();
        }

        protected override void OnKeyUp(KeyEventArgs e) {
            base.OnKeyUp(e);

            if (e.Key == Key.P) {
                sceneView.Camera.Perspective = !sceneView.Camera.Perspective;
                sceneView.Refresh();
            }
        }
    }
}
