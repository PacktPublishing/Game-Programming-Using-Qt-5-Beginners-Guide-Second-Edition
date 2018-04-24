#ifndef PLYREADER_H
#define PLYREADER_H

#include <QObject>
#include <QVector3D>
#include <QTextStream>
#include <QVector>

class QIODevice;

class PlyReader : public QObject {
public:
    struct ScenePoint {
        QVector3D coord;
        QVector3D normal;
    };

    PlyReader(const QString &fileName);
    bool read();

    inline const QVector<ScenePoint> vertices() const { return m_vertices; }
    inline const QVector<QVector<int>> faces() const { return m_faces; }

protected:
    void readVertices(QTextStream &stream, int vertexCount);
    void readFaces(QTextStream &stream, int faceCount);
    ScenePoint readVertex(QTextStream &stream);
    QVector<int> readFace(QTextStream &stream);

private:
    QString m_fileName;
    QVector<ScenePoint> m_vertices;
    QVector<QVector<int> > m_faces;

};

#endif // PLYREADER_H
