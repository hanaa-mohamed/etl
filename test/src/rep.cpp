//=======================================================================
// Copyright (c) 2014-2016 Baptiste Wicht
// Distributed under the terms of the MIT License.
// (See accompanying file LICENSE or copy at
//  http://opensource.org/licenses/MIT)
//=======================================================================

#include "test_light.hpp"

// Tests for rep_r

TEMPLATE_TEST_CASE_2("rep/fast_matrix_1", "rep", Z, float, double) {
    etl::fast_matrix<Z, 3> a({1.0, -2.0, 3.0});
    etl::fast_matrix<Z, 3, 3> b(etl::rep<3>(a));

    REQUIRE_EQUALS(b(0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1), 1.0);
    REQUIRE_EQUALS(b(0, 2), 1.0);
    REQUIRE_EQUALS(b(1, 0), -2.0);
    REQUIRE_EQUALS(b(1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 2), -2.0);
    REQUIRE_EQUALS(b(2, 0), 3.0);
    REQUIRE_EQUALS(b(2, 1), 3.0);
    REQUIRE_EQUALS(b(2, 2), 3.0);
}

TEMPLATE_TEST_CASE_2("rep/fast_matrix_2", "rep", Z, float, double) {
    etl::fast_matrix<Z, 3> a({1.0, -2.0, 3.0});
    etl::fast_matrix<Z, 3, 3> b;

    b = etl::rep<3>(a);

    REQUIRE_EQUALS(b(0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1), 1.0);
    REQUIRE_EQUALS(b(0, 2), 1.0);
    REQUIRE_EQUALS(b(1, 0), -2.0);
    REQUIRE_EQUALS(b(1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 2), -2.0);
    REQUIRE_EQUALS(b(2, 0), 3.0);
    REQUIRE_EQUALS(b(2, 1), 3.0);
    REQUIRE_EQUALS(b(2, 2), 3.0);
}

TEMPLATE_TEST_CASE_2("rep/fast_matrix_3", "rep", Z, float, double) {
    etl::fast_matrix<Z, 3> a({1.0, -2.0, 3.0});
    etl::fast_matrix<Z, 3, 3, 2> b;

    b = etl::rep<3, 2>(a);

    REQUIRE_EQUALS(b(0, 0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 0, 1), 1.0);
    REQUIRE_EQUALS(b(0, 1, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1, 1), 1.0);
    REQUIRE_EQUALS(b(0, 2, 0), 1.0);
    REQUIRE_EQUALS(b(0, 2, 1), 1.0);
    REQUIRE_EQUALS(b(1, 0, 0), -2.0);
    REQUIRE_EQUALS(b(1, 0, 1), -2.0);
    REQUIRE_EQUALS(b(1, 1, 0), -2.0);
    REQUIRE_EQUALS(b(1, 1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 2, 0), -2.0);
    REQUIRE_EQUALS(b(1, 2, 1), -2.0);
    REQUIRE_EQUALS(b(2, 0, 0), 3.0);
    REQUIRE_EQUALS(b(2, 0, 1), 3.0);
    REQUIRE_EQUALS(b(2, 1, 0), 3.0);
    REQUIRE_EQUALS(b(2, 1, 1), 3.0);
    REQUIRE_EQUALS(b(2, 2, 0), 3.0);
    REQUIRE_EQUALS(b(2, 2, 1), 3.0);
}

TEMPLATE_TEST_CASE_2("rep/fast_matrix_4", "rep", Z, float, double) {
    etl::fast_matrix<Z, 1> a({1.0});
    etl::fast_matrix<Z, 1, 3, 2, 5, 7> b;

    b = etl::rep<3, 2, 5, 7>(a);

    for (auto v : b) {
        REQUIRE_EQUALS(v, 1.0);
    }
}

