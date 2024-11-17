#include "ball_icon.hpp"
#include "abstract_widgets.hpp"

namespace widgets {

ball_icon::ball_icon(int radius) : m_radius(radius) {
}

int ball_icon::radius() const {
    return m_radius;
}

void ball_icon::radius(int radius) {
    m_radius = radius;
}

widget *ball_icon::child_at(int x, int y) {
    if (x > 0 && x < width() && y > 0 && y < height()) {
        return this;
    }
    return nullptr;
}

int ball_icon::width() const {
    return 2 * m_radius + 1;
}

int ball_icon::height() const {
    return 2 * m_radius + 1;
}

[[nodiscard]] std::unique_ptr<ball_icon> make_ball_icon(int radius) {
    return std::make_unique<ball_icon>(radius);
}
}  // namespace widgets
