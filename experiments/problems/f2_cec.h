//
// Created by rodolfo on 02/12/19.
//

#include "../../external/cec2013_benchmark_functions/include/cec2013/F2.h"
#include <decomposition/optimization_problem.h>

#ifndef CONTINUOUS_NON_LINEAR_OPTIMIZATION_F2_H
#define CONTINUOUS_NON_LINEAR_OPTIMIZATION_F2_H

using namespace decompose;

class f2_cec : public optimization_problem {
  public:
    using super = optimization_problem;

  protected:
    F2 f;
    scalar fx_star = 0.0;

  public:
    explicit f2_cec(size_t dimension, std::vector<scalar> lower_bound,
                    std::vector<scalar> upper_bound)
        : super(dimension, std::move(lower_bound), std::move(upper_bound)) {}

    scalar get_fx_start() { return fx_star; }

    scalar value(const std::vector<scalar> &x) override {
        const size_t dim = x.size();
        scalar *x_ = new scalar[dim];
        for (size_t i = 0; i < dim; i++) {
            x_[i] = x[i];
        }
        scalar fx = f.compute(x_);
        delete[] x_;
        return fx;
    }
};

#endif // CONTINUOUS_NON_LINEAR_OPTIMIZATION_F2_H
