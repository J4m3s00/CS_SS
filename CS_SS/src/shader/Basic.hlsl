R"(struct VOut
{
	float4 position : SV_POSITION;
	float2 uv : TEXCOLOR;
};

cbuffer CBuf
{
	matrix projection;
	matrix model;
};

VOut VShader(float4 position : POSITION, float2 texCoord : TEXCOORD, float3 normal : NORMAL, float3 tangent : TANGENT, float3 binormal : BINORMAL)
{
	VOut output;

	output.position = mul(mul(position, model), projection);
	output.uv = texCoord;

	return output;
}


Texture2D tex;

SamplerState splr;

float4 PShader(float4 position : SV_POSITION, float2 uv : TEXCOORD) : SV_TARGET
{
	return tex.Sample(splr, uv);
}
)"