
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

void GUI::createRightPanel( QGroupBox* radioSizeBox, QPushButton*& pushUndo, QVBoxLayout*& rightLayout, map< BoardMode, QRadioButton* >& mapRadioKind )
{
    mapRadioKind[BoardMode::NUMERIC] = new QRadioButton();
    mapRadioKind[BoardMode::GRAPHIC] = new QRadioButton();

    mapRadioKind[BoardMode::NUMERIC]->setChecked( true );
    mapRadioKind[BoardMode::NUMERIC]->setText( "Numeric" );
    mapRadioKind[BoardMode::GRAPHIC]->setText( "Graphic" );

    QVBoxLayout* radioKindLayout = new QVBoxLayout();
    QButtonGroup* radioKindGroup = new QButtonGroup();
    for( std::pair< BoardMode, QRadioButton* > radioKindPair : mapRadioKind )
    {
        radioKindLayout->addSpacing( 10 );
        radioKindLayout->addWidget( radioKindPair.second );
        radioKindPair.second->setStyleSheet( "margin-left:5px;" );
        radioKindGroup->addButton( radioKindPair.second );
    }
    radioKindLayout->addSpacing( 30 );

    QGroupBox* radioKindBox = new QGroupBox(" Kind of Board ");
    radioKindBox->setLayout( radioKindLayout );

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

