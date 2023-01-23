
#ifndef FIFTEEN_FIFTEEN_H
#define FIFTEEN_FIFTEEN_H

#include "Board.h"
#include "Controller.h"
#include "GUI/MenuBar.h"
#include "GUI/Panel.h"
#include "GUI/GUIMain.h"
#include "Types.h"

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>

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

    std::unique_ptr< Controller > controller;
    std::unique_ptr< GUI > gui;
    std::unique_ptr< Panel > panel;
    std::unique_ptr< MenuBar > menuBar;

    std::vector< std::unique_ptr< QPushButton >> tiles;

    void createTiles();
    void setTiles();
    void setTilesNumeric();
    void setTilesGraphic();

    void drawNumberOnTile( QIcon&, QPixmap&, int fontSize, uint number, NumberColor );

    void makeMove( Move, uint row, uint col );
    void moveNumericTile( uint rowSource, uint colSource, uint rowDest, uint colDest, uint boardSize, uint tileSize );
    void moveGraphicTile( uint rowSource, uint colSource, uint rowDest, uint colDest, uint boardSize, uint tileSize );

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

