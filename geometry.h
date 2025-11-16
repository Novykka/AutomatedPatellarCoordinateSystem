#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <cmath>

// 三维向量/点结构
struct Vector3D {
    double x, y, z;
    Vector3D() : x(0), y(0), z(0) {}
    Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_) {}
    
    // 运算符重载（方便计算）
    Vector3D operator+(const Vector3D& other) const { return {x+other.x, y+other.y, z+other.z}; }
    Vector3D operator-(const Vector3D& other) const { return {x-other.x, y-other.y, z-other.z}; }
    Vector3D operator*(double scalar) const { return {x*scalar, y*scalar, z*scalar}; }
};

// 几何计算函数（声明）
double dotProduct(const Vector3D& a, const Vector3D& b);       // 点积
Vector3D crossProduct(const Vector3D& a, const Vector3D& b);  // 叉积
double magnitude(const Vector3D& v);                          // 向量模长
Vector3D normalize(const Vector3D& v);                        // 单位化向量
double angleBetweenVectors(const Vector3D& a, const Vector3D& b); // 向量夹角（°）
double distanceBetweenPoints(const Vector3D& p1, const Vector3D& p2); // 点间距

#endif // GEOMETRY_H
