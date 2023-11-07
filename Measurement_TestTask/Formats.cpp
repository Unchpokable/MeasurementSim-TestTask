#include "Formats.h"

#include <iomanip>


Bracket RoundBrackets()
{
    return Bracket { '(', ')' };
}


Bracket SquareBrackets()
{
    return Bracket { '[', ']' };
}

Bracket GetBracket(Brackets brackets)
{
    switch(brackets) {
        case BR_ROUND:
            return RoundBrackets();
        case BR_SQUARE:
            return SquareBrackets();
    }

    return RoundBrackets();
}

std::string Point2StdString(const Point3d& point)
{
    std::stringstream buff {};
    buff << "Point at (";
    buff << std::fixed << std::setprecision(3) << point.x() << ", " << point.y() << ", " << point.z() << ")";

    return buff.str();
}

QString Point2String(const Point3d& point)
{
    return QString::fromUtf8(Point2StdString(point));
}

QString Data3d2String(const Data3D& source, bool need_header)
{
    std::stringstream buff {};
    
    if(need_header)
        buff << "3D Object";
    buff << "Nominal:\n";
    buff << std::fixed << std::setprecision(3) << Point2StdString(source.NominalPosition) << Point2StdString(source.Normal);
    buff << "\n";
    buff << "Actual:\n";
    buff << Point2StdString(source.ActualPosition) << "\n";

    return QString::fromUtf8(buff.str().c_str());
}

std::string Circle3d2StdString(const Circle3d& circle)
{
    std::stringstream buff {};

    buff << "Base Point: " << Point2StdString(circle.CenterPoint) << "\n";
    buff << "Plane Normal: :" << Point2StdString(circle.Normal) << "\n";
    buff << "Radius: " << std::fixed << std::setprecision(3) << circle.Radius;

    return buff.str();
}

std::string Plane3d2StdString(const Plane3d& plane)
{
    std::stringstream buff {};

    buff << std::fixed << std::setprecision(3);

    buff << "Plane normal: " << plane.Normal;

    buff << "Plane " << plane.A << "x + " << plane.B << "y + " << plane.C << "z + " << plane.D;

    return buff.str();
}

QString Plane3dToString(const Plane3d& plane)
{
    return QString::fromUtf8(Plane3d2StdString(plane));
}

QString Circle3d2String(const Circle3d& circle)
{
    return QString::fromUtf8(Circle3d2StdString(circle));
}

