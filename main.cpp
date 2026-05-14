#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <map>

std::unordered_map<int, std::set<int>> graph;

void addEdge(int u, int v) {
    graph[u].insert(v);
    graph[v].insert(u);
}

void loadGraph(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cout << "Error: could not open file " << filename << std::endl;
        return;
    }
    int u, v;
    while (file >> u >> v) {
        addEdge(u, v);
    }
    file.close();
    std::cout << "Loaded " << graph.size() << " nodes from " << filename << std::endl;
}

std::unordered_map<int, int> computeCores() {
    std::unordered_map<int, int> degree;
    for (auto& node : graph) {
        degree[node.first] = node.second.size();
    }

    std::unordered_map<int, int> coreNumber;
    std::set<int> remaining;

    for (auto& node : graph) {
        remaining.insert(node.first);
    }

    int k = 1;
    while (!remaining.empty()) {
        bool removed = true;
        while (removed) {
            removed = false;
            std::vector<int> toRemove;
            for (int node : remaining) {
                if (degree[node] < k) {
                    toRemove.push_back(node);
                }
            }
            for (int node : toRemove) {
                coreNumber[node] = k - 1;
                remaining.erase(node);
                for (int neighbour : graph[node]) {
                    if (remaining.count(neighbour)) {
                        degree[neighbour]--;
                    }
                }
                removed = true;
            }
        }
        if (!remaining.empty()) {
            for (int node : remaining) {
                coreNumber[node] = k;
            }
        }
        k++;
        if (k > 100) break;
    }
    return coreNumber;
}

void printSummary(std::unordered_map<int, int>& cores) {
    int maxCore = 0;
    std::map<int, std::vector<int>> coreGroups;

    for (auto& entry : cores) {
        if (entry.second > maxCore) maxCore = entry.second;
        coreGroups[entry.second].push_back(entry.first);
    }

    std::cout << "\n=== Summary ===" << std::endl;
    std::cout << "Total nodes: " << cores.size() << std::endl;
    std::cout << "Max core number (degeneracy): " << maxCore << std::endl;

    for (auto& group : coreGroups) {
        std::cout << "Core " << group.first << ": " << group.second.size() << " nodes -> ";
        for (int node : group.second) {
            std::cout << node << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    loadGraph("graph.txt");

    std::unordered_map<int, int> cores = computeCores();

    std::cout << "\nNode -> Core Number" << std::endl;
    std::cout << "-------------------" << std::endl;

    std::map<int, int> sorted(cores.begin(), cores.end());
    for (auto& entry : sorted) {
        std::cout << "Node " << entry.first << " -> " << entry.second << std::endl;
    }

    printSummary(cores);

    return 0;
}