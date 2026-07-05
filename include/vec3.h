#ifndef VEC3_H
#define VEC3_H


#include <iostream>
#include <cmath>

class vec3 {
    public :
    double a[3];
    vec3 (): a{0, 0, 0} {}
    vec3 (double a0, double a1, double a2): a{a0, a1, a2}{}

    double x() const {return a[0];}
    double y() const {return a[1];}
    double z() const {return a[2];}

    vec3 operator-() const { return vec3(-a[0], -a[1], -a[2]);} // inverts the data values
    double operator[] (int i) const {return a[i];} // for reading a vec3 
    double& operator[] (int i){return  a[i];} // for changing data 

    vec3 operator+=(const vec3& delta) {
        a[0]+=delta.a[0];
        a[1]+=delta.a[1];
        a[2]+=delta.a[2];
        return *this; // returns a refernce to objects 
    }
    vec3 operator*=(double delta) {
        a[0]*=delta;
        a[1]*=delta;
        a[2]*=delta;
        return *this;
    }
    vec3 operator/=(double delta) {
        return *this *=1/delta;
    }

    double length_squared() const{
        return (a[0]*a[0]+ a[1]*a[1]+ a[2]*a[2]);
    }
    double length() const{
        return std::sqrt(length_squared());
    }
};

using point3 = vec3;

inline std::ostream& operator<<(std::ostream& out, const vec3& v) {
    return out << v.a[0] << ' ' << v.a[1] << ' ' << v.a[2];
}

inline vec3 operator+(const vec3& u, const vec3& v){
    return vec3(u.a[0]+v.a[0],u.a[1]+v.a[1], u.a[2]+v.a[2]);
}

inline vec3 operator-(const vec3& u, const vec3& v){
    return vec3(u.a[0]-v.a[0],u.a[1]-v.a[1], u.a[2]-v.a[2]);
}

inline vec3 operator*(const vec3& u, const vec3& v){
    return vec3(u.a[0]*v.a[0],u.a[1]*v.a[1], u.a[2]*v.a[2]);
}

inline vec3 operator*(double v, const vec3& u){
    return vec3(u.a[0]*v,u.a[1]*v, u.a[2]*v);
}

inline vec3 operator*(const vec3& u, double v){
    return v*u;
}


inline vec3 operator/(const vec3& v, double t) {
    return (1/t) * v;
}

inline double dot(const vec3& u, const vec3& v) {
    return u.a[0] * v.a[0]
         + u.a[1] * v.a[1]
         + u.a[2] * v.a[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
    return vec3(u.a[1] * v.a[2] - u.a[2] * v.a[1],
                u.a[2] * v.a[0] - u.a[0] * v.a[2],
                u.a[0] * v.a[1] - u.a[1] * v.a[0]);
}

inline vec3 unit_vector(const vec3& v) {
    return v / v.length();
}


#endif