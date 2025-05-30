#include "graphe.hpp"

namespace Graph {

    void WeightedGraph::add_vertex(const Position& pos) {
        adjacency_list.emplace(pos, std::vector<WeightedGraphEdge>{});
    }

    void WeightedGraph::add_directed_edge(const Position& from, const Position& to, float weight) {
        adjacency_list[from].push_back({to, weight});
    }

    void WeightedGraph::add_undirected_edge(const Position& a, const Position& b, float weight) {
        add_directed_edge(a, b, weight);
        add_directed_edge(b, a, weight);
    }

    bool is_walkable(int x, int y, const std::vector<std::vector<int>>& grille, int height, int width) {
        return x >= 0 && y >= 0 && x < height && y < width && grille[x][y] == 0;
    }

    WeightedGraph build_from_grille(const std::vector<std::vector<int>>& grille) {
        WeightedGraph graph;
        int height = grille.size();
        int width = grille[0].size();

        for (int x = 0; x < height; ++x) {
            for (int y = 0; y < width; ++y) {
                if (!is_walkable(x, y, grille, height, width)) continue;

                Position current{x, y};
                graph.add_vertex(current);

                const std::vector<std::pair<int, int>> directions{{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
                for (const auto& [dx, dy] : directions) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (is_walkable(nx, ny, grille, height, width)) {
                        Position neighbor{nx, ny};
                        graph.add_vertex(neighbor);
                        graph.add_undirected_edge(current, neighbor);
                    }
                }
            }
        }

        return graph;
    }

}
