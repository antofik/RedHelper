#include "onlinestateindicator.h"
#include "core.h"

OnlineStateIndicator::OnlineStateIndicator(QWidget *parent) :
    QLabel(parent)
{
    connect(Core::network(), SIGNAL(stateChanged()), SLOT(stateChanged()));
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setScaledContents(true);
    setMinimumSize(QSize(16,16));
    setMaximumSize(QSize(16,16));
}

void OnlineStateIndicator::stateChanged()
{
    Network::OnlineState state = Core::network()->state();
    switch(state)
    {
        case Network::Online:
            setPixmap(QPixmap(":/Images/Ribbon/online.png"));
            break;
        case Network::Dnd:
            setPixmap(QPixmap(":/Images/Ribbon/dnd.png"));
            break;
        case Network::Away:
            setPixmap(QPixmap(":/Images/Ribbon/away.png"));
            break;
        case Network::Offline:
            setPixmap(QPixmap(":/Images/Ribbon/offline.png"));
            break;
    }
}
