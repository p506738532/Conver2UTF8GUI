#include "ConvertFormat.h"
#include <QDebug>
#include <QProcess>
#include <QApplication>
#include <QFile>
#include<IconvPair.h>

ConvertFormat::ConvertFormat()
{
    m_process = new QProcess(this);

    //获取当前路径

    m_programLocation = QCoreApplication::applicationDirPath() +"/ThirdExe/iconv.exe";
    qDebug() << "exe:" <<m_programLocation;
}

bool ConvertFormat::AddFiles(QStringList fileNameList)
{
    foreach (QString file, fileNameList) {

        FileInfo fileInfo;
        file.replace("\\","/");//路径中的反斜杠全部替换为正斜杠
        int lastSepara = file.lastIndexOf("/") ;
        fileInfo.fileName = file.mid(lastSepara+1,file.count() - lastSepara );
        fileInfo.filePath = file.left( lastSepara );
        fileInfo.beginFormat = "GBK";
        fileInfo.endFormat = "UTF-8";
        fileInfo.sucessBool = false;
        //加入到成员变量中
        m_fileInfoList.append( fileInfo );
    }
}

QList<FileInfo> ConvertFormat::GetFiles()
{
    return m_fileInfoList;
}

void ConvertFormat::ClearFiles()
{
    m_fileInfoList.clear();
}

void ConvertFormat::Convert()
{
    //调用iconv提供的exe实现编码的转换
    for( int ifile = 0; ifile < m_fileInfoList.count(); ifile++ )
    {
        FileInfo & file = m_fileInfoList[ifile];
        QStringList arguments;//iconv.exe -f gbk -t utf-8 gbk.txt
        arguments << "-f" << file.beginFormat;//转换前的格式
        arguments << "-t" << file.endFormat;//转换后的格式
        arguments << file.filePath + "/" +file.fileName;//源文件位置

        m_process->start(m_programLocation, arguments);

        while( !m_process->waitForFinished(3000) )
        {
            //延时函数 do nothing;
        }
        QString logStr;
        logStr.append( m_programLocation + " ");
        foreach(QString argu,arguments)
        {
            logStr.append(argu + " ");
        }
        logStr = m_process->readAllStandardError();
        qDebug( ) <<"error:" << logStr;
        //判断是否转换成功
        if( logStr.isEmpty() )
        {
            //success
            file.sucessBool = true;
            QString newFilePath = file.filePath +"/"  + file.fileName;
            QFile writeFile( newFilePath );
            if(!writeFile.open(QIODevice::WriteOnly|QIODevice::Text) )
            {
                qDebug()<<"OPEN FILE FAILED";
                file.sucessBool = false;
            }
            else
            {
                //写文件
                QByteArray transedByteArray = m_process->readAllStandardOutput() ;
                writeFile.write(transedByteArray);
                writeFile.close();
            }
        }
        else
        {
            file.sucessBool = false;
        }
    }
}
//ansi to utf8
void ConvertFormat::Convert2()
{
    for( int ifile = 0; ifile < m_fileInfoList.count(); ifile++ )
    {
        FileInfo file = m_fileInfoList.at(ifile);

        QString oldFilePath = file.filePath + "/" + file.fileName;
        QString newFilePath = file.filePath +"/" + "utf8_" + file.fileName;
        QFile readFile( oldFilePath );
        if(!readFile.open(QIODevice::ReadOnly|QIODevice::Text) )
            qDebug()<<"OPEN FILE FAILED";
        QFile writeFile( newFilePath );
        if(!writeFile.open(QIODevice::WriteOnly) )
            qDebug()<<"OPEN FILE FAILED";
        //QTextStream writeIn(&writeFile);//文本流
        //写文件
        QByteArray readByteArray = readFile.readAll();
        QByteArray transedByteArray = AnsiToUtf8(readByteArray);
        //writeIn << transedByteArray;
        //writeIn.flush();
        writeFile.write( transedByteArray );
        writeFile.close();
        readFile.close( );
        qDebug( ) << "read file:" <<readByteArray.toHex().toUpper();
        qDebug() << "output 0x " <<transedByteArray.toHex().toUpper();
    }
}

void TestIconv()
{
    QByteArray oldUtf8 = "我";
    qDebug()<<"oldUtf8 0x "<<oldUtf8.toHex().toUpper();
    QByteArray retAnsi = Utf8ToAnsi(oldUtf8);
    qDebug()<<"reAnsi 0x "<<retAnsi.toHex().toUpper();

    QByteArray retUtf8 = AnsiToUtf8(retAnsi);

    if(oldUtf8==retUtf8)
        qDebug()<<"result="<<(oldUtf8==retUtf8);
    //map<char*, char*> mapx = GetDictionary(NULL);
}
