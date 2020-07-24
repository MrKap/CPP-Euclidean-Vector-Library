// euclidean_vector_operation_tests
#include "comp6771/euclidean_vector.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fstream>
#include <iostream>
#include <string>

// Copy should make a new euclidean vector with the same contents, while also leaving the orginal
// intact
TEST_CASE("Copy Assignment test") {
	auto b = comp6771::euclidean_vector{1.0, 69.0, 4.0};
	auto a = b;

	// Check that 'a' copied correctly
	REQUIRE(a[0] == 1.0);
	REQUIRE(a[1] == 69.0);
	REQUIRE(a[2] == 4.0);
	REQUIRE(a.dimensions() == 3);

	// Check now that 'b' remains intact.
	REQUIRE(b[0] == 1.0);
	REQUIRE(b[1] == 69.0);
	REQUIRE(b[2] == 4.0);
	REQUIRE(b.dimensions() == 3);

	// modifying 'a' so Clang doesnt get annoyed
	a[1] = 69.0;
}

// Move should make a new euclidean vector with same contents, and original should not remain
// intact.
TEST_CASE("Move Assignment test") {
	auto b = comp6771::euclidean_vector{1.0, 69.0, 4.0, 65.7};
	auto a = std::move(b);

	// Check that 'a' moved correctly
	REQUIRE(a[0] == 1.0);
	REQUIRE(a[1] == 69.0);
	REQUIRE(a[2] == 4.0);
	REQUIRE(a[3] == 65.7);
	REQUIRE(a.dimensions() == 4);

	// Can no longer check 'b' contents after move, so check it is size 0.
	// To satistfy clang the line below has been used.
	// NOLINTNEXTLINE(bugprone-use-after-move, clang-analyzer-cplusplus.Move)
	REQUIRE(b.dimensions() == 0);
}

// Subscript operator allows to get and set the value in a given dimension of the Euclidean vector.
TEST_CASE("Subscript operator test") {
	// Test non const version of subscript operator
	auto b = comp6771::euclidean_vector{1.0, 69.0, 4.0};
	double a{b[1]};
	REQUIRE(a == 69.0);
	REQUIRE(b[2] == 4.0);

	b[2] = 3.0;
	REQUIRE(b[2] == 3.0);

	// Test const version of subscript operator
	const comp6771::euclidean_vector c{1.5, 2.6, 4.1};
	REQUIRE(c[2] == 4.1);
}

// Unary Plus operator should return a copy of the current euclid vector, leaving original intact.
TEST_CASE("Unary Plus operator test") {
	auto const a = comp6771::euclidean_vector{-6, 1};
	auto b = +a;
	CHECK(b == a);
}

// Negation operator should return copy of euclid vector with each scalar value having its sign
// negated.
TEST_CASE("Negation operator test") {
	auto const actual = comp6771::euclidean_vector{-6, 1};
	auto const expected = comp6771::euclidean_vector{6, -1};
	CHECK(expected == -actual);
}

TEST_CASE("Compound Addition test") {
	auto a = comp6771::euclidean_vector{1, 2, -1, 4.5, 1};
	auto b = comp6771::euclidean_vector{3, 4, 2, 1.5, 2};
	a += b;
	REQUIRE(a[0] == 4);
	REQUIRE(a[1] == 6);
	REQUIRE(a[2] == 1);
	REQUIRE(a[3] == 6);
	REQUIRE(a[4] == 3);

	// Testing it throws correctly when two different sized vectors.
	auto c = comp6771::euclidean_vector{1, 2, -1};
	auto d = comp6771::euclidean_vector{3, 4, 2, 1.5, 2};
	REQUIRE_THROWS_WITH(c += d, "Dimensions of LHS(3) and RHS(5) do not match");

	// Test adding two empty vectors
	auto e = comp6771::euclidean_vector();
	auto f = comp6771::euclidean_vector();
	e += f;
	REQUIRE(e == f); // since adding two empty vectors should give an empty vector.
}

TEST_CASE("Compound Subtraction test") {
	auto a = comp6771::euclidean_vector{1, 2, -1, 4.5, 1};
	auto b = comp6771::euclidean_vector{3, 4, 2, 1.5, 2};
	a -= b;
	REQUIRE(a[0] == -2);
	REQUIRE(a[1] == -2);
	REQUIRE(a[2] == -3);
	REQUIRE(a[3] == 3);
	REQUIRE(a[4] == -1);

	// Testing it throws correctly when two different sized vectors.
	auto c = comp6771::euclidean_vector{1, 2, -1};
	auto d = comp6771::euclidean_vector{3, 4, 2, 1.5, 2};
	REQUIRE_THROWS_WITH(c -= d, "Dimensions of LHS(3) and RHS(5) do not match");

	// Test adding two empty vectors
	auto e = comp6771::euclidean_vector();
	auto f = comp6771::euclidean_vector();
	e -= f;
	REQUIRE(e == f); // since subtracting two empty vectors should give an empty vector.
}

TEST_CASE("Compound Multiplication test") {
	auto a = comp6771::euclidean_vector{1, 2, -1, 4.5, -1.5};
	double b = 4;
	a *= b;
	REQUIRE(a[0] == 4);
	REQUIRE(a[1] == 8);
	REQUIRE(a[2] == -4);
	REQUIRE(a[3] == 18);
	REQUIRE(a[4] == -6);

	// Test multiplying an empty vector
	auto e = comp6771::euclidean_vector();
	auto empty_vector_to_compare_to = comp6771::euclidean_vector();
	e *= b;
	REQUIRE(e == empty_vector_to_compare_to); // since multiplying an empty vector by a double should
	                                          // give an empty vector.
}

TEST_CASE("Compound Division test") {
	auto a = comp6771::euclidean_vector{1, 2, -1, 4.5, -1.5};
	double b = 4;
	a /= b;
	REQUIRE(a[0] == 0.25);
	REQUIRE(a[1] == 0.5);
	REQUIRE(a[2] == -0.25);
	REQUIRE(a[3] == 1.125);
	REQUIRE(a[4] == -0.375);

	// Testing it throws correctly when two different sized vectors.
	double zero = 0;
	REQUIRE_THROWS_WITH(a /= zero, "Invalid vector division by 0");

	// Test dividing an empty vector
	auto e = comp6771::euclidean_vector();
	auto empty_vector_to_compare_to = comp6771::euclidean_vector();
	e /= b;
	REQUIRE(e == empty_vector_to_compare_to); // since dividing an empty vector by a double should
	                                          // give an empty vector.
}

TEST_CASE("Std::vector typecast test") {
	auto const a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	auto const vf = static_cast<std::vector<double>>(a);

	// Check all the information has been copied to std::vector correctly.
	REQUIRE(vf[0] == 0.0);
	REQUIRE(vf[1] == 1.0);
	REQUIRE(vf[2] == 2.0);
	CHECK(vf.size() == 3);
}

TEST_CASE("Std::list typecast test") {
	auto const a = comp6771::euclidean_vector{0.0, 1.0, 2.0};
	auto vf = static_cast<std::list<double>>(a);

	// check all information has been copied to std::list vector correctly.
	int i = 0;
	for (const auto j : vf) {
		REQUIRE(j == a[i]);
		i++;
	}
	CHECK(vf.size() == 3);
}