// euclidean_vector_constructor_tests
#include "comp6771/euclidean_vector.hpp"

#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>

TEST_CASE("No arg constructor test") {
	auto a1 = comp6771::euclidean_vector();
	REQUIRE(a1.dimensions() == 0);
}

TEST_CASE("Only Dimension constructor test") {
	auto a1 = comp6771::euclidean_vector(2);
	REQUIRE(a1.get_size() == 2);
	REQUIRE(a1[0] == 0.0);
	REQUIRE(a1[1] == 0.0);

	int i{3};
	auto b = comp6771::euclidean_vector(i);
	REQUIRE(b.get_size() == 3);
	REQUIRE(b[0] == 0.0);
	REQUIRE(b[1] == 0.0);
	REQUIRE(b[2] == 0.0);
}

TEST_CASE("Magnitude and Dimension constructor test") {
	auto a1 = comp6771::euclidean_vector(4, 3.4);

	REQUIRE(a1.get_size() == 4);
	REQUIRE(a1[0] == 3.4);
	REQUIRE(a1[1] == 3.4);
	REQUIRE(a1[2] == 3.4);
	REQUIRE(a1[3] == 3.4);

	auto x = int{3};
	auto y = double{3.24};
	auto b = comp6771::euclidean_vector(x, y);
	REQUIRE(b.get_size() == 3);
	REQUIRE(b[0] == 3.24);
	REQUIRE(b[1] == 3.24);
	REQUIRE(b[2] == 3.24);
}

TEST_CASE("Iterator Constructor test") {
	auto v = std::vector<double>{5.0, 6.5, 7.0};
	auto b = comp6771::euclidean_vector(v.begin(), v.end());
	REQUIRE(b.get_size() == 3);
	REQUIRE(b[0] == 5.0);
	REQUIRE(b[1] == 6.5);
	REQUIRE(b[2] == 7.0);
}

TEST_CASE("Init List Constructor test ") {
	auto b = comp6771::euclidean_vector{1.0, 2.0, 3.0};
	REQUIRE(b.get_size() == 3);
	REQUIRE(b[0] == 1.0);
	REQUIRE(b[1] == 2.0);
	REQUIRE(b[2] == 3.0);
}

TEST_CASE("Copy Constructor test") {
	auto a1 = comp6771::euclidean_vector(3, 3.4);
	auto b = comp6771::euclidean_vector(a1);
	REQUIRE(b.get_size() == a1.get_size());
	REQUIRE(b.get_size() == 3);
	REQUIRE(b[0] == 3.4);
	REQUIRE(b[1] == 3.4);
	REQUIRE(b[2] == 3.4);

	REQUIRE(a1.get_size() == 3);
	REQUIRE(a1[0] == 3.4);
	REQUIRE(a1[1] == 3.4);
	REQUIRE(a1[2] == 3.4);
}

TEST_CASE("Move Constructor test") {
	auto a1 = comp6771::euclidean_vector(5, 3.4);
	auto a_move = comp6771::euclidean_vector(std::move(a1));

	REQUIRE(a_move.get_size() == 5);
	REQUIRE(a_move[0] == 3.4);
	REQUIRE(a_move[1] == 3.4);
	REQUIRE(a_move[2] == 3.4);
	REQUIRE(a_move[3] == 3.4);
	REQUIRE(a_move[4] == 3.4);
}
