#include <Python.h>

#include "election_gui_utils.h"

#include <QFileInfo>

#include <cstdio>

namespace python_scripting
{

    void runPythonScript(const QFileInfo& script)
    {
        const auto scriptPathAsStdString = script.absoluteFilePath().toStdString();
        auto scriptPathAsCString = scriptPathAsStdString.c_str();

        auto scriptFilePtr = fopen(scriptPathAsCString, "r");
        // Not yet asynchronous but needs to be
        Py_Initialize();
        PyRun_SimpleFile(scriptFilePtr, scriptPathAsCString);
        Py_Finalize();
        fclose(scriptFilePtr);
    }

}

namespace geom_utils
{

    PolarPoint::PolarPoint(double r, double theta)
        : r_(r)
    {
        setTheta(theta);
    }

    void PolarPoint::rotate(double radians)
    {
        setTheta(theta_ + radians);
    }

    PolarPoint PolarPoint::rotated(double radians) const
    {
        auto rotatedCopy = *this;
        rotatedCopy.rotate(radians);
        return rotatedCopy;
    }

    double PolarPoint::r() const 
    { 
        return r_; 
    }
    
    double PolarPoint::theta() const
    { 
        return theta_; 
    }
    
    void PolarPoint::setR(double r)
    { 
        r_ = r; 
    }
    
    void PolarPoint::setTheta(double theta)
    {
        theta_ = std::fmod(theta, 2 * pi);
    }

    CartesianPoint::CartesianPoint(double x, double y)
        : x_(x)
        , y_(y)
    {}
    
    void CartesianPoint::rotateAbout(
        const CartesianPoint& fulcrum, double radians)
    {
        auto translatedPoint = *this - fulcrum;
        auto polarTranslatedPoint = cartesianToPolar(translatedPoint);
        auto rotatedPolarTranslatedPoint = polarTranslatedPoint.rotated(
            radians);
        auto rotatedTranslatedPoint = polarToCartesian(
            rotatedPolarTranslatedPoint);
        auto rotatedPoint = rotatedTranslatedPoint + fulcrum;
        *this = rotatedPoint;
    }

    CartesianPoint CartesianPoint::rotatedAbout(
        const CartesianPoint& fulcrum, double radians) const
    {
        auto rotatedCopy = *this;
        rotatedCopy.rotateAbout(fulcrum, radians);
        return rotatedCopy;
    }

    double CartesianPoint::x() const 
    { 
        return x_; 
    }
    
    double CartesianPoint::y() const 
    { 
        return y_; 
    }
    
    void CartesianPoint::setX(double x) 
    { 
        x_ = x; 
    }
    
    void CartesianPoint::setY(double y) 
    { 
        y_ = y; 
    }

    CartesianPoint operator+(
        const CartesianPoint& a, const CartesianPoint& b)
    {
        return CartesianPoint(a.x() + b.x(), a.y() + b.y());
    }


    CartesianPoint operator-(
        const CartesianPoint& a, const CartesianPoint& b)
    {
        return CartesianPoint(a.x() - b.x(), a.y() - b.y());
    }

    QPointF cartesianToQPointF(CartesianPoint& cp)
    {
        return QPointF(cp.x(), - (cp.y()));
    }

    PolarPoint cartesianToPolar(const CartesianPoint& cartPoint)
    {
        auto x = cartPoint.x();
        auto y = cartPoint.y();

        auto r = std::sqrt(std::pow(x, 2) + std::pow(y, 2));
        if (r < doublePrecisionTolerance)
            return PolarPoint(0.0, 0.0);

        auto theta = (y >= 0.0) ? std::acos(x / r) : - std::acos(x / r);

        return PolarPoint(r, theta);
    }

    CartesianPoint polarToCartesian(const PolarPoint& polarPoint)
    {
        CartesianPoint cartPoint;
        cartPoint.setX(polarPoint.r() * std::cos(polarPoint.theta()));
        cartPoint.setY(polarPoint.r() * std::sin(polarPoint.theta()));
        return cartPoint;
    }

    double dist(const CartesianPoint& a, const CartesianPoint& b)
    {
        return std::sqrt(
            std::pow(a.x() - b.x(), 2) + std::pow(a.y() - b.y(), 2));
    }

    double geom_utils::distFromOrigin(const QPointF& point)
    {
        return static_cast<double>(std::sqrt(
            std::pow(point.x(), 2) + 
            std::pow(point.y(), 2)));
    }

}
