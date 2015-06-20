#include "grassHF_GS.hlsli"

[maxvertexcount(21)]
void main(
	point VS_OUT input[1], 
	inout TriangleStream< GS_OUT > output
)
{
	uint rand = input[0].pos.w;
	float4x4 xViewProjection = mul(xView,xProjection);
	//float3 viewDir = xView._m02_m12_m22;
	float4 pos = float4(input[0].pos.xyz,1);
	float3 color = saturate(colTime.xyz+sin(pos.x-pos.y-pos.z)*0.013f)*0.5;
	float3 wind = sin(colTime.w+(pos.x+pos.y+pos.z)*0.1f)*windDir.xyz*0.1;
	if(rand%(uint)windRandomness) wind=-wind;
	float3 normal = /*normalize(*/input[0].nor.xyz/*-wind)*/;
	float length = /*lerp(*/input[0].nor.w/*,0,saturate(distance(pos.xyz,eye.xyz)/drawdistance))*/;
	//float3 front = cross(normal,float3(1,0,0))*0.5;
	float3 right = normalize(cross(input[0].tan.xyz, normal))*0.3;
	if(rand%2) right*=-1;
	//uint lod = input[0].pos.w;
	//color=float3(0,0.8,0);
	
	for(uint i=0;i<3;++i){
		float4 mod = pos + float4( cross( MOD[i],normal),0 );
		genBlade(output,xViewProjection,mod,normal,length,2,right,color, wind);
	}

	//genBlade(output,xViewProjection,pos,normal,length,2,right,color, wind);
	//genBlade(output,xViewProjection,pos+float4(0.2,-0.1,0,0),normal,length*0.97,3,right,color, wind);
	//genBlade(output,xViewProjection,pos+float4(-0.2,-0.01,-0.22,0),normal,length*0.6,3,right,color, wind);
	//genBlade(output,xViewProjection,pos+float4(0.3,-0.2,-0.1,0),normal,length*0.8,3,right,color, wind);

}