#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "AboutDialog.h"
#include "ConvertFormat.h"

#include <QFileDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //连接信号-槽
    initMainWindow( );

    m_convertFormat = new ConvertFormat;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initMainWindow()
{
    //设置主界面标题
    setWindowTitle(QString("[小工具]转换为UTF8"));
    //连接信号-槽
    connect( ui->actionAbout,SIGNAL(triggered(bool)),this,SLOT(sl_clickedAbout() ) );
    connect( ui->actionAdd,SIGNAL(triggered(bool)),this,SLOT(sl_addFile() ) );
    connect( ui->actionClear,SIGNAL(triggered(bool)),this,SLOT(sl_deleAllFiles( ) ) );
    connect( ui->action_UTF_8,SIGNAL(triggered(bool)),this,SLOT(sl_conver2UTF8() ) );

}

MainWindow::ShowAddedFiles(ConvertFormat *converformat)
{
    QList<FileInfo> fileList = converformat->GetFiles();
    ui->tableWidget->setRowCount( fileList.count( ) );
    for(int row = 0; row < fileList.count( ) ; ++row )
    {
        FileInfo fileIn = fileList.at(row);
        for( int col = 0; col < 5; ++col )
        {
            QTableWidgetItem * item = ui->tableWidget->item(row,col);
            if( item == NULL )
            {
                item = new QTableWidgetItem();
                ui->tableWidget->setItem(row,col,item);
            }
            QString itemText;
            if( col == 0 )
            {
                //文件名
                itemText = fileIn.fileName;
            }
            else if( col == 1 )
            {
                //路径
                itemText = fileIn.filePath;
            }
            else if ( col == 2 )
            {
                //转换前格式
                itemText = fileIn.beginFormat;
            }
            else if( col == 3 )
            {
                //转换后格式
                itemText = fileIn.endFormat;
            }
            else if( col == 4 )
            {
                //进度
                itemText = (fileIn.sucessBool ? QString("转换完成") : QString("未转换") );
            }

            item->setText(itemText);
        }
    }
}

MainWindow::ShowConverResult(ConvertFormat *converformat)
{
    QList<FileInfo> fileList = converformat->GetFiles();
    ui->tableWidget->setRowCount( fileList.count( ) );
    for(int row = 0; row < fileList.count( ) ; ++row )
    {
        FileInfo fileIn = fileList.at(row);
        for( int col = 0; col < 5; ++col )
        {
            QTableWidgetItem * item = ui->tableWidget->item(row,col);
            if( item == NULL )
            {
                item = new QTableWidgetItem();
                ui->tableWidget->setItem(row,col,item);
            }
            QString itemText;
            if( col == 0 )
            {
                //文件名
                itemText = fileIn.fileName;
            }
            else if( col == 1 )
            {
                //路径
                itemText = fileIn.filePath;
            }
            else if ( col == 2 )
            {
                //转换前格式
                itemText = fileIn.beginFormat;
            }
            else if( col == 3 )
            {
                //转换后格式
                itemText = fileIn.endFormat;
            }
            else if( col == 4 )
            {
                itemText = (fileIn.sucessBool ? QString("转换完成") : QString("失败") );
            }

            item->setText(itemText);
        }
    }
}

void MainWindow::sl_clickedAbout()
{
    AboutDialog aboueDlg;
    aboueDlg.exec();
}

void MainWindow::sl_addFile()
{
    QFileDialog fileDlg(this,QString("添加文件"));
    QStringList fileList = fileDlg.getOpenFileNames(this,QString("添加文件"));
    m_convertFormat->AddFiles( fileList );
    ShowAddedFiles( m_convertFormat );
}

void MainWindow::sl_deleAllFiles()
{
    m_convertFormat->ClearFiles();
    ShowAddedFiles( m_convertFormat );
}

void MainWindow::sl_conver2UTF8()
{
    m_convertFormat->Convert();
    ShowConverResult(m_convertFormat);
}
