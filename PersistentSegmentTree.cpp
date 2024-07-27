struct Node {
    Node *l = nullptr;
    Node *r = nullptr;
    int cnt = 0;
};

Node *add(Node* t, int l, int r, int x) {
    Node *nt = new Node();
    if (t) {
        *nt = *t;
    }
    nt->cnt++;
    if (r - l > 1) {
        int m = (l + r) / 2;
        if (x < m) {
            nt->l = add(nt->l, l, m, x);
        } else {
            nt->r = add(nt->r, m, r, x);
        }
    }
    return nt;
}

int query(Node *t1, Node *t2, int l, int r, int k) {
    if (r - l == 1) {
        return l;
    }
    int sum = 0;
    if (t2 && t2->l) {
        sum += t2->l->cnt;
    }
    if (t1 && t1->l) {
        sum -= t1->l->cnt;
    }
    int m = (l + r) / 2;
    if (k <= sum) {
        return query(t1 ? t1->l : nullptr, t2 ? t2->l : nullptr, l, m, k);
    } else {
        return query(t1 ? t1->r : nullptr, t2 ? t2->r : nullptr, m, r, k - sum);
    }
}