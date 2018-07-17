using Ghurund.Managed.Resource;

namespace Ghurund.Managed {
    public class Material : Resource.Resource {
        public Material() {
            FileName = "unnamed material.mtr";
        }

        public PipelineState PipelineState { get; set; }

        public Shader Shader { get; set; }
    }
}
