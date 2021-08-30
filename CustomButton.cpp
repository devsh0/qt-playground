#include "CustomButton.h"
#include <QGraphicsDropShadowEffect>

CustomButton::CustomButton(QWidget* parent)
    : QPushButton(parent)
{
    auto* effect = new QGraphicsDropShadowEffect;
    effect->setColor("black");
    effect->setBlurRadius(5);
    effect->setOffset(1.5);
    setGraphicsEffect(effect);
}

void CustomButton::paintEvent(QPaintEvent* event)
{
    QPushButton::paintEvent(event);
}

std::unique_ptr<QPainter> CustomButton::painter(QWidget* child)
{
    auto painter = std::make_unique<QPainter>(child);
    painter->setBrush(QBrush(icon_color().darker(isDown() * 120)));
    painter->setPen(QPen(icon_color().darker(isDown() * 120), 2));
    painter->setRenderHint(QPainter::Antialiasing, true);
    return painter;
}