cbuffer CBuf
{
    matrix model;
    matrix modelView;
    matrix modelViewProj;
};

struct VSOut
{
    float3 worldPos : Position;
    float3 camPos : CamPosition;
    float3 normal : Normal;
    float4 pos : SV_Position;
};

VSOut main(float3 pos : Position, float3 normal : Normal)
{
    VSOut vso;
    vso.worldPos = (float3) mul(float4(pos, 1.0f), model);
    vso.camPos = (float3) mul(float4(pos, 1.0f), modelView);
    vso.normal = mul(normal, (float3x3)modelView);
    vso.pos = mul(float4(pos, 1.0f), modelViewProj);

    return vso;
}