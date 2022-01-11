cbuffer LightCBuf
{
    float3 lightPos;
    float3 materialColor;
    float3 diffuseColor;
    float padding;
    float diffuseIntensity;
    float attConst;
    float attLin;
    float attQuad;
};

static const float3 ambient = { 0.15f, 0.15f, 0.15f };

float4 main(float3 worldPos : Position, float3 n : Normal) : SV_TARGET
{
    //fragment to light vector data
    const float3 vToL = lightPos - worldPos;
    const float distToL = length(vToL);
    const float3 dirToL = vToL / distToL;
    //diffuse attenuation
    const float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));
    //diffuse intensity
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, n));
    //final Color
    return float4(saturate((diffuse + ambient) * materialColor), 1.0f);
    //return faceColors[(tid / 2) % 8];
}