// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Engine/World.h" // For UWorld class
#include "GameFramework/Actor.h" // For AActor class
#include <iostream>
#include "GridGenerator.h"

using namespace std;


Grid::Grid(TSubclassOf<AActor> HexActorEven, TSubclassOf<AActor> HexActorOdd,  float CustomXOffset, float CustomXSpacing, float CustomYSpacing)
{
    hexGrid = HexGrid(16,16);


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

            AActor* Actor;
            if (x % 2 == 0)

                Actor = World->SpawnActor<AActor>(HexActorEven, SpawnLocation, FRotator::ZeroRotator);
        	else
                Actor = World->SpawnActor<AActor>(HexActorOdd, SpawnLocation, FRotator::ZeroRotator);
          

            if (Actor) {

            }
        }
    }
}

void Grid::ScaleAndSpawnNeighbors(int q, int r, float ScaleFactor, TSubclassOf<AActor> HexActorEven, TSubclassOf<AActor> HexActorOdd, float CustomXOffset, float CustomXSpacing, float CustomYSpacing)
{
    // Find the hexagon
    Hex hex(q, r);

    // Find neighbors
    std::vector<Hex> neighbors = hexGrid.hexNeighbors(hex);

    // Iterate through neighbors
    for (const auto& neighbor : neighbors)
    {
        // Calculate world location for neighbor
        FVector SpawnLocation = FVector((neighbor.q * CustomXSpacing), (neighbor.r * CustomYSpacing) + (neighbor.q % 2 == 0 ? 0 : CustomXOffset), 0);

        UWorld* World = GEngine->GameViewport->GetWorld();
        if (!World) {
			return;
		}
        // Spawn actor
        AActor* NeighborActor;
        if (neighbor.q % 2 == 0)
            NeighborActor = World->SpawnActor<AActor>(HexActorEven, SpawnLocation, FRotator::ZeroRotator);
        else
            NeighborActor = World->SpawnActor<AActor>(HexActorOdd, SpawnLocation, FRotator::ZeroRotator);

        // Scale actor if spawned successfully
        if (NeighborActor)
        {
            NeighborActor->SetActorScale3D(FVector(1, 1, ScaleFactor));
        }
    }
}


void Grid::distanceToTarget(TSubclassOf<AActor> HexActorSelected, float ScaleFactor, float CustomXOffset, float CustomXSpacing, float CustomYSpacing, int aq, int ar, int bq, int br)
{
    Hex a(aq, ar);
    Hex b(bq, br);
    
    UE_LOG(LogTemp, Warning, TEXT("Distance between (%d, %d) and (%d, %d) is %d"), a.q, a.r, b.q, b.r, hexGrid.hexDistance(a, b));

    // Get world context
    UWorld* World = GEngine->GameViewport->GetWorld(); // Assuming this is called within an actor or component with access to GetWorld()
    if (!World) return;

    // Define spawn parameters
    FActorSpawnParameters SpawnParams;

    FVector SpawnLocationA = FVector((a.q * CustomXSpacing), (a.r * CustomYSpacing) + (a.q % 2 == 0 ? 0 : CustomXOffset), 0);

    FVector SpawnLocationB = FVector((b.q * CustomXSpacing), (b.r * CustomYSpacing) + (b.q % 2 == 0 ? 0 : CustomXOffset), 0);


    // Spawn actors on hexes a and b
    AActor* ActorA = World->SpawnActor<AActor>(HexActorSelected, SpawnLocationA, FRotator::ZeroRotator, SpawnParams);
    AActor* ActorB = World->SpawnActor<AActor>(HexActorSelected, SpawnLocationB, FRotator::ZeroRotator, SpawnParams);

    ActorA->SetActorScale3D(FVector(1, 1, ScaleFactor));
    ActorB->SetActorScale3D(FVector(1, 1, ScaleFactor));
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
