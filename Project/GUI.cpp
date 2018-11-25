
#include "GUI.h"

void GUI::createGUI( MainWindow& owner )
{
    gui = new GUI( owner );
}

/*********************************************************************************/
/*********************************************************************************/

GUI* GUI::getGUI()
{
    return gui;
}

/*********************************************************************************/
/*********************************************************************************/

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

QVBoxLayout* GUI::createRightLayout( QButtonGroup*& radioSizeGroup, QPushButton*& pushUndo, map< BoardMode, QRadioButton* >& mapRadioKind,
                                                                                            map< BoardSize, QRadioButton* >& mapRadioSize)
{
    mapRadioSize[BoardSize::FOUR] = new QRadioButton();
    mapRadioSize[BoardSize::FIVE] = new QRadioButton();
    mapRadioSize[BoardSize::SIX] = new QRadioButton();
    mapRadioSize[BoardSize::SEVEN] = new QRadioButton();

    QVBoxLayout* radioSizeLayout = new QVBoxLayout();
    radioSizeGroup = new QButtonGroup();
    for( std::pair< BoardSize, QRadioButton* > radioSizePair : mapRadioSize )
    {
        radioSizeLayout->addSpacing( 10 );
        radioSizeLayout->addWidget( radioSizePair.second );
        radioSizePair.second->setStyleSheet( "margin-left:5px;" );
        radioSizeGroup->addButton( radioSizePair.second );
        radioSizeGroup->setId( radioSizePair.second, radioSizePair.first );
    }
    radioSizeLayout->addSpacing( 30 );

    mapRadioSize[BoardSize::FOUR]->setText( "4" );
    mapRadioSize[BoardSize::FIVE]->setText( "5" );
    mapRadioSize[BoardSize::SIX]->setText( "6" );
    mapRadioSize[BoardSize::SEVEN]->setText( "7" );
    mapRadioSize[BoardSize::FOUR]->setChecked( true );

    QGroupBox* radioSizeBox = new QGroupBox(" Dimension of Board ");
    radioSizeBox->setLayout( radioSizeLayout );

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

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setContentsMargins( 30, 0, 20, 0 );
    layout->addWidget( pushRandom );
    layout->addSpacing( 15 );
    layout->addWidget( pushSolve );
    layout->addSpacing( 15 );
    layout->addWidget( pushUndo );
    layout->addSpacing( 30 );
    layout->addWidget( radioSizeBox );
    layout->addStretch();
    layout->addWidget( radioKindBox );
    layout->addStretch();
    return layout;
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

GUI* GUI::gui = nullptr;
