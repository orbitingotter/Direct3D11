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

static const float specularIntensity = 0.6f;
static const float specularPower = 30.0f;

float4 main(float3 worldPos : Position, float3 camPos : CamPosition, float3 normal : Normal) : SV_Target
{
    const float3 vToL = lightPos - camPos;
    const float distToL = length(vToL);
    const float3 dirToL = vToL / distToL;

	// diffuse
    const float att = 1.0f / (attConst + attLin * distToL + attQuad * (distToL * distToL));
     float3 diffuse = diffuseColor * diffuseIntensity * att * max(0.0f, dot(dirToL, normal));
	// reflected light vector
    const float3 w = normal * dot(vToL, normal);
    const float3 r = w * 2.0f - vToL;
	// calculate specular intensity based on angle between viewing vector and reflection vector, narrow with power function
     float3 specular = att * (diffuseColor * diffuseIntensity) * specularIntensity *
                            pow(max(0.0f, dot(normalize(-r), normalize(camPos))), specularPower);
    //specular = float3(0.0f, 0.0f, 0.0f);
    //diffuse = float3(0.0f, 0.0f, 0.0f);

	// final color
    return float4(saturate((diffuse + ambient + specular) * materialColor), 1.0f);

}