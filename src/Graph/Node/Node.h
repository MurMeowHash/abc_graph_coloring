#pragma once

#include "../../utils/utils.h"
#include <vector>

struct Node {
    static constexpr int ABSENT_COLOR{-1};
    static constexpr const char *ABSENT_NAME{"NONE"};
    int color;
    const char *name;
    Node();
    explicit Node(const char *name);
};