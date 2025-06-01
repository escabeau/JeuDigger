#include "graphe.hpp"
#include <queue>

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


    std::unordered_map<Position, Position, PositionHash> updateFlowField(const WeightedGraph& graph, const Vector3D& posPerso){
        Graph::Position posHomer {static_cast<int>(posPerso.x),static_cast<int>(posPerso.y)};
        std::queue<Position> frontier{};
        //conversion des coordonnées de l'espace virtuel à l'espace grille
        float xHomer {(posHomer.x + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap[0].size())};
        float yHomer {(posHomer.y + GL_VIEW_SIZE/2) / (GL_VIEW_SIZE/grilleMap.size())};

        Position initPos {static_cast<int>(xHomer), static_cast<int>(yHomer)};
        
        frontier.push(initPos);

        std::unordered_map<Position, Position, PositionHash> came_from;
        came_from[initPos] = initPos; // homer vient de la case où il est


        while (!frontier.empty()) {
            Position current = frontier.front();
            frontier.pop();

            // pour chaque voisin du sommet courant
            if (graph.adjacency_list.find(current) != graph.adjacency_list.end()) {
                for (const auto& edge : graph.adjacency_list.at(current)) {
                    const Position& next = edge.to;

                    // si le voisin n’a pas encore été visité
                    if (came_from.find(next) == came_from.end()) {
                        frontier.push(next);
                        came_from[next] = current;
                    }
                }
            }
        }

        return came_from;
    }

}
