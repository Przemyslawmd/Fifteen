#ifndef TEXT_H
#define TEXT_H

#include <QString>
#include <QMap>

#define UTF(text) QString::fromUtf8(text)

typedef QMap <QString, QString> map;
typedef const QMap<QString, QString> cmap;

class Text
{
public:
    Text();

    void setPl( cmap**, cmap**, cmap**, cmap**, cmap** );
    void setEn( cmap**, cmap**, cmap**, cmap**, cmap** );

private:

    void setMenu();
    void setSettings();
    void setControls();
    void setAbout();
    void setMessages();

    map* menuPl;
    map* menuEn;

    map* settingsPl;
    map* settingsEn;

    map* ctrlPl;
    map* ctrlEn;

    map* aboutPl;
    map* aboutEn;

    map* messagesPl;
    map* messagesEn;
};

#endif // TEXT_H
