#pragma once

template <typename T>
struct Vector {
  T x;
  T y;

  Vector operator-() const { return Vector(-x, -y); }

  Vector operator+(Vector other) const {
    return Vector(x + other.x, y + other.y);
  }
  Vector operator-(Vector other) const {
    return Vector(x - other.x, y - other.y);
  }
  Vector operator*(T mult) const { return Vector(x * mult, y * mult); }

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
};
