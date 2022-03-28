module;

#include "entity/camera/Camera.h"

#include <angelscript.h>

export module Ghurund.Engine.Script.Bindings.CameraScriptBindings;

import Ghurund.Engine.Script.Bindings.ScriptBindings;

export namespace Ghurund {

    class CameraScriptBindings:ScriptBindings<Camera> {
    public:
        static void registerClass(asIScriptEngine& engine) {
            ScriptBindings<Camera>::registerRefClass(engine, Camera::GET_TYPE().Name.Data);

            auto r = engine.RegisterObjectMethod(Camera::GET_TYPE().Name.Data, "bool getPerspective() const", asMETHOD(Camera, getPerspective), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::GET_TYPE().Name.Data, "void setPerspective(bool pers)", asMETHOD(Camera, setPerspective), asCALL_THISCALL); assert(r >= 0);

            r = engine.RegisterObjectMethod(Camera::GET_TYPE().Name.Data, "void setPositionTargetUp(const float3 pos, const float3 target, const float3 up = float3(0, 1, 0))", asMETHOD(Camera, setPositionTargetUp), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::GET_TYPE().Name.Data, "void setPositionDirectionDistanceUp(const float3 pos, const float3 dir, float dist = 1, const float3 up = float3(0, 1, 0))", asMETHOD(Camera, setPositionDirectionDistanceUp), asCALL_THISCALL); assert(r >= 0);

            r = engine.RegisterObjectMethod(Camera::GET_TYPE().Name.Data, "float3 getRotation() const", asMETHOD(Camera, getRotation), asCALL_THISCALL); assert(r >= 0);

            r = engine.RegisterObjectMethod(Camera::GET_TYPE().Name.Data, "void setRotation(float yaw, float pitch, float roll=0)", asMETHOD(Camera, setRotation), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::GET_TYPE().Name.Data, "void setOrbit(float yaw, float pitch, float roll=0)", asMETHOD(Camera, setOrbit), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::GET_TYPE().Name.Data, "void rotate(float yaw, float pitch, float roll=0)", asMETHOD(Camera, rotate), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::GET_TYPE().Name.Data, "void orbit(float yaw, float pitch, float roll=0)", asMETHOD(Camera, orbit), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::GET_TYPE().Name.Data, "void pan(float x, float y)", asMETHOD(Camera, pan), asCALL_THISCALL); assert(r >= 0);
            r = engine.RegisterObjectMethod(Camera::GET_TYPE().Name.Data, "void zoom(float z)", asMETHOD(Camera, zoom), asCALL_THISCALL); assert(r >= 0);
        }
    };

}