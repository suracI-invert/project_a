#include"obj.h"

vector::vector(float x_, float y_) {
    x=x_;
    y=y_;
}

float vector::magnitude() const {
    if(x==0 && y==0) {
        return 0;  
    }
    if(x==0) {
        return y;
    }
    if(y==0) {
        return x;
    }
    return sqrt(x*x+y*y);;
}

float vector::rad() const {
    if(x==0 && y==0) {
        return 0;
    }
    if(x==0) {
        return PI/2;
    }
    if(y==0) {
        return 0;
    }
    if(y>0) {
        return acosf(x/magnitude());
    }
    return -acosf(x/magnitude());
}

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

bool vector::operator==(const vector& other) {
    if(this->x==other.x && this->y==other.y) return true;
    return false;
}

bool vector::operator!=(const vector& other) {
    if(this->x==other.x && this->y==other.y) return false;
    return true;
}

vector vector::normalize() {
    float vd=1;
    if(this->x!=0 || this->y!=0) {
        vd=sqrt(this->x*this->x+this->y*this->y);
    }
    return vector{this->x/vd, this->y/vd};
}

float vector::getDeltaRad(const vector& other) {
    return this->rad()-other.rad();
}

vector vector::direction(const vector& otherPos) {
    vector v;
    v.x=otherPos.x-this->x;
    v.y=otherPos.y-this->y;
    return v;
}


double degToRad(const double deg) {
    return deg*(PI/180);
}
float degToRad(const float deg) {
    return deg*(PI/180);
}

double radToDeg(const double rad) {
    return rad*(180/PI);
}

float radToDeg(const float rad) {
    return rad*(180/PI);
}