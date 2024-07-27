template<class Info, class Tag>
struct JrySegmentTree {
    int n;
    std::vector<Info> info;
    std::vector<Tag> tag;
    JrySegmentTree() : n(0) {}
    JrySegmentTree(int n_, Info v_ = Info()) {
        init(n_, v_);
    }
    template<class T>
    JrySegmentTree(std::vector<T> init_) {
        init(init_);
    }
    void init(int n_, Info v_ = Info()) {
        init(std::vector(n_, v_));
    }
    template<class T>
    void init(std::vector<T> init_) {
        n = init_.size();
        info.assign(4 << std::__lg(n), Info());
        tag.assign(4 << std::__lg(n), Tag());
        std::function<void(int, int, int)> build = [&](int p, int l, int r) {
            if (r - l == 1) {
                info[p] = init_[l];

                return;
            }
            int m = (l + r) / 2;
            build(2 * p, l, m);
            build(2 * p + 1, m, r);
            pull(p);
        };
        build(1, 0, n);
    }
    void pull(int p) {
        info[p] = info[2 * p] + info[2 * p + 1];
    }
    void apply(int p, const Tag &v) {
        info[p].apply(v);
        tag[p].apply(v);
    }
    void push(int p) {
        i64 maxn = std::max(info[p * 2].max1, info[p * 2 + 1].max1);
        for (auto xp : {p * 2, p * 2 + 1}) {
            if (info[xp].max1 == maxn) {
                apply(xp, tag[p]);
            } else {
                apply(xp, {tag[p].x3, tag[p].x4, tag[p].x3, tag[p].x4});
            }
        }
        tag[p] = Tag();
    }
    void modify(int p, int l, int r, int x, const Info &v) {
        if (r - l == 1) {
            info[p] = v;
            return;
        }
        int m = (l + r) / 2;
        push(p);
        if (x < m) {
            modify(2 * p, l, m, x, v);
        } else {
            modify(2 * p + 1, m, r, x, v);
        }
        pull(p);
    }
    void modify(int p, const Info &v) {
        modify(1, 0, n, p, v);
    }
    Info rangeQuery(int p, int l, int r, int x, int y) {
        if (l >= y || r <= x) {
            return Info();
        }
        if (l >= x && r <= y) {
            return info[p];
        }
        int m = (l + r) / 2;
        push(p);
        return rangeQuery(2 * p, l, m, x, y) + rangeQuery(2 * p + 1, m, r, x, y);
    }
    Info rangeQuery(int l, int r) {
        return rangeQuery(1, 0, n, l, r);
    }
    void rangeApply(int p, int l, int r, int x, int y, const Tag &v) {
        if (l >= y || r <= x) {
            return;
        }
        if (l >= x && r <= y) {
            apply(p, v);
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApply(2 * p, l, m, x, y, v);
        rangeApply(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApply(int l, int r, const Tag &v) {
        return rangeApply(1, 0, n, l, r, v);
    }
    void rangeApplyMin(int p, int l, int r, int x, int y, const i64 &v) {
        if (l >= y || r <= x || info[p].max1 <= v) {
            return;
        }
        if (l >= x && r <= y && info[p].max2 < v) {
            apply(p, {v - info[p].max1, v - info[p].max1, 0LL, 0LL});
            return;
        }
        int m = (l + r) / 2;
        push(p);
        rangeApplyMin(2 * p, l, m, x, y, v);
        rangeApplyMin(2 * p + 1, m, r, x, y, v);
        pull(p);
    }
    void rangeApplyMin(int l, int r, const i64 &v) {
        return rangeApplyMin(1, 0, n, l, r, v);
    }
};

struct Tag {
    i64 x1 = 0, x2 = 0, x3 = 0, x4 = 0;

    void apply(const Tag& t) {
        x2 = std::max(x2, x1 + t.x2);
        x1 += t.x1;
        x4 = std::max(x4, x3 + t.x4);
        x3 += t.x3;
    }
};

constexpr i64 inf = std::numeric_limits<i64>::max(); 
struct Info {
    int len = 1, max1cnt = 0;
    i64 sum = 0;
    i64 max1 = -inf, max2 = -inf, hmax = -inf;
    void apply(const Tag& t) {
        sum += t.x1 * max1cnt + t.x3 * (len - max1cnt);
        hmax = std::max(hmax, max1 + t.x2);
        max1 += t.x1;
        if (max2 != -inf) {
            max2 += t.x3;
        }
    }
};

Info operator+(Info a, Info b) {
    Info c;
    c.len = a.len + b.len;
    c.sum = a.sum + b.sum;
    c.max1 = std::max(a.max1, b.max1);
    c.hmax = std::max(a.hmax, b.hmax);
    if (a.max1 == b.max1) {
        c.max1cnt = a.max1cnt + b.max1cnt;
        c.max2 = std::max(a.max2, b.max2);
    } else {
        c.max1cnt = (a.max1 > b.max1 ? a.max1cnt : b.max1cnt);
        c.max2 = (a.max1 > b.max1 ? std::max(b.max1, a.max2) : std::max(a.max1, b.max2));
    }
    return c;
}