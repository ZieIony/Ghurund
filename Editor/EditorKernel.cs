using System;
using Ghurund.Managed.Game;
using Ghurund.Managed.Resource;
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


            kernel.Bind<ParameterManager>().ToSelf().InSingletonScope();
            kernel.Bind<ResourceManager>().ToSelf().InSingletonScope();
            kernel.Bind<EditorSettings>().ToMethod(context => {
                return Controls.Workspace.Extensions.ReadFromBinaryFile<EditorSettings>(EditorSettings.EDITOR_SETTINGS_FILE_NAME)??new EditorSettings();
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