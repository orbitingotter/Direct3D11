cbuffer LightCBuf
{
    float3 lightPos;
    float3 materialColor;
    float3 ambient;
    float3 diffuseColor;
    float diffuseIntensity;
    float attConst;
    float attLin;
    float attQuad;
};

static const float specualarIntensity = 0.8f;
static const float specualarPower = 50.0f;

float4 main(float3 worldPos : Position, float3 camPos : CamPosition, float3 normal : Normal) : SV_Target
{
    const float3 vToL = lightPos - worldPos;
    const float distToL = length(vToL);
    const float3 dirToL = vToL / distToL;

    // diffuse attentuation
    const float att = 1.0f / (attQuad * (distToL * distToL) + attLin * distToL + attConst);
    // diffuse intensity
    const float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, normal));
    // specular
    const float3 r = reflect(lightPos - worldPos, normal);
    const float3 specular = diffuseColor * diffuseIntensity * specualarIntensity *
                            pow(max(0.0f, dot(normalize(r), normalize(camPos))), specualarPower);
    // final color
    return float4(saturate(ambient + diffuse + specular) * materialColor, 1.0f);

}