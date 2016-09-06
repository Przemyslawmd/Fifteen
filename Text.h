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

    void setPl( cmap**, cmap**, cmap** );
    void setEn( cmap**, cmap**, cmap** );

private:

    void setMenu();
    void setControls();
    void setMessages();

    map* menuPl;
    map* menuEn;  

    map* ctrlPl;
    map* ctrlEn;

    map* messagesPl;
    map* messagesEn;
};

#endif // TEXT_H
