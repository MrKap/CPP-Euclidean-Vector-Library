// euclidean_vector_friends_tests
#include "comp6771/euclidean_vector.hpp"
#include <catch2/catch.hpp>
#include <fmt/format.h>
#include <fmt/ostream.h>
#include <fstream>
#include <iostream>
#include <string>

TEST_CASE("Equal test") {
	auto a = comp6771::euclidean_vector{1.0, 69.0, 4.0, -1.5};

	auto v = std::vector<double>{1.0, 69.0, 4.0, -1.5};
	const comp6771::euclidean_vector b(v.begin(), v.end());

	// Check both ways
	CHECK(a == b);
	CHECK(b == a);
}

TEST_CASE("Not Equals test") {
	auto a = comp6771::euclidean_vector{1.0, 69.0, 4.0, -1.5};

	auto v = std::vector<double>{1.0, 65.0, 4.0, -1.5};
	const comp6771::euclidean_vector b(v.begin(), v.end());

	// Check both ways
	CHECK(a != b);
	CHECK(b != a);
}

TEST_CASE("Addition test") {
	comp6771::euclidean_vector a(4, 10);
	comp6771::euclidean_vector b(4, 20);
	std::vector<double> l;
	l.push_back(1.0);
	l.push_back(3.5);
	l.push_back(4.0);
	l.push_back(2.0);
	comp6771::euclidean_vector vec{l.begin(), l.end()};

	auto c = a + b;
	REQUIRE(c[0] == 30);
	REQUIRE(c[1] == 30);
	REQUIRE(c[2] == 30);
	REQUIRE(c[3] == 30);

	auto d = c + vec;
	REQUIRE(d[0] == 31);
	REQUIRE(d[1] == 33.5);
	REQUIRE(d[2] == 34);
	REQUIRE(d[3] == 32);

	// Testing it throws correctly when two different sized vectors.
	auto j = comp6771::euclidean_vector{1, 2, -1};
	auto k = comp6771::euclidean_vector{3, 4, 2, 1.5, 2};
	REQUIRE_THROWS_WITH(j + k, "Dimensions of LHS(3) and RHS(5) do not match");

	// Testing it can add two empty vectors to give an empty vector.
	auto p = comp6771::euclidean_vector();
	auto q = comp6771::euclidean_vector();
	auto h = p + q;
	REQUIRE(h == q);
}

TEST_CASE("Subtraction test") {
	comp6771::euclidean_vector a(4, 10);
	comp6771::euclidean_vector b(4, 20);
	std::vector<double> l;
	l.push_back(1.0);
	l.push_back(3.5);
	l.push_back(4.0);
	l.push_back(2.0);
	comp6771::euclidean_vector vec{l.begin(), l.end()};

	auto c = a - b;
	REQUIRE(c[0] == -10);
	REQUIRE(c[1] == -10);
	REQUIRE(c[2] == -10);
	REQUIRE(c[3] == -10);

	auto d = c - vec;
	REQUIRE(d[0] == -11);
	REQUIRE(d[1] == -13.5);
	REQUIRE(d[2] == -14);
	REQUIRE(d[3] == -12);

	// Testing it throws correctly when two different sized vectors.
	auto j = comp6771::euclidean_vector{1, 2, -1};
	auto k = comp6771::euclidean_vector{3, 4, 2, 1.5, 2};
	REQUIRE_THROWS_WITH(j - k, "Dimensions of LHS(3) and RHS(5) do not match");

	// Testing it can add two empty vectors to give an empty vector.
	auto p = comp6771::euclidean_vector();
	auto q = comp6771::euclidean_vector();
	auto h = p - q;
	REQUIRE(h == q);
}

TEST_CASE("Multiplication test") {
	auto b = comp6771::euclidean_vector{1, 2, -1};

	// Test when scalar on the right of vector
	auto a = b * 3;
	REQUIRE(a[0] == 3);
	REQUIRE(a[1] == 6);
	REQUIRE(a[2] == -3);
	REQUIRE(a.get_size() == 3);

	// Test when scalar on the left of vector
	auto d = -5 * a;
	REQUIRE(d[0] == -15);
	REQUIRE(d[1] == -30);
	REQUIRE(d[2] == 15);

	// Testing it can multiply an empty vector, to give an empty vector.
	auto p = comp6771::euclidean_vector();
	auto q = comp6771::euclidean_vector();
	auto h = p * 5;
	REQUIRE(h == q);
}

TEST_CASE("Division test") {
	auto b = comp6771::euclidean_vector{1, 2, -8};
	auto a = b / -4;
	REQUIRE(a[0] == -0.25);
	REQUIRE(a[1] == -0.5);
	REQUIRE(a[2] == 2);
	REQUIRE(a.get_size() == 3);

	// Test throws exception when divide by 0;
	REQUIRE_THROWS_WITH(b / 0, "Invalid vector division by 0");

	// Testing can divide with an empty vector, to give an empty vector.
	auto p = comp6771::euclidean_vector();
	auto q = comp6771::euclidean_vector();
	auto h = p / 5;
	REQUIRE(h == q);
}

TEST_CASE("Output Stream test") {
	auto a = comp6771::euclidean_vector{1, 2.77, -8};
	std::string expected_output = "[1 2.77 -8]";
	std::cout << a;
	REQUIRE((fmt::format("{}", a) == expected_output));

	// Print empty vector
	auto b = comp6771::euclidean_vector();
	std::string expected_output_2 = "[]";
	std::cout << b;
	REQUIRE((fmt::format("{}", b) == expected_output_2));
}
