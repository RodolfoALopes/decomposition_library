#include "common.h"

using namespace decompose;
using namespace std;

options options::defaults() {
    options op_{};
    op_.dg_epsilon = 0.1;
    op_.fii_epsilon_1 = 0.01;
    op_.fii_epsilon_2 = 0.01;
    op_.fii_sigma = 10.0;
    op_.fii_delta = 10.0;
    op_.gdg_alpha = 1e-25;
    op_.gdg_k = 10;
    op_.xdg_epsilon = 0.1;
    op_.rg_number_groups = 2;
    op_.rdg_1_alpha = 1e-12;
    op_.rdg_1_k = 10;
    op_.rdg_3_epsilon_n = 50;
    return op_;
}

scalar  options::get_dg_epsilon() const{
    return dg_epsilon;
}

void options::set_dg_epsilon(scalar s){
    dg_epsilon = s;
}

scalar options::get_fii_epsilon_1() const{
    return fii_epsilon_1;
}

void options::set_fii_epsilon_1(scalar s){
    fii_epsilon_1 = s;
}

scalar options::get_fii_epsilon_2() const{
    return fii_epsilon_2;
}

void options::set_fii_epsilon_2(scalar s){
    fii_epsilon_2 = s;
}

scalar options::get_fii_sigma() const{
    return fii_sigma;
}

void options::set_fii_sigma(scalar s){
    fii_sigma = s;
}

scalar options::get_fii_delta() const{
    return fii_delta;
}

void options::set_fii_delta(scalar s){
    fii_delta = s;
}

scalar options::get_gdg_alpha() const{
    return gdg_alpha;
}

void options::set_gdg_alpha(scalar s){
    gdg_alpha = s;
}

scalar options::get_xdg_epsilon() const{
    return xdg_epsilon;
}

void options::set_xdg_epsilon(scalar s){
    xdg_epsilon = s;
}

size_t options::get_gdg_k() const{
    return gdg_k;
}

void options::set_gdg_k(size_t s){
    gdg_k = s;
}

size_t options::get_rg_number_groups() const{
    return rg_number_groups;
}

void options::set_rg_number_groups(size_t s){
    rg_number_groups = s;
}

size_t options::get_rdg_1_k() const{
    return rdg_1_k;
}

void options::set_rdg_1_k(size_t s){
    rdg_1_k = s;
}

scalar options::get_rdg_1_alpha() const{
    return rdg_1_alpha;
}

void options::set_rdg_1_alpha(scalar s){
    rdg_1_alpha = s;
}

scalar options::get_rdg_3_epsilon_n() const{
    return rdg_3_epsilon_n;
}

void options::set_rdg_3_epsilon_n(size_t s){
    rdg_3_epsilon_n = s;
}


criteria::criteria() {
    reset();
}

criteria criteria::defaults() {
    criteria d;
    d.iterations = 10000;
    d.evaluations = 1000000;
    d.fx_is_know = false;
    d.fx_best = max_limits();
    d.error_fx_best = 0.0;
    return d;
}

void criteria::reset() {
    iterations = 0;
    evaluations = 0;
    fx_best = max_limits();
}

void criteria::print(std::ostream &os) const {
    os << "Iterations:  " << iterations << std::endl;
    os << "Evaluations: " << evaluations << std::endl;
    os << "f(x_best):   " << (scalar)fx_best << std::endl;
}

void stats::push(scalar fx, size_t e){
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

std::vector<stats::stat> stats::get_history(){
    return history;
}

void stats::reset(){
    history.clear();
    starting_time = std::chrono::steady_clock::now();
}