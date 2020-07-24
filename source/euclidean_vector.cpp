// Copyright (c) Christopher Di Bella.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
#include "comp6771/euclidean_vector.hpp"
#include <cmath>
#include <cstddef>
#include <fmt/ostream.h>
#include <memory>
#include <sstream>

namespace comp6771 {

	/*--------------------
	-----Constructors-----
	----------------------
	*/

	// No arg constructor
	euclidean_vector::euclidean_vector() {
		this->size_ = 0;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(0);
	}

	// Size constructor
	euclidean_vector::euclidean_vector(int size) {
		this->size_ = size;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(size));
		for (int i = 0; i < size; i++) {
			this->magnitudes_[static_cast<size_t>(i)] = 0.0;
		}
	}

	// Size, Magnitude Constructor
	euclidean_vector::euclidean_vector(int size, double magnitude) {
		this->size_ = size;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(size));
		for (int i = 0; i < size; i++) {
			this->magnitudes_[static_cast<size_t>(i)] = magnitude;
		}
	}

	// Iterator constructor
	euclidean_vector::euclidean_vector(std::vector<double>::const_iterator begin,
	                                   std::vector<double>::const_iterator end) {
		this->size_ = 0;
		for (auto curr = begin; curr != end; curr++) {
			this->size_++;
		}

		auto curr = begin;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->size_));
		for (size_t i = 0; curr != end; i++, curr++) {
			this->magnitudes_[i] = *curr;
		}
	}

	// Initializer list constructor
	euclidean_vector::euclidean_vector(std::initializer_list<double> magnitude_list) {
		this->size_ = int(magnitude_list.size());

		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->size_));
		const auto* curr = magnitude_list.begin();
		const auto* end = magnitude_list.end();

		for (size_t i = 0; curr != end; i++, curr++) {
			this->magnitudes_[i] = *curr;
		}
	}

	// Copy Constructor
	euclidean_vector::euclidean_vector(euclidean_vector const& original) {
		this->size_ = original.size_;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->size_));
		for (size_t i = 0; int(i) < this->size_; i++) {
			this->magnitudes_[i] = original.magnitudes_[i];
		}
	}

	// Move constructor
	euclidean_vector::euclidean_vector(euclidean_vector&& original) noexcept {
		this->size_ = original.get_size();
		this->magnitudes_ = std::move(original.magnitudes_);
		original.size_ = 0;
	}

	/*
	------------------------
	------ Operations ------
	------------------------
	*/

	// Copy Assignment
	auto euclidean_vector::operator=(euclidean_vector const& vector) -> euclidean_vector& {
		if (&vector == this) {
			return *this;
		}

		this->size_ = vector.size_;
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		this->magnitudes_ = std::make_unique<double[]>(static_cast<size_t>(this->size_));

		for (int i = 0; i < vector.get_size(); i++) {
			this->magnitudes_[static_cast<size_t>(i)] = vector[i];
		}

		return *this;
	}

	// Move Assignment
	auto euclidean_vector::operator=(euclidean_vector&& vector) noexcept -> euclidean_vector& {
		this->size_ = vector.get_size();
		this->magnitudes_ = std::move(vector.magnitudes_);
		vector.size_ = 0;
		return *this;
	}

	// Subscript Operation
	auto euclidean_vector::operator[](int index) -> double& {
		assert(index >= 0 || index > (this->get_size() - 1));
		return this->magnitudes_[static_cast<size_t>(index)];
	}

	// Subscript Operation - const
	auto euclidean_vector::operator[](int index) const -> double& {
		assert(index >= 0 || index > (this->get_size() - 1));
		return this->magnitudes_[static_cast<size_t>(index)];
	}

	// Unary Plus
	auto euclidean_vector::operator+() const -> euclidean_vector {
		euclidean_vector new_vector = *this;
		return new_vector;
	}

	// Negation
	auto euclidean_vector::operator-() const -> euclidean_vector {
		euclidean_vector new_vector = *this;
		for (int i = 0; i < new_vector.get_size(); i++) {
			new_vector.magnitudes_[static_cast<size_t>(i)] *= -1;
		}

		return new_vector;
	}

	// Compound Addition
	auto euclidean_vector::operator+=(euclidean_vector const& addend_vector) -> euclidean_vector& {
		if (this->get_size() != addend_vector.get_size()) {
			std::ostringstream error;
			error << "Dimensions of LHS(";
			error << this->dimensions();
			error << ") and RHS(";
			error << addend_vector.dimensions();
			error << ") do not match";
			throw euclidean_vector_error(error.str());
		}

		for (int i = 0; i < this->get_size(); i++) {
			this->magnitudes_[static_cast<size_t>(i)] += addend_vector[i];
		}

		return *this;
	}

	// Compound Subtraction
	auto euclidean_vector::operator-=(euclidean_vector const& subtrahend_vector) -> euclidean_vector& {
		if (this->get_size() != subtrahend_vector.get_size()) {
			std::ostringstream error;
			error << "Dimensions of LHS(";
			error << this->dimensions();
			error << ") and RHS(";
			error << subtrahend_vector.dimensions();
			error << ") do not match";
			throw euclidean_vector_error(error.str());
		}

		for (int i = 0; i < this->get_size(); i++) {
			this->magnitudes_[static_cast<size_t>(i)] -= subtrahend_vector[i];
		}

		return *this;
	}

	// Compound Multiplication
	auto euclidean_vector::operator*=(double multiplier) -> euclidean_vector& {
		for (int i = 0; i < this->get_size(); i++) {
			this->magnitudes_[static_cast<size_t>(i)] *= multiplier;
		}

		return *this;
	}

	// Compound Division
	auto euclidean_vector::operator/=(double scalar_divisor) -> euclidean_vector& {
		if (scalar_divisor == 0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}

		for (int i = 0; i < this->get_size(); i++) {
			this->magnitudes_[static_cast<size_t>(i)] /= scalar_divisor;
		}

		return *this;
	}

	// std::vector typecast
	euclidean_vector::operator std::vector<double>() const {
		std::vector<double> vector;
		vector.reserve(static_cast<size_t>(this->get_size()));
		for (int i = 0; i < this->get_size(); i++) {
			vector.push_back(this->magnitudes_[static_cast<size_t>(i)]);
		}
		return vector;
	}

	// std::list typecast
	euclidean_vector::operator std::list<double>() const {
		std::list<double> list;
		for (int i = 0; i < this->get_size(); i++) {
			list.push_back(this->magnitudes_[static_cast<size_t>(i)]);
		}
		return list;
	}

	/*------------------------
	---- Member Functions ----
	------------------------*/

	// at - const
	auto euclidean_vector::at(int i) const -> double {
		if (i < 0 || i > (this->size_ - 1)) {
			std::ostringstream error;
			error << "Index ";
			error << i;
			error << " is not valid for this euclidean_vector object";
			throw euclidean_vector_error(error.str());
		}
		return this->magnitudes_[static_cast<size_t>(i)];
	}

	// at
	auto euclidean_vector::at(int i) -> double& {
		if (i < 0 || i > (this->size_ - 1)) {
			std::ostringstream error;
			error << "Index ";
			error << i;
			error << " is not valid for this euclidean_vector object";
			throw euclidean_vector_error(error.str());
		}
		return this->magnitudes_[static_cast<size_t>(i)];
	}

	// get dimensions
	auto euclidean_vector::dimensions() const -> int {
		return this->get_size();
	}

	/*----------------------
	-------- Friends -------
	------------------------
	*/

	// Equal
	auto operator==(euclidean_vector const& first, euclidean_vector const& second) -> bool {
		if (first.size_ != second.size_) {
			return false;
		}
		for (int i = 0; i < first.get_size(); i++) {
			if (first[i] != second[i]) {
				return false;
			}
		}

		return true;
	}

	// Not Equal
	auto operator!=(euclidean_vector const& first, euclidean_vector const& second) -> bool {
		return !(first == second);
	}

	// Addition
	auto operator+(euclidean_vector const& first, euclidean_vector const& second) -> euclidean_vector {
		if (first.dimensions() != second.dimensions()) {
			std::ostringstream error;
			error << "Dimensions of LHS(";
			error << first.dimensions();
			error << ") and RHS(";
			error << second.dimensions();
			error << ") do not match";
			throw euclidean_vector_error(error.str());
		}

		std::vector<double> result_vector;
		result_vector.reserve(static_cast<size_t>(first.dimensions()));
		for (int i = 0; i < first.size_; i++) {
			result_vector.push_back(first[i] + second[i]);
		}
		return euclidean_vector(result_vector.begin(), result_vector.end());
	}

	// Subtraction
	auto operator-(euclidean_vector const& first, euclidean_vector const& second) -> euclidean_vector {
		if (first.dimensions() != second.dimensions()) {
			std::ostringstream error;
			error << "Dimensions of LHS(";
			error << first.dimensions();
			error << ") and RHS(";
			error << second.dimensions();
			error << ") do not match";
			throw euclidean_vector_error(error.str());
		}
		std::vector<double> result_vector;
		result_vector.reserve(static_cast<size_t>(first.dimensions()));
		for (int i = 0; i < first.size_; i++) {
			result_vector.push_back(first[i] - second[i]);
		}
		return euclidean_vector(result_vector.begin(), result_vector.end());
	}

	// Multiply
	auto operator*(euclidean_vector const& vector, double multiplier) -> euclidean_vector {
		std::vector<double> result_vector;

		result_vector.reserve(static_cast<size_t>(vector.dimensions()));
		for (int i = 0; i < vector.size_; i++) {
			result_vector.push_back(vector[i] * multiplier);
		}
		return euclidean_vector(result_vector.begin(), result_vector.end());
	}

	// Multiply v2
	auto operator*(double multiplier, euclidean_vector const& vector) -> euclidean_vector {
		return vector * multiplier; // making use of multiply opertaor
	}

	// Division
	auto operator/(euclidean_vector const& vector, double dividend) -> euclidean_vector {
		if (dividend == 0) {
			throw euclidean_vector_error("Invalid vector division by 0");
		}
		std::vector<double> result_vector;
		result_vector.reserve(static_cast<size_t>(vector.dimensions()));
		for (int i = 0; i < vector.size_; i++) {
			result_vector.push_back(vector[i] / dividend);
		}
		return euclidean_vector(result_vector.begin(), result_vector.end());
	}

	// Output Stream
	auto operator<<(std::ostream& output, euclidean_vector const& vector) -> std::ostream& {
		output << "[";
		for (int i = 0; i < vector.size_; i++) {
			if (vector.size_ != 0 && i == vector.size_ - 1) {
				output << vector[i] << "]";
			}
			else {
				output << vector[i] << " ";
			}
		}

		if (vector.size_ == 0) {
			output << "]";
		}

		return output;
	}

	/*-----------------------
	--- Utility Functions ---
	-------------------------
	*/

	// Euclidean Normal
	auto euclidean_norm(euclidean_vector const& v) -> double {
		// Empty vector
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a norm");
		}

		double mag_squares_sum = 0.0;
		for (int i = 0; i < v.get_size(); i++) {
			mag_squares_sum += (v[i] * v[i]);
		}
		return sqrt(mag_squares_sum);
	}

	// Unit Vector
	auto unit(euclidean_vector const& v) -> euclidean_vector {
		if (v.dimensions() == 0) {
			throw euclidean_vector_error("euclidean_vector with no dimensions does not have a unit "
			                             "vector");
		}
		if (euclidean_norm(v) == 0) {
			throw euclidean_vector_error("euclidean_vector with zero euclidean normal does not have a "
			                             "unit vector");
		}
		return v / euclidean_norm(v);
	}

	// Dot product
	auto dot(euclidean_vector const& x, euclidean_vector const& y) -> double {
		if (x.dimensions() != y.dimensions()) {
			std::ostringstream error;
			error << "Dimensions of LHS(";
			error << x.dimensions();
			error << ") and RHS(";
			error << y.dimensions();
			error << ") do not match";
			throw euclidean_vector_error(error.str());
		}
		double dot_product = 0.0;
		for (int i = 0; i < x.dimensions(); i++) {
			dot_product += (x[i] * y[i]);
		}
		return dot_product;
	}

} // namespace comp6771
