#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QButtonGroup>
#include <QRadioButton>
#include <QGroupBox>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include <Board.h>
#include <WindowSetting.h>
#include <WindowAbout.h>
#include <Images/ImageLoad.h>
#include <Types.h>
#include <Options.h>
#include <Images/ImageProvider.h>

#define ACTION_COUNT 6

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Radio { FOUR, FIVE, SIX, SEVEN, NUMERICAL, GRAPHIC };
    enum Action { OPENG, REMG, SAVE, LOAD, SETT, INFO };

    QMenuBar* mainMenu;
    QMenu* fileMenu;

    QAction* action[ACTION_COUNT];

    QWidget* window;
    QHBoxLayout* mainLayout;
    QVBoxLayout* rightLayout;


    // IMAGE PANEL
    QGridLayout* imageLayout;
    QVBoxLayout* layImageVertical;
    QHBoxLayout** layImageHorizontal;
    QGroupBox* boxImages;
    QPushButton** control;

    // RIGHT PANEL
    // Separate layouts for radio buttons seem to be needed because of a group box
    QVBoxLayout* layRadioDim;
    QVBoxLayout* layRadioKind;
    QPushButton* pushRandom;
    QPushButton* pushSolve;

    QRadioButton radio[6];

    QButtonGroup* groupRadioKind;
    QButtonGroup* groupRadioDimension;
    QGroupBox* boxRadioKind;
    QGroupBox* boxRadioDimension;

    Board* board;
    ImageProvider* imageProvider;

    QString* numberStyleBlue;
    QString* numberStyleRed;
    QString* numberStyleGreen;
    QString* numberStyle;
    QString* emptyStyle;    

    bool isNumber;          // It indicates whether there is a numeric or a graphic board

    ImageLoad* imagesLoad;

    void createMenu();
    void createControls();
    void createSquares();

    void setSquaresNumber( bool );
    void setSquaresGraphic( bool );

    void createLayouts();
    void deleteSquares();

private slots:

    // MENU SLOTS
    void slotLoadGraphic();
    void slotRemoveGraphic();
    void slotSaveBoard();
    void slotReadBoard();
    void slotSettings();
    void slotAbout();

    // PUSH SLOTS
    void slotGenerateBoard();
    void slotSolveBoard();

public:
    explicit MainWindow( QWidget *parent = 0 );
    void setColor();
    void redrawSquares();

public slots:
    void passSignal();
};

#endif // MAINWINDOW_H
