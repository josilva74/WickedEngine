#ifndef _WI_GPU_BVH_H_
#define _WI_GPU_BVH_H_

#include "CommonInclude.h"
#include "wiGraphicsDevice.h"
#include "wiSceneSystem_Decl.h"
#include "wiRectPacker.h"
#include "ShaderInterop_TracedRendering.h"

#include <vector>
#include <unordered_map>
#include <unordered_set>

class wiGPUBVH
{
private:
	// Scene BVH intersection resources:
	wiGraphics::GPUBuffer bvhNodeBuffer;
	wiGraphics::GPUBuffer bvhAABBBuffer;
	wiGraphics::GPUBuffer bvhFlagBuffer;
	wiGraphics::GPUBuffer triangleBuffer;
	wiGraphics::GPUBuffer clusterCounterBuffer;
	wiGraphics::GPUBuffer clusterIndexBuffer;
	wiGraphics::GPUBuffer clusterMortonBuffer;
	wiGraphics::GPUBuffer clusterSortedMortonBuffer;
	wiGraphics::GPUBuffer clusterOffsetBuffer;
	wiGraphics::GPUBuffer clusterAABBBuffer;
	wiGraphics::GPUBuffer clusterConeBuffer;
	uint32_t maxTriangleCount = 0;
	uint32_t maxClusterCount = 0;

	// Scene material resources:
	wiGraphics::GPUBuffer globalMaterialBuffer;
	wiGraphics::Texture2D globalMaterialAtlas;
	std::vector<TracedRenderingMaterial> materialArray;
	std::unordered_map<const wiGraphics::Texture2D*, wiRectPacker::rect_xywh> storedTextures;
	std::unordered_set<const wiGraphics::Texture2D*> sceneTextures;
	void UpdateGlobalMaterialResources(const wiSceneSystem::Scene& scene, GRAPHICSTHREAD threadID);

public:
	void Build(const wiSceneSystem::Scene& scene, GRAPHICSTHREAD threadID);
	void Bind(wiGraphics::SHADERSTAGE stage, GRAPHICSTHREAD threadID) const;

	static void LoadShaders();

};

#endif // _WI_GPU_BVH_H_
