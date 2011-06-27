float4x4 World;
float4x4 View;
float4x4 Projection;

float3 LightDirection = normalize(float3(1, 1, 1));

float Offset;

float EdgeWidth = 1.0f;
float EdgeMovAmount = 2.0f;

texture Texture;

sampler ModelTextureSampler = sampler_state
{
    Texture = <Texture>;

    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
    AddressU = Clamp;
    AddressV = Clamp;
};

texture Intesity;

sampler IntesitySampler = sampler_state
{
    Texture = <Intesity>;

    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
    AddressU = Clamp;
    AddressV = Clamp;
};


texture RandomTex;

sampler RandomSampler = sampler_state
{
    Texture = <RandomTex>;

    MinFilter = Linear;
    MagFilter = Linear;
    MipFilter = Linear;
    AddressU = Wrap;
    AddressV = Wrap;
};



struct VertexShaderInput
{
    float4 Position				: POSITION0;
    float4 Color				: COLOR0;
    float3 Normal				: NORMAL0;
    float2 TextureCoordinate	: TEXCOORD0;
};

struct NormalDepthVertexShaderOutput
{
    float4 Position				: POSITION0;
    float4 Color				: COLOR0;
};

struct LightingVertexShaderOutput
{
    float4 Position				: POSITION0;
    float4 Color				: COLOR0;
    float2 TextureCoordinate	: TEXCOORD0;
    float LightAmount			: TEXCOORD1;
    float4 Position3D			: TEXCOORD2;
};

struct LightingPixelShaderInput
{
	float4 Color				: COLOR0;
    float2 TextureCoordinate	: TEXCOORD0;
    float LightAmount			: TEXCOORD1;
    float4 Position3D			: TEXCOORD2;
};

//---------------------
// Vertex shaders
//---------------------

NormalDepthVertexShaderOutput NormalDepthVertexShader(VertexShaderInput input)
{
    NormalDepthVertexShaderOutput output;

    // Apply camera matrices to the input position.
    output.Position = mul(mul(mul(input.Position, World), View), Projection);
    
    float3 worldNormal = mul(input.Normal, World);

    // The output color holds the normal, scaled to fit into a 0 to 1 range.
    output.Color.rg = (worldNormal.xy + 1) / 2;
    
    // The output blue color holds the amount of light
    output.Color.b = dot(worldNormal, LightDirection);

    // The output alpha holds the depth, scaled to fit into a 0 to 1 range.
    output.Color.a = output.Position.z / output.Position.w;
    
    return output;    
}

LightingVertexShaderOutput LightingVertexShader(VertexShaderInput input)
{
    LightingVertexShaderOutput output;

    // Apply camera matrices to the input position.
    output.Position = mul(mul(mul(input.Position, World), View), Projection);
    output.Position3D = output.Position;
    
    // Copy across the input texture coordinate.
    output.TextureCoordinate = input.TextureCoordinate;

    // Compute the overall lighting brightness.
    float3 worldNormal = mul(input.Normal, World);
    
    output.LightAmount = dot(worldNormal, LightDirection);
    
    output.Color = input.Color;
    
    return output;
}

LightingVertexShaderOutput BlackVertexShader(VertexShaderInput input)
{
    LightingVertexShaderOutput output = (LightingVertexShaderOutput)0;
    
    // Compute the overall lighting brightness.
    float3 worldNormal = mul(input.Normal, World);

    // Apply camera matrices to the input position.
    float4 worldPosition = mul(input.Position, World);
    worldPosition = worldPosition + float4(worldNormal,0) * EdgeWidth;
    worldPosition = worldPosition + float4(worldNormal,0) * 
		EdgeMovAmount * 
		tex2Dlod(RandomSampler, float4(worldPosition.x, worldPosition.z,0,0) + Offset).r;
    output.Position = mul(mul(worldPosition, View), Projection);
     
    return output;
}


//---------------------
// Pixel shaders
//---------------------

float4 NormalDepthPixelShader(float4 color : COLOR0) : COLOR0
{
	float4 finalColor = color;
	color.b = tex2D(IntesitySampler, float2(color.b,0.0)).r;
    return color;
}

float4 ToonPixelShader(LightingPixelShaderInput input, uniform bool toon) : COLOR0
{
    float4 color = tex2D(ModelTextureSampler, input.TextureCoordinate);
        
    if(toon)
    {
		float intensity = tex2D(IntesitySampler, float2(input.LightAmount,0.0));              
		color.rgb *= intensity;
    }
    else
		color.rgb = color.rgb * 0.5 * input.LightAmount + 0.5 * color.rgb;
    
    return color;
}

float4 BlackPixelShader(LightingPixelShaderInput input) : COLOR0
{
    return 0;
}

//---------------------
// Technique
//---------------------

technique NormalDepth
{
    pass P0
    {
        VertexShader = compile vs_1_1 NormalDepthVertexShader();
        PixelShader = compile ps_2_0 NormalDepthPixelShader();
    }
}

//technique Toon
technique Technique0
{
    pass P0
    {
        VertexShader = compile vs_1_1 LightingVertexShader();
        PixelShader = compile ps_2_0 ToonPixelShader(true);
    }
}

technique Lambert
{
    pass P0
    {
        VertexShader = compile vs_1_1 LightingVertexShader();
        PixelShader = compile ps_2_0 ToonPixelShader(false);
    }
}

technique Black
{
    pass P0
    {
        VertexShader = compile vs_3_0 BlackVertexShader();
        PixelShader = compile ps_1_1 BlackPixelShader();
    }
}
