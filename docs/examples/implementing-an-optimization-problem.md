---
layout: default
title: Implementing an Optimization Problem
nav_order: 1
has_children: false
parent: Examples
grand_parent: 
has_toc: false
---
# Implementing an Optimization Problem

The code below presents an optimization problem example:

```cpp
#include "problem.h"

using namespace decompose;

class problem_example_1 : public problem {
public:
    using super = problem;

public:
    explicit problem_example_1(size_t dim, vector<scalar> lower_bound, vector<scalar> upper_bound) : super(dim, std::move(lower_bound), std::move(upper_bound)) {}

    scalar value(const vector<scalar> &x) override {
        scalar sum = 0.0;
        for(scalar x_i : x){
            sum += x_i * x_i;
        }
        return sum;
    }
};
```





<!-- Generated with mdsplit: https://github.com/alandefreitas/mdsplit -->
