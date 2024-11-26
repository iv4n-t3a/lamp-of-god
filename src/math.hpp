#pragma once

#include <cmath>

template <typename T>
struct Vector {
  T x = T();
  T y = T();

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

  Vector<double>& Normalize() {
    T len = Len();
    x /= len;
    y /= len;
    return *this;
  }
  Vector<T> Normalized() {
    T len = Len();
    return Vector<double>(x / len, y / len);
  }

  T SqrDist(Vector<T> other) const {
    double distx = other.x - x;
    double disty = other.y - y;
    return distx * distx + disty * disty;
  }
  T Dist(Vector<T> other) const { return std::sqrt(SqrDist(other)); }
};
