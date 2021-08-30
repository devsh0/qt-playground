#include "CustomPlaylistNavButton.h"
#include <QPainter>

void CustomPlaylistNavButton::paintEvent(QPaintEvent* event)
{
    CustomButton::paintEvent(event);

    QPolygon polygon;
    int polygon_x_offset = size().width() / 3;
    int polygon_y_offset = size().height() / 4;
    if (m_navigate_left) {
        polygon.append(QPoint(polygon_x_offset * 2, polygon_y_offset));
        polygon.append(QPoint(polygon_x_offset, polygon_y_offset * 2));
        polygon.append(QPoint(polygon_x_offset * 2, polygon_y_offset * 3));
    }
    else {
        polygon.append(QPoint(polygon_x_offset, polygon_y_offset));
        polygon.append(QPoint(polygon_x_offset * 2, polygon_y_offset * 2));
        polygon.append(QPoint(polygon_x_offset, polygon_y_offset * 3));
    }
    painter(this)->drawPolygon(polygon);

    QPoint top_left;
    QPoint bottom_right;
    int x_top_left;
    int y_top_left;
    int x_bottom_right;
    int y_bottom_right;
    if (m_navigate_left) {
        x_top_left = polygon_x_offset - 1;
        y_top_left = polygon_y_offset;
        x_bottom_right = polygon_x_offset;
        y_bottom_right = polygon_y_offset * 3;
    }
    else {
        x_top_left = polygon_x_offset * 2;
        y_top_left = polygon_y_offset;
        x_bottom_right = x_top_left + 1;
        y_bottom_right = polygon_y_offset * 3;
    }
    top_left.setX(x_top_left);
    top_left.setY(y_top_left);
    bottom_right.setX(x_bottom_right);
    bottom_right.setY(y_bottom_right);

    painter(this)->drawRect(QRect(top_left, bottom_right));
}
