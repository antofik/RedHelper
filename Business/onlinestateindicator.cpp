#include "onlinestateindicator.h"
#include "core.h"

OnlineStateIndicator::OnlineStateIndicator(QWidget *parent) :
    QLabel(parent)
{
    connect(Core::network(), SIGNAL(stateChanged()), SLOT(stateChanged()));
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setScaledContents(false);
    setMinimumSize(QSize(16,16));
    setMaximumSize(QSize(16,16));
    stateChanged();
}

void OnlineStateIndicator::stateChanged()
{
    Network::OnlineState state = Core::network()->state();
    qDebug() << "state is " << state;
    switch(state)
    {
        case Network::Online:
            setPixmap(QPixmap(":/Images/Statuses/online16.png"));
            break;
        case Network::Dnd:
            setPixmap(QPixmap(":/Images/Statuses/2ndline16.png"));
            break;
        case Network::Away:
            setPixmap(QPixmap(":/Images/Statuses/away16.png"));
            break;
        case Network::Offline:
            setPixmap(QPixmap(":/Images/Statuses/offline16.png"));
            break;
    }
}
