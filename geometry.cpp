#include "geometry.h"

double dotProduct(const Vector3D& a, const Vector3D& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vector3D crossProduct(const Vector3D& a, const Vector3D& b) {
    return {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}

double magnitude(const Vector3D& v) {
    return std::sqrt(dotProduct(v, v));
}

Vector3D normalize(const Vector3D& v) {
    double mag = magnitude(v);
    return mag == 0 ? Vector3D() : v * (1/mag);
}

double angleBetweenVectors(const Vector3D& a, const Vector3D& b) {
    double cosTheta = dotProduct(a, b) / (magnitude(a)*magnitude(b));
    return std::acos(std::clamp(cosTheta, -1.0, 1.0)) * 180 / M_PI;
}

double distanceBetweenPoints(const Vector3D& p1, const Vector3D& p2) {
    return magnitude(p1 - p2);
}
