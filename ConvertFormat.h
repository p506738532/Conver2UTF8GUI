#ifndef CONVERTFORMAT_H
#define CONVERTFORMAT_H
#include <QObject>
/* *********************************************
 * 用来转换文本的编码格式
 * *********************************************/
struct FileInfo
{
    QString fileName;
    QString filePath;
    QString beginFormat;
    QString endFormat;
    bool sucessBool;
    QString newFilePath;
};
class QProcess;
//测试函数
void TestIconv();
class ConvertFormat: public QObject
{
public:
    ConvertFormat();

    bool AddFiles(QStringList fileNameList );
    QList<FileInfo> GetFiles( );
    void ClearFiles( );
    //转换函数
    void Convert();
    void Convert2();


private:
    QList<FileInfo> m_fileInfoList;
    QProcess * m_process;
    QString m_programLocation;
};

#endif // CONVERTFORMAT_H
