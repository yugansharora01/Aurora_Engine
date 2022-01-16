cbuffer CBuf
{
	float4 color;
};

float4 main(float4 pos : SV_Position,uint tid : SV_PrimitiveID) : SV_TARGET
{
	return color;
}