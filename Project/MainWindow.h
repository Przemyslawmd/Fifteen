
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Board.h"
#include "Types.h"
#include "UndoMove.h"
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <memory>
#include <array>
#include <map>

using std::array;
using std::map;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class GUI;

    Board* board;
    unique_ptr< UndoMove > undoMoveService;
    map< Action, QAction* > action;

    map< BoardSize, QRadioButton* > radioSize;
    map< BoardMode, QRadioButton* > radioKind;

    void createSquares();
    void setSquaresNumeric( bool isRandom );
    void setSquaresGraphic( bool isRandom );
    void drawNumberOnGraphicSquare( QPainter&, QPixmap&, QColor, int fontSize, int number );

    void makeMove( Move, int row, int col );
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
    void slotUndoMove();

public:

    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    void setColor();
    void redrawSquares();
    void createUndoMovesService();
    void deleteUndoMovesService();

public slots:

    void pressSquare();
};

#endif // MAINWINDOW_H

