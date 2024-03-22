// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Engine/World.h" // For UWorld class
#include "GameFramework/Actor.h" // For AActor class
#include <iostream>
#include "GridGenerator.h"

using namespace std;


Grid::Grid()
{

}

Grid::Grid(TSubclassOf<AHexagon> HexagonBlueprintClass,int32 Height, int32 Width, float CustomXOffset, float CustomXSpacing, float CustomYSpacing)
{
    hexGrid = HexGrid(Height,Width);


    UWorld* World = GEngine->GameViewport->GetWorld();
    if (!World) {
        return;
    }
    for (int x = 0; x < hexGrid.GetWidth(); ++x) {
        for (int y = 0; y < hexGrid.GetHeight(); ++y) {
            // Calculate the x-offset based on whether it's an even or odd lane
            float xOffset = (x % 2 == 0) ? 0 : CustomXOffset;

            // Get the location to spawn the actor with the calculated x-offset
            FVector SpawnLocation = FVector((x * CustomXSpacing), (y * CustomYSpacing) + xOffset, 0);

            AHexagon* Actor;
            if (x % 2 == 0)

                Actor = World->SpawnActor<AHexagon>(HexagonBlueprintClass, SpawnLocation, FRotator::ZeroRotator);
        	else
                Actor = World->SpawnActor<AHexagon>(HexagonBlueprintClass, SpawnLocation, FRotator::ZeroRotator);
          

            if (Actor) {

                Actor->Q = x; // Set the Q coordinate
                Actor->R = y; // Set the R coordinate

             //   Actor->Tags.Add(FName(*FString::Printf(TEXT("GridActor_%d_%d"), x, y)));
                  ActorsInfo.Add(FGridActorInfo(Actor, Hex(x, y)));
            }
        }

    }
}

void Grid::ScaleAndSpawnNeighbors(int q, int r, float ScaleFactor, float CustomXOffset, float CustomXSpacing, float CustomYSpacing)
{
    // Find the hexagon
    Hex hex(q, r);
    // Find neighbors
    std::vector<Hex> neighbors = hexGrid.hexNeighbors(hex);
    ResetActorScales(ResetN); // Reset the scales of the previously scaled actors
    ResetActorScales(ResetT); // Reset the scales of the previously scaled actors 
	ResetT.Empty();
    ResetN.Empty();
    for (const auto& neighbor : neighbors) {
        // Look for an existing actor in ActorsInfo that matches the neighbor's coordinates
        for (auto& actorInfo : ActorsInfo) {
            if (actorInfo.Coordinates.q == neighbor.q && actorInfo.Coordinates.r == neighbor.r) {
                // If a matching actor is found, scale it
                if (actorInfo.Actor) {
                    actorInfo.Actor->SetActorScale3D(FVector(1, 1, ScaleFactor));
                    ResetN.Add(FGridActorInfo(actorInfo.Actor, Hex(neighbor.q, neighbor.r)));
                }
                break; // Stop searching once a match is found
            }
        }
    }
}

int32 Grid::distanceToTarget(float ScaleFactor, float CustomXOffset, float CustomXSpacing, float CustomYSpacing, int aq, int ar, int bq, int br)
{
    Hex a(aq, ar);
    Hex b(bq, br);
    int32 distance = hexGrid.hexDistance(a, b);
    UE_LOG(LogTemp, Warning, TEXT("Distance between (%d, %d) and (%d, %d) is %d"), a.q, a.r, b.q, b.r, distance);
    ResetActorScales(ResetT); // Reset the scales of the previously scaled actors 
    ResetActorScales(ResetN); // Reset the scales of the previously scaled actors
    ResetN.Empty();
    ResetT.Empty();
    // Iterate through ActorsInfo to find and modify actors at hexes a and b
    for (auto& actorInfo : ActorsInfo) {
        if ((actorInfo.Coordinates.q == a.q && actorInfo.Coordinates.r == a.r) ||
            (actorInfo.Coordinates.q == b.q && actorInfo.Coordinates.r == b.r)) {
            // If a matching actor is found, scale it
            if (actorInfo.Actor) {
                actorInfo.Actor->SetActorScale3D(FVector(1, 1, ScaleFactor));
                ResetT.Add(FGridActorInfo(actorInfo.Actor, Hex(actorInfo.Coordinates.q, actorInfo.Coordinates.r)));
            }
        }
    }
    return distance;
}



void Grid::ResetActorScales(TArray<FGridActorInfo> ResetArray) {
    for (auto& actorInfo : ResetArray) {
        if (actorInfo.Actor) {
            actorInfo.Actor->SetActorScale3D(FVector(1, 1, 1)); // Reset to original scale
        }
    }
    ResetArray.Empty(); // Optionally clear the array if these actors won't be reset again
}


// Example usage
//hexGrid.printHexGrid(grid);
//Hex a(0, 0);
//Hex b(3, 3);
//UE_LOG(LogTemp, Warning, TEXT("Distance between (%d, %d) and (%d, %d) is %d"), a.q, a.r, b.q, b.r, hexGrid.hexDistance(a, b));
//
//vector<Hex> neighbors = hexGrid.hexNeighbors(a);
//FString neighborStr;
//for (const auto& neighbor : neighbors) {
//    neighborStr += FString::Printf(TEXT("(%d, %d) "), neighbor.q, neighbor.r);
//}
//UE_LOG(LogTemp, Warning, TEXT("Neighbors of (%d, %d) are: %s"), a.q, a.r, *neighborStr);


//std::vector<std::pair<int, int>> directions;
//if (isEvenRow == isEvenColumn) {
//    // Define directions
//    directions = {
//    {0, 1}, {0, -1},        // Up, Down
//    {1, 0}, {-1, 0},        // Right, Left
//    {1, hex.r % 2 == 0 ? -1 : 1}, {-1, hex.r % 2 == 0 ? -1 : 1}   // Up-right, Down-left
//    };
//}
//else {
//    // Define directions
//    directions = {
//    {0, 1}, {0, -1},        // Up, Down
//    {1, 0}, {-1, 0},        // Right, Left
//    {1, hex.r % 2 == 0 ? 1 : -1}, {-1, hex.r % 2 == 0 ? 1 : -1}   // Up-right, Down-left
//    };
