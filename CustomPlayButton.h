#pragma once

#include "CustomButton.h"
#include <QPaintEvent>
#include <QPainter>
#include <QPen>

class CustomPlayButton : public CustomButton {
public:
    explicit CustomPlayButton(QWidget* parent)
        : CustomButton(parent) {};

protected:
    void paintEvent(QPaintEvent*) override;
};