TEMPLATE_TEST_CASE_2("rep/fast_matrix_5", "rep", Z, float, double) {
    etl::fast_matrix<Z, 2, 3> a({1.0, -2.0, 3.0, -4.0, 5.0, -6.0});
    etl::fast_matrix<Z, 2, 3, 3, 2> b;

    b = etl::rep<3, 2>(a);

    REQUIRE_EQUALS(b(0, 0, 0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1, 0, 0), -2.0);
    REQUIRE_EQUALS(b(0, 2, 0, 0), 3.0);
    REQUIRE_EQUALS(b(1, 0, 0, 0), -4.0);
    REQUIRE_EQUALS(b(1, 1, 0, 0), 5.0);
    REQUIRE_EQUALS(b(1, 2, 0, 0), -6.0);

    REQUIRE_EQUALS(b(0, 0, 0, 1), 1.0);
    REQUIRE_EQUALS(b(0, 1, 2, 0), -2.0);
    REQUIRE_EQUALS(b(0, 2, 0, 1), 3.0);
    REQUIRE_EQUALS(b(1, 0, 0, 0), -4.0);
    REQUIRE_EQUALS(b(1, 1, 1, 1), 5.0);
    REQUIRE_EQUALS(b(1, 2, 0, 0), -6.0);
}

TEMPLATE_TEST_CASE_2("rep/fast_matrix_6", "rep", Z, float, double) {
    etl::fast_matrix<Z, 2, 3> a({1.0, -2.0, 3.0, -4.0, 5.0, -6.0});

    auto b = etl::rep<3, 2>(a);

    REQUIRE_EQUALS(b(0, 0, 0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1, 0, 0), -2.0);
    REQUIRE_EQUALS(b(0, 2, 0, 0), 3.0);
    REQUIRE_EQUALS(b(1, 0, 0, 0), -4.0);
    REQUIRE_EQUALS(b(1, 1, 0, 0), 5.0);
    REQUIRE_EQUALS(b(1, 2, 0, 0), -6.0);

    REQUIRE_EQUALS(b(0, 0, 0, 1), 1.0);
    REQUIRE_EQUALS(b(0, 1, 2, 0), -2.0);
    REQUIRE_EQUALS(b(0, 2, 0, 1), 3.0);
    REQUIRE_EQUALS(b(1, 0, 0, 0), -4.0);
    REQUIRE_EQUALS(b(1, 1, 1, 1), 5.0);
    REQUIRE_EQUALS(b(1, 2, 0, 0), -6.0);
}

TEMPLATE_TEST_CASE_2("rep/dyn_matrix_1", "rep", Z, float, double) {
    etl::dyn_vector<Z> a(3, etl::values(1.0, -2.0, 3.0));
    etl::dyn_matrix<Z> b(etl::rep<3>(a));

    REQUIRE_EQUALS(b(0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1), 1.0);
    REQUIRE_EQUALS(b(0, 2), 1.0);
    REQUIRE_EQUALS(b(1, 0), -2.0);
    REQUIRE_EQUALS(b(1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 2), -2.0);
    REQUIRE_EQUALS(b(2, 0), 3.0);
    REQUIRE_EQUALS(b(2, 1), 3.0);
    REQUIRE_EQUALS(b(2, 2), 3.0);
}

TEMPLATE_TEST_CASE_2("rep/dyn_matrix_2", "rep", Z, float, double) {
    etl::dyn_vector<Z> a(3, etl::values(1.0, -2.0, 3.0));
    etl::dyn_matrix<Z> b(3, 3);

    b = etl::rep<3>(a);

    REQUIRE_EQUALS(b(0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1), 1.0);
    REQUIRE_EQUALS(b(0, 2), 1.0);
    REQUIRE_EQUALS(b(1, 0), -2.0);
    REQUIRE_EQUALS(b(1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 2), -2.0);
    REQUIRE_EQUALS(b(2, 0), 3.0);
    REQUIRE_EQUALS(b(2, 1), 3.0);
    REQUIRE_EQUALS(b(2, 2), 3.0);
}

