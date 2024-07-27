struct Node {
	Node *l = nullptr;
	Node *r = nullptr;
	i64 sum = 0;
};

Node *modify(Node *t, int l, int r, int x, int v) {
	Node *t1 = new Node;

	if (t) {
		*t1 = *t;
	}

	t1->sum += v;

	if (r - l > 1) {
		int m = (l + r) / 2;
		if (x < m) {
			t1->l = modify(t1->l, l, m, x, v);
		} else {
			t1->r = modify(t1->r, m, r, x, v);
		}
	}

	return t1;
}

i64 query(Node *t, int l, int r, int x, int y) {
	if (l >= y || r <= x || !t) {
		return 0;
	}

	if (l >= x && r <= y) {
		return t->sum;
	}

	int m = (l + r) / 2;
	return query(t->l, l, m, x, y) + query(t->r, m, r, x, y);
}