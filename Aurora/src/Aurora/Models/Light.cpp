#include "pch.h"
#include "Light.h"

namespace Aurora
{
    Light::Light(LightInfo info)
    {
        Set(info);
    }
    void Light::Set(LightInfo other)
    {
        Position = other.Position;
        ambient = other.ambient;
        diffuseColor = other.diffuseColor;
        diffuseIntensity = other.diffuseIntensity;
        attConst = other.attConst;
        attLin = other.attLin;
        attQuad = other.attQuad;
        type = other.type;
    }
}