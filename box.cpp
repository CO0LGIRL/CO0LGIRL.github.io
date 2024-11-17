#include "box.hpp"

namespace widgets {

box::box(kind kind) : m_width(0), m_height(0), m_kind(kind) {
    update_layout();
}

int box::size() const {
    return static_cast<int>(m_children.size());
}

widget *box::get(int index) const {
    if (index < 0 || index >= static_cast<int>(m_children.size())) {
        return nullptr;
    }
    return m_children[index].get();
}

widget *box::add(std::unique_ptr<widget> child) {
    set_parent(this, child.get());
    m_children.push_back(std::move(child));
    update_layout();
    return m_children.back().get();
}

std::unique_ptr<widget> box::remove(int index) {
    if (index < 0 || index >= static_cast<int>(m_children.size())) {
        return nullptr;
    }
    set_parent(nullptr, m_children[index].get());
    std::unique_ptr<widget> removed = std::move(m_children[index]);
    m_children.erase(m_children.begin() + index);
    update_layout();
    return removed;
}

void box::update_layout() {
    if (m_kind == kind::HORIZONTAL) {
        m_width = 0;
        m_height = 0;
        for (const auto &child : m_children) {
            if (child->height() > m_height) {
                m_height = child->height();
            }
            m_width += child->width();
        }
    } else {
        m_width = 0;
        m_height = 0;
        for (const auto &child : m_children) {
            if (child->width() > m_width) {
                m_width = child->width();
            }
            m_height += child->height();
        }
    }
}

widget *box::child_at(int x, int y) {
    if (x >= 0 && x < width() && y >= 0 && y < height()) {
        if (m_kind == kind::HORIZONTAL) {
            return find_child_horizontal(x, y);
        } else {
            return find_child_vertical(x, y);
        }
    }
    return nullptr;
}

widget *box::find_child_vertical(int x, int y) {
    int current_y = 0;
    for (const auto &child : m_children) {
        if (y >= current_y && y < current_y + child->height()) {
            const int x_offset = (width() - child->width()) / 2;
            if (x >= x_offset && x < x_offset + child->width()) {
                return child->child_at(x - x_offset, y - current_y);
            }
        }
        current_y += child->height();
    }
    return nullptr;
}

widget *box::find_child_horizontal(int x, int y) {
    int current_x = 0;
    for (const auto &child : m_children) {
        if (x >= current_x && x < current_x + child->width()) {
            const int y_offset = (height() - child->height()) / 2;
            if (y >= y_offset && y < y_offset + child->height()) {
                return child->child_at(x - current_x, y - y_offset);
            }
        }
        current_x += child->width();
    }
    return nullptr;
}

[[nodiscard]] std::unique_ptr<box> make_box(box::kind kind) {
    return std::make_unique<box>(kind);
}
}  // namespace widgets