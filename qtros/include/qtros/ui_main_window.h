/********************************************************************************
** Form generated from reading UI file 'main_window.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAIN_WINDOW_H
#define UI_MAIN_WINDOW_H

#include <QtCore/QLocale>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindowDesign
{
public:
    QAction *action_Quit;
    QAction *action_Preferences;
    QAction *actionAbout;
    QAction *actionAbout_Qt;
    QWidget *centralwidget;
    QGridLayout *gridLayout_2;
    QTabWidget *tab_manager;
    QWidget *tab_status;
    QVBoxLayout *verticalLayout_2;
    QFrame *frame;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QLineEdit *line_edit_host;
    QLineEdit *line_edit_topic;
    QCheckBox *checkbox_use_environment;
    QLabel *label;
    QLabel *label_3;
    QLabel *label_2;
    QLabel *label_4;
    QPushButton *button_connect;
    QCheckBox *checkbox_remember_settings;
    QLineEdit *line_edit_master;
    QPushButton *quit_button;
    QWidget *tab2;
    QLabel *view_logging;
    QPushButton *startvideo;
    QPushButton *suspendvideo;
    QPushButton *snapshot;
    QPushButton *pushButton_lin_up;
    QPushButton *pushButton_lin_left;
    QPushButton *pushButton_lin_right;
    QPushButton *pushButton_lin_down;
    QPushButton *pushButton_ori_up;
    QPushButton *pushButton_ori_down;
    QPushButton *pushButton_ori_left;
    QPushButton *pushButton_ori_right;
    QLabel *label_7;
    QLabel *label_8;
    QProgressBar *battery_tab2;
    QWidget *tab_4;
    QPushButton *pushButton_go;
    QPushButton *pushButton_charge;
    QListWidget *listmarkers_tab4_wpt;
    QProgressBar *battery_tab4;
    QListWidget *listmarkers_tab4_poi;
    QPushButton *pushButton_look;
    QPushButton *pushButton_refresh;
    QLabel *label_9;
    QLabel *label_10;
    QWidget *tab_3;
    QPushButton *pushButton_load;
    QLabel *label_5;
    QLabel *label_6;
    QFrame *line;
    QPushButton *pushButton_create_POI;
    QPushButton *pushButton_delete_POI;
    QPushButton *pushButton_create_wpt;
    QPushButton *pushButton_delete_wpt;
    QPushButton *pushButton_save;
    QLineEdit *lineEdit_markers;
    QProgressBar *battery_tab3;
    QMenuBar *menubar;
    QMenu *menu_File;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindowDesign)
    {
        if (MainWindowDesign->objectName().isEmpty())
            MainWindowDesign->setObjectName(QStringLiteral("MainWindowDesign"));
        MainWindowDesign->resize(1228, 862);
        QIcon icon;
        icon.addFile(QStringLiteral(":/images/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindowDesign->setWindowIcon(icon);
        MainWindowDesign->setLocale(QLocale(QLocale::English, QLocale::Australia));
        action_Quit = new QAction(MainWindowDesign);
        action_Quit->setObjectName(QStringLiteral("action_Quit"));
        action_Quit->setShortcutContext(Qt::ApplicationShortcut);
        action_Preferences = new QAction(MainWindowDesign);
        action_Preferences->setObjectName(QStringLiteral("action_Preferences"));
        actionAbout = new QAction(MainWindowDesign);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionAbout_Qt = new QAction(MainWindowDesign);
        actionAbout_Qt->setObjectName(QStringLiteral("actionAbout_Qt"));
        centralwidget = new QWidget(MainWindowDesign);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout_2 = new QGridLayout(centralwidget);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        tab_manager = new QTabWidget(centralwidget);
        tab_manager->setObjectName(QStringLiteral("tab_manager"));
        tab_manager->setMinimumSize(QSize(100, 0));
        tab_manager->setLocale(QLocale(QLocale::English, QLocale::Australia));
        tab_status = new QWidget();
        tab_status->setObjectName(QStringLiteral("tab_status"));
        verticalLayout_2 = new QVBoxLayout(tab_status);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        frame = new QFrame(tab_status);
        frame->setObjectName(QStringLiteral("frame"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        verticalLayout_3 = new QVBoxLayout(frame);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        groupBox = new QGroupBox(frame);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        line_edit_host = new QLineEdit(groupBox);
        line_edit_host->setObjectName(QStringLiteral("line_edit_host"));
        line_edit_host->setMaximumSize(QSize(402, 16777215));

        gridLayout->addWidget(line_edit_host, 4, 0, 1, 1);

        line_edit_topic = new QLineEdit(groupBox);
        line_edit_topic->setObjectName(QStringLiteral("line_edit_topic"));
        line_edit_topic->setEnabled(false);
        line_edit_topic->setMaximumSize(QSize(402, 16777215));

        gridLayout->addWidget(line_edit_topic, 13, 3, 1, 1);

        checkbox_use_environment = new QCheckBox(groupBox);
        checkbox_use_environment->setObjectName(QStringLiteral("checkbox_use_environment"));
        checkbox_use_environment->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(checkbox_use_environment, 11, 3, 1, 1);

        label = new QLabel(groupBox);
        label->setObjectName(QStringLiteral("label"));
        label->setMaximumSize(QSize(400, 30));
        label->setFrameShape(QFrame::StyledPanel);
        label->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label, 1, 0, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setMaximumSize(QSize(400, 30));
        label_3->setFrameShape(QFrame::StyledPanel);
        label_3->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_3, 12, 3, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setMaximumSize(QSize(400, 30));
        label_2->setFrameShape(QFrame::StyledPanel);
        label_2->setFrameShadow(QFrame::Raised);

        gridLayout->addWidget(label_2, 3, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 2, 13, 1);

        button_connect = new QPushButton(groupBox);
        button_connect->setObjectName(QStringLiteral("button_connect"));
        button_connect->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(button_connect->sizePolicy().hasHeightForWidth());
        button_connect->setSizePolicy(sizePolicy1);
        button_connect->setMaximumSize(QSize(402, 50));

        gridLayout->addWidget(button_connect, 6, 0, 1, 1);

        checkbox_remember_settings = new QCheckBox(groupBox);
        checkbox_remember_settings->setObjectName(QStringLiteral("checkbox_remember_settings"));
        checkbox_remember_settings->setLayoutDirection(Qt::RightToLeft);

        gridLayout->addWidget(checkbox_remember_settings, 10, 3, 1, 1);

        line_edit_master = new QLineEdit(groupBox);
        line_edit_master->setObjectName(QStringLiteral("line_edit_master"));
        line_edit_master->setMaximumSize(QSize(402, 16777215));

        gridLayout->addWidget(line_edit_master, 2, 0, 1, 1);

        quit_button = new QPushButton(groupBox);
        quit_button->setObjectName(QStringLiteral("quit_button"));
        sizePolicy1.setHeightForWidth(quit_button->sizePolicy().hasHeightForWidth());
        quit_button->setSizePolicy(sizePolicy1);
        quit_button->setMaximumSize(QSize(402, 50));

        gridLayout->addWidget(quit_button, 8, 0, 1, 1);


        verticalLayout_3->addWidget(groupBox);


        verticalLayout_2->addWidget(frame);

        tab_manager->addTab(tab_status, QString());
        tab2 = new QWidget();
        tab2->setObjectName(QStringLiteral("tab2"));
        view_logging = new QLabel(tab2);
        view_logging->setObjectName(QStringLiteral("view_logging"));
        view_logging->setGeometry(QRect(10, 10, 800, 640));
        view_logging->setMaximumSize(QSize(800, 640));
        view_logging->setFrameShape(QFrame::Box);
        view_logging->setFrameShadow(QFrame::Plain);
        startvideo = new QPushButton(tab2);
        startvideo->setObjectName(QStringLiteral("startvideo"));
        startvideo->setGeometry(QRect(40, 660, 221, 61));
        suspendvideo = new QPushButton(tab2);
        suspendvideo->setObjectName(QStringLiteral("suspendvideo"));
        suspendvideo->setGeometry(QRect(300, 660, 221, 61));
        snapshot = new QPushButton(tab2);
        snapshot->setObjectName(QStringLiteral("snapshot"));
        snapshot->setGeometry(QRect(560, 660, 221, 61));
        pushButton_lin_up = new QPushButton(tab2);
        pushButton_lin_up->setObjectName(QStringLiteral("pushButton_lin_up"));
        pushButton_lin_up->setGeometry(QRect(940, 170, 89, 25));
        pushButton_lin_left = new QPushButton(tab2);
        pushButton_lin_left->setObjectName(QStringLiteral("pushButton_lin_left"));
        pushButton_lin_left->setGeometry(QRect(840, 210, 89, 25));
        pushButton_lin_right = new QPushButton(tab2);
        pushButton_lin_right->setObjectName(QStringLiteral("pushButton_lin_right"));
        pushButton_lin_right->setGeometry(QRect(1030, 210, 89, 25));
        pushButton_lin_down = new QPushButton(tab2);
        pushButton_lin_down->setObjectName(QStringLiteral("pushButton_lin_down"));
        pushButton_lin_down->setGeometry(QRect(940, 250, 89, 25));
        pushButton_ori_up = new QPushButton(tab2);
        pushButton_ori_up->setObjectName(QStringLiteral("pushButton_ori_up"));
        pushButton_ori_up->setGeometry(QRect(940, 340, 89, 25));
        pushButton_ori_down = new QPushButton(tab2);
        pushButton_ori_down->setObjectName(QStringLiteral("pushButton_ori_down"));
        pushButton_ori_down->setGeometry(QRect(940, 440, 89, 25));
        pushButton_ori_left = new QPushButton(tab2);
        pushButton_ori_left->setObjectName(QStringLiteral("pushButton_ori_left"));
        pushButton_ori_left->setGeometry(QRect(840, 390, 89, 25));
        pushButton_ori_right = new QPushButton(tab2);
        pushButton_ori_right->setObjectName(QStringLiteral("pushButton_ori_right"));
        pushButton_ori_right->setGeometry(QRect(1030, 390, 89, 25));
        label_7 = new QLabel(tab2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(950, 210, 67, 16));
        label_8 = new QLabel(tab2);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(940, 390, 81, 21));
        battery_tab2 = new QProgressBar(tab2);
        battery_tab2->setObjectName(QStringLiteral("battery_tab2"));
        battery_tab2->setGeometry(QRect(890, 0, 311, 23));
        battery_tab2->setValue(24);
        tab_manager->addTab(tab2, QString());
        tab_4 = new QWidget();
        tab_4->setObjectName(QStringLiteral("tab_4"));
        pushButton_go = new QPushButton(tab_4);
        pushButton_go->setObjectName(QStringLiteral("pushButton_go"));
        pushButton_go->setGeometry(QRect(220, 510, 171, 61));
        pushButton_charge = new QPushButton(tab_4);
        pushButton_charge->setObjectName(QStringLiteral("pushButton_charge"));
        pushButton_charge->setGeometry(QRect(970, 30, 171, 31));
        listmarkers_tab4_wpt = new QListWidget(tab_4);
        listmarkers_tab4_wpt->setObjectName(QStringLiteral("listmarkers_tab4_wpt"));
        listmarkers_tab4_wpt->setGeometry(QRect(90, 160, 481, 321));
        battery_tab4 = new QProgressBar(tab_4);
        battery_tab4->setObjectName(QStringLiteral("battery_tab4"));
        battery_tab4->setGeometry(QRect(890, 0, 311, 23));
        battery_tab4->setValue(24);
        listmarkers_tab4_poi = new QListWidget(tab_4);
        listmarkers_tab4_poi->setObjectName(QStringLiteral("listmarkers_tab4_poi"));
        listmarkers_tab4_poi->setGeometry(QRect(640, 160, 481, 321));
        pushButton_look = new QPushButton(tab_4);
        pushButton_look->setObjectName(QStringLiteral("pushButton_look"));
        pushButton_look->setGeometry(QRect(800, 510, 171, 61));
        pushButton_refresh = new QPushButton(tab_4);
        pushButton_refresh->setObjectName(QStringLiteral("pushButton_refresh"));
        pushButton_refresh->setGeometry(QRect(490, 510, 231, 61));
        label_9 = new QLabel(tab_4);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(260, 130, 201, 31));
        label_10 = new QLabel(tab_4);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(800, 140, 241, 20));
        tab_manager->addTab(tab_4, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QStringLiteral("tab_3"));
        pushButton_load = new QPushButton(tab_3);
        pushButton_load->setObjectName(QStringLiteral("pushButton_load"));
        pushButton_load->setGeometry(QRect(440, 140, 271, 25));
        label_5 = new QLabel(tab_3);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(420, 220, 161, 31));
        label_6 = new QLabel(tab_3);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(620, 220, 161, 31));
        line = new QFrame(tab_3);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(560, 230, 41, 191));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        pushButton_create_POI = new QPushButton(tab_3);
        pushButton_create_POI->setObjectName(QStringLiteral("pushButton_create_POI"));
        pushButton_create_POI->setGeometry(QRect(440, 270, 121, 51));
        pushButton_delete_POI = new QPushButton(tab_3);
        pushButton_delete_POI->setObjectName(QStringLiteral("pushButton_delete_POI"));
        pushButton_delete_POI->setGeometry(QRect(440, 360, 121, 51));
        pushButton_create_wpt = new QPushButton(tab_3);
        pushButton_create_wpt->setObjectName(QStringLiteral("pushButton_create_wpt"));
        pushButton_create_wpt->setGeometry(QRect(600, 270, 121, 51));
        pushButton_delete_wpt = new QPushButton(tab_3);
        pushButton_delete_wpt->setObjectName(QStringLiteral("pushButton_delete_wpt"));
        pushButton_delete_wpt->setGeometry(QRect(600, 360, 121, 51));
        pushButton_save = new QPushButton(tab_3);
        pushButton_save->setObjectName(QStringLiteral("pushButton_save"));
        pushButton_save->setGeometry(QRect(440, 460, 281, 31));
        lineEdit_markers = new QLineEdit(tab_3);
        lineEdit_markers->setObjectName(QStringLiteral("lineEdit_markers"));
        lineEdit_markers->setGeometry(QRect(440, 180, 271, 31));
        battery_tab3 = new QProgressBar(tab_3);
        battery_tab3->setObjectName(QStringLiteral("battery_tab3"));
        battery_tab3->setGeometry(QRect(890, 0, 311, 23));
        battery_tab3->setValue(24);
        tab_manager->addTab(tab_3, QString());

        gridLayout_2->addWidget(tab_manager, 0, 1, 1, 1);

        MainWindowDesign->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindowDesign);
        menubar->setObjectName(QStringLiteral("menubar"));
        menubar->setGeometry(QRect(0, 0, 1228, 22));
        menu_File = new QMenu(menubar);
        menu_File->setObjectName(QStringLiteral("menu_File"));
        MainWindowDesign->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindowDesign);
        statusbar->setObjectName(QStringLiteral("statusbar"));
        MainWindowDesign->setStatusBar(statusbar);
        toolBar = new QToolBar(MainWindowDesign);
        toolBar->setObjectName(QStringLiteral("toolBar"));
        MainWindowDesign->addToolBar(Qt::TopToolBarArea, toolBar);

        menubar->addAction(menu_File->menuAction());
        menu_File->addAction(action_Preferences);
        menu_File->addSeparator();
        menu_File->addAction(actionAbout);
        menu_File->addAction(actionAbout_Qt);
        menu_File->addSeparator();
        menu_File->addAction(action_Quit);

        retranslateUi(MainWindowDesign);
        QObject::connect(action_Quit, SIGNAL(triggered()), MainWindowDesign, SLOT(close()));
        QObject::connect(quit_button, SIGNAL(clicked()), MainWindowDesign, SLOT(close()));

        tab_manager->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindowDesign);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowDesign)
    {
        MainWindowDesign->setWindowTitle(QApplication::translate("MainWindowDesign", "QRosApp", Q_NULLPTR));
        action_Quit->setText(QApplication::translate("MainWindowDesign", "&Quit", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        action_Quit->setShortcut(QApplication::translate("MainWindowDesign", "Ctrl+Q", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        action_Preferences->setText(QApplication::translate("MainWindowDesign", "&Preferences", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindowDesign", "&About", Q_NULLPTR));
        actionAbout_Qt->setText(QApplication::translate("MainWindowDesign", "About &Qt", Q_NULLPTR));
        groupBox->setTitle(QString());
        line_edit_host->setText(QApplication::translate("MainWindowDesign", "192.168.1.67", Q_NULLPTR));
        line_edit_topic->setText(QApplication::translate("MainWindowDesign", "unused", Q_NULLPTR));
        checkbox_use_environment->setText(QApplication::translate("MainWindowDesign", "Use environment variables", Q_NULLPTR));
        label->setText(QApplication::translate("MainWindowDesign", "Ros Master Url", Q_NULLPTR));
        label_3->setText(QApplication::translate("MainWindowDesign", "Ros Hostname", Q_NULLPTR));
        label_2->setText(QApplication::translate("MainWindowDesign", "Ros IP", Q_NULLPTR));
        label_4->setText(QString());
#ifndef QT_NO_TOOLTIP
        button_connect->setToolTip(QApplication::translate("MainWindowDesign", "Set the target to the current joint trajectory state.", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
#ifndef QT_NO_STATUSTIP
        button_connect->setStatusTip(QApplication::translate("MainWindowDesign", "Clear all waypoints and set the target to the current joint trajectory state.", Q_NULLPTR));
#endif // QT_NO_STATUSTIP
        button_connect->setText(QApplication::translate("MainWindowDesign", "Connect", Q_NULLPTR));
        checkbox_remember_settings->setText(QApplication::translate("MainWindowDesign", "Remember settings on startup", Q_NULLPTR));
        line_edit_master->setText(QApplication::translate("MainWindowDesign", "http://192.168.1.2:11311/", Q_NULLPTR));
        quit_button->setText(QApplication::translate("MainWindowDesign", "Quit", Q_NULLPTR));
        tab_manager->setTabText(tab_manager->indexOf(tab_status), QApplication::translate("MainWindowDesign", "Ros Communications", Q_NULLPTR));
        view_logging->setText(QApplication::translate("MainWindowDesign", "cam1", Q_NULLPTR));
        startvideo->setText(QApplication::translate("MainWindowDesign", "Start", Q_NULLPTR));
        suspendvideo->setText(QApplication::translate("MainWindowDesign", "Stop", Q_NULLPTR));
        snapshot->setText(QApplication::translate("MainWindowDesign", "Snapshot", Q_NULLPTR));
        pushButton_lin_up->setText(QApplication::translate("MainWindowDesign", "UP", Q_NULLPTR));
        pushButton_lin_left->setText(QApplication::translate("MainWindowDesign", "LEFT", Q_NULLPTR));
        pushButton_lin_right->setText(QApplication::translate("MainWindowDesign", "RIGHT", Q_NULLPTR));
        pushButton_lin_down->setText(QApplication::translate("MainWindowDesign", "DOWN", Q_NULLPTR));
        pushButton_ori_up->setText(QApplication::translate("MainWindowDesign", "UP", Q_NULLPTR));
        pushButton_ori_down->setText(QApplication::translate("MainWindowDesign", "DOWN", Q_NULLPTR));
        pushButton_ori_left->setText(QApplication::translate("MainWindowDesign", "LEFT", Q_NULLPTR));
        pushButton_ori_right->setText(QApplication::translate("MainWindowDesign", "RIGHT", Q_NULLPTR));
        label_7->setText(QApplication::translate("MainWindowDesign", "Linear", Q_NULLPTR));
        label_8->setText(QApplication::translate("MainWindowDesign", "orientation", Q_NULLPTR));
        tab_manager->setTabText(tab_manager->indexOf(tab2), QApplication::translate("MainWindowDesign", "Camera ", Q_NULLPTR));
        pushButton_go->setText(QApplication::translate("MainWindowDesign", "GO", Q_NULLPTR));
        pushButton_charge->setText(QApplication::translate("MainWindowDesign", "GO CHARGING", Q_NULLPTR));
        pushButton_look->setText(QApplication::translate("MainWindowDesign", "LOOK", Q_NULLPTR));
        pushButton_refresh->setText(QApplication::translate("MainWindowDesign", "REFRESH ALL MARKERS", Q_NULLPTR));
        label_9->setText(QApplication::translate("MainWindowDesign", "WAYPOINTS", Q_NULLPTR));
        label_10->setText(QApplication::translate("MainWindowDesign", "POINTS OF INTEREST", Q_NULLPTR));
        tab_manager->setTabText(tab_manager->indexOf(tab_4), QApplication::translate("MainWindowDesign", "Move Husky", Q_NULLPTR));
        pushButton_load->setText(QApplication::translate("MainWindowDesign", "LOAD MARKERS", Q_NULLPTR));
        label_5->setText(QApplication::translate("MainWindowDesign", "POINTS OF INTEREST", Q_NULLPTR));
        label_6->setText(QApplication::translate("MainWindowDesign", "WAYPOINTS", Q_NULLPTR));
        pushButton_create_POI->setText(QApplication::translate("MainWindowDesign", "CREATE", Q_NULLPTR));
        pushButton_delete_POI->setText(QApplication::translate("MainWindowDesign", "DELETE", Q_NULLPTR));
        pushButton_create_wpt->setText(QApplication::translate("MainWindowDesign", "CREATE", Q_NULLPTR));
        pushButton_delete_wpt->setText(QApplication::translate("MainWindowDesign", "DELETE", Q_NULLPTR));
        pushButton_save->setText(QApplication::translate("MainWindowDesign", "SAVE MARKERS", Q_NULLPTR));
        tab_manager->setTabText(tab_manager->indexOf(tab_3), QApplication::translate("MainWindowDesign", "Place Waypoints", Q_NULLPTR));
        menu_File->setTitle(QApplication::translate("MainWindowDesign", "&App", Q_NULLPTR));
        toolBar->setWindowTitle(QApplication::translate("MainWindowDesign", "toolBar", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindowDesign: public Ui_MainWindowDesign {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAIN_WINDOW_H
