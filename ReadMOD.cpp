i64 reader() {   
    using u64 = unsigned long long;
    constexpr i64 MOD = 998244353;
    char ch = std::cin.get();
    u64 sum1 = 0, sum2 = 0;

    bool tag = false;
    while (!std::isdigit(ch)) {
        ch = std::cin.get();
    }
    while (std::isdigit(ch)) {
        sum1 = (sum1 * 10 + (ch ^ 48)) % MOD, sum2 = sum2 * 10 + (ch ^ 48), sum2 >= P && (sum2 %= P - 1, tag = true), ch = std::cin.get();
    }
    return sum1 + (sum2 - sum1 + 2 * MOD - 2) % (MOD - 1) * MOD + tag * (MOD - 1) * MOD;
}