struct Trie {
    static constexpr int ALPHABET = 26;
    struct Node {
        std::array<int, ALPHABET> next;
        Node() : next{} {}
    };
    
    std::vector<Node> t;
    std::vector<int> num;
    
    Trie() {
        init();
    }
    
    void init() {
        t.assign(2, Node());
        t[0].next.fill(1);
        num.resize(2);
    }
    
    int newNode() {
        t.emplace_back();
        num.emplace_back();
        return t.size() - 1;
    }
    
    int add(const std::vector<int> &a) {
        int p = 1;
        for (auto x : a) {
            if (t[p].next[x] == 0) {
                t[p].next[x] = newNode();
            }
            p = t[p].next[x];
        }
        num[p]++;
        return p;
    }
    
    int add(const std::string &a, char offset = 'a') {
        std::vector<int> b(a.size());
        for (int i = 0; i < a.size(); i++) {
            b[i] = a[i] - offset;
        }
        return add(b);
    }

    int query(const std::vector<int> &a) {
        int p = 1; 
        for (auto x : a) {
            if (t[p].next[x] == 0) {
                return 0;
            }
            p = t[p].next[x];
        }
        return num[p];
    }

    int query(const std::string &a, char offset = 'a') {
        std::vector<int> b(a.size());
        for (int i = 0; i < a.size(); i++) {
            b[i] = a[i] - offset;
        }
        return query(b);
    }
};