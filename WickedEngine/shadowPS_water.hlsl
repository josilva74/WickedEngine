#include "globals.hlsli"
#include "objectHF.hlsli"

struct VertextoPixel
{
	float4 pos				: SV_POSITION;
	float4 color			: COLOR;
	float4 uvsets			: UVSETS;
};

float4 main(VertextoPixel input) : SV_TARGET
{
	float2 pixel = input.pos.xy;

	const float2 UV_baseColorMap = g_xMat_uvset_baseColorMap == 0 ? input.uvsets.xy : input.uvsets.zw;
	float4 color = xBaseColorMap.Sample(sampler_objectshader, UV_baseColorMap);
	color.rgb = DEGAMMA(color.rgb);
	color *= input.color;
	ALPHATEST(color.a);
	float opacity = color.a;

	// Water does not generate shadows to not mess up the smooth falloff on geometry intersections:
	//  This could be resolved if this shader could sample depth, but the depthbuffer is currently bound
	//  so leave it at this for the moment
	color.rgb = 1;

	// Use the alpha channel for refraction caustics effect:
	float3 bumpColor;

	float2 bumpColor0 = 0;
	float2 bumpColor1 = 0;
	float2 bumpColor2 = 0;
	const float2 UV_normalMap = g_xMat_uvset_normalMap == 0 ? input.uvsets.xy : input.uvsets.zw;
	bumpColor0 = 2.0f * xNormalMap.Sample(sampler_objectshader, UV_normalMap - g_xMat_texMulAdd.ww).rg - 1.0f;
	bumpColor1 = 2.0f * xNormalMap.Sample(sampler_objectshader, UV_normalMap + g_xMat_texMulAdd.zw).rg - 1.0f;
	bumpColor = float3(bumpColor0 + bumpColor1 + bumpColor2, 1)  * g_xMat_refractionIndex;
	bumpColor.rg *= g_xMat_normalMapStrength;
	bumpColor = normalize(max(bumpColor, float3(0, 0, 0.0001f)));

	color.a = 1 - saturate(abs(dot(bumpColor, float3(0, 0, 1))));

	return color;
}
