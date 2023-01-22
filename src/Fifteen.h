
#ifndef FIFTEEN_FIFTEEN_H
#define FIFTEEN_FIFTEEN_H

#include "Board.h"
#include "Controller.h"
#include "GUI/GUIMain.h"
#include "GraphicBoard/ImageProvider.h"
#include "Types.h"
#include "UndoMove.h"

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>

#include <map>
#include <memory>


class Fifteen : public QMainWindow
{
    Q_OBJECT

    friend class GUI;

public:

    explicit Fifteen( QWidget *parent = 0 );
    Fifteen( const Fifteen& ) = delete;
    Fifteen operator=( const Fifteen& ) = delete;

    void initGame();
    void setColor();
    void redrawTiles();

public slots:

    void pressTile();

private:

    std::unique_ptr< Board > board;
    std::unique_ptr< Controller > controller;
    std::unique_ptr< GUI > gui;
    std::unique_ptr< ImageProvider > imageProvider;
    std::unique_ptr< UndoMove > undoMoveService;

    void createTiles();
    void setTiles();
    void setTilesNumeric();
    void setTilesGraphic();

    void prepareQIconForTile( QIcon&, QPixmap&, int fontSize, uint number, NumberColor );

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

