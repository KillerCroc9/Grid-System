
#include "HexGrid.h"


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



void offsetToCube(int col, int row, int& x, int& y, int& z) {
    x = col;
    int offset = col / 2;
    z = row - offset;
    y = -x - z;
}

int cubeDistance(int x1, int y1, int z1, int x2, int y2, int z2) {
    return (abs(x1 - x2) + abs(y1 - y2) + abs(z1 - z2)) / 2;
}

int HexGrid::hexDistance(const Hex& a, const Hex& b) {
    int ax, ay, az, bx, by, bz;
    offsetToCube(a.q, a.r, ax, ay, az);
    offsetToCube(b.q, b.r, bx, by, bz);
    return cubeDistance(ax, ay, az, bx, by, bz);
}



// Function to find neighbors of a hex
std::vector<Hex> HexGrid::hexNeighbors(const Hex& hex) {
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
