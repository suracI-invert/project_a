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
        
    public:
        float x;
        float y;

        vector()=default;
        vector(float x_, float y_);

        float magnitude() const;
        float rad() const;

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
        vector direction(const vector& other);
        float dotProduct(const vector& other);
        float length() const;
        float getDeltaRad(const vector& other);
};

#endif