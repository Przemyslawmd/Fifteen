
#ifndef FIFTEEN_FIFTEEN_H
#define FIFTEEN_FIFTEEN_H

#include <memory>

#include <QMainWindow>
#include <QPushButton>
#include <QRadioButton>

#include "Board.h"
#include "Controller.h"
#include "GUI/MenuBar.h"
#include "GUI/Panel.h"
#include "GUI/TilesBoard.h"
#include "Types.h"


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

    std::unique_ptr<Controller> controller;
    std::unique_ptr<TilesBoard> tilesBoard;
    std::unique_ptr<Panel> panel;
    std::unique_ptr<MenuBar> menuBar;

    void createTiles();
    void setTiles();
    void setTilesNumeric();
    void setTilesGraphic();

    void drawNumberOnTile( QIcon&, QPixmap&, size_t fontSize, size_t number, GraphicTileCaption );

    void makeMove( Move, size_t row, size_t col );
    void moveNumericTile( size_t rowSource, size_t colSource, size_t rowDest, size_t colDest );
    void moveGraphicTile( size_t rowSource, size_t colSource, size_t rowDest, size_t colDest );

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

