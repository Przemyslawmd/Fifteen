
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
#include <GraphicBoard/ImageLoad.h>
#include <Types.h>
#include <Options.h>
#include <GraphicBoard/ImageProvider.h>
#include <IOFile.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Board* board;
    ImagesState* images;

    enum EnumSize { FOUR, FIVE, SIX, SEVEN, COUNT_SIZE };
    enum EnumKind { NUMERIC, GRAPHIC, COUNT_KIND };
    enum Action { OPENGRAPHIC, REMGRAPHIC, SAVEBOARD, LOADBOARD, SETTINGS, ABOUT, COUNTACTIONS };

    QMenuBar* mainMenu;
    QMenu* fileMenu;

    QAction* action[COUNTACTIONS];

    // Main panel
    QWidget* mainPanel;

    QHBoxLayout* mainLayout;
    QVBoxLayout* rightLayout;

    // Board panel
    QVBoxLayout* boardVerticalLayout;
    QHBoxLayout* boardHorizontalLayout;
    QGroupBox* boxImages;
    QPushButton** control;

    // Right panel - press buttons
    QPushButton* pushRandom;
    QPushButton* pushSolve;

    // Right panel - radio controls for a size of board
    QRadioButton* radioSize[EnumSize::COUNT_SIZE];
    QGroupBox* boxRadioSize;
    QButtonGroup* groupRadioSize;
    QVBoxLayout* layRadioSize;

    // Right panel - radio controls for a kind of board
    QRadioButton* radioKind[EnumKind::COUNT_KIND];
    QGroupBox* boxRadioKind;
    QButtonGroup* groupRadioKind;
    QVBoxLayout* layRadioKind;

    void createMenu();

    void createRightPanel();
    void createLayouts();

    void createSquares();
    void setSquaresNumeric( bool isRandom );
    void setSquaresGraphic( bool isRandom );
    void deleteSquares();

    void moveNumericSquares( int rowSource, int colSource, int rowDest, int colDest );
    void moveGraphicSquares( int rowSource, int colSource, int rowDest, int colDest );

    // Pointer to a method which indicates moveNumericSquares or moveGraphicSquares
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

    // Methods setColor and redrawSquares are invoked from WindowSettings
    void setColor();
    void redrawSquares();

public slots:

    void pressSquare();
};

#endif // MAINWINDOW_H
