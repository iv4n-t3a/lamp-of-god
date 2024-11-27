#pragma once

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <vector>

template <typename T>
struct Vector {
  T x = T();
  T y = T();

  Vector() = default;
  Vector(const Vector&) = default;
  Vector(T vec_x, T vec_y) : x(vec_x), y(vec_y) {
    assert(not std::isnan(vec_x) and not std::isnan(vec_y));
  }

  Vector operator-() const { return Vector(-x, -y); }

  Vector operator+(Vector other) const {
    return Vector(x + other.x, y + other.y);
  }
  Vector operator-(Vector other) const {
    return Vector(x - other.x, y - other.y);
  }
  Vector operator*(T mult) const { return Vector(x * mult, y * mult); }
  Vector operator/(T div) const {
    assert(div != T());
    return Vector(x / div, y / div);
  }

  Vector& operator+=(Vector other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  Vector& operator-=(Vector other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  Vector& operator*=(T mult) {
    x *= mult;
    y *= mult;
    return *this;
  }
  Vector& operator/=(T div) {
    assert(div != T());
    x /= div;
    y /= div;
    return *this;
  }

  T SqrLen() const { return x * x + y * y; }
  T Len() const { return std::sqrt(SqrLen()); }

  Vector<T>& Normalize() {
    T len = Len();

    if (len == T()) {
      return {T(), T()};
    }

    x /= len;
    y /= len;
    return *this;
  }
  Vector<T> Normalized() {
    T len = Len();

    if (len == T()) {
      return {T(), T()};
    }

    return Vector<T>(x / len, y / len);
  }

  T SqrDist(Vector<T> other) const {
    T distx = other.x - x;
    T disty = other.y - y;
    return distx * distx + disty * disty;
  }
  T Dist(Vector<T> other) const { return std::sqrt(SqrDist(other)); }
};

template <typename T>
void SolvePoisson(std::vector<std::vector<T>>& potential_matrix,
                  const std::vector<std::vector<bool>>& boundary_conditions,
                  T tolerance = 1e-6) {
  std::vector<std::vector<T>> new_potential_matrix = potential_matrix;
  while (true) {
    new_potential_matrix = potential_matrix;
    for (size_t i = 1; i < new_potential_matrix.size() - 1; i++) {
      for (size_t j = 1; j < new_potential_matrix[i].size() - 1; j++) {
        if (!boundary_conditions[i][j]) {
          new_potential_matrix[i][j] =
              (potential_matrix[i - 1][j] + potential_matrix[i + 1][j] +
               potential_matrix[i][j - 1] + potential_matrix[i][j - 1]) /
              4;
        }
      }
    }

    T max_difference = 0;
    for (size_t i = 1; i < new_potential_matrix.size() - 1; i++) {
      for (size_t j = 1; j < new_potential_matrix[i].size() - 1; j++) {
        max_difference = std::max(
            max_difference,
            std::abs(potential_matrix[i][j], new_potential_matrix[i][j]));
      }
    }

    if (max_difference < tolerance) {
      potential_matrix = new_potential_matrix;
      return;
    }
  }
}
