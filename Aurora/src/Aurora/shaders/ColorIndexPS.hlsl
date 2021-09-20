cbuffer CBuf
{
	float4 faceColors[8];
};

float4 main(uint tid : SV_PrimitiveID) : SV_TARGET
{
	return faceColors[(tid / 2) % 8];
}