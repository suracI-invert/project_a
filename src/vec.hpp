#pragma once

class vec {
    public:
        float x, y;

        vec(): x(0.0f), y(0.0f) {}

        vec(float x, float y): x(x), y(y) {}

        vec operator+(const vec& other) const {
            return vec(x + other.x, y + other.y);
        }

        vec& operator+=(const vec& other) {
            this->x += other.x;
            this->y += other.y;
            return *this;
        }

        vec operator-(const vec& other) const {
            return vec(x - other.x, y - other.y);
        }

        vec& operator-=(const vec& other) {
            this->x -= other.x;
            this->y -= other.y;
            return *this;
        }

        vec operator*(const vec& other) const {
            return vec(x * other.x, y * other.y);
        }

        vec& operator*=(const vec& other) {
            this->x *= other.x;
            this->y *= other.y;
            return *this;
        }

        vec operator*(const float a) const {
            return vec(x * a, y * a);
        }

        vec& operator*=(const float a) {
            this->x *= a;
            this->y *= a;
            return *this;
        }

        bool operator==(const vec& other) const {
            if (this->x == other.x && this->y == other.y) return true;
            return false;
        }

        bool operator!=(const vec& other) const {
            if (this->x != other.x && this->y != other.y) return true;
            return false;
        }
};