
#include "WindowSetting.h"
#include <memory>

using std::unique_ptr;

WindowSetting::WindowSetting( MainWindow& parent ) : slider{ Qt::Horizontal, this }, parent( parent )
{
    setModal( true );
    setWindowTitle( "" );
    setGeometry( 100, 100, 400, 560 );
    setMaximumSize( 400, 870 );
    setMinimumSize( 400, 870 );

    QVBoxLayout layWindow;
    optionsCurrent = Options::sendData();

    /* Graphic loading box *****************************************/

    mapRadioGraphicMode[GraphicMode::SCALED] = new QRadioButton();
    mapRadioGraphicMode[GraphicMode::CROPPED] = new QRadioButton();
    mapRadioGraphicMode[GraphicMode::SCALED]->setText( "Graphic is to be scalled" );
    mapRadioGraphicMode[GraphicMode::SCALED]->setChecked( optionsCurrent->graphicMode == GraphicMode::SCALED );
    mapRadioGraphicMode[GraphicMode::CROPPED]->setText( "Graphic is to be cropped" );

    for ( auto& mapRadio : mapRadioGraphicMode )
    {
        mapRadio.second->setStyleSheet( "margin-left: 5px;" );
        groupRadioGraphicMode.addButton( mapRadio.second );
    }

    mapRadioGraphicMode[ optionsCurrent->graphicMode]->setChecked( true );

    checkImage[BoardSize::FOUR] = new QCheckBox();
    checkImage[BoardSize::FOUR]->setText(  "Graphic is to be loaded for a board  4x4" );
    checkImage[BoardSize::FOUR]->setChecked( optionsCurrent->fourImageToBeLoaded );
    checkImage[BoardSize::FIVE] = new QCheckBox();
    checkImage[BoardSize::FIVE]->setText(  "Graphic is to be loaded for a board  5x5" );
    checkImage[BoardSize::FIVE]->setChecked( optionsCurrent->fiveImageToBeLoaded );
    checkImage[BoardSize::SIX] = new QCheckBox();
    checkImage[BoardSize::SIX]->setText(  "Graphic is to be loaded for a board  6x6" );
    checkImage[BoardSize::SIX]->setChecked( optionsCurrent->sixImageToBeLoaded );
    checkImage[BoardSize::SEVEN] = new QCheckBox();
    checkImage[BoardSize::SEVEN]->setText(  "Graphic is to be loaded for a board  7x7" );
    checkImage[BoardSize::SEVEN]->setChecked( optionsCurrent->sevenImageToBeLoaded );

    for ( auto& check : checkImage )
    {
        check.second->setStyleSheet( "margin-left: 5px;" );
    }

    radioNumberOnImage[ NumberColor::NO ] = new QRadioButton();
    radioNumberOnImage[ NumberColor::NO ]->setText( "Number on an graphic square : No" );
    radioNumberOnImage[ NumberColor::BLACK ] = new QRadioButton();
    radioNumberOnImage[ NumberColor::BLACK ]->setText( "Number on an graphic square : Black" );
    radioNumberOnImage[ NumberColor::WHITE ] = new QRadioButton();
    radioNumberOnImage[ NumberColor::WHITE ]->setText( "Number on an graphic square : White" );

    for ( auto radioMap : radioNumberOnImage )
    {
        radioMap.second->setStyleSheet( "margin-left: 5px;" );
        groupRadioNumberOnImage.addButton( radioMap.second );
    }

    radioNumberOnImage[ optionsCurrent->numberColor ]->setChecked( true );

    QVBoxLayout layRadioImage;
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( mapRadioGraphicMode[GraphicMode::SCALED] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( mapRadioGraphicMode[GraphicMode::CROPPED] );
    layRadioImage.addSpacing( 15 );
    layRadioImage.addWidget( checkImage[BoardSize::FOUR] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( checkImage[BoardSize::FIVE] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( checkImage[BoardSize::SIX] );
    layRadioImage.addSpacing( 8 );
    layRadioImage.addWidget( checkImage[BoardSize::SEVEN] );
    layRadioImage.addSpacing( 15 );
    layRadioImage.addWidget( radioNumberOnImage[NumberColor::NO] );
    layRadioImage.addSpacing( 12 );
    layRadioImage.addWidget( radioNumberOnImage[NumberColor::BLACK] );
    layRadioImage.addSpacing( 12 );
    layRadioImage.addWidget( radioNumberOnImage[NumberColor::WHITE] );
    layRadioImage.addSpacing( 15 );
    boxRadioImage.setLayout( &layRadioImage );
    boxRadioImage.setTitle( "Image fof graphic board" );

    /* Color of numeric board **************************************/

    radioColor[Color::BLUE] = new QRadioButton();
    radioColor[Color::GREEN] = new QRadioButton();
    radioColor[Color::RED] = new QRadioButton();
    radioColor[Color::BLUE]->setText( "Blue" );
    radioColor[Color::GREEN]->setText( "Green" );
    radioColor[Color::RED]->setText( "Red" );

    for ( auto& radio : radioColor )
    {
        radio.second->setStyleSheet( "margin-left:5px;" );
        groupRadioColor.addButton( radio.second );
    }

    radioColor[ optionsCurrent->squareColor ]->setChecked( true );

    QVBoxLayout layRadioColor;
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( radioColor[BLUE] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( radioColor[GREEN] );
    layRadioColor.addSpacing( 7 );
    layRadioColor.addWidget( radioColor[RED] );
    layRadioColor.addSpacing( 7 );
    boxRadioColor.setLayout( &layRadioColor );
    boxRadioColor.setTitle( "Color of Numeric Board" );

    /* Slider for square size **************************************/

    slider.setRange( 1, 5 );
    slider.setSingleStep( 1 );
    sliderLabels[0].setText( " 50" );
    sliderLabels[1].setText( "  100" );
    sliderLabels[2].setText( "150" );
    sliderLabels[3].setText( "200  " );
    sliderLabels[4].setText( "250" );
    slider.setValue( optionsCurrent->squareSizeIndex );

    QGridLayout layoutSlider;
    layoutSlider.setContentsMargins( 10, 20, 30, 20 );
    layoutSlider.addWidget( &slider,          0, 0, 1, 5 );
    layoutSlider.addWidget( &sliderLabels[0], 1, 0, 1, 1, Qt::AlignLeft );
    layoutSlider.addWidget( &sliderLabels[1], 1, 1, 1, 1, Qt::AlignLeft );
    layoutSlider.addWidget( &sliderLabels[2], 1, 2, 1, 1, Qt::AlignCenter );
    layoutSlider.addWidget( &sliderLabels[3], 1, 3, 1, 1, Qt::AlignRight );
    layoutSlider.addWidget( &sliderLabels[4], 1, 4, 1, 1, Qt::AlignRight );
    boxSquareSize.setLayout( &layoutSlider );
    boxSquareSize.setTitle( "Size of Square" );

    /* Undo availability *******************************************/

    checkUndoEnabled.setText( "Enable undo to ten moves" );
    checkUndoEnabled.setChecked( optionsCurrent->undoEnabled );
    checkUndoEnabled.setStyleSheet( "margin-left: 5px" );
    QVBoxLayout layoutUndoEnabled;
    layoutUndoEnabled.addSpacing( 10 );
    layoutUndoEnabled.addWidget( &checkUndoEnabled );
    layoutUndoEnabled.addSpacing( 10 );
    boxUndoEnabled.setLayout( &layoutUndoEnabled );

    /* General layout **********************************************/

    QHBoxLayout layControls;
    accept.setStyleSheet( "height:20px;" );
    accept.setText( "Accept ");
    connect( &accept, SIGNAL( clicked() ), this, SLOT( acceptSettings() ));

    layControls.addSpacing( 120 );
    layControls.addWidget( &accept );
    layControls.addSpacing( 120 );

    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioImage );
    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxRadioColor);
    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxSquareSize );
    layWindow.addSpacing( 20 );
    layWindow.addWidget( &boxUndoEnabled );
    layWindow.addSpacing( 20 );
    layWindow.addLayout( &layControls );
    layWindow.addSpacing( 10 );
    layWindow.addStretch();

    this->setLayout( &layWindow );
    this->show();
}

/*********************************************************************************/
/*********************************************************************************/

void WindowSetting::acceptSettings()
{
    unique_ptr< OptionsData > optionsNew ( new OptionsData );
    optionsNew->graphicMode = mapRadioGraphicMode[GraphicMode::SCALED]->isChecked() ? GraphicMode::SCALED : GraphicMode::CROPPED;
    optionsNew->fourImageToBeLoaded = checkImage[BoardSize::FOUR]->isChecked();
    optionsNew->fiveImageToBeLoaded = checkImage[BoardSize::FIVE]->isChecked();
    optionsNew->sixImageToBeLoaded = checkImage[BoardSize::SIX]->isChecked();
    optionsNew->sevenImageToBeLoaded = checkImage[BoardSize::SEVEN]->isChecked();
    optionsNew->squareSizeIndex = slider.value();
    optionsNew->numberColor = getChoosenOption< NumberColor >( radioNumberOnImage, groupRadioNumberOnImage );
    optionsNew->undoEnabled = checkUndoEnabled.isChecked();
    optionsNew->squareColor = getChoosenOption< Color >( radioColor, groupRadioColor );

    bool numberImageChanged = optionsNew->numberColor != optionsCurrent->numberColor;
    bool squareSizeChanged = optionsNew->squareSizeIndex != optionsCurrent->squareSizeIndex;
    bool undoMovesChanged = optionsNew->undoEnabled != optionsCurrent->undoEnabled;
    bool colorChanged = optionsNew->squareColor != optionsCurrent->squareColor;

    Options::receiveData( std::move( optionsNew ));

    if ( squareSizeChanged && optionsCurrent->boardMode == BoardMode::NUMERIC )
    {
        parent.redrawSquares();
    }

    if ( numberImageChanged && optionsCurrent->boardMode == BoardMode::GRAPHIC )
    {
        parent.redrawSquares();
    }

    if ( colorChanged && optionsCurrent->boardMode == BoardMode::NUMERIC )
    {
        parent.setColor();
    }

    if ( undoMovesChanged )
    {
        if ( optionsCurrent->undoEnabled )
        {
            parent.deleteUndoMovesService();
        }
        else
        {
            parent.createUndoMovesService();
        }
    }

    close();
}

/*********************************************************************************/
/*********************************************************************************/

template< typename T > T WindowSetting::getChoosenOption( map< T, QRadioButton* >& mapButton, QButtonGroup& group )
{
    QRadioButton* choosen = static_cast< QRadioButton* >( group.checkedButton() );

    for ( auto it = mapButton.begin(); it != mapButton.end(); it++ )
    {
        if ( it->second == choosen )
        {
            return it->first;
        }
    }
    return mapButton.begin()->first;
}

