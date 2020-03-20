#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    init();

    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(onTreeItemChanged(QTreeWidgetItem*)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    ui->treeWidget->clear();    //初始化树形控件
    ui->treeWidget->setHeaderHidden(true);  //隐藏表头


    //定义第一个树形组 爷爷项
    QTreeWidgetItem* group1 = new QTreeWidgetItem(ui->treeWidget);
    group1->setText(0, QStringLiteral("设备使用权限"));    //树形控件显示的文本信息
    //group1->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);   //设置树形控件子项的属性
    //Qt::ItemIsUserCheckable | Qt::ItemIsSelectable 两个都是方框是否可选状态，暂时没用
    //Qt::ItemIsEnabled 使能，不使能会显示为灰色，可以在查看的时候而非添加的时候用
    //Qt::ItemIsEditable 文字可编辑与否，我们都不让编辑
    group1->setFlags( Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);   //设置树形控件子项的属性
    group1->setCheckState(0, Qt::Unchecked); //初始状态没有被选中
    //第一组子项
    QTreeWidgetItem* subItem11 = new QTreeWidgetItem(group1);
    subItem11->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    subItem11->setText(0, "二级");  //设置子项显示的文本
    subItem11->setCheckState(0, Qt::Unchecked); //设置子选项的显示格式和状态

    QTreeWidgetItem* subItem12 = new QTreeWidgetItem(group1);
    subItem12->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    subItem12->setText(0, "二级");
    subItem12->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem13 = new QTreeWidgetItem(group1);
    subItem13->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    subItem13->setText(0, "二级");
    subItem13->setCheckState(0, Qt::Unchecked);


    //父亲项
    QTreeWidgetItem* group2 = new QTreeWidgetItem(subItem13);
    group2->setText(0, "三级");
    group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group2->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group3 = new QTreeWidgetItem(subItem13);
    group3->setText(0, "三级");
    group3->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group3->setCheckState(0, Qt::Unchecked);

    //孙子项
    QTreeWidgetItem* subItem21 = new QTreeWidgetItem(group2);   //指定子项属于哪一个父项
    subItem21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    subItem21->setText(0, "四级");
    subItem21->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem22 = new QTreeWidgetItem(group2);
    subItem22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    subItem22->setText(0, "四级");
    subItem22->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* subItem23 = new QTreeWidgetItem(group2);
    subItem23->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    subItem23->setText(0, "四级");
    subItem23->setCheckState(0, Qt::Unchecked);

    ui->treeWidget->expandAll();  //展开树

}

void MainWindow::updateParentItem(QTreeWidgetItem* item)
{

    QTreeWidgetItem *parent = item->parent();

    if (parent == NULL)
        return;

    int nSelectedCount = 0;//选中数
    int nHalfSelectedCount = 0;//半选中数
    int childCount = parent->childCount();//孩子数

    for (int i = 0; i < childCount; i++) //判断有多少个子项被选中
    {
        QTreeWidgetItem* childItem = parent->child(i);
        if (childItem->checkState(0) == Qt::Checked)
        {
            nSelectedCount++;
        }
        else if (childItem->checkState(0) == Qt::PartiallyChecked)
        {
            nHalfSelectedCount++;
        }
    }

    if ((nSelectedCount+nHalfSelectedCount) <= 0)  //如果没有子项被选中，父项设置为未选中状态
        parent->setCheckState(0, Qt::Unchecked);
    else if ((childCount>nHalfSelectedCount && nHalfSelectedCount > 0)||(childCount>nSelectedCount && nSelectedCount>0))// && nSelectedCount < childCount)    //如果有部分子项被选中，父项设置为部分选中状态，即用灰色显示
        parent->setCheckState(0, Qt::PartiallyChecked);
    else if (nSelectedCount == childCount)    //如果子项全部被选中，父项则设置为选中状态
        parent->setCheckState(0, Qt::Checked);

    updateParentItem(parent);//

}

void MainWindow::onTreeItemChanged(QTreeWidgetItem* item)//利用changed自动递归。
{
    int count = item->childCount(); //返回子项的个数

    if (Qt::Checked == item->checkState(0))
    {
        item->setCheckState(0, Qt::Checked);
        if (count > 0)
        {
            for (int i = 0; i < count; i++)
            {
                item->child(i)->setCheckState(0, Qt::Checked);
            }
        }
        else{ updateParentItem(item);}
    }
    else if (Qt::Unchecked == item->checkState(0))
    {
        if (count > 0)
        {
            for (int i = 0; i < count; i++)
            {
                item->child(i)->setCheckState(0, Qt::Unchecked);
            }
        }
        else{updateParentItem(item);}
    }

}
