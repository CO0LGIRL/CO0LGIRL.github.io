#include "abstract_widgets.hpp"

namespace widgets {

widget::~widget() = default;

widget *widget::child_at(int x, int y) {
    if (x >= 0 && x < width() && y >= 0 && y < height()) {
        return this;
    }
    return nullptr;
}
}  // namespace widgets