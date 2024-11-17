#ifndef BALL_ICON_HPP_
#define BALL_ICON_HPP_

#include "abstract_widgets.hpp"

namespace widgets {

class ball_icon : public widget {
public:
    explicit ball_icon(int radius);
    [[nodiscard]] int radius() const;
    void radius(int radius);
    [[nodiscard]] int width() const final;
    [[nodiscard]] int height() const final;
    widget *child_at(int x, int y) final;

private:
    int m_radius;
};

[[nodiscard]] std::unique_ptr<ball_icon> make_ball_icon(int radius);

}  // namespace widgets

#endif