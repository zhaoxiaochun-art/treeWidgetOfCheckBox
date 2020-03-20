#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(onTreeItemChanged(QTreeWidgetItem*)));
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::init()
{
    ui->treeWidget->clear();    //初始化树形控件
    ui->treeWidget->setHeaderHidden(true);  //隐藏表头
     QFont serifFont("Times", 14);
    ui->treeWidget->setFont(serifFont);

    //定义第一个树形组 爷爷项
    QTreeWidgetItem* group = new QTreeWidgetItem(ui->treeWidget);
    group->setText(0, "设备使用权限");    //树形控件显示的文本信息
    //group->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);   //设置树形控件子项的属性
    //Qt::ItemIsUserCheckable | Qt::ItemIsSelectable 两个都是方框是否可选状态，暂时没用
    //Qt::ItemIsEnabled 使能，不使能会显示为灰色，可以在查看的时候而非添加的时候用
    //Qt::ItemIsEditable 文字可编辑与否，我们都不让编辑
    group->setFlags( Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);   //设置树形控件子项的属性
    group->setCheckState(0, Qt::Unchecked); //初始状态没有被选中
    //第一组子项
    QTreeWidgetItem* group1 = new QTreeWidgetItem(group);
    group1->setFlags(Qt::ItemIsUserCheckable|Qt::ItemIsEnabled|Qt::ItemIsSelectable);
    group1->setText(0, "设备运行");  //设置子项显示的文本
    group1->setCheckState(0, Qt::Checked); //设置子选项的显示格式和状态

    QTreeWidgetItem* group2 = new QTreeWidgetItem(group);
    group2->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group2->setText(0, "设置");
    group2->setCheckState(0, Qt::Unchecked);

    //父亲项
    QTreeWidgetItem* group21 = new QTreeWidgetItem(group2);
    group21->setText(0, "模板管理");
    group21->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group21->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group22 = new QTreeWidgetItem(group2);
    group22->setText(0, "相机参数");
    group22->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group22->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group23 = new QTreeWidgetItem(group2);
    group23->setText(0, "PLC设置");
    group23->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group23->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group24 = new QTreeWidgetItem(group2);
    group24->setText(0, "用户管理");
    group24->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group24->setCheckState(0, Qt::Unchecked);

//孙子项1
    QTreeWidgetItem* group211 = new QTreeWidgetItem(group21);   //指定子项属于哪一个父项
    group211->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group211->setText(0, "保存/应用");
    group211->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group212 = new QTreeWidgetItem(group21);
    group212->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group212->setText(0, "添加");
    group212->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group213 = new QTreeWidgetItem(group21);
    group213->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group213->setText(0, "删除");
    group213->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group214 = new QTreeWidgetItem(group21);
    group214->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group214->setText(0, "修改名称");
    group214->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group215 = new QTreeWidgetItem(group21);
    group215->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group215->setText(0, "算法设置");
    group215->setCheckState(0, Qt::Unchecked);
//孙子项2
    QTreeWidgetItem* group221 = new QTreeWidgetItem(group22);
    group221->setText(0, "相机调试");
    group221->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group221->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group222 = new QTreeWidgetItem(group22);
    group222->setText(0, "采集测试");
    group222->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group222->setCheckState(0, Qt::Unchecked);

//孙子项3
    QTreeWidgetItem* group231 = new QTreeWidgetItem(group23);
    group231->setText(0, "参数读取");
    group231->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group231->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group232 = new QTreeWidgetItem(group23);
    group232->setText(0, "参数写入");
    group232->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group232->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group233 = new QTreeWidgetItem(group23);
    group233->setText(0, "采集");
    group233->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group233->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group234 = new QTreeWidgetItem(group23);
    group234->setText(0, "控制测试");
    group234->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable );
    group234->setCheckState(0, Qt::Unchecked);

    //孙子项4
    QTreeWidgetItem* group241 = new QTreeWidgetItem(group24);
    group241->setText(0, "添加");
    group241->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group241->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group242 = new QTreeWidgetItem(group24);
    group242->setText(0, "切换用户");
    group242->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group242->setCheckState(0, Qt::Unchecked);

    QTreeWidgetItem* group243 = new QTreeWidgetItem(group24);
    group243->setText(0, "删除");
    group243->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
    group243->setCheckState(0, Qt::Unchecked);



    //ui->treeWidget->expandAll();  //展开树
    ui->treeWidget->expandToDepth(1);
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
