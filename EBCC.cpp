struct EBCC {
    int n;
    std::vector<std::vector<std::pair<int, int>>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low, bel;
    int cur, cnt;
    
    EBCC() {}
    EBCC(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        bel.assign(n, -1);
        stk.clear();
        cur = cnt = 0;
    }
    
    void addEdge(int u, int v, int info) {
        adj[u].push_back({v, info * 2});
        adj[v].push_back({u, info * 2 + 1});
    }
    
    void dfs(int x, int p) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        
        for (auto [y, info] : adj[x]) {
            if (info == (p ^ 1)) {
                continue;
            }
            if (dfn[y] == -1) {
                dfs(y, info);
                low[x] = std::min(low[x], low[y]);
            } else if (bel[y] == -1 && dfn[y] < dfn[x]) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }
        
        if (dfn[x] == low[x]) {
            int y;
            do {
                y = stk.back();
                bel[y] = cnt;
                stk.pop_back();
            } while (y != x);
            cnt++;
        }
    }
    
    std::vector<int> work(int root = 0) {
        dfs(root, -1);
        return bel;
    }
    
    struct Graph {
        int n;
        std::vector<std::pair<int, int>> edges;
        std::vector<int> siz;
        std::vector<int> cnte;
        std::vector<int> deg;
    };
    Graph compress() {
        Graph g;
        g.n = cnt;
        g.siz.resize(cnt);
        g.cnte.resize(cnt);
        g.deg.resize(cnt);
        for (int i = 0; i < n; i++) {
            g.siz[bel[i]]++;
            for (auto [j, _] : adj[i]) {
                if (bel[i] < bel[j]) {
                    g.edges.emplace_back(bel[i], bel[j]);
                    g.deg[bel[i]]++;
                    g.deg[bel[j]]++;
                } else if (bel[i] == bel[j] && i < j) {
                    g.cnte[bel[i]]++;
                }
            }
        }
        return g;
    }
};