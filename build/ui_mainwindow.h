/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QFrame *frame;
    QVBoxLayout *verticalLayout;
    QGridLayout *gridLayout;
    QPushButton *grabButton;
    QPushButton *manualButton;
    QCheckBox *checkBox;
    QLabel *moneyLabel;
    QLineEdit *lineEdit;
    QLabel *label;
    QHBoxLayout *horizontalLayout_2;
    QProgressBar *progressBar;
    QPushButton *pushButton;
    QGraphicsView *graphicsView_2;
    QGraphicsView *graphicsView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(823, 713);
        MainWindow->setMinimumSize(QSize(0, 0));
        MainWindow->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QStringLiteral(":/trainIcons/Nuova cartella/crossing.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setMaximumSize(QSize(200, 16777215));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Sunken);
        frame->setLineWidth(1);
        frame->setMidLineWidth(5);
        verticalLayout = new QVBoxLayout(frame);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        grabButton = new QPushButton(frame);
        grabButton->setObjectName(QStringLiteral("grabButton"));
        grabButton->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(grabButton->sizePolicy().hasHeightForWidth());
        grabButton->setSizePolicy(sizePolicy);
        grabButton->setMinimumSize(QSize(0, 20));
        grabButton->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(grabButton, 0, 0, 1, 1);

        manualButton = new QPushButton(frame);
        manualButton->setObjectName(QStringLiteral("manualButton"));
        manualButton->setMinimumSize(QSize(0, 20));
        manualButton->setMaximumSize(QSize(80, 16777215));

        gridLayout->addWidget(manualButton, 0, 1, 1, 1);

        checkBox = new QCheckBox(frame);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setEnabled(true);
        checkBox->setChecked(true);

        gridLayout->addWidget(checkBox, 1, 0, 1, 1);

        moneyLabel = new QLabel(frame);
        moneyLabel->setObjectName(QStringLiteral("moneyLabel"));
        moneyLabel->setEnabled(true);
        moneyLabel->setMaximumSize(QSize(200, 20));
        QFont font;
        font.setFamily(QStringLiteral("DejaVu Sans"));
        font.setBold(true);
        font.setItalic(true);
        font.setWeight(75);
        moneyLabel->setFont(font);

        gridLayout->addWidget(moneyLabel, 2, 1, 1, 1);

        lineEdit = new QLineEdit(frame);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit->sizePolicy().hasHeightForWidth());
        lineEdit->setSizePolicy(sizePolicy1);
        lineEdit->setMaximumSize(QSize(72, 16777215));
        lineEdit->setToolTipDuration(5);

        gridLayout->addWidget(lineEdit, 1, 1, 1, 1);

        label = new QLabel(frame);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 1);


        verticalLayout->addLayout(gridLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        progressBar = new QProgressBar(frame);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setMaximum(100);
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        horizontalLayout_2->addWidget(progressBar);

        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setMinimumSize(QSize(25, 0));
        pushButton->setMaximumSize(QSize(25, 16777215));

        horizontalLayout_2->addWidget(pushButton);


        verticalLayout->addLayout(horizontalLayout_2);

        graphicsView_2 = new QGraphicsView(frame);
        graphicsView_2->setObjectName(QStringLiteral("graphicsView_2"));
        graphicsView_2->setEnabled(true);
        graphicsView_2->setMaximumSize(QSize(16777215, 16777215));
        graphicsView_2->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        graphicsView_2->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        verticalLayout->addWidget(graphicsView_2);


        horizontalLayout->addWidget(frame);

        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy2);
        QPalette palette;
        QBrush brush(QColor(241, 120, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::HighlightedText, brush);
        QBrush brush1(QColor(170, 85, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::LinkVisited, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::HighlightedText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::LinkVisited, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::HighlightedText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::LinkVisited, brush1);
        graphicsView->setPalette(palette);
        graphicsView->setFocusPolicy(Qt::StrongFocus);
        graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        graphicsView->setInteractive(true);
        graphicsView->setRenderHints(QPainter::Antialiasing|QPainter::HighQualityAntialiasing|QPainter::SmoothPixmapTransform|QPainter::TextAntialiasing);

        horizontalLayout->addWidget(graphicsView);

        MainWindow->setCentralWidget(centralWidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Hungarian Plains", nullptr));
        grabButton->setText(QApplication::translate("MainWindow", "Grab Keys", nullptr));
        manualButton->setText(QApplication::translate("MainWindow", "Start", nullptr));
        checkBox->setText(QApplication::translate("MainWindow", "Self Stop", nullptr));
        moneyLabel->setText(QApplication::translate("MainWindow", "\342\202\254", nullptr));
#ifndef QT_NO_TOOLTIP
        lineEdit->setToolTip(QApplication::translate("MainWindow", "Seed", nullptr));
#endif // QT_NO_TOOLTIP
        label->setText(QApplication::translate("MainWindow", "Time:", nullptr));
        progressBar->setFormat(QString());
#ifndef QT_NO_TOOLTIP
        pushButton->setToolTip(QApplication::translate("MainWindow", "Restart Turn", nullptr));
#endif // QT_NO_TOOLTIP
        pushButton->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
