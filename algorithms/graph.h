#ifndef GRAPH_H
#define GRAPH_H

#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

class Graph {
private:
    int vertices;
    std::vector<std::vector<std::pair<int, int>>> adj;

public:
    explicit Graph(int v)
        : vertices(v), adj(v) {}

    bool addRoad(int u, int v, int distance) {
        if (u < 0 || u >= vertices ||
            v < 0 || v >= vertices ||
            distance < 0) {
            return false;
        }

        adj[u].push_back({v, distance});
        adj[v].push_back({u, distance});

        return true;
    }

    std::vector<int> dijkstra(int source) const {
        const int INF = std::numeric_limits<int>::max();

        std::vector<int> dist(vertices, INF);

        if (source < 0 || source >= vertices) {
            return dist;
        }

        using Node = std::pair<int, int>;

        std::priority_queue<
            Node,
            std::vector<Node>,
            std::greater<Node>
        > pq;

        dist[source] = 0;
        pq.push({0, source});

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int u = pq.top().second;

            pq.pop();

            if (currentDistance != dist[u]) {
                continue;
            }

            for (const auto& road : adj[u]) {
                int v = road.first;
                int weight = road.second;

                if (currentDistance <= INF - weight &&
                    currentDistance + weight < dist[v]) {

                    dist[v] = currentDistance + weight;
                    pq.push({dist[v], v});
                }
            }
        }

        return dist;
    }
};

#endif
