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
	float4 color : Color;
	float4 pos : SV_Position;
	float EntityId : ID;
};



VSOut main( float3 pos : POSITION,float4 color : Color )
{
	VSOut vso;
	vso.pos = mul(float4(pos, 1.0f), transform);
	vso.color = color;
	vso.EntityId = id;
	return vso;
}