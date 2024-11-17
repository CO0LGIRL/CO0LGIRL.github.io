#ifndef BOX_HPP_
#define BOX_HPP_

#include <deque>
#include "abstract_widgets.hpp"

namespace widgets {

class box : public container {
public:
    enum class kind { HORIZONTAL, VERTICAL };
    explicit box(kind kind);
    [[nodiscard]] int size() const;
    [[nodiscard]] widget *get(int index) const;
    widget *add(std::unique_ptr<widget> child);
    std::unique_ptr<widget> remove(int index);
    widget *child_at(int x, int y) final;
    void update_layout() final;

    [[nodiscard]] int width() const final {
        return m_width;
    }

    [[nodiscard]] int height() const final {
        return m_height;
    }

    widget *find_child_horizontal(int x, int y);
    widget *find_child_vertical(int x, int y);

private:
    int m_width;
    int m_height;
    std::deque<std::unique_ptr<widget>> m_children;
    const kind m_kind;
};

[[nodiscard]] std::unique_ptr<box> make_box(box::kind kind);

}  // namespace widgets

#endif