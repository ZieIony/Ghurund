#pragma once

#include "collection/String.h"
#include "core/NamedObject.h"
#include "game/parameter/ParameterProvider.h"
#include "game/parameter/ParameterManager.h"
#include "editor/ObservableObject.h"
#include "resource/Resource.h"
#include "script/Script.h"

#include <atomic>
#include <DirectXCollision.h>

namespace Ghurund {

    class RenderStep;

    typedef unsigned long id_t;

    class Entity: public Resource, public NamedObject, public ParameterProvider, public virtual ObservableObject {
    private:
        bool selectable = true, visible = true, editMode = false;
        id_t id = 0;
        static PointerList<Entity*> entities;
        static atomic<id_t> currentId;
        Script* script = nullptr;
        Entity* parent = nullptr;

        friend class EntityList;

    protected:
        mutable XMFLOAT4X4 world;

        virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
            world = stream.read<XMFLOAT4X4>();
            Name = stream.readUnicode();
            return Status::OK;
        }

        virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
            stream.write<XMFLOAT4X4>(world);
            stream.writeUnicode(Name);
            return Status::OK;
        }

    public:
        Entity() {
            id = currentId++;
            XMStoreFloat4x4(&world, XMMatrixIdentity());
        }

        id_t getId() const {
            return id;
        }

        __declspec(property(get = getId)) id_t Id;

        virtual void render(RenderStep& step, XMFLOAT4X4& transformation) = 0;

        virtual bool intersects(XMFLOAT3& pos, XMFLOAT3& dir, float& dist) {
            return false;
        }

        virtual BoundingBox* getBoundingBox() const {
            return nullptr;
        }

        __declspec(property(get = getBoundingBox)) BoundingBox* BoundingBox;

        void setSelectable(bool selectable) {
            this->selectable = selectable;
        }

        bool isSelectable() const {
            return selectable;
        }

        __declspec(property(get = isSelectable, put = setSelectable)) bool Selectable;

        void setVisible(bool visible) {
            this->visible = visible;
        }

        bool isVisible() const {
            return visible;
        }

        __declspec(property(get = isVisible, put = setVisible)) bool Visible;

        void setInEditMode(bool inEditMode) {
            this->editMode = inEditMode;
        }

        bool isInEditMode()const {
            return editMode;
        }

        __declspec(property(get = isInEditMode, put = setInEditMode)) bool InEditMode;

        static Entity* find(id_t id) {
            for (auto e : entities)
                if (e->Id == id)
                    return e;
            return nullptr;
        }

        static id_t getCurrentId() {
            return currentId;
        }

        inline Script* getScript() {
            return script;
        }

        inline void setScript(Script* script) {
            this->script = script;
        }

        __declspec(property(get = getScript, put = setScript)) Script* Script;

        inline Entity* getParent() const {
            return parent;
        }

        __declspec(property(get = getParent)) Entity* Parent;

        virtual XMFLOAT4X4& getTransformation() const {
            return world;
        }

        __declspec(property(get = getTransformation)) XMFLOAT4X4& Transformation;
    };

}