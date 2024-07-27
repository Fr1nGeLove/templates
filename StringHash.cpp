struct H {
	using u64 = unsigned long long;
	u64 x; 
    H(u64 x = 0) : x(x) {}
#define OP(O, A, B) H operator O(H o) { u64 r = x; asm \
	(A "addq %%rdx, %0\n adcq $0,%0" : "+a"(r) : B); return r; }
	OP(+, , "d"(o.x))
    OP(*,"mul %1\n", "r"(o.x) : "rdx")
	H operator-(H o) { 
        return *this + ~o.x; 
    }
	u64 get() const { 
        return x + !~x; 
    }
	bool operator==(H o) const { 
        return get() == o.get(); 
    }
	bool operator<(H o) const { 
        return get() < o.get(); 
    }
};
static const H C = i64(1E11) + 3; // (order ~ 3e9; random also ok)

struct StringHash {
	std::vector<H> ha, pw;
	StringHash(std::string& str) : ha(str.size() + 1), pw(ha) {
		pw[0] = 1;
        for (int i = 0; i < str.size(); i++) {
			ha[i + 1] = ha[i] * C + str[i],
			pw[i + 1] = pw[i] * C;
        }
	}
	H get(int l, int r) {
		return ha[r] - ha[l] * pw[r - l];
	}
};