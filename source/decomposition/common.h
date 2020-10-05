#ifndef DECOMPOSITION_LIBRARY_COMMON_H
#define DECOMPOSITION_LIBRARY_COMMON_H

#include <string>
#include <iostream>
#include <chrono>
#include <random>
#include <utility>

namespace decompose {
    typedef double scalar;

    enum class debug_level { None, Low, High };

    enum class status {
        NotStarted = -1,
        Continue = 0,
        IterationLimit,
        EvaluationLimit,
        FOptimum
    };

    inline scalar max_limits() { return std::numeric_limits<scalar>::max(); }

    inline std::default_random_engine &default_generator() {
        static std::default_random_engine generator_(
            (int)std::chrono::system_clock::now().time_since_epoch().count());
        return generator_;
    }

    class options{

    protected:
        // Differential Grouping Method
       scalar dg_epsilon;

        // Fast Interdependency Identification Method
        scalar fii_epsilon_1;
        scalar fii_epsilon_2;
        scalar fii_sigma;
        scalar fii_delta;

        // Global Differential Grouping Method
        scalar gdg_alpha;
        size_t gdg_k;

        // Extended Differential Grouping Method
        scalar xdg_epsilon;

        // Random Grouping
        size_t rg_number_groups;

        // Recursive Differential Grouping 1 - Method
        scalar rdg_1_alpha;
        size_t rdg_1_k;

        // Recursive Differential Grouping 3 - Method
        size_t rdg_3_epsilon_n;

    public:

        static options defaults() {
            options op_{};
            // DG
            op_.dg_epsilon = 0.1;
            // FII
            op_.fii_epsilon_1 = 0.01;
            op_.fii_epsilon_2 = 0.01;
            op_.fii_sigma = 10.0;
            op_.fii_delta = 10.0;
            // GDG
            op_.gdg_alpha = 1e-25;
            op_.gdg_k = 10;
            // XDG
            op_.xdg_epsilon = 0.1;
            // Random Grouping
            op_.rg_number_groups = 2;
            // Recursive Differential Grouping 1 - Method
            op_.rdg_1_alpha = 1e-12;
            op_.rdg_1_k = 10;
            // Recursive Differential Grouping 3 - Method
            op_.rdg_3_epsilon_n = 50;
            return op_;
        }

        scalar get_dg_epsilon() const{
            return dg_epsilon;
        }

        void set_dg_epsilon(scalar s){
            dg_epsilon = s;
        }

        scalar get_fii_epsilon_1() const{
            return fii_epsilon_1;
        }

        void set_fii_epsilon_1(scalar s){
            fii_epsilon_1 = s;
        }

        scalar get_fii_epsilon_2() const{
            return fii_epsilon_2;
        }

        void set_fii_epsilon_2(scalar s){
            fii_epsilon_2 = s;
        }

        scalar get_fii_sigma() const{
            return fii_sigma;
        }

        void set_fii_sigma(scalar s){
            fii_sigma = s;
        }

        scalar get_fii_delta() const{
            return fii_delta;
        }

        void set_fii_delta(scalar s){
            fii_delta = s;
        }

        scalar get_gdg_alpha() const{
            return gdg_alpha;
        }

        void set_gdg_alpha(scalar s){
            gdg_alpha = s;
        }

        scalar get_xdg_epsilon() const{
            return xdg_epsilon;
        }

        void set_xdg_epsilon(scalar s){
            xdg_epsilon = s;
        }

        size_t get_gdg_k() const{
            return gdg_k;
        }

        void set_gdg_k(size_t s){
            gdg_k = s;
        }

        size_t get_rg_number_groups() const{
            return rg_number_groups;
        }

        void set_rg_number_groups(size_t s){
            rg_number_groups = s;
        }

        size_t get_rdg_1_k() const{
            return rdg_1_k;
        }

        void set_rdg_1_k(size_t s){
            rdg_1_k = s;
        }

        scalar get_rdg_1_alpha() const{
            return rdg_1_alpha;
        }

        void set_rdg_1_alpha(scalar s){
            rdg_1_alpha = s;
        }

        scalar get_rdg_3_epsilon_n() const{
            return rdg_3_epsilon_n;
        }

        void set_rdg_3_epsilon_n(size_t s){
            rdg_3_epsilon_n = s;
        }
    };

    class criteria {
    public:
        long iterations{};
        long evaluations{};
        bool fx_is_know{};
        scalar fx_best{};
        scalar error_fx_best{};

        criteria() {
            reset();
        }

        static criteria defaults() {
            criteria d;
            d.iterations = 10000;
            d.evaluations = 1000000;
            d.fx_is_know = false;
            d.fx_best = max_limits();
            d.error_fx_best = 0.0;
            return d;
        }

        void reset() {
            iterations = 0;
            evaluations = 0;
            fx_best = max_limits();
        }

        void print(std::ostream &os) const {
            os << "Iterations:  " << iterations << std::endl;
            os << "Evaluations: " << evaluations << std::endl;
            os << "f(x_best):   " << fx_best << std::endl;
        }
    };


    class stats{
        struct stat{
            scalar fx;
            size_t evaluation;
            std::chrono::duration<double> time;
        };

    private:
        std::vector<stat> history;
        std::chrono::steady_clock::time_point starting_time;

    public:
        explicit stats() = default;

        void push(scalar fx, size_t e){
            if (history.empty()) {
                stat s{};
                s.fx = fx;
                s.evaluation = e;
                s.time = std::chrono::steady_clock::now() - starting_time;
                history.push_back(s);
            } else if (fx < history.back().fx) {
                stat s{};
                s.fx = fx;
                s.evaluation = e;
                s.time = std::chrono::steady_clock::now() - starting_time;
                history.push_back(s);
            }
        }

        std::vector<stat> get_history(){
            return history;
        }

        void reset(){
            history.clear();
            starting_time = std::chrono::steady_clock::now();
        }
    };
    
}
#endif
