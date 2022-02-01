#include "pch.h"
#include "Light.h"

namespace Aurora
{
    Light::Light(LightInfo info)
    {
        Position = info.Position;
        ambient = info.ambient;
        diffuseColor = info.diffuseColor;
        diffuseIntensity = info.diffuseIntensity;
        attConst = info.attConst;
        attLin = info.attLin;
        attQuad = info.attQuad;
        type = info.type;
    }
}