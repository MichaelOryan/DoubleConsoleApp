#include <vector>
#include <algorithm>

namespace bignumber {

    typedef vector<Digit>::size_t size_v;
    const Digit BASE = 10;

    bignumber& operator=(const bignumber & rhs) {
        integers = rhs.integers;
        fractions = rhs.fractions;
    }

    bignumber SumFractions(const bignumber & lhs, const bignumber & rhs) {
      bignumber bignumber_sum;
      vector<Digit> reverse_fractional_sum;

      size_v lhs_size = lhs.fractions.size();
      size_v rhs_size = rhs.fractions.size();

      if(rhs_size > lhs_size) {
          return SumFractions(rhs, lhs);
      }

      Digit carry = 0;
      for(size_v i = lhs_size - 1; i >= 0; i--){

          Digit sum = carry + lhs.fractions[i];
          carry = 0;

          if(i < rhs.fractions.size()) {
              sum += rhs.fractions[i];
          }

          if(sum >= BASE) {
              carry = 1;
              sum -= BASE;
          }

          reverse_fractional_sum.push_back(sum);
      }

      std::reverse_copy (reverse_fractional_sum.begin(), reverse_fractional_sum.end(), bignumber_sum.fractions.begin());

      bignumber_sum.integers.push_back(carry);

      return bignumber_sum;

    }

    bignumber SumIntegers (const bignumber & lhs, const bignumber & rhs) {
        bignumber bignumber_sum;

        size_v lhs_size = lhs.numbers.size();
        size_v rhs_size = rhs.numbers.size();

        if(rhs_size > lhs_size) {
            return SumIntegers(rhs, lhs);
        }

        Digit carry = 0;

        for(size_v i = 0; i < lhs_size; i++) {
            Digit sum = lhs.numbers[i] + carry;
            carry = 0;

            if(i < rhs_size) {
                sum += rhs.numbers[i];
            }

            if(sum >= BASE) {
                carry = 1;
                sum -= BASE;
            }

            bignumber_sum.numbers.push_back(sum);
        }

        if(carry > 0) {
            bignumber_sum.numbers.push_back(carry);
        }

        return bignumber_sum;
    }

    bignumber& SumBoth(const bignumber & fractions, const bignumber & integers) {
        bignumber integer_part;
        integer_part.integers = fractions.integers;
        bignumber sum = SumIntegers(integer_part, integers);
        sum.fractions = fractions.fractions;
        return sum;
    }

    bignumber& operator+(const bignumber & rhs) {
        bignumber fractional_sum = SumFractions(*this, rhs);
        bignumber integer_sum = SumIntegers(*this.rhs);
        return = SumBoth(fractional_sum, integer_sum);
    }
    bignumber& operator-(const bignumber & rhs) {

    }
    bignumber& operator/(const bignumber & rhs) {

    }
    bignumber& operator*(const bignumber & rhs) {

    }
    bignumber& operator++() {

    }
    bignumber operator++(int) {

    }
    bignumber& operator--() {

    }
    bignumber operator--(int) {

    }
}
