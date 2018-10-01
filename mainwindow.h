#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAction>

namespace Ui {
class MainWindow;
}
class ConvertFormat;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    //初始化主界面
    void initMainWindow( );
    //展示加载的文件
    ShowAddedFiles( ConvertFormat * converformat);
    ShowConverResult( ConvertFormat * converformat );

private slots:
    //关于信息
    void sl_clickedAbout( );
    //添加文件
    void sl_addFile();
    //清空列表
    void sl_deleAllFiles( );
    //开始转换
    void sl_conver2UTF8();
private:
    Ui::MainWindow *ui;
    QAction * m_actOpenFile;
    ConvertFormat * m_convertFormat;
};

#endif // MAINWINDOW_H
