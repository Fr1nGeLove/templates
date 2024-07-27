int minRotation(std::vector<int> s) {
    int a = 0, N = s.size();
    for (int i = 0; i < N; i++) {
        s.push_back(s[i]);
    }
    for (int b = 0; b < N; b++) {
        for (int k = 0; k < N; k++) {
            if (a + k == b || s[a + k] < s[b + k]) {
                b += std::max(0, k - 1);
                break;
            }
            if (s[a + k] > s[b + k]) {
                a = b;
                break;
            }
        }
    }
    return a;
}