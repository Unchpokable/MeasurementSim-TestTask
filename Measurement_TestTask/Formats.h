#pragma once
#include <QString>
#include "GeometryData.h"
#include "MathFunctions.h"

enum Brackets
{
    BR_ROUND,
    BR_SQUARE
};

struct Bracket
{
    char Open, Close;
};

Bracket RoundBrackets();
Bracket SquareBrackets();

//Returns Bracket struct with Open-Close brackets by given type
Bracket GetBracket(Brackets brackets);

std::string Point2StdString(const Point3d& point);

QString Point2String(const Point3d& point);

QString Data3d2String(const Data3D& source, bool need_header = true);

std::string Circle3d2StdString(const Circle3d& circle);

std::string Plane3d2StdString(const Plane3d& plane);

QString Plane3dToString(const Plane3d& plane);

QString Circle3d2String(const Circle3d& circle);