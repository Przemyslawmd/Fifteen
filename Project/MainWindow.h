
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Board.h"
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
#include "GraphicBoard/ImageProvider.h"
#include "Types.h"
#include <array>
#include <map>

using std::array;
using std::map;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum EnumSize { FOUR, FIVE, SIX, SEVEN, COUNT_SIZE };
    enum class Action { OPEN_GRAPHIC, REM_GRAPHIC, SAVE_BOARD, LOAD_BOARD, SETTINGS, ABOUT };

    Board* board;

    QWidget* mainPanel;
    QMenuBar* mainMenu;
    QMenu* fileMenu;

    map< Action, QAction* > action;

    QHBoxLayout* mainLayout;
    QVBoxLayout* rightLayout;

    QVBoxLayout* boardVerticalLayout;
    QHBoxLayout* boardHorizontalLayout;
    QGroupBox* boxImages;
    vector< QPushButton* > squares;

    QPushButton* pushRandom;
    QPushButton* pushSolve;

    array< QRadioButton* , EnumSize::COUNT_SIZE > radioSize;
    QGroupBox* boxRadioSize;
    QButtonGroup* groupRadioSize;
    QVBoxLayout* layRadioSize;

    map< BoardMode, QRadioButton* > radioKind;
    QGroupBox* boxRadioKind;
    QButtonGroup* groupRadioKind;
    QVBoxLayout* layRadioKind;

    void createMenu();

    void createRightPanel();
    void createLayouts();

    void createSquares();
    void deleteSquares();
    void setSquaresNumeric( bool isRandom );
    void setSquaresGraphic( bool isRandom );
    void drawNumberOnGraphicSquare( QPixmap&, int number );

    void moveNumericSquares( int rowSource, int colSource, int rowDest, int colDest );
    void moveGraphicSquares( int rowSource, int colSource, int rowDest, int colDest );

    void ( MainWindow::*moveSquare ) ( int rowSource, int colSource, int rowDest, int colDest );

private slots:

    // Menu slots
    void slotLoadGraphic();
    void slotRemoveGraphic();
    void slotSaveBoard();
    void slotReadBoard();
    void slotSettings();
    void slotAbout();

    // Push buttons slots
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
