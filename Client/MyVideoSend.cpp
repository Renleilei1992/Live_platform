#include "MyVideoSend.h"

MyVideoSend::MyVideoSend(QObject *parent)
    :QAbstractVideoSurface(parent)
{

}

QList<QVideoFrame::PixelFormat> MyVideoSend::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
    return QList<QVideoFrame::PixelFormat>()<<QVideoFrame::Format_RGB32;
}

bool MyVideoSend::present(const QVideoFrame &frame)
{
    emit videoChanged(frame);
    return true;
}
