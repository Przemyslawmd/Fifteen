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
#include <Images/ImageProvider.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Radio { FOUR, FIVE, SIX, SEVEN, NUMERICAL, GRAPHIC };

    QMenuBar* mainMenu;
    QMenu* fileMenu;
    QAction* infoMenu;

    // FILE MENU ACTIONS
    QAction* acOpenGraphic;
    QAction* acRemoveGraphic;
    QAction* acSaveBoard;
    QAction* acLoadBoard;

    QAction* acSettings;
    QAction* acHelp;

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
    // Separate layouts for radio buttons seems to be needed because of a group box
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

    // Current size of board
    Size size;
    QString* numberStyleBlue;
    QString* numberStyleRed;
    QString* numberStyleGreen;
    QString* numberStyle;
    QString* emptyStyle;    

    bool isNumber;          // It indicates whether there is a numerical or graphical board
    bool isScaled;          // It indicates whether a loading image is to be scalled or cropped

    Color color;
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

public slots:
    void passSignal();
};

#endif // MAINWINDOW_H
