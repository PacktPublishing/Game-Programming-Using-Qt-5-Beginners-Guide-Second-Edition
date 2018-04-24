#ifndef CAESARCIPHERDEVICE_H
#define CAESARCIPHERDEVICE_H

#include <QIODevice>

class CaesarCipherDevice : public QIODevice
{
    Q_OBJECT
    Q_PROPERTY(int key READ key WRITE setKey)
public:
    explicit CaesarCipherDevice(QObject *parent = 0);
    void setBaseDevice(QIODevice *dev) {
        m_baseDevice = dev;
    }
    QIODevice *baseDevice() const {
        return m_baseDevice;
    }
    void setKey(int k) {
        m_key = k;
    }
    inline int key() const {
        return m_key;
    }
    bool open(OpenMode mode);
protected:
    qint64 writeData(const char *data, qint64 len);
    qint64 readData(char *data, qint64 maxlen);
private:
    int m_key;
    QIODevice *m_baseDevice;
};

#endif // CAESARCIPHERDEVICE_H
