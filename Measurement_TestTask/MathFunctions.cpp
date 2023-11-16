#include "MathFunctions.h"

Plane3d PlaneFromPoints(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3)
{
    const auto v1 = pt2 - pt1;
    const auto v2 = pt3 - pt1;

    auto normal = v1.cross(v2).normalized();

    const auto a = normal.x();
    const auto b = normal.y();
    const auto c = normal.z();
    const auto d = -a * pt1.x() - b * pt1.y() - c * pt1.z();

    return Plane3d { a, b, c, d, normal };
}

Circle3d CircleFromPoints(const Point3d& p1, const Point3d& p2, const Point3d& p3)
{
    Circle3d circle;

    const Eigen::Vector3d t = p2 - p1;
    const Eigen::Vector3d u = p3 - p1;
    const Eigen::Vector3d v = p3 - p2;

    // triangle normal
    const Eigen::Vector3d w = t.cross(u);
    const double wsl = w.squaredNorm();
    if(wsl < 1.0e-14) {
        circle.Normal = Eigen::Vector3d::Zero();
        circle.CenterPoint = Eigen::Vector3d::Zero();
        circle.Radius = 0.0;
        return circle;
    }

    // helpers
    const double iwsl2 = 1.0 / (2.0 * wsl);
    const double tt = t.squaredNorm();
    const double uu = u.squaredNorm();

    // result circle
    circle.CenterPoint = p1 + (u * tt * (u.dot(v)) - t * uu * (t.dot(v))) * iwsl2;
    circle.Radius = sqrt(tt * uu * (v.squaredNorm()) * iwsl2 * 0.5);
    circle.Normal = w / sqrt(wsl);

    return circle;
}

Point3d Project(const Point3d& point, const Plane3d& plane)
{
    //Algo stealed from MathNet sources. I have no idea is this works properly
    auto num = plane.Normal.dot(point);
    auto vec = plane.Normal;

    return point - (num + plane.D) * vec;
}