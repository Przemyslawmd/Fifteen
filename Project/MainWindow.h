
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
using std::unique_ptr;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    friend class GUI;

    Board* board;
    unique_ptr< UndoMove > undoMoveService;
    map< Action, QAction* > action;

    map< BoardSize, QRadioButton* > radioSize;
    map< BoardMode, QRadioButton* > radioKind;

    void createTiles();
    void setTilesNumeric( bool isRandom );
    void setTilesGraphic( bool isRandom );
    void drawNumberOnGraphicTile( QPainter&, QPixmap&, QColor, int fontSize, int number );

    void makeMove( Move, int row, int col );
    void moveNumericTile( int rowSource, int colSource, int rowDest, int colDest );
    void moveGraphicTile( int rowSource, int colSource, int rowDest, int colDest );

    void ( MainWindow::*moveTile ) ( int rowSource, int colSource, int rowDest, int colDest );

private slots:

    void slotLoadGraphic();
    void slotRemoveGraphic();
    void slotSaveBoard();
    void slotReadBoard();
    void slotSettings();
    void slotAbout();

    void slotGenerateBoard();
    void slotSolveBoard();
    void slotUndoMove();

public:

    explicit MainWindow( QWidget *parent = 0 );
    ~MainWindow();

    void setColor();
    void redrawTiles();
    void createUndoMovesService();
    void deleteUndoMovesService();

public slots:

    void pressTile();
};

#endif // MAINWINDOW_H

