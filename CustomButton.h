#pragma once

#include <QPushButton>
#include <QPainter>
#include <memory>

class CustomButton : public QPushButton {
public:
    explicit CustomButton(QWidget* parent);

protected:
    const QColor m_background_color = { "#131212" };
    const QColor m_icon_color = m_background_color.lighter(450);


    void paintEvent(QPaintEvent*) override;
    const QColor& bg_color() const { return m_background_color; }
    const QColor& icon_color() const { return m_icon_color; }
    std::unique_ptr<QPainter> painter(QWidget*);
};
