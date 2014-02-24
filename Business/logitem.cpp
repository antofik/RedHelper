#include "logitem.h"

LogItem::LogItem(int type, QString message):
    type(type),
    message(message)
{    
    time = QDateTime::currentDateTime();
}
