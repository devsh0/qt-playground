#include "CustomPlayButton.h"
#include <QDebug>
#include <QGraphicsDropShadowEffect>
#include <QPropertyAnimation>
#include <QStringBuilder>

void CustomPlayButton::paintEvent(QPaintEvent* event)
{
    CustomButton::paintEvent(event);
    auto border_radius = size().width() / 2;
    auto background = isDown() ? bg_color().darker(120).name() : bg_color().name();
    auto style = QString("border: 2px solid %1;"
                         "background: %1;"
                         "border-radius: %2px;")
                     .arg(background)
                     .arg(border_radius);
    setStyleSheet(style);

    QPolygon polygon;
    int x_extra_offset = size().width() / 20;
    int icon_x_offset = size().width() / 3 + x_extra_offset;
    int icon_y_offset = size().height() / 4;
    polygon.append(QPoint(icon_x_offset, icon_y_offset));
    polygon.append(QPoint(icon_x_offset * 2, icon_y_offset * 2));
    polygon.append(QPoint(icon_x_offset, icon_y_offset * 3));
    painter(this)->drawPolygon(polygon);
}