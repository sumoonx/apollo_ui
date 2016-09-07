#include "threedimenworker.h"
#include <math.h>

const double ThreeDimenWorker::v0 = 1.2053;

const double ThreeDimenWorker::a = -49.87;

const double ThreeDimenWorker::L = 0.25;

ThreeDimenWorker::ThreeDimenWorker(QObject *parent)
    :PositioningWorker(parent)
{

}

void ThreeDimenWorker::doWork(QList<Anchor> anchors)
{
    emit resultReady(getLocation(anchors));
}

QList<Anchor> ThreeDimenWorker::pickThree(QList<Anchor> anchors) {
    return anchors;
}

Location ThreeDimenWorker::getLocation(QList<Anchor> anchors) {
    QList<Anchor> anchs = pickThree(anchors);
    double vr1 = log(anchs[0].getRssi() / v0);
    double vr2 = log(anchs[1].getRssi() / v0);
    double vr3 = log(anchs[2].getRssi() / v0);

    double c2 = (3 * (vr1 - vr2) * (vr1 - vr2)
          + (vr1 + vr2 - 2*vr3) * (vr1 + vr2 - 2*vr3))
          / (12 * a * L * L);
    double c1 = -(vr1 + vr2 + vr3) / 3;
    double c0 = a * L * L / 3;

    double minerr = 1000000;
    double he = 0;
    for (double h = 1.5; h < 3; h += 0.01) {
        double H = h * h;
        double err = c2 * H * H + c1 * H + c0 - H * log(H);
        if (abs(err) < abs(minerr)) {
            minerr = err;
            he = h;
        }
    }
    double xe = 0.5 * ((vr1 - vr2) * he * he / (a * L) + L);
    double ye = sqrt(3) / 6 * ((vr1 + vr2 - 2 * vr3) * he * he / (a * L) + L);

    Location location(xe, ye, he);
    return location;
}
