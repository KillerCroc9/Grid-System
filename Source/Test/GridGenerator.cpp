// Fill out your copyright notice in the Description page of Project Settings.


#include "GridGenerator.h"
#include "Grid.h"

// Sets default values
AGridGenerator::AGridGenerator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGridGenerator::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AGridGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGridGenerator::GenerateGrid(int32 Height,int32 Width)
{
	_Grid = Grid::Grid(HexagonBlueprintClass, Height, Width, CustomXOffset, CustomXSpacing, CustomYSpacing);
}

void AGridGenerator::findNeighbors(int32 Q, int32 R)
{
	_Grid.ScaleAndSpawnNeighbors(Q,R,ActorScale, CustomXOffset, CustomXSpacing, CustomYSpacing);
}

int32 AGridGenerator::distanceToTarget(int32 AQ, int32 AR, int32 BQ, int32 BR)
{
	int32 Distance = _Grid.distanceToTarget(ActorScale, CustomXOffset, CustomXSpacing, CustomYSpacing, AQ, AR, BQ, BR);
	return Distance;
}

TArray<FGridActorInfoWrapper> AGridGenerator::GetActorInfo()
{
	TArray<FGridActorInfoWrapper> Info;
	for (auto& actorInfo : _Grid.ActorsInfo) {
		FGridActorInfoWrapper actorInfoWrapper{};
		actorInfoWrapper.Actor = actorInfo.Actor;
		actorInfoWrapper.Q = actorInfo.Coordinates.q;
		actorInfoWrapper.R = actorInfo.Coordinates.r;
		
		Info.Add(actorInfoWrapper);
	}

	return Info;
}

