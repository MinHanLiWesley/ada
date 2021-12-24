#include "ada-hw4-p3.h"

// feel free to use global variables
std::vector<int> contest;

std::vector<int> init(int N) {
    contest.resize(N);
    for (int i = 0; i < N; ++i)
        contest[i] = i;
    return contest;
}

std::vector<int> insert(int p, int id) {
    contest.insert(contest.begin() + p, id);
    return contest;
}

std::vector<int> remove(int p) {
    contest.erase(contest.begin() + p);
    return contest;
}
