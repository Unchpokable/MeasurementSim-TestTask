#pragma once

#include <eigen/include/Eigen/Core>

using Point3d = Eigen::Vector3d;

struct Data3D
{
    Eigen::Vector3d Normal;
    Eigen::Vector3d ActualNormal;
    Point3d NominalPosition;
    Point3d ActualPosition;
};

struct Point3dEx
{
    Point3d Point;
    Eigen::Vector3d Normal;
};

struct ProjectionPoint3d
{
    Point3d ProjectionActual;
    Point3d ProjectionNominal;

    Eigen::Vector3d NormalActual;
    Eigen::Vector3d NormalNominal;
};