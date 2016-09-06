#include "Text.h"

Text::Text()
{
    menuPl = new map();
    menuEn = new map();
    setMenu();  

    ctrlPl = new map();
    ctrlEn = new map();
    setControls();   

    messagesPl = new map();
    messagesEn = new map();
    setMessages();
}

/*******************************************************************************************************************/
/*******************************************************************************************************************/

void Text::setMenu()
{
    menuEn->insert("file", "File");
    menuEn->insert("fOpenG", "Load Graphic File");
    menuEn->insert("fRemG", "Remove Graphic");
    menuEn->insert("fSaveB", "Save Board");
    menuEn->insert("fLoadB", "Load Board");

    menuPl->insert("file", "Plik");
    menuPl->insert("fOpenG", UTF("Wczytaj plik graficzny"));
    menuPl->insert("fRemG", UTF("Usuń grafikę"));
    menuPl->insert("fSaveB", UTF("Zapisz planszę"));
    menuPl->insert("fLoadB", UTF("Wczytaj planszę"));

    menuEn->insert("solution", "Solution");
    menuEn->insert("settings", "Settings");
    menuEn->insert("info", "Information");
    menuEn->insert("iHelp", "Help");
    menuEn->insert("iAbout", "About");

    menuPl->insert("solution", UTF("Rozwiązanie"));
    menuPl->insert("settings", "Ustawienia");
    menuPl->insert("info", "Informacja");
    menuPl->insert("iHelp", "Pomoc");
    menuPl->insert("iAbout", "O aplikacji");

    menuEn->insert("set", "Settings");
    menuPl->insert("set", "Ustawienia");

    menuEn->insert("info", "Information");    
    menuPl->insert("info", "Informacja");

}

/*******************************************************************************************************************/
/*******************************************************************************************************************/

void Text::setControls()
{
    ctrlPl->insert("random",UTF("Generuj planszę"));
    ctrlPl->insert("set",UTF("Ułóż planszę"));
    ctrlPl->insert("dim","Wymiar planszy");
    ctrlPl->insert("kind","Rodzaj planszy");
    ctrlPl->insert("num","numeryczna");
    ctrlPl->insert("graph","graficzna");

    ctrlEn->insert("random","Random Board");
    ctrlEn->insert("set","Solve Board");
    ctrlEn->insert("dim","Dimension of Board");
    ctrlEn->insert("kind","Kind of Board");
    ctrlEn->insert("num","Numeric");
    ctrlEn->insert("graph","Graphic");
}

/*******************************************************************************************************************/
/*******************************************************************************************************************/

void Text::setMessages()
{
    messagesPl->insert("noImage", UTF("Brak załadowanej grafiki dla planszy "));
    messagesEn->insert("noImage", "There is no loaded graphic for a board ");

    messagesPl->insert("success",UTF("Grafika została wczytana dla planszy "));
    messagesEn->insert("success","Graphic was loaded for a board ");

    messagesPl->insert("failure", UTF("Niepowodzenie wczytania grafiki dla planszy "));
    messagesEn->insert("failure", "Failure of loading graphic for a board ");

    messagesPl->insert("toLow", UTF("Niewystarczający rozmiar grafiki dla planszy "));
    messagesEn->insert("toLow", "To low size of graphic for a board ");

    messagesPl->insert("openGFail","Niepowodzenie wczytania grafiki\t");
    messagesEn->insert("openGFail", "Failure of loading an image\t");

    messagesPl->insert("remG",UTF("Grafika usunięta\t"));
    messagesEn->insert("remG", "Graphic removed\t");

}

/********************************************************************************************************************/
/********************************************************************************************************************/

void Text::setEn(cmap** menu, cmap** ctrl, cmap** mes )
{
    *menu = menuEn;    
    *ctrl = ctrlEn;
    *mes = messagesEn;    
}

void Text::setPl(cmap** menu, cmap** ctrl, cmap** mes )
{
    *menu = menuPl;    
    *ctrl = ctrlPl;
    *mes = messagesPl;    
}
