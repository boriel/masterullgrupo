//-----------------------------------------------------------------------------
// Variables del efecto
//-----------------------------------------------------------------------------

// Matriz WVP
float4x4 worldViewProj;
float4x4 matWorldInv;
float3 LightDirection = float3(0,1,0);
float AmbientIntensity = 0.6;

sampler2D Diffuse_0 = sampler_state {
	minFilter = LinearMipMapLinear;
	magFilter = Linear;
	AddressU = Repeat;
	AddressV = Repeat;
};

// Datos del vertice
struct VS_INPUT
{
    float3 position : POSITION;
	float2 tex0 	: TEXCOORD0;
	float3 normal 	: NORMAL;
};

// Datos de salida del vertex shader
struct VS_OUTPUT
{
    float4 position : POSITION;
	float2 tex0 : TEXCOORD0;
	float3 normal 	: TEXCOORD1;
	float3 Light : TEXCOORD2;
};

//-----------------------------------------------------------------------------
// Vertex Shader
//-----------------------------------------------------------------------------
VS_OUTPUT myvs( const VS_INPUT IN )
{
	VS_OUTPUT OUT;
	float4 position = float4(IN.position, 1.0);
	OUT.position = mul( worldViewProj, position );
	OUT.normal =  normalize(mul( float4(IN.normal, 0.0), matWorldInv ).xyz);
	OUT.Light = normalize(LightDirection);
	OUT.tex0 = IN.tex0;
	return OUT;
}


//-----------------------------------------------------------------------------
// Pixel Shader
//-----------------------------------------------------------------------------
float4 myps( VS_OUTPUT IN ): COLOR
{
	float lfLightIntensity = saturate(dot(IN.Light,IN.normal) + AmbientIntensity);
	float4 lColor = tex2D(Diffuse_0, IN.tex0);
	lColor = lColor * lfLightIntensity;
	return float4(lColor.xyz, 1.0);  
}

//-----------------------------------------------------------------------------
// Simple Effect (1 technique with 1 pass)
//-----------------------------------------------------------------------------
technique Technique0
{
    pass Pass0
    {
        Zenable  = true;
        CullFaceEnable = false;

        VertexShader = compile arbvp1 myvs();
        PixelShader  = compile arbfp1 myps();
    }
}
