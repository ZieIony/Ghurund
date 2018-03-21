namespace Ghurund.Managed.Resource {
    public interface IResource {
        string FileName { get; set; }

        string DefaultExtension { get; }

        bool load(ResourceManager resourceManager, string fileName);

        bool save(ResourceManager resourceManager, string fileName);
    }
}
