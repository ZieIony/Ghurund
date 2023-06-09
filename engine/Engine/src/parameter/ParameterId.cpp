#include "ghpch.h"

#include "ParameterId.h"

namespace Ghurund {
    const ParameterId ParameterId::VIEWPORT_SIZE = ParameterId(ParameterIdEnum::VIEWPORT_SIZE, "VIEWPORT_SIZE", "viewportSize", ParameterType::FLOAT2);
    const ParameterId ParameterId::OUTLINE_COLOR = ParameterId(ParameterIdEnum::OUTLINE_COLOR, "OUTLINE_COLOR", "outlineColor", ParameterType::COLOR);
    const ParameterId ParameterId::PARTY_COLOR = ParameterId(ParameterIdEnum::PARTY_COLOR, "PARTY_COLOR", "partyColor", ParameterType::COLOR);
    const ParameterId ParameterId::RANDOM = ParameterId(ParameterIdEnum::RANDOM, "RANDOM", "random", ParameterType::FLOAT);
    const ParameterId ParameterId::AMBIENT_LIGHT = ParameterId(ParameterIdEnum::AMBIENT_LIGHT, "AMBIENT_LIGHT", "ambientLight", ParameterType::COLOR);
    const ParameterId ParameterId::POSITION = ParameterId(ParameterIdEnum::POSITION, "POSITION", "position", ParameterType::FLOAT3);
    const ParameterId ParameterId::ROTATION = ParameterId(ParameterIdEnum::ROTATION, "ROTATION", "rotation", ParameterType::FLOAT3);
    const ParameterId ParameterId::SCALE = ParameterId(ParameterIdEnum::SCALE, "SCALE", "scale", ParameterType::FLOAT3);
    const ParameterId ParameterId::CAMERA_DIRECTION = ParameterId(ParameterIdEnum::CAMERA_DIRECTION, "CAMERA_DIRECTION", "cameraDirection", ParameterType::FLOAT3);
    const ParameterId ParameterId::CAMERA_POSITION = ParameterId(ParameterIdEnum::CAMERA_POSITION, "CAMERA_POSITION", "cameraPosition", ParameterType::FLOAT3);
    const ParameterId ParameterId::CAMERA_TARGET = ParameterId(ParameterIdEnum::CAMERA_TARGET, "CAMERA_TARGET", "cameraTarget", ParameterType::FLOAT3);
    const ParameterId ParameterId::CAMERA_UP = ParameterId(ParameterIdEnum::CAMERA_UP, "CAMERA_UP", "cameraUp", ParameterType::FLOAT3);
    const ParameterId ParameterId::CAMERA_RIGHT = ParameterId(ParameterIdEnum::CAMERA_RIGHT, "CAMERA_RIGHT", "cameraRight", ParameterType::FLOAT3);
    const ParameterId ParameterId::FOV = ParameterId(ParameterIdEnum::FOV, "FOV", "fov", ParameterType::FLOAT);
    const ParameterId ParameterId::ZNEAR = ParameterId(ParameterIdEnum::ZNEAR, "ZNEAR", "zNear", ParameterType::FLOAT);
    const ParameterId ParameterId::ZFAR = ParameterId(ParameterIdEnum::ZFAR, "ZFAR", "zFar", ParameterType::FLOAT);
    const ParameterId ParameterId::WORLD = ParameterId(ParameterIdEnum::WORLD, "WORLD", "world", ParameterType::MATRIX);
    const ParameterId ParameterId::WORLD_IT = ParameterId(ParameterIdEnum::WORLD_IT, "WORLD_IT", "worldIT", ParameterType::MATRIX);
    const ParameterId ParameterId::VIEW = ParameterId(ParameterIdEnum::VIEW, "VIEW", "view", ParameterType::MATRIX);
    const ParameterId ParameterId::PROJECTION = ParameterId(ParameterIdEnum::PROJECTION, "PROJECTION", "projection", ParameterType::MATRIX);
    const ParameterId ParameterId::VIEW_PROJECTION = ParameterId(ParameterIdEnum::VIEW_PROJECTION, "VIEW_PROJECTION", "viewProjection", ParameterType::MATRIX);
    const ParameterId ParameterId::VIEW_PROJECTION_INV = ParameterId(ParameterIdEnum::VIEW_PROJECTION_INV, "VIEW_PROJECTION_INV", "viewProjectionInv", ParameterType::MATRIX);
    const ParameterId ParameterId::DIFFUSE_TEXTURE = ParameterId(ParameterIdEnum::DIFFUSE_TEXTURE, "DIFFUSE_TEXTURE", "diffuseTexture", ParameterType::TEXTURE);
    const ParameterId ParameterId::SPECULAR_TEXTURE = ParameterId(ParameterIdEnum::SPECULAR_TEXTURE, "SPECULAR_TEXTURE", "specularTexture", ParameterType::TEXTURE);
    const ParameterId ParameterId::NORMAL_TEXTURE = ParameterId(ParameterIdEnum::NORMAL_TEXTURE, "NORMAL_TEXTURE", "normalTexture", ParameterType::TEXTURE);
}