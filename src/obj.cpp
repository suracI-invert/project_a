#include"obj.h"

vector::vector(float x_, float y_) {
    x=x_;
    y=y_;
    // length=sqrt(x*x+y*y);
    // if(length==0) rad=0;
    // else rad=acosf(x/length);
}

// vector::vector(float length, float rad) {
//     this->length=length;
//     this->rad=rad;
//     x=length*cosf(rad);
//     y=length*sinf(rad);
// }

// vector& vector::add(const vector& v) {
//     this->x+=v.x;
//     this->y+=v.y;
// }

// vector& vector::subtract(const vector& v) {
//     this->x-=v.x;
//     this->y-=v.y;
// }

// vector& vector::multiply(const vector& v) {
//     this->x*=v.x;
//     this->y*=v.y;
// }

// vector& vector::divide(const vector& v) {
//     this->x/=v.x;
//     this->y/=v.y;
// }

vector vector::operator+(const vector& other) {
    vector v;
    v.x=this->x+other.x;
    v.y=this->y+other.y;
    return v;
}
vector vector::operator-(const vector& other) {
    vector v;
    v.x=this->x-other.x;
    v.y=this->y-other.y;
    return v;
}
vector vector::operator*(const vector& other) {
    vector v;
    v.x=this->x*other.x;
    v.y=this->y*other.y;
    return v;
}
vector vector::operator/(const vector& other) {
    vector v;
    v.x=this->x/other.x;
    v.y=this->y/other.y;
    return v;
}

vector vector::operator+(const int& other) {
    vector v;
    v.x=this->x+other;
    v.y=this->y+other;
    return v;
}
vector vector::operator-(const int& other) {
    vector v;
    v.x=this->x-other;
    v.y=this->y-other;
    return v;
}
vector vector::operator*(const int& other) {
    vector v;
    v.x=this->x*other;
    v.y=this->y*other;
    return v;
}
vector vector::operator/(const int& other) {
    vector v;
    v.x=this->x/other;
    v.y=this->y/other;
    return v;
}

vector vector::operator+(const float& other) {
    vector v;
    v.x=this->x+other;
    v.y=this->y+other;
    return v;
}
vector vector::operator-(const float& other) {
    vector v;
    v.x=this->x-other;
    v.y=this->y-other;
    return v;
}
vector vector::operator*(const float& other) {
    vector v;
    v.x=this->x*other;
    v.y=this->y*other;
    return v;
}
vector vector::operator/(const float& other) {
    vector v;
    v.x=this->x/other;
    v.y=this->y/other;
    return v;
}

vector vector::normalize() {
    float vd=1;
    if(this->x!=0 || this->y!=0) {
        vd=sqrt(this->x*this->x+this->y*this->y);
    }
    return vector{this->x/vd, this->y/vd};
}

