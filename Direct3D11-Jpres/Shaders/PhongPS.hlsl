cbuffer LightCBuf
{
    float3 lightPos;
};

static const float3 materialColor = { 0.7f, 0.7f, 0.9f };
static const float3 ambient = { 0.5f, 0.5f, 0.5f };
static const float3 diffuseColor = { 1.0f, 1.0f, 1.0f };
static const float diffuseIntensity = 1.0f;
static const float attConst = 1.0f;
static const float attLin = 0.045f;
static const float attQuad = 0.0075f;


float4 main(float3 worldPos : Position, float3 normal : Normal) : SV_Target
{
    const float3 vToL = lightPos - worldPos;
    const float distToL = length(vToL);
    const float3 dirToL = vToL / distToL;

    // diffuse attentuation
    const float att = 1.0f / (attQuad * (distToL * distToL) + attLin * distToL + attConst);
    // diffuse intensity
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, normal));
    // final color
    return float4(saturate(diffuse + ambient) * materialColor, 1.0f);

}