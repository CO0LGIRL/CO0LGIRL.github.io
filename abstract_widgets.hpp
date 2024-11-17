#ifndef ABSTRACT_WIDGETS_HPP_
#define ABSTRACT_WIDGETS_HPP_

#include <memory>

namespace widgets {

struct container;

struct widget {
    [[nodiscard]] virtual int width() const = 0;
    [[nodiscard]] virtual int height() const = 0;

    virtual widget *child_at(int x, int y);

    widget(const widget &) = delete;
    widget(widget &&) = delete;
    widget &operator=(const widget &) = delete;
    widget &operator=(widget &&) = delete;

    [[nodiscard]] container *parent() const {
        return m_parent;
    }

    virtual ~widget();
    friend struct container;

protected:
    widget() = default;

private:
    container *m_parent = nullptr;
};

struct container : widget {
    virtual void update_layout() = 0;

protected:
    container() = default;

    void static set_parent(container *parent, widget *child) {
        if (parent != child) {
            child->m_parent = parent;
        }
    }
};
}  // namespace widgets

#endif  // ABSTRACT_WIDGETS_HPP_