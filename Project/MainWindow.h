
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
#include <QFont>
#include <QFileDialog>
#include <QMessageBox>
#include <QBuffer>
#include <memory>
#include <Board.h>
#include <WindowSetting.h>
#include <WindowAbout.h>
#include <GraphicBoard//ImageLoad.h>
#include <Types.h>
#include <Options.h>
#include <GraphicBoard/ImageProvider.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum Radio { FOUR, FIVE, SIX, SEVEN, NUMERIC, GRAPHIC };
    enum Action { OPENGRAPHIC, REMGRAPHIC, SAVEBOARD, LOADBOARD, SETTINGS, ABOUT, COUNTACTIONS };

    QMenuBar* mainMenu;
    QMenu* fileMenu;

    QAction* action[COUNTACTIONS];

    // Main Panel of GUI, layout is being created starting
    // from this panel
    QWidget mainPanel;

    QHBoxLayout* mainLayout;
    QVBoxLayout* rightLayout;

    // Image panel
    QGridLayout* imageLayout;
    QVBoxLayout* layImageVertical;
    QHBoxLayout** layImageHorizontal;
    QGroupBox* boxImages;
    QPushButton** control;

    // Right panel
    QVBoxLayout layRadioSize;
    QVBoxLayout layRadioKind;
    QPushButton pushRandom;
    QPushButton pushSolve;

    QRadioButton radio[6];

    QButtonGroup groupRadioKind;
    QButtonGroup groupRadioSize;
    QGroupBox boxRadioKind;
    QGroupBox boxRadioSize;

    Board* board;

    QString styleEmpty { "background-color:white; color:white; font-size:20px; border:1px solid white;" };
    QString* currentStyle;

    ImagesState* images;

    void createMenu();
    void createControls();
    void createSquares();

    void setSquaresNumber( bool );
    void setSquaresGraphic( bool );

    void createLayouts();
    void deleteSquares();

private slots:

    // Menu slots
    void slotLoadGraphic();
    void slotRemoveGraphic();
    void slotSaveBoard();
    void slotReadBoard();
    void slotSettings();
    void slotAbout();

    // Push slots
    void slotGenerateBoard();
    void slotSolveBoard();

public:
    explicit MainWindow( QWidget *parent = 0 );
    void setColor();
    void redrawSquares();

public slots:
    void pressSquare();
};

#endif // MAINWINDOW_H
