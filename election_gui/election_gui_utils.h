#ifndef ELECTION_GUI_UTILS_H
#define ELECTION_GUI_UTILS_H

class QFileInfo;

namespace python_script_running
{

void runPythonScript(const QFileInfo& script);

};

namespace geom_utils
{

template <class T>
struct PolarPoint
{
    T r_;
    T theta_;
};

template <class T>
struct CartesianPoint
{
    T x_;
    T y_;
};

template <class T>
PolarPoint<T> cartesianToPolar(const CartesianPoint<T>& cartPoint)
{

}

template <class T>
CartesianPoint<T> polarToCartesian(const PolarPoint<T>& polarPoint)
{

}

};

#endif // ELECTION_GUI_UTILS_H
