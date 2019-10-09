struct VOut
{
	float4 position : SV_POSITION;
	float4 color : COLOR;
};

cbuffer CBuf
{
	matrix projection;
};

VOut VShader(float4 position : POSITION, float2 texCoord : TEXCOORD, float3 normal : NORMAL, float3 tangent : TANGENT, float3 binormal : BINORMAL)
{
	VOut output;

	output.position = mul(position, projection);
	output.color = float4(0.8, 0.2, 0.3, 1.0);

	return output;
}


float4 PShader(float4 position : SV_POSITION, float4 color : COLOR) : SV_TARGET
{
	return color;
}
