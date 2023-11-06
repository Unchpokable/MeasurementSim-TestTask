#pragma once

#include "eigen/include/Eigen/Core"
#include "eigen/include/Eigen/Dense"
#include "eigen/include/Eigen/Geometry"

using Point3d = Eigen::Vector3d;

struct Plane3d
{
    double A, B, C, D;
    Eigen::Vector3d Normal;
};

struct Circle3d
{
    Eigen::Vector3d Normal;
    Point3d CenterPoint;
    double Radius;
};

Plane3d PlaneFromPoints(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3);

Circle3d CircleFromPoints(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3);

Point3d Project(const Point3d& point, const Plane3d& plane);