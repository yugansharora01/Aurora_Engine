//cbuffer cbuf
//{
//	int2 mouse;
//};

cbuffer CBuf
{
	float4 faceColors[8];
};

//struct EntityID
//{
//	float EntityId;
//};

//AppendStructuredBuffer<EntityID> EntityIdbuf;

struct MRI
{
	float4 color : SV_TARGET0;
	float id : SV_TARGET1;
};

MRI main(float4 pos : SV_Position, float id : ID, uint tid : SV_PrimitiveID)
{
	MRI m;
	//int x = (int)pos.x;
	//int y = (int)pos.y;
	//if (x == mouse.x && y == mouse.y)
	//{
	//	EntityID eid;
	//	eid.EntityId = id;
	//	EntityIdbuf.Append(eid);
	//}

	m.color = faceColors[(tid / 2) % 8];
	m.id = id;
	return m;
}