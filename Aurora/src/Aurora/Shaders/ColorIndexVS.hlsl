cbuffer CBuf
{
	matrix transform;
};

struct VSOut
{
	float4 pos : SV_Position;
};

VSOut main(float3 pos : Position)
{
	VSOut vso;
	vso.pos = mul(float4(pos, 1.0f), transform);
	return vso;
}