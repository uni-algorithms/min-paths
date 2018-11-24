#ifndef PATHS_HPP
#define PATHS_HPP

#include <algorithm>
#include <fstream>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <vector>

using namespace std;

typedef int node;
typedef unordered_map<node, unordered_set<node>> graph;

void add_node(graph &g, const node &n) {
    g.emplace(n, unordered_set<node>());
}

void add_arch(graph &g, const node &a, const node &b) {
    g.find(a)->second.insert(b);
}

template<typename K, typename V>
K take_first(const pair<K, V> &p) {
    return p.first;
}

pair<int, int> min_paths(const graph &g, const node &a, const node &b) {
    vector<int> reach_b;
    unordered_map<node, int> erdos = {{a, 0}};
    queue<node> q;
    q.push(a);

    for (; !q.empty(); q.pop()) {
        const auto u = q.front();
        const auto e = erdos.find(u)->second;

        const auto adjs = g.find(u)->second;
        const auto fb = count(begin(adjs), end(adjs), b);

        for (int i = 0; i < fb; i++) {
            reach_b.push_back(e + 1);
        }

        if (fb == 0)
            for (const auto adj : adjs)
                if (erdos.insert({adj, e + 1}).second || erdos.find(adj)->second == e + 1)
                    q.push(adj);
    }

    auto min = *min_element(begin(reach_b), end(reach_b));
    auto num = count(begin(reach_b), end(reach_b), min);
    return {min, num};
}

void from_stream(graph &g, istream &input, const int nodes, const int arches) {
    for (node n = 0; n < nodes; n++) {
        add_node(g, n);
    }

    for (auto i = 0; i < arches; i++) {
        node a;
        node b;

        input >> a >> b;
        add_arch(g, a, b);
    }
}

pair<long, int> min_paths(std::istream &input) {
    int n;
    int m;
    node s;
    node t;

    input >> n >> m >> s >> t;
    graph g;
    from_stream(g, input, n, m);
    return min_paths(g, s, t);
}

#endif //PATHS_HPP
