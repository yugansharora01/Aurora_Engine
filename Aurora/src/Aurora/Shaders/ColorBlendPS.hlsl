
struct MRI
{
	float4 color : SV_TARGET0;
	float id : SV_TARGET1;
};


float4 main(float4 color : Color,float id : ID)
{
	MRI m;
	m.color = color;
	m.id = id;
	return m;
}