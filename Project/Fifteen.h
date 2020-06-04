
#ifndef FIFTEEN_H
#define FIFTEEN_H

#include "GUI/GUIMain.h"
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

    void initGame();
    void setColor();
    void redrawTiles();
    void createUndoMovesService();
    void deleteUndoMovesService();

public slots:

    void pressTile();

private:

    unique_ptr< Board > board;
    unique_ptr< GUI > gui;
    unique_ptr< UndoMove > undoMoveService;

    void createTiles();
    void setTiles();
    void setTilesNumeric();
    void setTilesGraphic();

    void prepareIconWithNumber( QIcon&, QPixmap&, QColor, int fontSize, uint number );

    void makeMove( Move, uint row, uint col );
    void moveNumericTile( uint rowSource, uint colSource, uint rowDest, uint colDest );
    void moveGraphicTile( uint rowSource, uint colSource, uint rowDest, uint colDest );

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

#endif

