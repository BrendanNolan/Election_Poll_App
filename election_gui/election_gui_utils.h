#ifndef ELECTION_GUI_UTILS_H
#define ELECTION_GUI_UTILS_H

/*
    These utils are far from their final form. I am addiing to them as and when
    I need new utilities.
*/

#include <cmath>

class QFileInfo;

namespace python_script_running
{

void runPythonScript(const QFileInfo& script);

};

namespace geom_utils
{

const auto pi = 3.141;

template <class T>
class PolarPoint
{
public:
    PolarPoint() = default;
    PolarPoint(T r, T theta)
        : r_(r)
    {
        setTheta(theta);
    }

    void rotate(T radians)
    {
        setTheta(theta_ + radians);
    }

    PolarPoint rotated(T radians)
    {
        auto rotatedCopy = *this;
        rotatedCopy.rotate(radians);
        return rotatedCopy;
    }

    T r() const { return r_; }
    T theta() const { return theta_; }
    void setR(T r) { r_ = r; }
    void setTheta(T theta) 
    { 
        auto thetaAsDouble = static_cast<double>(theta);
        theta_ = static_cast<T>(thetaAsDouble % (2 * pi));
    }

private:
    T r_ = 0;
    T theta_ = 0;
};

template <class T>
class CartesianPoint
{
public:
    CartesianPoint() = default;
    CartesianPoint(T x, T y)
        : x_(x)
        , y_(y)
    {}

    void rotateAbout(
        const CartesianPoint& fulcrum, T radians);

    CartesianPoint rotatedAbout(
        const CartesianPoint& fulcrum, T radians) const
    {
        auto rotatedCopy = *this;
        rotatedCopy.rotateAbout(fulcrum, radians);
        return rotatedCopy;
    }

    T x() const { return x_; }
    T y() const { return y_; }
    void setX(T x) { x_ = x; }
    void setY(T y) { y_ = y; }

private:
    T x_ = 0;
    T y_ = 0;
};

template <class T>
CartesianPoint<T> operator+(
    const CartesianPoint<T>& a, const CartesianPoint<T>& b)
{
    return CartesianPoint<T>(a.x() + b.x(), a.y() + b.y());
}

template <class T>
CartesianPoint<T> operator-(
    const CartesianPoint<T>& a, const CartesianPoint<T>& b)
{
    return CartesianPoint<T>(a.x() - b.x(), a.y() - b.y());
}

template <class T>
PolarPoint<T> cartesianToPolar(const CartesianPoint<T>& cartPoint)
{
    auto x = cartPoint.x();
    auto y = cartPoint.y();

    if (x == 0 && y == 0)
    {
        return PolarPoint<T>(0, 0);
    }

    auto r = static_cast<T>(std::sqrt((x ^ 2) + (y ^ 2)));
    auto theta = 0;

    if (x == 0)
        theta = (y > 0) ? static_cast<T>(pi / 2) : static_cast<T>((3 * pi) / 2);
    else 
        theta = std::atan(y / x);
    return PolarPoint<T>(r, theta);
}

template <class T>
CartesianPoint<T> polarToCartesian(const PolarPoint<T>& polarPoint)
{
    CartesianPoint<T> cartPoint;
    cartPoint.setX(polarPoint.r() * std::cos(polarPoint.theta()));
    cartPoint.setY(polarPoint.r() * std::sin(polarPoint.theta()));
    return cartPoint;
}

template <class T>
void CartesianPoint<T>::rotateAbout(
    const CartesianPoint& fulcrum, T radians)
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

};

#endif // ELECTION_GUI_UTILS_H
