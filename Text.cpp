#include "Text.h"

Text::Text()
{
    menuPl = new map();
    menuEn = new map();
    setMenu();

    settingsPl = new map();
    settingsEn = new map();
    setSettings();

    ctrlPl = new map();
    ctrlEn = new map();
    setControls();

    aboutPl = new map();
    aboutEn = new map();
    setAbout();

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
/* SETS SETTINGS ***************************************************************************************************/

void Text::setSettings()
{
    settingsPl->insert("title","USTAWIENIA");
    settingsPl->insert("graphic","Grafika");
    settingsPl->insert("graphic4","Grafika jest wczytywana dla planszy 4x4");
    settingsPl->insert("graphic5","Grafika jest wczytywana dla planszy 5x5");
    settingsPl->insert("graphic6","Grafika jest wczytywana dla planszy 7x7");
    settingsPl->insert("graphic7","Grafika jest wczytywana dla planszy 7x7");
    settingsPl->insert("graphicScal", "Grafika jest skalowana");
    settingsPl->insert("graphicCrop", "Grafika jest kadrowana");
    settingsPl->insert("color", "Kolor planszy numerycznej");
    settingsPl->insert("colorR", "Czerwony");
    settingsPl->insert("colorG", "Zielony");
    settingsPl->insert("colorB", "Niebieski");
    settingsPl->insert("lan",UTF("Język"));
    settingsPl->insert("pol","Polski");
    settingsPl->insert("eng","Angielski");
    settingsPl->insert("acc","Akceptuj");


    settingsEn->insert("title","SETTINGS");
    settingsEn->insert("graphic","Graphic");
    settingsEn->insert("graphic4","Graphic is to be loaded for a board 4x4");
    settingsEn->insert("graphic5","Graphic is to be loaded for a board 5x5");
    settingsEn->insert("graphic6","Graphic is to be loaded for a board 6x6");
    settingsEn->insert("graphic7","Graphic is to be loaded for a board 7x7");
    settingsEn->insert("graphicScal", "Graphic is to be scalled");
    settingsEn->insert("graphicCrop", "Graphic is to be cropped");
    settingsEn->insert("color", "Color of Numeric Board");
    settingsEn->insert("colorR", "Red");
    settingsEn->insert("colorG", "Green");
    settingsEn->insert("colorB", "Blue");
    settingsEn->insert("lan","Language");
    settingsEn->insert("pol","Polish");
    settingsEn->insert("eng","English");
    settingsEn->insert("acc","Accept");
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

/*******************************************************************************************************************/\
/*******************************************************************************************************************/

void Text::setAbout()
{
    aboutEn->insert("about", "ABOUT APPLICATION");
    aboutEn->insert("aboutVer",     "<pre>  Version:      1.1.2");
    aboutEn->insert("aboutAuth",UTF("<pre>  Author:       Przemyslaw Madej, Cracow 2016</pre>"));
    aboutEn->insert("aboutWeb",     "<pre>  Page:         http://przemeknet.pl/fifteenEn.aspx</pre>");
    aboutEn->insert("aboutLicense", "<pre>  License:      Freeware</pre>");

    aboutPl->insert("about", "O APLIKACJI");
    aboutPl->insert("aboutVer",       "<pre>  Wersja:     1.1.2");
    aboutPl->insert("aboutAuth",  UTF("<pre>  Autor:      Przemysław Madej, Kraków 2016</pre>"));
    aboutPl->insert("aboutWeb",       "<pre>  Strona:     http://przemeknet.pl/fifteenPl.aspx</pre>");
    aboutPl->insert("aboutLicense",   "<pre>  Licencja:   Freeware</pre>");
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

void Text::setEn(cmap** menu, cmap** set, cmap** ctrl, cmap** mes, cmap** about)
{
    *menu = menuEn;
    *set = settingsEn;
    *ctrl = ctrlEn;
    *mes = messagesEn;
    *about = aboutEn;
}

void Text::setPl(cmap** menu, cmap** set, cmap** ctrl, cmap** mes, cmap** about)
{
    *menu = menuPl;
    *set = settingsPl;
    *ctrl = ctrlPl;
    *mes = messagesPl;
    *about = aboutPl;
}
