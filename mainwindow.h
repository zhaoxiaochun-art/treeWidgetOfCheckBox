#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidgetItem>
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
    Ui::MainWindow *ui;
public: //申明初始化函数
    void init();
    void updateParentItem(QTreeWidgetItem* item);

public slots:   //申明信号与槽,当树形控件的子选项被改变时执行
    void onTreeItemChanged(QTreeWidgetItem* item);

};

#endif // MAINWINDOW_H
