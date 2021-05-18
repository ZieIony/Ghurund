#include "core/reflection/TypeBuilder.h"
#include "core/reflection/TypedProperty.h"

#define reflection_a4b79cbf_50fe_4728_bfbe_1ab44dd54d18 protected:\
static const Ghurund::Type& GET_TYPE() {\
static auto PROPERTY_DEVICE = Ghurund::TypedProperty<Graphics, ID3D12Device*>("ID3D12Device*", "Device", (ID3D12Device*(Graphics::*)())&getDevice);\
static auto PROPERTY_DIRECTQUEUE = Ghurund::TypedProperty<Graphics, ID3D12CommandQueue*>("ID3D12CommandQueue*", "DirectQueue", (ID3D12CommandQueue*(Graphics::*)())&getDirectQueue);\
static auto PROPERTY_COMPUTEQUEUE = Ghurund::TypedProperty<Graphics, ID3D12CommandQueue*>("ID3D12CommandQueue*", "ComputeQueue", (ID3D12CommandQueue*(Graphics::*)())&getComputeQueue);\
static auto PROPERTY_COPYQUEUE = Ghurund::TypedProperty<Graphics, ID3D12CommandQueue*>("ID3D12CommandQueue*", "CopyQueue", (ID3D12CommandQueue*(Graphics::*)())&getCopyQueue);\
static auto PROPERTY_FACTORY = Ghurund::TypedProperty<Graphics, IDXGIFactory4*>("IDXGIFactory4*", "Factory", (IDXGIFactory4*(Graphics::*)())&getFactory);\
static auto PROPERTY_DESCRIPTORALLOCATOR = Ghurund::TypedProperty<Graphics, Ghurund::DescriptorAllocator&>("Ghurund::DescriptorAllocator&", "DescriptorAllocator", (Ghurund::DescriptorAllocator&(Graphics::*)())&getDescriptorAllocator);\
static auto PROPERTY_RESOURCEFACTORY = Ghurund::TypedProperty<Graphics, GPUResourceFactory&>("GPUResourceFactory&", "ResourceFactory", (GPUResourceFactory&(Graphics::*)())&getResourceFactory);\
\
static const auto CONSTRUCTOR = Ghurund::NoArgsConstructor<Graphics>();\
\
static const Ghurund::Type TYPE = Ghurund::TypeBuilder("Ghurund", "Graphics")\
.withProperty(PROPERTY_DEVICE)\
.withProperty(PROPERTY_DIRECTQUEUE)\
.withProperty(PROPERTY_COMPUTEQUEUE)\
.withProperty(PROPERTY_COPYQUEUE)\
.withProperty(PROPERTY_FACTORY)\
.withProperty(PROPERTY_DESCRIPTORALLOCATOR)\
.withProperty(PROPERTY_RESOURCEFACTORY)\
.withConstructor(CONSTRUCTOR)\
.withSupertype(__super::GET_TYPE());\
\
return TYPE;\
}\
\
public:\
inline static const Ghurund::Type& TYPE = GET_TYPE();\
\
virtual const Ghurund::Type& getType() const override {\
return TYPE;\
}
