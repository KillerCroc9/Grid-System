#pragma once




struct Hex {
    int q; // Axial coordinate
    int r; // Axial coordinate

    Hex(int q = 0, int r = 0) : q(q), r(r) {}  // Default parameters allow for empty initialization
};


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
