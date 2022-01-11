cbuffer CBuf
{
	matrix transform;
};

cbuffer cbuf
{
	float id;
};

struct VSOut
{
	float4 pos : SV_Position;
	float EntityId : ID;
};

VSOut main(float3 pos : Position)
{
	VSOut vso;
	vso.pos = mul(float4(pos, 1.0f), transform);
	vso.EntityId = id;
	return vso;
}