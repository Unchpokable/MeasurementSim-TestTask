#pragma once

#include <eigen/include/Eigen/Core>

using Point3d = Eigen::Vector3d;

struct Data3D
{
    Eigen::Vector3d Normal;
    Point3d NominalPosition;
    Point3d ActualPosition;
};