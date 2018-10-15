
#include "GUI.h"

GUI::GUI( MainWindow& owner ) : owner( owner ){}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createMenu( map< Action, QAction* >& actions )
{
    QMenu* fileMenu = new QMenu();
    fileMenu->setTitle( "File" );
    fileMenu->setStyleSheet( "padding-left:10px;" );

    bindAction( actions[Action::OPEN_GRAPHIC], &MainWindow::slotLoadGraphic,   "Load Graphic File" );
    bindAction( actions[Action::REM_GRAPHIC],  &MainWindow::slotRemoveGraphic, "Remove Graphic" );
    bindAction( actions[Action::SAVE_BOARD],   &MainWindow::slotSaveBoard,     "Save Board" );
    bindAction( actions[Action::LOAD_BOARD],   &MainWindow::slotReadBoard,     "Load Board" );
    bindAction( actions[Action::SETTINGS],     &MainWindow::slotSettings,      "Settings" );
    bindAction( actions[Action::ABOUT],        &MainWindow::slotAbout,         "About" );

    fileMenu->addAction( actions[Action::OPEN_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( actions[Action::REM_GRAPHIC] );
    fileMenu->addSeparator();
    fileMenu->addAction( actions[Action::SAVE_BOARD] );
    fileMenu->addSeparator();
    fileMenu->addAction( actions[Action::LOAD_BOARD] );

    QMenuBar* menuBar = new QMenuBar();
    menuBar->addMenu( fileMenu );
    menuBar->addAction( actions[Action::SETTINGS] );
    menuBar->addAction( actions[Action::ABOUT] );
    menuBar->setStyleSheet( "padding-left: 5px; margin: 3px;" );

    owner.setMenuBar( menuBar );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::createRightPanel( QGroupBox* radioSizeBox, QGroupBox* radioKindBox, QPushButton*& pushUndo, QVBoxLayout*& rightLayout )
{
    QPushButton* pushRandom = new QPushButton(" Generate Board ");
    pushRandom->setStyleSheet( "height:20px;" );
    connect( pushRandom, &QPushButton::clicked, &owner, &MainWindow::slotGenerateBoard );

    QPushButton* pushSolve = new QPushButton(" Solve Board ");
    pushSolve->setStyleSheet( "height:20px;" );
    connect( pushSolve, &QPushButton::clicked, &owner, &MainWindow::slotSolveBoard );

    pushUndo = new QPushButton(" Undo Move ");
    pushUndo->setText("Undo Move");
    pushUndo->setStyleSheet( "height:20px;" );
    pushUndo->setDisabled( true );
    connect( pushUndo, &QPushButton::clicked, &owner, &MainWindow::slotUndoMove );

    rightLayout = new QVBoxLayout();
    rightLayout->setContentsMargins( 30, 0, 20, 0 );
    rightLayout->addWidget( pushRandom );
    rightLayout->addSpacing( 15 );
    rightLayout->addWidget( pushSolve );
    rightLayout->addSpacing( 15 );
    rightLayout->addWidget( pushUndo );
    rightLayout->addSpacing( 30 );
    rightLayout->addWidget( radioSizeBox );
    rightLayout->addStretch();
    rightLayout->addWidget( radioKindBox );
    rightLayout->addStretch();
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::completeLayouts( QWidget* mainPanel, QVBoxLayout*& boardVerticalLayout, QVBoxLayout* rightLayout )
{
    mainPanel = new QWidget();
    mainPanel->setContentsMargins( 20, 20, 0, 10 );

    boardVerticalLayout = new QVBoxLayout();
    boardVerticalLayout->setSpacing( 0 );

    QGroupBox* boxImages = new QGroupBox();
    boxImages->setLayout( boardVerticalLayout );

    QHBoxLayout* mainLayout = new QHBoxLayout( mainPanel );
    mainLayout->addWidget( boxImages );
    mainLayout->addLayout( rightLayout );

    owner.setCentralWidget( mainPanel );
}

/*********************************************************************************/
/*********************************************************************************/

void GUI::bindAction( QAction*& action, SlotMainWindow slot, QString text )
{
    action = new QAction( &owner );
    action->setText( text );
    connect( action, &QAction::triggered, &owner, slot );
}

