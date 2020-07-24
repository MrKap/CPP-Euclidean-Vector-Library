// euclidean_vector_utility_function_tests
#include "comp6771/euclidean_vector.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fstream>
#include <iostream>
#include <string>

TEST_CASE("Euclidean Normal Test") {
	auto a = comp6771::euclidean_vector(2, 10);
	auto result_1 = comp6771::euclidean_norm(a);
	REQUIRE(result_1 == sqrt(200));

	auto b = comp6771::euclidean_vector{1.0, -69.0, 4.0};
	auto result_2 = comp6771::euclidean_norm(b);
	REQUIRE(result_2 == sqrt(4778));

	// Test exception thrown for empty vector.
	auto c = comp6771::euclidean_vector();
	REQUIRE_THROWS_WITH(comp6771::euclidean_norm(c),
	                    "euclidean_vector with no dimensions does not have a norm");
}

TEST_CASE("Unit Vector Test") {
	auto a = comp6771::euclidean_vector{1.0, -69.0, 4.0};
	auto result = comp6771::unit(a);
	auto expected_result =
	   comp6771::euclidean_vector{(1 / sqrt(4778)), ((-69) / sqrt(4778)), (4 / sqrt(4778))};
	REQUIRE(result == expected_result);

	// Test exception thrown for a vector with euclidean normal equal to 0 .
	auto b = comp6771::euclidean_vector(4, 0);
	REQUIRE_THROWS_WITH(comp6771::unit(b),
	                    "euclidean_vector with zero euclidean normal does not have a unit vector");

	// Test exception thrown for an empty vector.
	auto c = comp6771::euclidean_vector();
	REQUIRE_THROWS_WITH(comp6771::unit(c),
	                    "euclidean_vector with no dimensions does not have a unit vector");
}

TEST_CASE("Dot Product Test") {
	auto a = comp6771::euclidean_vector{1.0, -69.0, 4.0};
	auto b = comp6771::euclidean_vector{2.0, 7.5, -4.0};
	auto result = double{comp6771::dot(a, b)};
	auto expected_result = double{-531.5};
	REQUIRE(result == expected_result);

	// Test exception case when dot product of vectors with diff sizes.
	auto c = comp6771::euclidean_vector{1.0, -69.0, 4.0};
	auto d = comp6771::euclidean_vector{2.0, 7.5, -4.0, 9, 2};
	REQUIRE_THROWS_WITH(double{comp6771::dot(c, d)}, "Dimensions of LHS(3) and RHS(5) do not match");
}