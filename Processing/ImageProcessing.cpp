#include "ImageProcessing.h"

ImageProcessing::ImageProcessing(QObject *parent) : QObject(parent)
{

}

QPoint ImageProcessing::findImageOnImage(const QString &smallImagePath, const QString &largeImagePath)
{
//    LOG << "[ImageProcessing]"  << smallImagePath.split("/").last() << largeImagePath.split("/").last();

    QPoint retVal;

//    LOG << "[ImageProcessing]" << "Small image: " << QImage(smallImagePath).size();
//    LOG << "[ImageProcessing]" << "Large image: " << QImage(largeImagePath).size();
#ifdef USE_OPENCV

    cv::Mat _smallImage = cv::imread(smallImagePath.toUtf8().constData());
    cv::Mat _largeImage = cv::imread(largeImagePath.toUtf8().constData());

    //kiểm tra kích cỡ của ảnh input & template
    if (_smallImage.rows > _largeImage.rows || _smallImage.cols > _largeImage.cols)
    {
        LOG << "[ImageProcessing]" << "Mat template must be smaller than matInput";
        return retVal;
    }else if(_smallImage.rows <= 0 || _smallImage.cols <= 0 || _largeImage.rows <= 0 || _largeImage.cols <= 0){
        LOG << "[ImageProcessing]" << "Invalid Image";
        return retVal;
    }

    cv::Mat result;
    int result_cols = _largeImage.cols - _smallImage.cols + 1;
    int result_rows = _largeImage.rows - _smallImage.rows + 1;
    result.create(result_rows, result_cols, CV_32FC1);

    //tìm mẫu
    cv::matchTemplate(_largeImage, _smallImage, result, CV_TM_CCORR_NORMED);


    double threshold = 0.98;
    cv::threshold(result, result, threshold, 1., CV_THRESH_TOZERO);
    double minval, maxval;
    double bestMaxval = 0;
    //ngưỡng chính xác, giảm xuống thì sẽ tìm được nhiều đối tượng hơn nhưng sai số nhiều hơn

    while (true)
    {
        cv::Point minloc, maxloc;
        cv::minMaxLoc(result, &minval, &maxval, &minloc, &maxloc);

        if (maxval > threshold)
        {
            //vẽ hình chữ nhật lên đối tượng tìm được
            if(maxval > bestMaxval){
                bestMaxval = maxval;
                retVal = QPoint(maxloc.x + _smallImage.cols/2, maxloc.y + _smallImage.rows/2);
            }
            cv::floodFill(result, maxloc, cv::Scalar(0), 0, cv::Scalar(.1), cv::Scalar(1.));

        }
        else
            break;
    }

//    LOG << "[ImageProcessing]" << "Return values: " << retVal << " --- bestMaxVal: " << bestMaxval;
#endif
    return retVal;
}

QString ImageProcessing::extractCaptchaImage(const QString &path)
{
    LOG << "[ImageProcessing]" << "Path: " << path;

#ifndef USE_OPENCV
    return  QString("");
#else
    cv::Mat src = cv::imread(path.toUtf8().constData());
    cv::Rect crop(58 , 473, 715, 216);
    cv::Mat rez = src(crop);

    QString captImgPath = (QDir::currentPath() + "/captcha.png");
    cv::imwrite(captImgPath.toUtf8().constData(),rez);
    cv::waitKey(100);

    if(QFile(captImgPath).exists() && !QImage(captImgPath).isNull()){
        return captImgPath;
    }else{
        LOG << "[ImageProcessing]" << "Couldn't extract captcha image";
        return QString("");
    }
#endif
}
