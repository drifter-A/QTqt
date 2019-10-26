/********************************************************************************
** Form generated from reading UI file 'serialform.ui'
**
** Created by: Qt User Interface Compiler version 5.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SERIALFORM_H
#define UI_SERIALFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_serialform
{
public:
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;

    void setupUi(QWidget *serialform)
    {
        if (serialform->objectName().isEmpty())
            serialform->setObjectName(QStringLiteral("serialform"));
        serialform->resize(1201, 758);
        verticalLayoutWidget = new QWidget(serialform);
        verticalLayoutWidget->setObjectName(QStringLiteral("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 1201, 751));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(serialform);

        QMetaObject::connectSlotsByName(serialform);
    } // setupUi

    void retranslateUi(QWidget *serialform)
    {
        serialform->setWindowTitle(QApplication::translate("serialform", "Form", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class serialform: public Ui_serialform {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SERIALFORM_H
