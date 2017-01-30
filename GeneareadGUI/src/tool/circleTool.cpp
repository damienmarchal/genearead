#include <header/algorithm/algorithm.h>
#include <header/tool/circleTool.h>

#include <opencv2/imgproc.hpp>

CircleTool::CircleTool() {

}

QString CircleTool::getName() {
    return "pinceau"; //gomme rectangle
}

void CircleTool::draw(Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject *parameters) {
    int radius;

    QVariant v;
    if(!(v=parameters->property("radius")).isNull())
        radius = v.toInt();

    qDebug() << "drawing circle";

    int a;
    float xd = cv::abs(xe-xs);
    float yd = cv::abs(ye-ys);
    float xadd, yadd;
    if(xd > yd) {
        if(xs>xe) {
            a = xs;
            xs = xe;
            xe = a;
            a = ys;
            ys = ye;
            ye = a;
        }
        xadd = 1.0f;
        yadd = (float)(ye-ys)/xd;
        float y = ys;
        for(float x=xs; x<xe; ++x) {
            qDebug() << x << y;
            cv::circle(*layer, cv::Point2f(x, y), radius, color, -1);
            y += yadd;
        }
    } else {
        if(ys>ye) {
            a = ys;
            ys = ye;
            ye = a;
            a = xs;
            xs = xe;
            xe = a;
        }
        yadd = 1.0f;
        xadd = (float)(xe-xs)/yd;
        float x = xs;
        for(float y=ys; y<ye; ++y) {
            qDebug() << x << y;
            cv::circle(*layer, cv::Point2f(x, y), radius, color, -1);
            x += xadd;
        }
    }
}
