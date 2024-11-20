#pragma once

#include <cmath>

template <typename T>
struct Vector {
  T x = T();
  T y = T();

  inline Vector operator-() const { return Vector(-x, -y); }

  inline Vector operator+(Vector other) const {
    return Vector(x + other.x, y + other.y);
  }
  inline Vector operator-(Vector other) const {
    return Vector(x - other.x, y - other.y);
  }
  inline Vector operator*(T mult) const { return Vector(x * mult, y * mult); }
  inline Vector operator/(T div) const { return Vector(x / div, y / div); }

  inline Vector& operator+=(Vector other) {
    x += other.x;
    y += other.y;
    return *this;
  }
  inline Vector& operator-=(Vector other) {
    x -= other.x;
    y -= other.y;
    return *this;
  }
  inline Vector& operator*=(T mult) {
    x *= mult;
    y *= mult;
    return *this;
  }
  inline Vector& operator/=(T div) {
    x /= div;
    y /= div;
    return *this;
  }

  inline T SqrLen() const { return x * x + y * y; }
  inline T Len() const { return std::sqrt(SqrLen()); }

  inline Vector<double>& Normalize() {
    T len = Len();
    x /= len;
    y /= len;
    return *this;
  }
  inline Vector<T> Normalized() {
    T len = Len();
    return Vector<double>(x / len, y / len);
  }

  inline T SqrDist(Vector<T> other) const {
    double distx = other.x - x;
    double disty = other.y - y;
    return distx * distx + disty * disty;
  }
  inline T Dist(Vector<T> other) const { return std::sqrt(SqrDist(other)); }
};
