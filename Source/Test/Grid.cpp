// Fill out your copyright notice in the Description page of Project Settings.


#include "Grid.h"
#include "Engine/World.h" // For UWorld class
#include "GameFramework/Actor.h" // For AActor class
#include <iostream>
#include "GridGenerator.h"

using namespace std;


class HexGrid
{
public:
    HexGrid();
    HexGrid(int width, int height);
    int hexDistance(const Hex& a, const Hex& b);
    std::vector<Hex> hexNeighbors(const Hex& hex);
    void printHexGrid();
    TArray<TArray<Hex>> ConvertVectorToTArray(const std::vector<std::vector<Hex>>& vectorGrid);
    int GetWidth();  // Get width of the grid
    int GetHeight(); // Get height of the grid

    private:
        std::vector<std::vector<Hex>> grid;

};

HexGrid::HexGrid()
{
}

HexGrid::HexGrid(int width, int height) {
        for (int q = 0; q < width; ++q) {
            std::vector<Hex> column;
            int r1 = std::max(-q, 0);  // Start row (inclusive)
            int r2 = std::min(height, width - q);  // End row (exclusive)
            for (int r = r1; r < r2; ++r) {
                column.emplace_back(q, r);
            }
            grid.push_back(column);
        }
    }


    // Function to calculate the distance between two hexes
    int HexGrid::hexDistance(const Hex & a, const Hex & b) {
        return (std::abs(a.q - b.q) + std::abs(a.q + a.r - b.q - b.r) + std::abs(a.r - b.r)) / 2;
    }

    // Function to find neighbors of a hex
    std::vector<Hex> HexGrid::hexNeighbors(const Hex & hex) {
        std::vector<Hex> neighbors;

        //// Determine whether the current row is even or odd
        bool isEvenRow = hex.r % 2 == 0;
        bool isEvenColumn = hex.q % 2 == 0;

        std::vector<std::pair<int, int>> directions;

        if (isEvenRow == isEvenColumn) {
            // Define directions
            directions = {
            {0, 1}, {0, -1},        // Up, Down
            {1, 0}, {-1, 0},        // Right, Left
            {1, hex.r % 2 == 0 ? -1 : 1}, {-1, hex.r % 2 == 0 ? -1 : 1}   // Up-right, Down-left
            };
        }
        else
        {
			// Define directions
			directions = {
			{0, 1}, {0, -1},        // Up, Down
			{1, 0}, {-1, 0},        // Right, Left
			{1, hex.r % 2 == 0 ? 1 : -1}, {-1, hex.r % 2 == 0 ? 1 : -1}   // Up-right, Down-left
			};
        }

        for (const auto& direction : directions) {
            int neighbor_q = hex.q + direction.first;
            int neighbor_r = hex.r + direction.second;

            // Check if the generated neighbor is within bounds
            if (neighbor_q >= 0 && neighbor_r >= 0 && neighbor_q < grid.size() && neighbor_r < grid[0].size()) {
                neighbors.emplace_back(neighbor_q, neighbor_r);
            }
        }

        return neighbors;
    }

    void HexGrid::printHexGrid() {
        for (const auto& row : grid) {
            FString rowStr;
            for (const auto& hex : row) {
                rowStr += FString::Printf(TEXT("(%d, %d) "), hex.q, hex.r);
            }
            UE_LOG(LogTemp, Warning, TEXT("%s"), *rowStr);
        }
    }


    TArray<TArray<Hex>> HexGrid::ConvertVectorToTArray(const std::vector<std::vector<Hex>>& vectorGrid)
    {
        TArray<TArray<Hex>> UnrealGrid;

        for (const auto& row : vectorGrid)
        {
            TArray<Hex> UnrealRow;
            for (const auto& hex : row)
            {
                UnrealRow.Add(hex);
            }
            UnrealGrid.Add(UnrealRow);
        }

        return UnrealGrid;
    }

    int HexGrid::GetWidth()
    {
        return grid.size();
    }

    int HexGrid::GetHeight()
    {
        return grid.size();
    }
    
Grid::Grid(TSubclassOf<AActor> HexActorEven, TSubclassOf<AActor> HexActorOdd,  float CustomXOffset, float CustomXSpacing, float CustomYSpacing)
{
    HexGrid hexGrid(15, 15);

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
    HexGrid hexGrid(15, 15);

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
