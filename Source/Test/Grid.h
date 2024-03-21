// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include <vector>
#include <cmath>

/**
 * 
 */


struct Hex {
	int q; // Axial coordinate
	int r; // Axial coordinate

	Hex(int q = 0, int r = 0) : q(q), r(r) {}  // Default parameters allow for empty initialization
};
class TEST_API Grid
{
public:

	Grid(TSubclassOf<AActor> HexActorEven, TSubclassOf<AActor> HexActorOdd, float CustomXOffset, float CustomXSpacing, float CustomYSpacing);

	void ScaleAndSpawnNeighbors(int q, int r, float ScaleFactor, TSubclassOf<AActor> HexActorEven, TSubclassOf<AActor> HexActorOdd, float CustomXOffset, float CustomXSpacing, float CustomYSpacing);



};
