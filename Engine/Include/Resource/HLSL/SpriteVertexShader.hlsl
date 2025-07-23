cbuffer MatrixBuffer : register(b0)
{
    matrix viewProj;
};

struct VS_INPUT
{
    float3 Pos : POSITION;
    float2 UV : TEXCOORD;
};

struct VS_OUTPUT
{
    float4 Pos : SV_POSITION;
    float2 UV : TEXCOORD;
};

VS_OUTPUT SVSMain(VS_INPUT input)
{
    VS_OUTPUT output;
    output.Pos = mul(float4(input.Pos, 1.0f), viewProj);
    output.UV = input.UV;
    return output;
}
