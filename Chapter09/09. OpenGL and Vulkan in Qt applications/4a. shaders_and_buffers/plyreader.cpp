#include "plyreader.h"
#include <QFile>

PlyReader::PlyReader(const QString &fileName) {
    m_fileName = fileName;
}

bool PlyReader::read() {
    m_vertices.clear();
    m_faces.clear();
    QFile file(m_fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }
    QTextStream stream(&file);
    QString line = stream.readLine();
    if(line != "ply") {
        return false;
    }
    line = stream.readLine();
    int vertexCount = 0, faceCount = 0;
    while(line != "end_header") {
        if(line.startsWith("element")) {
            QStringList args = line.split(QRegExp("\\s+"));
            if(args.count() < 3) {
                break;
            }
            if(args.at(1) == "vertex") {
                vertexCount = args.at(2).toInt();
            } else if(args.at(1) == "face") {
                faceCount = args.at(2).toInt();
            }
        }
        line = stream.readLine();
    }
    readVertices(stream, vertexCount);
    readFaces(stream, faceCount);
    return true;
}

void PlyReader::readVertices(QTextStream &stream, int vertexCount) {
    m_vertices.reserve(vertexCount);
    for(int i = 0; i < vertexCount; ++i) {
        m_vertices << readVertex(stream);
    }
}

void PlyReader::readFaces(QTextStream &stream, int faceCount) {
    m_faces.reserve(faceCount);
    for(int i = 0; i < faceCount; ++i) {
        m_faces << readFace(stream);
    }
}

PlyReader::ScenePoint PlyReader::readVertex(QTextStream &stream) {
    ScenePoint pt;
    float xpos, ypos, zpos;
    float nx, ny, nz;
    stream >> xpos >> ypos >> zpos >> nx >> ny >> nz;
    pt.coord = QVector3D(xpos, ypos, zpos);
    pt.normal = QVector3D(nx, ny, nz);
    return pt;
}

QVector<int> PlyReader::readFace(QTextStream &stream) {
    int cnt, pt;
    stream >> cnt;
    QVector<int> face;
    face.reserve(cnt);
    for(int v = 0; v < cnt; ++v) {
        stream >> pt;
        face << pt;
    }
    return face;
}
