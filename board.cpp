/** noam sayada
 *  noamsayada1@gmail.com
 */

#include "board.hpp"
#include <iostream>

using namespace ariel;
using namespace std;

Board::Board() {
    // Generate hexagonal grid with 5 rows
    unsigned int rowLengths[5] = {3, 4, 5, 4, 3};
    unsigned int index = 0;
    for (unsigned int x = 0; x < 5; ++x) {
        for (unsigned int y = 0; y < rowLengths[x]; ++y) {
            hexagons.emplace_back(Hexagon(HexagonTypes[index], HexagonNumbers[index], x, y));
            index++;
        }
    }

    // Initialize vertexs
    for (unsigned int i = 0; i < vertex2hexagons.size(); ++i) {
        vertexs.emplace_back(Vertex(i));
    }

    // Store the hexagons adjacent to each vertex:
    initializeVertexsWithAdjHexagons();

    // Initialize the edges:
    initializeEdges();
}

Board::~Board() {
    hexagons.clear();
    edges.clear();
}

Hexagon& Board::getHexagon(unsigned int x, unsigned int y) {
    // Find the hexagon
    for (auto& hex : hexagons) {
        if (hex.getX() == x && hex.getY() == y) {
            return hex;
        }
    }

    throw std::invalid_argument("Hexagon not found");
}

Vertex& Board::getVertex(unsigned int index) {
    // Check bound
    if (index >= vertexs.size()) {
        throw std::invalid_argument("Vertex index out of range");
    }

    return vertexs[index];
}

Edge& Board::getEdge(unsigned int index) {
    // Check bound
    if (index >= edges.size()) {
        throw std::invalid_argument("Edge index out of range");
    }

    return edges[index];
}

void Board::initializeVertexsWithAdjHexagons() {
    for (unsigned int i = 0; i < vertex2hexagons.size(); ++i) {
        // Go over the hexagon adjacent to the vertex
        for (const auto& hexagon : vertex2hexagons[i]) {
            vertexs[i].addAdjacentHexagon(hexagon.first, hexagon.second);
        }
    }
}

void Board::initializeEdges() {
    for (unsigned int i = 0; i < edge2vertexs.size(); ++i) {
        edges.emplace_back(Edge(i, edge2vertexs[i].first, edge2vertexs[i].second));
    }
}

unsigned int Board::getVertex2HexagonsSize() {
    return vertex2hexagons.size();
}

unsigned int Board::getEdge2VertexsSize() {
    return edge2vertexs.size();
}

const std::vector<std::pair<unsigned int, unsigned int>>& Board::getEdge2Vertexs() const {
    return edge2vertexs;
}

const std::vector<std::vector<std::pair<unsigned int, unsigned int>>> Board::getVertex2Hexagons() {
    return vertex2hexagons;
}

const std::vector<Hexagon>& Board::getHexagons() const {
    return hexagons;
}

const std::vector<Vertex>& Board::getVertexs() const {
    return vertexs;
}

void Board::showVertexs() const {
    // Go over the vertexs
    for (const auto& vertex : vertexs) {
        // If there is a settlement or city
        if (vertex.getStructure() != Structure::None) {
            string structureName = (vertex.getStructure() == Structure::Settlement) ? "Settlement" : "City";
            string ownerName = vertex.getOwner() ? vertex.getOwner()->getName() : "None";
            std::cout << "Vertex Index: " << vertex.getIndex()
                     << ", Structure: " << structureName
                     << ", Owner: " << ownerName << std::endl;
        }
    }
}

void Board::showRoads() const {
    // Go over the edges
    for (const auto& edge : edges) {
        // If there is an owner
        if (edge.getOwner() != nullptr) {
            std::string ownerName = edge.getOwner()->getName();
            std::cout << "Edge Index: " << edge.getIndex()
                     << ", Owner: " << ownerName << std::endl;
        }
    }
}
