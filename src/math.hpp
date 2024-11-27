#pragma once

#include <cassert>
#include <cmath>
#include <cstdlib>

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
  Vector operator/(T div) const { return Vector(x / div, y / div); }

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
    x /= div;
    y /= div;
    return *this;
  }

  T SqrLen() const { return x * x + y * y; }
  T Len() const { return std::sqrt(SqrLen()); }

  Vector<T>& Normalize() {
    T len = Len();

    if (len == 0) {
      return {0, 0};
    }

    x /= len;
    y /= len;
    return *this;
  }
  Vector<T> Normalized() {
    T len = Len();

    if (len == 0) {
      return {0, 0};
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
