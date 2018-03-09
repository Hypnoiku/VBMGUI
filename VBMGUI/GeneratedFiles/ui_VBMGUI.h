/********************************************************************************
** Form generated from reading UI file 'VBMGUI.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VBMGUI_H
#define UI_VBMGUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_VBMGUIClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QPushButton *pushButton;
    QProgressBar *progressBar;
    QPushButton *pushButton_2;
    QTabWidget *tabWidget;
    QWidget *tab;
    QListWidget *listWidget;
    QWidget *tab_2;
    QListWidget *listWidget_2;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *VBMGUIClass)
    {
        if (VBMGUIClass->objectName().isEmpty())
            VBMGUIClass->setObjectName(QStringLiteral("VBMGUIClass"));
        VBMGUIClass->resize(600, 400);
        centralWidget = new QWidget(VBMGUIClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 20, 581, 16));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(260, 50, 75, 23));
        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setGeometry(QRect(0, 320, 601, 23));
        progressBar->setValue(0);
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(260, 80, 81, 23));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 40, 261, 221));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        listWidget = new QListWidget(tab);
        listWidget->setObjectName(QStringLiteral("listWidget"));
        listWidget->setGeometry(QRect(0, 0, 256, 192));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        listWidget_2 = new QListWidget(tab_2);
        listWidget_2->setObjectName(QStringLiteral("listWidget_2"));
        listWidget_2->setGeometry(QRect(0, 0, 256, 192));
        tabWidget->addTab(tab_2, QString());
        VBMGUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(VBMGUIClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 600, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        VBMGUIClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(VBMGUIClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        VBMGUIClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(VBMGUIClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        VBMGUIClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuHelp->menuAction());

        retranslateUi(VBMGUIClass);
        QObject::connect(pushButton, SIGNAL(clicked()), VBMGUIClass, SLOT(startVM()));
        QObject::connect(pushButton_2, SIGNAL(pressed()), VBMGUIClass, SLOT(compactHDD()));

        tabWidget->setCurrentIndex(1);
        listWidget->setCurrentRow(-1);


        QMetaObject::connectSlotsByName(VBMGUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *VBMGUIClass)
    {
        VBMGUIClass->setWindowTitle(QApplication::translate("VBMGUIClass", "VBMGUI", nullptr));
        label->setText(QApplication::translate("VBMGUIClass", "TextLabel", nullptr));
        pushButton->setText(QApplication::translate("VBMGUIClass", "Start VM", nullptr));
        pushButton_2->setText(QApplication::translate("VBMGUIClass", "Compact HDD", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("VBMGUIClass", "VMs", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("VBMGUIClass", "HDDs", nullptr));
        menuFile->setTitle(QApplication::translate("VBMGUIClass", "File", nullptr));
        menuHelp->setTitle(QApplication::translate("VBMGUIClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class VBMGUIClass: public Ui_VBMGUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VBMGUI_H
