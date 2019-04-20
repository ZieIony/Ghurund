#pragma once

#include "game/entity/TransformedEntity.h"
#include "game/parameter/ParameterProvider.h"
#include "graphics/mesh/Mesh.h"
#include "graphics/Material.h"
#include "graphics/mesh/CubeMesh.h"
#include "graphics/mesh/SphereMesh.h"
#include "graphics/RenderingStatistics.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class Model: public TransformedEntity {
    private:
        Mesh *mesh = nullptr;
        Material *material = nullptr;

        void finalize() {
            safeRelease(mesh);
            safeRelease(material);
        }

    protected:
        List<Entity*> entities;

        virtual Status loadInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryInputStream &stream, LoadOption options) override;
        virtual Status saveInternal(ResourceManager &resourceManager, ResourceContext &context, const DirectoryPath &workingDir, MemoryOutputStream &stream, SaveOption options) const override;

    public:

        Model(){}

        Model(Mesh *mesh, Material *material) {
            setPointer(this->mesh, mesh);
            setPointer(this->material, material);
        }

        ~Model() {
            finalize();
        }

        virtual void invalidate() override {
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

        virtual ::BoundingBox* getBoundingBox() const override {
            return &mesh->BoundingBox;
        }

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

        void draw(Graphics &graphics, CommandList &commandList) {
            material->set(graphics, commandList);
            mesh->draw(commandList);
        }

        void draw(Graphics &graphics, CommandList &commandList, RenderingStatistics &statistics) {
            if(material->set(graphics, commandList))
                statistics.materialChanges++;
            mesh->draw(commandList);
            statistics.modelsRendered++;
            statistics.trianglesRendered += mesh->IndexCount/3;
        }

        virtual const Ghurund::Type &getType() const override {
            return Type::MODEL;
        }

        static const Array<ResourceFormat*> &getFormats() {
            static const Array<ResourceFormat*> formats = {(ResourceFormat*)&ResourceFormat::MODEL};
            return formats;
        }

        __declspec(property(get = getFormats)) Array<ResourceFormat*> &Formats;

        virtual void flatten(RenderStep &step, XMFLOAT4X4 &transformation) override;

        virtual bool intersects(XMFLOAT3 &pos, XMFLOAT3 &dir, float &dist) {
            return mesh->intersects(pos, dir, dist);
        }

    };
}