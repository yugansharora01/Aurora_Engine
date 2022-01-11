cbuffer CBuf
{
	float4 faceColors[8];
};

float4 main(float4 pos : SV_Position,uint tid : SV_PrimitiveID) : SV_TARGET
{
	return faceColors[(tid / 2) % 8];
}