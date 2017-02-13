#include <header/algorithm/algorithm.h>
#include <header/tool/circleTool.h>

CircleTool::CircleTool() {

}

QString CircleTool::getName() {
    return "brush";
}

cv::Scalar CircleTool::getActualColor(cv::Scalar color, bool isRightButton) {
    return color;
}

bool CircleTool::usesHiddenLayer() {
    return false;
}

void CircleTool::mousePressed(ImageManager* imageManager, Layer* layer, int x, int y, cv::Scalar color, QObject* parameters) {
    color = getActualColor(color, false);
    int radius = 0;
    QVariant v;
    if(!(v=parameters->property("radius")).isNull())
        radius = v.toInt();

    cv::circle(*layer, cv::Point2i(x, y), radius, color, -1);
}

void CircleTool::mouseDragged(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters) {
    color = getActualColor(color, false);
    int radius = 0;
    QVariant v;
    if(!(v=parameters->property("radius")).isNull())
        radius = v.toInt();

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
            //qDebug() << x << y;
            cv::circle(*layer, cv::Point2i(x, y), radius, color, -1);
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
        for(float y=ys; y<=ye; ++y) {
            //qDebug() << x << y;
            cv::circle(*layer, cv::Point2i(x, y), radius, color, -1);
            x += xadd;
        }
    }
}

void CircleTool::mouseReleased(ImageManager* imageManager, Layer* layer, int xs, int ys, int xe, int ye, cv::Scalar color, QObject* parameters) {

}

bool CircleTool::requiresNewLayerOnPressed(cv::Scalar color) {return false;}
bool CircleTool::requiresNewLayerOnDragged(cv::Scalar color) {return false;}
bool CircleTool::requiresNewLayerOnReleased(cv::Scalar color) {return false;}
