#include "Renderer.h"

namespace Ghurund {
    void Renderer::draw(Camera & camera, Entity & entity, ParameterManager & parameterManager) {
        RenderingBatch batch;
        batch.initParameters(parameterManager);
        XMFLOAT4X4 identity;
        XMStoreFloat4x4(&identity, XMMatrixIdentity());
        entity.flatten(batch, identity);
        batch.cull(camera);
        //onPreDraw(batch);
        CommandList &commandList = swapChain->CommandList;
        batch.draw(*graphics, commandList, parameterManager, material
#if defined(_DEBUG) || defined(GHURUND_EDITOR)
                   , invalidMaterial
#endif
        );
        batch.clear();
    }
}