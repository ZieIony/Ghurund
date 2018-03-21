using Ghurund.Managed.Resource;

namespace Ghurund.Managed {
    public class Material : IResource {
        public Material() {
            FileName = "unnamed material." + DefaultExtension;
        }

        public string FileName { get; set; }

        public string DefaultExtension {
            get {
                return "mtr";
            }
        }

        public bool load(ResourceManager resourceManager, string fileName) {
            throw new System.NotImplementedException();
        }

        public bool save(ResourceManager resourceManager, string fileName) {
            throw new System.NotImplementedException();
        }

        public PipelineState PipelineState { get; set; }

        public Shader VertexShader { get; set; }

        public Shader PixelShader { get; set; }
    }
}
