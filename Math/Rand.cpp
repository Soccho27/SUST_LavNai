int rng(){
    static std::mt19937 gen(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<int>(1, INT64_MAX)(gen);
}
