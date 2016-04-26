// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

// Polyvox Includes
#include "PolyVox/PagedVolume.h"
#include "PolyVox/MaterialDensityPair.h"

#include "GameFramework/Actor.h"
#include "AVoxelSomething.generated.h"

UCLASS()
class VOXELCRAFT_API AAVoxelSomething : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAVoxelSomething();

	// Called after the C++ constructor and after the properties have been initialized.
	virtual void PostInitializeComponents() override;

	// Some variables to control our terrain generator
	// The seed of our fractal
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) int32 Seed;

	// The number of octaves that the noise generator will use
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) int32 NoiseOctaves;

	// The frequency of the noise
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) float NoiseFrequency;

	// The scale of the noise. The output of the TerrainFractal is multiplied by this.
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) float NoiseScale;

	// The offset of the noise. This value is added to the output of the TerrainFractal.
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) float NoiseOffset;

	// The maximum height of the generated terrain in voxels. NOTE: Changing this will affect where the ground begins!
	UPROPERTY(Category = "Voxel Terrain", BlueprintReadWrite, EditAnywhere) float TerrainHeight;

private:
	TSharedPtr<PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>> VoxelVolume;
	
};

class VoxelTerrainPager : public PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Pager
{
public:
	// Constructor
	VoxelTerrainPager(uint32 NoiseSeed = 123, uint32 Octaves = 3, float Frequency = 0.01, float Scale = 32, float Offset = 0, float Height = 64);

	// Destructor
	virtual ~VoxelTerrainPager() {};

	// PagedVolume::Pager functions
	virtual void pageIn(const PolyVox::Region> region, PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Chunk* pChunk);
	virtual void pageOut(const PolyVox::Region> region, PolyVox::PagedVolume<PolyVox::MaterialDensityPair44>::Chunk* pChunk);

private:
	// Some variables to control our terrain generator
	// The seed of our fractal
	uint32 Seed = 123;

	// The number of octaves that the noise generator will use
	uint32 NoiseOctaves = 3;

	// The frequency of the noise
	float NoiseFrequency = 0.01;

	// The scale of the noise. The output of the TerrainFractal is multiplied by this.
	float NoiseScale = 32;

	// The offset of the noise. This value is added to the output of the TerrainFractal.
	float NoiseOffset = 0;

	// The maximum height of the generated terrain in voxels. NOTE: Changing this will affect where the ground begins!
	float TerrainHeight = 64;
};