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

Circle3d CircleFromPoints(const Point3d& pt1, const Point3d& pt2, const Point3d& pt3)
{
    const auto vec1 = pt2 - pt1;
    const auto vec2 = pt3 - pt1;

    const auto normal = vec1.cross(vec2).normalized();

    Point3d center {};
    const auto pt_sum = pt1 + pt2 + pt3;

    center.x() = pt_sum.x() / 3.0;
    center.y() = pt_sum.y() / 3.0;
    center.z() = pt_sum.z() / 3.0;
    const auto radius = Eigen::Vector3d(pt1.x() - center.x(), pt1.y() - center.y(), pt1.z() - center.z()).norm();
    return { normal, center, radius };
}


Point3d Project(const Point3d& point, const Plane3d& plane)
{
    //Algo stealed from MathNet sources. I have no idea is this works properly
    auto num = plane.Normal.dot(point);
    auto vec = plane.Normal;

    return point - (num + plane.D) * vec;
}


