#ifndef _VEC_H
#define _VEC_H

#include<cmath>
#define PI 3.14159265359

struct circle{
    float x, y;
    float r;
};

class vector{
    private:
        // float rad, length;
    public:
        float x;
        float y;

        vector()=default;
        vector(float x_, float y_);
        // vector(float length, float rad);

        // vector& add(const vector& v);
        // vector& subtract(const vector& v);
        // vector& multiply(const vector& v);
        // vector& divide(const vector& v);

        vector operator+(const vector& other);
        vector operator-(const vector& other);
        vector operator*(const vector& other);
        vector operator/(const vector& other);

        vector operator+(const int& other);
        vector operator-(const int& other);
        vector operator*(const int& other);
        vector operator/(const int& other);

        vector operator+(const float& other);
        vector operator-(const float& other);
        vector operator*(const float& other);
        vector operator/(const float& other);

        vector normalize();

        // vector& operator+=(const vector& other);
        // vector& operator-=(const vector& other);
        // vector& operator*=(const vector& other);
        // vector& operator/=(const vector& other);
};

#endif