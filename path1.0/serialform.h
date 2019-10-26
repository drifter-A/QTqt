#ifndef SERIALFORM_H
#define SERIALFORM_H

#include <QWidget>
#include <QtCharts/qchartview.h>
#include <QtCharts/qchart.h>
#include <QSplineSeries>
#include <QHBoxLayout>
#include <QValueAxis>



namespace Ui {
class serialform;
}

class serialform : public QWidget
{
    Q_OBJECT

public:
    explicit serialform(QWidget *parent = 0);
    ~serialform();

private:
    Ui::serialform *ui;

};

#endif // SERIALFORM_H
