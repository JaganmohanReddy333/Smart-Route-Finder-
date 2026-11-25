#include "../include/Dijkstra.h"

#include <queue>
#include <unordered_map>
#include <climits>
#include <algorithm>
#include <cctype>

#define RESET "\033[0m"
#define GREEN "\033[32m"
#define CYAN "\033[36m"
#define RED "\033[31m"
#define YELLOW "\033[33m"

using namespace std;

string toLowerCase(string text) {

    for (char &c : text) {
        c = tolower(c);
    }

    return text;
}

double Dijkstra::shortestPath(Graph& graph,
                            string start,
                            string destination) {

    auto &adjList = graph.getAdjList();

    unordered_map<string, string> normalizedCities;

    for (auto city : adjList) {

        normalizedCities[
            toLowerCase(city.first)
        ] = city.first;
    }

    start = toLowerCase(start);
    destination = toLowerCase(destination);

    if (normalizedCities.find(start)
        == normalizedCities.end()
        ||
        normalizedCities.find(destination)
        == normalizedCities.end()) {

        cout << RED;
        cout << "City not found in map.\n";
        cout << RESET;

        return -1;
    }

    start = normalizedCities[start];
    destination = normalizedCities[destination];

    unordered_map<string, int> distance;
    unordered_map<string, string> parent;

    for (auto city : adjList) {
        distance[city.first] = INT_MAX;
    }

    priority_queue<
        pair<int, string>,
        vector<pair<int, string>>,
        greater<pair<int, string>>
    > pq;

    distance[start] = 0;

    pq.push({0, start});

    while (!pq.empty()) {

        string currentCity = pq.top().second;
        int currentDistance = pq.top().first;

        pq.pop();

        for (auto neighbor : adjList[currentCity]) {

            string nextCity = neighbor.first;
            int roadDistance = neighbor.second;

            if (currentDistance + roadDistance
                < distance[nextCity]) {

                distance[nextCity]
                    = currentDistance + roadDistance;

                parent[nextCity]
                    = currentCity;

                pq.push({
                    distance[nextCity],
                    nextCity
                });
            }
        }
    }

    cout << CYAN;
    cout << "\n===== SHORTEST PATH RESULT =====\n";
    cout << RESET;

    if (distance[destination] == INT_MAX) {

        cout << RED;
        cout << "No route found.\n";
        cout << RESET;

        return -1;
    }

    vector<string> path;

    string current = destination;

    while (current != start) {

        if (parent.find(current)
            == parent.end()) {

            cout << RED;
            cout << "Invalid route.\n";
            cout << RESET;

            return -1;
        }

        path.push_back(current);

        current = parent[current];
    }

    path.push_back(start);

    reverse(path.begin(),
            path.end());

    cout << GREEN;

    cout << "Shortest Distance: "
         << distance[destination]
         << " km\n\n";

    cout << YELLOW;
    cout << "Optimal Route:\n";

    for (int i = 0;
         i < path.size();
         i++) {

        cout << path[i];

        if (i != path.size() - 1)
            cout << " -> ";
    }

    cout << endl;
    cout << RESET;

    return distance[destination];
}