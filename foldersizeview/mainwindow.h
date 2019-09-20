#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class DirParser;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void showFolder(const QString & dirPath);

    void refreshFolder();

private slots:
    void on_actionOpen_triggered();

    void on_actionAbout_triggered();
    void on_actionReload_triggered();

    void slotDropFolderEvent(QString dirPath);

    void on_actionFollow_Wechat_triggered();

    void on_actionExport_triggered();

    void on_actionBuy_me_a_coffee_triggered();

    void on_actionBuy_my_products_triggered();

    void on_actionStar_my_projects_triggered();

    void on_actionFeedback_triggered();

    void on_actionReleases_triggered();

    void on_actionContact_Me_triggered();

    void on_actionFollow_Weibo_triggered();

    void on_actionGroup_by_file_extension_triggered(bool checked);

    void on_actionSunburst_Mode_triggered(bool checked);

private:
    Ui::MainWindow *ui;
    QString mCurrentFolderPath;
};

#endif // MAINWINDOW_H
