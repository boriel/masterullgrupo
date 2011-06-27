struct PS_INPUT
{
   float2 texcoord0:     TEXCOORD0;
};

sampler RT;

// Size of a one texel offset, this is hardcoded to 256
// for simplicity and since RenderMonkey cannot allow you
// to know the size of a texture,
const float off = 0.1 / 256.0;
float4 PShader( float2 TexCoord : TEXCOORD0 ) : COLOR
{
	// Sample the neighbor pixels
	float s00 = tex2D(RT, TexCoord + float2(-off, -off));
	float s01 = tex2D(RT, TexCoord + float2( 0, -off));
	float s02 = tex2D(RT, TexCoord + float2( off, -off));
	float s10 = tex2D(RT, TexCoord + float2(-off, 0));
	float s12 = tex2D(RT, TexCoord + float2( off, 0));
	float s20 = tex2D(RT, TexCoord + float2(-off, off));
	float s21 = tex2D(RT, TexCoord + float2( 0, off));
	float s22 = tex2D(RT, TexCoord + float2( off, off));
	
	// Sobel filter in X and Y directions
	float sobelX = s00 + 2 * s10 + s20 - s02 - 2 * s12 - s22;
	float sobelY = s00 + 2 * s01 + s02 - s20 - 2 * s21 - s22;

	// Find edge using a threshold of 0.07 which is sufficient
	// to detect most edges.
	float edgeSqr = (sobelX * sobelX + sobelY * sobelY);
	return 1.0 -(edgeSqr > (0.07 * 0.07));
}

technique RenderScene
{
    pass p0
    {
        PixelShader = compile ps_2_0 PShader();
    }
}