TEMPLATE_TEST_CASE_2("rep/dyn_matrix_3", "rep", Z, float, double) {
    etl::dyn_vector<Z> a(3, etl::values(1.0, -2.0, 3.0));
    etl::dyn_matrix<Z, 3> b(3, 3, 2);

    b = etl::rep<3, 2>(a);

    REQUIRE_EQUALS(b(0, 0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 0, 1), 1.0);
    REQUIRE_EQUALS(b(0, 1, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1, 1), 1.0);
    REQUIRE_EQUALS(b(0, 2, 0), 1.0);
    REQUIRE_EQUALS(b(0, 2, 1), 1.0);
    REQUIRE_EQUALS(b(1, 0, 0), -2.0);
    REQUIRE_EQUALS(b(1, 0, 1), -2.0);
    REQUIRE_EQUALS(b(1, 1, 0), -2.0);
    REQUIRE_EQUALS(b(1, 1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 2, 0), -2.0);
    REQUIRE_EQUALS(b(1, 2, 1), -2.0);
    REQUIRE_EQUALS(b(2, 0, 0), 3.0);
    REQUIRE_EQUALS(b(2, 0, 1), 3.0);
    REQUIRE_EQUALS(b(2, 1, 0), 3.0);
    REQUIRE_EQUALS(b(2, 1, 1), 3.0);
    REQUIRE_EQUALS(b(2, 2, 0), 3.0);
    REQUIRE_EQUALS(b(2, 2, 1), 3.0);
}

TEMPLATE_TEST_CASE_2("rep/dyn_matrix_4", "rep", Z, float, double) {
    etl::dyn_vector<Z> a(1, 1.0);
    etl::dyn_matrix<Z, 5> b(1, 3, 2, 5, 7);

    b = etl::rep<3, 2, 5, 7>(a);

    for (auto v : b) {
        REQUIRE_EQUALS(v, 1.0);
    }
}

// Tests for rep_l

TEMPLATE_TEST_CASE_2("rep_l/fast_matrix_1", "rep", Z, float, double) {
    etl::fast_matrix<Z, 3> a({1.0, -2.0, 3.0});
    etl::fast_matrix<Z, 3, 3> b(etl::rep_l<3>(a));

    REQUIRE_EQUALS(b(0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1), -2.0);
    REQUIRE_EQUALS(b(0, 2), 3.0);
    REQUIRE_EQUALS(b(1, 0), 1.0);
    REQUIRE_EQUALS(b(1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 2), 3.0);
    REQUIRE_EQUALS(b(2, 0), 1.0);
    REQUIRE_EQUALS(b(2, 1), -2.0);
    REQUIRE_EQUALS(b(2, 2), 3.0);
}

TEMPLATE_TEST_CASE_2("rep_l/fast_matrix_2", "rep", Z, float, double) {
    etl::fast_matrix<Z, 3> a({1.0, -2.0, 3.0});
    etl::fast_matrix<Z, 3, 3> b;

    b = etl::rep_l<3>(a);

    REQUIRE_EQUALS(b(0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1), -2.0);
    REQUIRE_EQUALS(b(0, 2), 3.0);
    REQUIRE_EQUALS(b(1, 0), 1.0);
    REQUIRE_EQUALS(b(1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 2), 3.0);
    REQUIRE_EQUALS(b(2, 0), 1.0);
    REQUIRE_EQUALS(b(2, 1), -2.0);
    REQUIRE_EQUALS(b(2, 2), 3.0);
}

