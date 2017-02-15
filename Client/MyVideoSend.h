#ifndef MYVIDEOSEND_H
#define MYVIDEOSEND_H

#include <QObject>
#include <QAbstractVideoSurface>
#include <QVideoFrame>

class MyVideoSend : public QAbstractVideoSurface
{
    Q_OBJECT
public:
    //设置图像处理格式
    QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const;
    //捕获图像信息
    MyVideoSend(QObject *parent = Q_NULLPTR);

    bool present(const QVideoFrame &frame);

signals:
    void videoChanged(const QVideoFrame& frame);
};

#endif // MYVIDEOSEND_H
