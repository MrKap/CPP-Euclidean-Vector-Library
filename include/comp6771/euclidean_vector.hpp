#ifndef COMP6771_EUCLIDEAN_VECTOR_HPP
#define COMP6771_EUCLIDEAN_VECTOR_HPP

#include <compare>
#include <functional>
#include <list>
#include <memory>
#include <ostream>
#include <range/v3/algorithm.hpp>
#include <range/v3/iterator.hpp>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

namespace comp6771 {
	class euclidean_vector_error : public std::runtime_error {
	public:
		explicit euclidean_vector_error(std::string const& what) noexcept
		: std::runtime_error(what) {}
	};

	class euclidean_vector {
	public:
		// Constructors
		euclidean_vector();
		explicit euclidean_vector(int size);
		euclidean_vector(int size, double mag);
		euclidean_vector(std::vector<double>::const_iterator, std::vector<double>::const_iterator);
		euclidean_vector(std::initializer_list<double>);
		euclidean_vector(euclidean_vector const&);
		euclidean_vector(euclidean_vector&&) noexcept;

		// Destructor
		~euclidean_vector() noexcept = default;

		// Getter
		[[nodiscard]] auto get_size() const -> int {
			return this->size_;
		}

		// Operations
		auto operator=(euclidean_vector const&) -> euclidean_vector&;
		auto operator=(euclidean_vector&&) noexcept -> euclidean_vector&;
		auto operator+() const -> euclidean_vector;
		auto operator-() const -> euclidean_vector;
		auto operator[](int index) -> double&;
		auto operator[](int index) const -> double&;
		auto operator+=(euclidean_vector const&) -> euclidean_vector&;
		auto operator-=(euclidean_vector const&) -> euclidean_vector&;
		auto operator/=(double) -> euclidean_vector&;
		auto operator*=(double) -> euclidean_vector&;
		explicit operator std::vector<double>() const;
		explicit operator std::list<double>() const;

		// Member Functions
		[[nodiscard]] auto at(int) const -> double;
		auto at(int) -> double&;
		[[nodiscard]] auto dimensions() const -> int;

		// Friends
		friend auto operator==(euclidean_vector const&, euclidean_vector const&) -> bool;
		friend auto operator!=(euclidean_vector const&, euclidean_vector const&) -> bool;
		friend auto operator+(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;
		friend auto operator-(euclidean_vector const&, euclidean_vector const&) -> euclidean_vector;
		friend auto operator*(euclidean_vector const&, double) -> euclidean_vector;
		friend auto operator*(double, euclidean_vector const&) -> euclidean_vector;
		friend auto operator*(euclidean_vector const&, double) -> euclidean_vector;
		friend auto operator/(euclidean_vector const&, double) -> euclidean_vector;
		friend auto operator<<(std::ostream&, euclidean_vector const&) -> std::ostream&;

	private:
		// NOLINTNEXTLINE(modernize-avoid-c-arrays)
		std::unique_ptr<double[]> magnitudes_;
		int size_{};
	};

	// Utility Functions
	auto euclidean_norm(euclidean_vector const&) -> double;
	auto unit(euclidean_vector const&) -> euclidean_vector;
	auto dot(euclidean_vector const&, euclidean_vector const&) -> double;

} // namespace comp6771
#endif // COMP6771_EUCLIDEAN_VECTOR_HPP
