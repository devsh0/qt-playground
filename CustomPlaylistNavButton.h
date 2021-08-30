#pragma once

#include "CustomButton.h"
class CustomPlaylistNavButton : public CustomButton {
    const bool m_navigate_left;
public:
    explicit CustomPlaylistNavButton(QWidget* parent, bool nav_left)
        : CustomButton(parent),
        m_navigate_left(nav_left)
    {
    }

protected:
    void paintEvent(QPaintEvent*) override;
};
