#ifndef _ICONV_PAIR_HXX_
#define _ICONV_PAIR_HXX_

#include<map>
#include<string>
#include<iostream>
#include <vector>
#include <stdlib.h>
#include <algorithm>
using namespace std;

#include <string.h>
#include <stdio.h>
#include <map>
#include <hash_map>
using namespace std;
#include <QCoreApplication>
#include <QDebug>
#include <QMessageBox>

//#define _CUR_SYS_LINUX_ 1	//根据你的系统自己设置_CUR_SYS_LINUX_

#ifdef _CUR_SYS_LINUX_
    #include <iconv.h>
#else
    #include <windows.h>
    #include <stdio.h>
#endif

/*
unicode文件：0xff 0xfe + 内容
utf8文件：0xEF 0xBB 0xBF + 内容
无bom的utf8文件：没有前面3个字节
"回车"（carriage return） 13
"换行"（line feed）       10
Windows系统里面，每行结尾是"<回车><换行>"，即"\r\n"；
Unix系统里，每行结尾只有"<换行>"，即"\n"；
Mac系统里，每行结尾是"<回车>"，即"\r"。
*/
#ifdef _CUR_SYS_LINUX_
inline int code_convert(char *from_charset,char *to_charset,char *inbuf,int inlen,char *outbuf,int outlen)
{
    iconv_t cd;
    //int rc;
    char **pin = &inbuf;
    char **pout = &outbuf;
    cd = iconv_open(to_charset,from_charset);
    if (cd==0) return -1;
    memset(outbuf,0,outlen);
    //if (iconv(cd,pin,(size_t*)(&inlen),pout,(size_t*)(&outlen))==-1) return -1;
    iconv(cd,pin,(size_t*)(&inlen),pout,(size_t*)(&outlen));
    iconv_close(cd);
    return 0;
}
#endif

/****************************************************
*utf8到ansi的转换
*输入参数:
*输出参数:
*****************************************************/
inline QByteArray Utf8ToAnsi(QByteArray &inUtf8)
{
#ifdef _CUR_SYS_LINUX_
    QByteArray qbaOut;
    char *outBuf = new char[inUtf8.size()+1];
    memset(outBuf,0,inUtf8.size()+1);
    char utf8Buf[] = {"utf-8"};
    char gb2312Buf[] = {"gb2312"};
    //ansi.resize(utf8.size());
    int code = code_convert(utf8Buf,gb2312Buf,inUtf8.data(),inUtf8.size(),outBuf,inUtf8.size());
    if (code == -1) {
        delete []outBuf;
        qbaOut = "";
        //qDebug() << "Utf8ToAnsi error";
        return qbaOut;
    }
    qbaOut = outBuf;
    ////qDebug() << "utf8 length=" << utf8.size();
    ////qDebug() << "ansi length=" << ansi.size();
    delete []outBuf;
    return qbaOut;
#else
    int len;
    QByteArray result;
    //UTF-8转UNICODE
    len = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)inUtf8.data(), -1, NULL,0);
    WCHAR * unicode = new WCHAR[len+1];
    memset(unicode, 0, len * 2 + 2);
    MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)inUtf8.data(), -1, unicode, len);
    //UNICODE转ANSI
    len = WideCharToMultiByte(CP_ACP, 0, unicode, -1, NULL, 0, NULL, NULL);
    char *ansi=new char[len + 1];
    memset(ansi, 0, len + 1);
    WideCharToMultiByte (CP_ACP, 0, unicode, -1, ansi, len, NULL,NULL);
    //赋值
    result = ansi;
    delete[] unicode;
    delete[] ansi;
    return result;
#endif
}

/****************************************************
*ansi到utf8的转换
*输入参数:
*输出参数:
*****************************************************/
inline QByteArray AnsiToUtf8(QByteArray &ansi)
{
#ifdef _CUR_SYS_LINUX_
    QByteArray utf8;
    char *buf = new char[ansi.size()*2];
    char utf8Buf[] = {"utf-8"};
    char gb2312Buf[] = {"gb2312"};
    //ansi.resize(ansi.size()*2);
    int code = code_convert(gb2312Buf,utf8Buf,ansi.data(),ansi.size(),buf,2*ansi.size());
    if (code == -1) {
        delete []buf;
        utf8 = "";
        return utf8;
    }
    utf8 = buf;
    delete []buf;
    return utf8;
#else
    int len;
    QByteArray result;
    //ANSI转UNICODE
    len = MultiByteToWideChar(CP_ACP, NULL, ansi.data(), -1, NULL, 0);
    WCHAR * unicode = new WCHAR[len+1];
    memset(unicode, 0, len * 2 + 2);
    MultiByteToWideChar(CP_ACP, NULL, ansi.data(), -1, unicode, len);
    //UNICODE转utf8
    len = WideCharToMultiByte(CP_UTF8, 0, unicode, -1, NULL, 0, NULL, NULL);
    char *utf8=new char[len + 1];
    memset(utf8, 0, len + 1);
    WideCharToMultiByte (CP_UTF8, 0, unicode, -1, utf8, len, NULL,NULL);
    //赋值
    result = utf8;
    delete[] unicode;
    delete[] utf8;
    return result;
#endif
}

#endif
