// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <cmath>
#include "HexGrid.h"
#include "Hexagon.h"

struct FGridActorInfo {
	AActor* Actor; // Pointer to the actor
	Hex Coordinates; // Coordinates of the actor on the grid
	// Add other relevant information here

	FGridActorInfo(AActor* InActor, Hex InCoordinates)
		: Actor(InActor), Coordinates(InCoordinates) {}
};

/**
 * 
 */
class TEST_API Grid
{
public:

	
	Grid();

	Grid(TSubclassOf<AHexagon> HexagonBlueprintClass,int32 Height, int32 Width, float CustomXOffset, float CustomXSpacing, float CustomYSpacing);

	void ResetActorScales(TArray<FGridActorInfo> ResetArray);

	void ScaleAndSpawnNeighbors(int32 q, int32 r, float ScaleFactor, float CustomXOffset, float CustomXSpacing, float CustomYSpacing);

	int32 distanceToTarget(float ScaleFactor, float CustomXOffset, float CustomXSpacing, float CustomYSpacing, int32 aq, int32 ar, int32 bq, int32 br);
	
	TArray<FGridActorInfo> ActorsInfo;


private:
	
	HexGrid hexGrid;



	TArray<FGridActorInfo> ResetN;

	TArray<FGridActorInfo> ResetT;


};

