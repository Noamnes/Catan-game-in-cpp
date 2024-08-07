// noam sayada
// noamsayada1@gmail.com

#pragma once

#include <string>
#include <vector>
#include "Hexagon.hpp"
#include "Vertex.hpp"
#include "Edge.hpp"
#include "CardType.hpp"

namespace ariel {
    class Board {
        private:
            std::vector<Hexagon> hexagons; // Collection of all hexagons
            std::vector<Vertex> vertexs; // Collection of all vertices
            std::vector<Edge> edges; // Collection of all edges

            // Set up vertices based on neighboring hexagons
            void initializeVertexsWithAdjHexagons();

            // Set up edges based on neighboring vertices
            void initializeEdges();

            // Mapping of vertices to adjacent hexagons
            const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> vertex2hexagons = Vertex::getVertex2HexagonsMapping();

            // Mapping of edges to adjacent vertices
            const std::vector<std::pair<unsigned int, unsigned int>> edge2vertexs = {
                {0,  1}, {1,  2}, {2,  3}, {3,  4}, {4,  5}, {5,  6}, {0,  8}, {2,  10},
                {4,  12}, {6,  14}, {7,  8}, {8,  9}, {9,  10}, {10, 11}, {11, 12}, {12, 13},
                {13, 14}, {14, 15}, {7,  17}, {9,  19}, {11, 21}, {13, 23}, {15, 25}, {16, 17},
                {17, 18}, {18, 19}, {19, 20}, {20, 21}, {21, 22}, {22, 23}, {23, 24}, {24, 25},
                {25, 26}, {16, 27}, {18, 29}, {20, 31}, {22, 33}, {24, 35}, {26, 37}, {27, 28},
                {28, 29}, {29, 30}, {30, 31}, {31, 32}, {32, 33}, {33, 34}, {34, 35}, {35, 36},
                {36, 37}, {28, 38}, {30, 40}, {32, 42}, {34, 44}, {36, 46}, {38, 39}, {39, 40},
                {40, 41}, {41, 42}, {42, 43}, {43, 44}, {44, 45}, {45, 46}, {39, 47}, {41, 49},
                {43, 51}, {45, 53}, {47, 48}, {48, 49}, {49, 50}, {50, 51}, {51, 52}, {52, 53}};

        public:
            // Constructor & Destructor
            Board();
            ~Board();

            // Access the Hexagon at specific coordinates.
            // @param x The x-coordinate.
            // @param y The y-coordinate.
            // @return A reference to the specified Hexagon.
            // @throws std::invalid_argument if the hexagon is not found.
            Hexagon &getHexagon(unsigned int x, unsigned int y);

            // Access the Vertex at a specific index.
            // @param index The index of the vertex.
            // @return A reference to the specified Vertex.
            // @throws std::invalid_argument if the index is out of bounds.
            Vertex &getVertex(unsigned int index);

            // Access the Edge at a specific index.
            // @param index The index of the edge.
            // @return A reference to the specified Edge.
            // @throws std::invalid_argument if the index is out of bounds.
            Edge &getEdge(unsigned int index);

            // Get the total number of vertex connections.
            // @return The count of vertex adjacencies.
            unsigned int getVertex2HexagonsSize();

            // Get the total number of edge connections.
            // @return The count of edge adjacencies.       
            unsigned int getEdge2VertexsSize();

            // Retrieve the vertex adjacency mapping.
            // @return A reference to the edge-to-vertex mapping vector.
            const std::vector<std::pair<unsigned int, unsigned int>>& getEdge2Vertexs() const;

            // Retrieve the vertex adjacency mapping.
            // @return A vector containing vertex adjacencies.
            const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> getVertex2Hexagons();

            // Access the collection of Hexagons.
            // @return A reference to the vector of Hexagons.
            const std::vector<Hexagon>& getHexagons() const;

            // Access the collection of Vertex objects.
            // @return A reference to the vector of Vertex objects.
            const std::vector<Vertex>& getVertexs() const;

            // Display all vertices on the board.
            void showVertexs() const;

            // Display all roads on the board.
            void showRoads() const;
    };

    // Collection of hexagon types on the board
    const std::vector<CardType> HexagonTypes = {
            CardType::Ore, CardType::Wool, CardType::Lumber, CardType::Grain, CardType::Brick,
            CardType::Wool, CardType::Brick, CardType::Grain, CardType::Lumber,
            CardType::Lumber, // Middle hexagon should be Desert but the type is not available.
            CardType::Lumber, CardType::Ore, CardType::Lumber, CardType::Ore, CardType::Grain,
            CardType::Wool, CardType::Brick, CardType::Grain, CardType::Wool
    };

    // Collection of numbers assigned to hexagons on the board
    const std::vector<unsigned int> HexagonNumbers = {
            10, 2, 9, 12, 6, 4, 10, 9, 11,
            1, // Middle hexagon should be Desert but the type is not available, so it remains unaffected by dice rolls.
            3, 8, 8, 3, 4, 5, 5, 6, 11};
}
