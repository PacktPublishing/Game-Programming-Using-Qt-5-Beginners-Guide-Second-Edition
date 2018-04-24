#include "caesarcipherdevice.h"
#include <QDebug>

CaesarCipherDevice::CaesarCipherDevice(QObject *parent) : QIODevice(parent) {
    m_key = 0;
    m_baseDevice = 0;
}

bool CaesarCipherDevice::open(OpenMode mode) {
    if(!m_baseDevice) {
        qWarning("CaesarCipherDevice::open: No base device");
        setErrorString(tr("No base device"));
        return false;
    }
    if(!m_baseDevice->isOpen()) {
        qWarning("CaesarCipherDevice::open: Base device is not open");
        setErrorString(tr("Base device is not open"));
        return false;
    }
    if(m_baseDevice->openMode() != mode) {
        qWarning("CaesarCipherDevice::open: Base device has a different openMode()");
        setErrorString(tr("Base device has a different openMode()"));
        return false;
    }
    return QIODevice::open(mode);
}

qint64 CaesarCipherDevice::writeData(const char *data, qint64 len) {
    QByteArray byteArray;
    byteArray.resize(len);
    for(int i = 0; i < len; ++i) {
        byteArray[i] = data[i] + m_key;
    }
    int written = m_baseDevice->write(byteArray);
    emit bytesWritten(written);
    return written;
}

qint64 CaesarCipherDevice::readData(char *data, qint64 maxlen) {
    QByteArray baseData = m_baseDevice->read(maxlen);
    const int size = baseData.size();
    for(int i = 0; i < size; ++i) {
        data[i] = baseData[i] - m_key;
    }
    return size;
}
