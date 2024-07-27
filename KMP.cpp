std::vector<int> f(n + 1);

for (int i = 1, j = 0; i < n; i++) {
    while (j && p[i] != p[j]) {
        j = f[j];
    }
    j += (p[i] == p[j]);
    f[i + 1] = j;
}

for (int i = 0, j = 0; i < m; i++) {
    while (j && s[i] != p[j]) {
        j = f[j];
    }
    j += (s[i] == p[j]);
    if (j == n) {
        std::cout << i - j + 1 << " ";
        j = f[j];
    }
}