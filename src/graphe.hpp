#pragma once
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <iostream>
#include "utils.hpp"

namespace Graph {

    struct Position {
        int x{}, y{};
        bool operator==(const Position& other) const = default;
    };

    struct PositionHash {
        std::size_t operator()(const Position& pos) const {
            return std::hash<int>()(pos.x) ^ (std::hash<int>()(pos.y) << 1);
        }
    };

    struct WeightedGraphEdge {
        Position to{};
        float weight{1.0f};
        bool operator==(const WeightedGraphEdge& other) const = default;
    };

    struct WeightedGraph {
        std::unordered_map<Position, std::vector<WeightedGraphEdge>, PositionHash> adjacency_list;

        void add_vertex(const Position& pos);
        void add_directed_edge(const Position& from, const Position& to, float weight = 1.0f);
        void add_undirected_edge(const Position& a, const Position& b, float weight = 1.0f);
    };

    WeightedGraph build_from_grille(const std::vector<std::vector<int>>& grille);

    std::unordered_map<Graph::Position, Graph::Position, Graph::PositionHash> updateFlowField(const Graph::WeightedGraph& graph, const Graph::Position& posHomer);

}