TEMPLATE_TEST_CASE_2("rep_l/fast_matrix_3", "rep", Z, float, double) {
    etl::fast_matrix<Z, 3> a({1.0, -2.0, 3.0});
    etl::fast_matrix<Z, 3, 2, 3> b;

    b = etl::rep_l<3, 2>(a);

    REQUIRE_EQUALS(b(0, 0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 0, 1), -2.0);
    REQUIRE_EQUALS(b(0, 0, 2), 3.0);
    REQUIRE_EQUALS(b(0, 1, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1, 1), -2.0);
    REQUIRE_EQUALS(b(0, 1, 2), 3.0);
    REQUIRE_EQUALS(b(1, 0, 0), 1.0);
    REQUIRE_EQUALS(b(1, 0, 1), -2.0);
    REQUIRE_EQUALS(b(1, 0, 2), 3.0);
    REQUIRE_EQUALS(b(1, 1, 0), 1.0);
    REQUIRE_EQUALS(b(1, 1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 1, 2), 3.0);
    REQUIRE_EQUALS(b(2, 0, 0), 1.0);
    REQUIRE_EQUALS(b(2, 0, 1), -2.0);
    REQUIRE_EQUALS(b(2, 0, 2), 3.0);
    REQUIRE_EQUALS(b(2, 1, 0), 1.0);
    REQUIRE_EQUALS(b(2, 1, 1), -2.0);
    REQUIRE_EQUALS(b(2, 1, 2), 3.0);
}

TEMPLATE_TEST_CASE_2("rep_l/fast_matrix_4", "rep", Z, float, double) {
    etl::fast_matrix<Z, 1> a({1.0});
    etl::fast_matrix<Z, 3, 2, 5, 7, 1> b;

    b = etl::rep_l<3, 2, 5, 7>(a);

    for (auto v : b) {
        REQUIRE_EQUALS(v, 1.0);
    }
}

TEMPLATE_TEST_CASE_2("rep_l/fast_matrix_5", "rep", Z, float, double) {
    etl::fast_matrix<Z, 2, 3> a({1.0, -2.0, 3.0, -4.0, 5.0, -6.0});
    etl::fast_matrix<Z, 3, 4, 2, 3> b(etl::rep_l<3, 4>(a));

    REQUIRE_EQUALS(b(0, 0, 0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 0, 0, 1), -2.0);
    REQUIRE_EQUALS(b(0, 0, 0, 2), 3.0);
    REQUIRE_EQUALS(b(0, 0, 1, 0), -4.0);
    REQUIRE_EQUALS(b(0, 0, 1, 1), 5.0);
    REQUIRE_EQUALS(b(0, 0, 1, 2), -6.0);

    REQUIRE_EQUALS(b(0, 1, 0, 0), 1.0);
    REQUIRE_EQUALS(b(1, 0, 0, 1), -2.0);
    REQUIRE_EQUALS(b(0, 2, 0, 2), 3.0);
    REQUIRE_EQUALS(b(2, 2, 1, 0), -4.0);
    REQUIRE_EQUALS(b(1, 1, 1, 1), 5.0);
    REQUIRE_EQUALS(b(0, 0, 1, 2), -6.0);
}

TEMPLATE_TEST_CASE_2("rep_l/fast_matrix_6", "rep", Z, float, double) {
    etl::fast_matrix<Z, 2, 3> a({1.0, -2.0, 3.0, -4.0, 5.0, -6.0});

    auto b = etl::rep_l<3, 4>(a);

    REQUIRE_EQUALS(b(0, 0, 0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 0, 0, 1), -2.0);
    REQUIRE_EQUALS(b(0, 0, 0, 2), 3.0);
    REQUIRE_EQUALS(b(0, 0, 1, 0), -4.0);
    REQUIRE_EQUALS(b(0, 0, 1, 1), 5.0);
    REQUIRE_EQUALS(b(0, 0, 1, 2), -6.0);

    REQUIRE_EQUALS(b(0, 1, 0, 0), 1.0);
    REQUIRE_EQUALS(b(1, 0, 0, 1), -2.0);
    REQUIRE_EQUALS(b(0, 2, 0, 2), 3.0);
    REQUIRE_EQUALS(b(2, 2, 1, 0), -4.0);
    REQUIRE_EQUALS(b(1, 1, 1, 1), 5.0);
    REQUIRE_EQUALS(b(0, 0, 1, 2), -6.0);
}

