
#ifndef FIFTEEN_H
#define FIFTEEN_H

#include "Board.h"
#include "Types.h"
#include "UndoMove.h"
#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>
#include <memory>
#include <map>

using std::map;
using std::unique_ptr;

class Fifteen : public QMainWindow
{
    Q_OBJECT

    friend class GUI;

public:

    explicit Fifteen( QWidget *parent = 0 );
    ~Fifteen();

    void setColor();
    void redrawTiles();
    void createUndoMovesService();
    void deleteUndoMovesService();

public slots:

    void pressTile();

private:

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

    void ( Fifteen::*moveTile ) ( int rowSource, int colSource, int rowDest, int colDest );

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
};

#endif // FIFTEEN_H

