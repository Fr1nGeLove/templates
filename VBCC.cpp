struct VBCC {
    int n;
    std::vector<std::vector<int>> adj;
    std::vector<int> stk;
    std::vector<int> dfn, low;
    std::vector<std::vector<int>> dcc;
    int cur;
    
    VBCC() {}
    VBCC(int n) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        adj.assign(n, {});
        dfn.assign(n, -1);
        low.resize(n);
        stk.clear();
        cur = 0;
    }
    
    void addEdge(int u, int v) {
        if (u != v) {
            adj[u].push_back(v);
            adj[v].push_back(u);
        }
    }
    
    void dfs(int x, int p) {
        dfn[x] = low[x] = cur++;
        stk.push_back(x);
        
        if (p == -1 && adj[x].size() == 0) {
            dcc.push_back({x}); 
            return;
        }
        for (auto y : adj[x]) {
            if (y == p) {
                continue;
            }
            if (dfn[y] == -1) {
                dfs(y, x);
                low[x] = std::min(low[x], low[y]);
                if (low[y] >= dfn[x]) {
                    std::vector<int> t;
                    int z;
                    do {
                        z = stk.back();
                        t.push_back(z);
                        stk.pop_back();
                    } while (z != y);
                    t.push_back(x);
                    dcc.push_back(t);
                }
            } else if (dfn[x] > dfn[y]) {
                low[x] = std::min(low[x], dfn[y]);
            }
        }

    }
    
    void work(int root = 0) {
        dfs(root, -1);
    }
};