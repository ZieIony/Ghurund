#pragma once

#include "graphics/mesh/Mesh.h"
#include "Material.h"
#include "graphics/mesh/CubeMesh.h"
#include "graphics/mesh/SphereMesh.h"
#include "resource/ResourceManager.h"
#include "game/Entity.h"
#include "game/ParameterProvider.h"

namespace Ghurund {
    class Model: public Entity {
    private:
        Mesh *mesh = nullptr;
        Material *material = nullptr;

        void finalize() {
            safeRelease(mesh);
            safeRelease(material);
        }

    protected:
        List<Entity*> entities;

        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, MemoryInputStream &stream, LoadOption options) override;
        virtual Status saveInternal(ResourceManager &resourceManager, MemoryOutputStream &stream, SaveOption options) const override;

    public:

        Model(){}

        Model(Mesh *mesh, Material *material) {
            setPointer(this->mesh, mesh);
            setPointer(this->material, material);
        }

        ~Model() {
            finalize();
        }

        virtual void invalidate() {
            finalize();
            __super::invalidate();
        }

        Mesh *getMesh() {
            return mesh;
        }

        void setMesh(Mesh *mesh) {
            this->mesh = mesh;
        }

        __declspec(property(get = getMesh, put = setMesh)) Mesh *Mesh;

        Material *getMaterial() {
            return material;
        }

        void setMaterial(Material *material) {
            setPointer(this->material, material);
        }

        __declspec(property(get = getMaterial, put = setMaterial)) Material *Material;

        virtual void initParameters(ParameterManager &parameterManager) override {
            material->initParameters(parameterManager);
        }

        virtual void updateParameters() override {
            material->updateParameters();
        }

        virtual Array<Parameter*> &getParameters() {
            return material->Parameters;
        }

        virtual bool isValid() const override {
            return material!=nullptr&&material->Valid&&mesh!=nullptr&&mesh->Valid&&__super::Valid;
        }

        void draw(CommandList &commandList) {
            material->set(commandList);
            mesh->draw(commandList);
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::MODEL;
        }

        virtual const Array<ResourceFormat> &getFormats() const override {
            static const Array<ResourceFormat> formats = {ResourceFormat::AUTO, ResourceFormat::MODEL};
            return formats;
        }

        virtual const ResourceFormat &getDefaultFormat() const override {
            return ResourceFormat::MODEL;
        }

        virtual void flatten(RenderingBatch &batch, XMFLOAT4X4 &transformation) override;

        virtual bool intersects(XMFLOAT3 &pos, XMFLOAT3 &dir) {
            return mesh->intersects(pos, dir);
        }

    };
}