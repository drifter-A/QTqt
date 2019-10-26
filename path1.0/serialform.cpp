#include "serialform.h"
#include "ui_serialform.h"
#include "beziver.h"


QT_CHARTS_USE_NAMESPACE



serialform::serialform(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::serialform)
{
    ui->setupUi(this);
    //this->hide();
    QLineSeries *series = new QLineSeries(this);
//        series->append(0, 5);
//        series->append(4, 10);
//        series->append(8, 6);
        //*series << QPointF(13, 5) << QPointF(17, 6) << QPointF(20, 2);

        for(int i = 0;i<=NUM_POINTS-2;i++)
        {
            series->append(i,chassis_speed[i] );
        }
        // 构建图表
        QChart *chart = new QChart();
        chart->legend()->hide();  // 隐藏图例
        chart->addSeries(series);  // 将 series 添加至图表中
        chart->createDefaultAxes();  // 基于已添加到图表的 series 来创轴
        chart->setTitle("速度曲线");  // 设置图表的标题

        // 构建 QChartView，并设置抗锯齿、标题、大小
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);
        chartView->setWindowTitle("速度曲线");
        chartView->resize(400, 300);
        QVBoxLayout *layout = ui->verticalLayout;
        layout->addWidget(chartView);
        //chartView->show();
}

serialform::~serialform()
{
    delete ui;
}



