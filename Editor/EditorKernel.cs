using System;
using System.IO;
using Ghurund.Editor.Panel;
using Ghurund.Editor.ResourceEditor;
using Ghurund.Managed.Audio;
using Ghurund.Managed.Game;
using Ghurund.Managed.Graphics;
using Ghurund.Managed.Resource;
using Ghurund.Managed.Script;
using Ninject;

namespace Ghurund.Editor {
    public sealed class EditorKernel {
        private static volatile EditorKernel instance;
        private static object syncRoot = new Object();

        public static EditorKernel Instance {
            get {
                if (instance == null) {
                    lock (syncRoot) {
                        if (instance == null)
                            instance = new EditorKernel();
                    }
                }

                return instance;
            }
        }




        IKernel kernel = new StandardKernel();

        private EditorKernel() {
            kernel.Bind<WelcomePage>().ToSelf().InSingletonScope();
            kernel.Bind<IWelcomePage>().ToMethod(context => context.Kernel.Get<WelcomePage>()).InSingletonScope();

            kernel.Bind<ProjectExplorerPanel>().ToSelf().InSingletonScope();
            kernel.Bind<IProjectExplorerPanel>().ToMethod(context => context.Kernel.Get<ProjectExplorerPanel>()).InSingletonScope();

            kernel.Bind<PropertiesPanel>().ToSelf().InSingletonScope();
            kernel.Bind<IPropertiesPanel>().ToMethod(context => context.Kernel.Get<PropertiesPanel>()).InSingletonScope();

            kernel.Bind<ParametersPanel>().ToSelf().InSingletonScope();
            kernel.Bind<IParametersPanel>().ToMethod(context => context.Kernel.Get<ParametersPanel>()).InSingletonScope();

            kernel.Bind<ResourceManagerPanel>().ToSelf().InSingletonScope();
            kernel.Bind<IResourceManagerPanel>().ToMethod(context => context.Kernel.Get<ResourceManagerPanel>()).InSingletonScope();

            kernel.Bind<SceneExplorerPanel>().ToSelf().InSingletonScope();
            kernel.Bind<ISceneExplorerPanel>().ToMethod(context => context.Kernel.Get<SceneExplorerPanel>()).InSingletonScope();

            kernel.Bind<StatisticsPanel>().ToSelf().InSingletonScope();
            kernel.Bind<IStatisticsPanel>().ToMethod(context => context.Kernel.Get<StatisticsPanel>()).InSingletonScope();

            kernel.Bind<LogPanel>().ToSelf().InSingletonScope();
            kernel.Bind<ILogPanel>().ToMethod(context => context.Kernel.Get<LogPanel>()).InSingletonScope();


            kernel.Bind<Graphics>().ToMethod(context => {
                Graphics graphics = new Graphics();
                graphics.Init();
                return graphics;
            }).InSingletonScope();
            kernel.Bind<Audio>().ToSelf().InSingletonScope();
            kernel.Bind<ParameterManager>().ToSelf().InSingletonScope();
            kernel.Bind<ResourceManager>().ToSelf().InSingletonScope();
            kernel.Bind<ResourceContext>().ToMethod(context => {
                return new ResourceContext(context.Kernel.Get<Graphics>(), context.Kernel.Get<Audio>(), context.Kernel.Get<ParameterManager>(), context.Kernel.Get<ScriptEngine>());
            }).InSingletonScope();
            kernel.Bind<EditorSettings>().ToMethod(context => {
                return Controls.Workspace.Extensions.ReadFromBinaryFile<EditorSettings>(EditorSettings.EDITOR_SETTINGS_FILE_NAME, new Type[] { typeof(SceneEditorState) }) ?? new EditorSettings();
            }).InSingletonScope();
            kernel.Bind<Managed.Core.Timer>().ToSelf().InSingletonScope();
            kernel.Bind<ScriptEngine>().ToMethod(context => {
                ScriptEngine scriptEngine = new ScriptEngine();
                scriptEngine.Init(context.Kernel.Get<Managed.Core.Timer>());
                return scriptEngine;
            }).InSingletonScope();
        }

        public void Inject(object target) {
            kernel.Inject(target);
        }

        public object GetService(Type type) {
            return kernel.GetService(type);
        }
    }
}