Texture2D tex : register(t0);
SamplerState samp : register(s0);

float4 SPSMain(float2 uv : TEXCOORD) : SV_TARGET
{
    return tex.Sample(samp, uv);
}
