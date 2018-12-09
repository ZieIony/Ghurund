using System;
using System.Windows;
using Ghurund.Managed.Audio;
using Ghurund.Managed.Core;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;

namespace Ghurund.Preview {
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
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
            parameterManager = new ParameterManager();

            surfaceView.Init(graphics, parameterManager);

            audio = new Audio();
            resourceContext = new ResourceContext(graphics, audio, parameterManager);
            resourceManager = new ResourceManager();
            scene = new Scene();
            scene.Load(resourceManager, resourceContext, filePath);
            surfaceView.Scene = scene;
        }

        private void log(string log) {
            Console.WriteLine(log);
        }

        protected override void OnClosed(EventArgs e) {
            base.OnClosed(e);

            scene.Dispose();
            resourceManager.Dispose();
            resourceContext.Dispose();
            audio.Dispose();

            surfaceView.Uninit();

            graphics.Dispose();
            parameterManager.Dispose();

            Graphics.reportLiveObjects();
        }
    }
}
