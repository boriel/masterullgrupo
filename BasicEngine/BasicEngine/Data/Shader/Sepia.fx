// Sepia.fx 

// ###################
// ##### GLOBALS #####
float3 ImageTone = {0.815,0.666,0};
float3 DarkTone = {0.313,0.258,0};
float3 GreyTransfer = {0.3,0.59,0.11};

// absolute alpha value returned for the pixel color
float GlobalAlpha
<
    string UIWidget = "slider";
    string UIMin = "0.0";
    string UIMax = "1.0";
    string UIStep = "0.1";
    string UIName = "Global Alpha";
> = 1.0;

float Desaturation
<
    string UIWidget = "slider";
    string UIMin = "0.0";
    string UIMax = "1.0";
    string UIStep = "0.1";
    string UIName = "Desaturation";
> = 1.0f;

float Toning
<
    string UIWidget = "slider";
    string UIMin = "0.0";
    string UIMax = "1.0";
    string UIStep = "0.05";
    string UIName = "Toning";
> = 0.35f;


// #######################
// ##### PARAMENTERS #####

sampler samplerState;

// Main pass pixel shader
struct PixelShaderInput
{
	float2 TexCoord        : TEXCOORD0; // interpolated texture coordinates
};


// #######################
// ##### PIXELSHADER #####

// Main pass pixel shader
float4 PixelShader(PixelShaderInput input) : COLOR0
{
  	float3 pixelColor = tex2D(samplerState, input.TexCoord);
    
    float3 scene = pixelColor * ImageTone;
	
	float grey = dot(GreyTransfer, scene);
	float3 muted = lerp(scene, grey.xxx, Desaturation);
	float3 sepia = lerp(DarkTone, ImageTone, grey);
	pixelColor = lerp(muted, sepia, Toning);
  
  	// return final pixel color
  	return float4(pixelColor, GlobalAlpha);
}

technique Sepia {
		pass P0{ 
			PixelShader = compile ps_2_0 PixelShader(); 
		}
}