TEMPLATE_TEST_CASE_2("rep_l/dyn_matrix_1", "rep", Z, float, double) {
    etl::dyn_vector<Z> a(3, etl::values(1.0, -2.0, 3.0));
    etl::dyn_matrix<Z> b(etl::rep_l<3>(a));

    REQUIRE_EQUALS(b(0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1), -2.0);
    REQUIRE_EQUALS(b(0, 2), 3.0);
    REQUIRE_EQUALS(b(1, 0), 1.0);
    REQUIRE_EQUALS(b(1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 2), 3.0);
    REQUIRE_EQUALS(b(2, 0), 1.0);
    REQUIRE_EQUALS(b(2, 1), -2.0);
    REQUIRE_EQUALS(b(2, 2), 3.0);
}

TEMPLATE_TEST_CASE_2("rep_l/dyn_matrix_2", "rep", Z, float, double) {
    etl::dyn_vector<Z> a(3, etl::values(1.0, -2.0, 3.0));
    etl::dyn_matrix<Z> b(3, 3);

    b = etl::rep_l<3>(a);

    REQUIRE_EQUALS(b(0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1), -2.0);
    REQUIRE_EQUALS(b(0, 2), 3.0);
    REQUIRE_EQUALS(b(1, 0), 1.0);
    REQUIRE_EQUALS(b(1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 2), 3.0);
    REQUIRE_EQUALS(b(2, 0), 1.0);
    REQUIRE_EQUALS(b(2, 1), -2.0);
    REQUIRE_EQUALS(b(2, 2), 3.0);
}

TEMPLATE_TEST_CASE_2("rep_l/dyn_matrix_3", "rep", Z, float, double) {
    etl::dyn_vector<Z> a(3, etl::values(1.0, -2.0, 3.0));
    etl::dyn_matrix<Z, 3> b(3, 2, 3);

    b = etl::rep_l<3, 2>(a);

    REQUIRE_EQUALS(b(0, 0, 0), 1.0);
    REQUIRE_EQUALS(b(0, 0, 1), -2.0);
    REQUIRE_EQUALS(b(0, 0, 2), 3.0);
    REQUIRE_EQUALS(b(0, 1, 0), 1.0);
    REQUIRE_EQUALS(b(0, 1, 1), -2.0);
    REQUIRE_EQUALS(b(0, 1, 2), 3.0);
    REQUIRE_EQUALS(b(1, 0, 0), 1.0);
    REQUIRE_EQUALS(b(1, 0, 1), -2.0);
    REQUIRE_EQUALS(b(1, 0, 2), 3.0);
    REQUIRE_EQUALS(b(1, 1, 0), 1.0);
    REQUIRE_EQUALS(b(1, 1, 1), -2.0);
    REQUIRE_EQUALS(b(1, 1, 2), 3.0);
    REQUIRE_EQUALS(b(2, 0, 0), 1.0);
    REQUIRE_EQUALS(b(2, 0, 1), -2.0);
    REQUIRE_EQUALS(b(2, 0, 2), 3.0);
    REQUIRE_EQUALS(b(2, 1, 0), 1.0);
    REQUIRE_EQUALS(b(2, 1, 1), -2.0);
    REQUIRE_EQUALS(b(2, 1, 2), 3.0);
}

TEMPLATE_TEST_CASE_2("rep_l/dyn_matrix_4", "rep", Z, float, double) {
    etl::dyn_vector<Z> a(1, 1.0);
    etl::dyn_matrix<Z, 5> b(3, 2, 5, 7, 1);

    b = etl::rep_l<3, 2, 5, 7>(a);

    for (auto v : b) {
        REQUIRE_EQUALS(v, 1.0);
    }
}
