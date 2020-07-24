// euclidean_vector_member_function_tests
#include "comp6771/euclidean_vector.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fstream>
#include <iostream>
#include <string>

// "at" method should act similar to subscript operator, hoewever this one throws an exception when
// invalid index, rather than assert;
TEST_CASE("The 'at' method test") {
	// Test non const version of "at" operator
	auto b = comp6771::euclidean_vector{1.0, 69.0, 4.0};
	double a{b.at(1)};
	REQUIRE(a == 69.0);
	REQUIRE(b.at(2) == 4.0);

	// Test assignment of non const
	b.at(2) = 3.0;
	REQUIRE(b.at(2) == 3.0);

	// Test const version of "at" operator
	const comp6771::euclidean_vector c{1.5, 2.6, 4.1};
	REQUIRE(c.at(2) == 4.1);

	// Test exception throwing of non const vector
	REQUIRE_THROWS_WITH(b.at(-1), "Index -1 is not valid for this euclidean_vector object");
	REQUIRE_THROWS_WITH(b.at(5), "Index 5 is not valid for this euclidean_vector object");

	// Test exception throwing of const vector.
	REQUIRE_THROWS_WITH(c.at(-1), "Index -1 is not valid for this euclidean_vector object");
	REQUIRE_THROWS_WITH(c.at(5), "Index 5 is not valid for this euclidean_vector object");
}

// dimensions method should return the size/dimensions of a vector.
TEST_CASE("Dimensions test") {
	auto a = comp6771::euclidean_vector();
	auto b = comp6771::euclidean_vector(2);
	const comp6771::euclidean_vector c{1.5, 2.6, 4.1};

	REQUIRE(a.dimensions() == 0);
	REQUIRE(b.dimensions() == 2);
	REQUIRE(c.dimensions() == 3);
}
