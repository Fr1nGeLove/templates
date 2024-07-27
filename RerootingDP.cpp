std::vector<int> siz(n);
std::vector<Z> dis(n, -1);
dis[0] = 0;

auto dfs1 = [&](auto self, int x, int p) -> void {
    siz[x] = 1;
    for (auto [y, w] : adj[x]) {
        if (y == p) {
            continue;
        }
        dis[y] = dis[x] + w;
        self(self, y, x);
        siz[x] += siz[y];
    }
};
dfs1(dfs1, 0, -1);

dis[0] = std::accumulate(dis.begin(), dis.end(), Z(0));
std::fill(dis.begin() + 1, dis.end(), -1);

auto dfs2 = [&](auto self, int x, int p) -> void {
    for (auto [y, w] : adj[x]) {
        if (y == p) {
            continue;
        }
        dis[y] = dis[x] + Z(w) * (n - 2 * siz[y]);
        self(self, y, x);
    }
};
dfs2(dfs2, 0, -1);