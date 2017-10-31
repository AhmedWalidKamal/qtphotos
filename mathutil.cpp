#include "mathutil.h"
#include <QtMath>
double math::calculateAngle(QPoint start, QPoint end) {
    QPoint vec = end - start;
    double angle = qAtan2(vec.y(), vec.x());
}
