#ifndef GRID_HPP_
#define GRID_HPP_

#include <vector>
#include "abstract_widgets.hpp"

namespace widgets {
class grid : public container {
public:
    explicit grid(int rows, int columns);

    [[nodiscard]] int rows() const {
        return m_rows;
    }

    [[nodiscard]] int columns() const {
        return m_columns;
    }

    [[nodiscard]] widget *get(int row, int column) const;
    widget *child_at(int x, int y) final;
    widget *add(std::unique_ptr<widget> child, int row, int column);
    std::unique_ptr<widget> remove(int row, int column);
    void update_layout() final;

    [[nodiscard]] int width() const final {
        return m_width;
    };

    [[nodiscard]] int height() const final {
        return m_height;
    };

private:
    int m_rows;
    int m_columns;
    std::vector<std::vector<std::unique_ptr<widget>>> m_children;
    std::vector<int> m_column_widths;
    std::vector<int> m_row_heights;
    int m_width;
    int m_height;
};

[[nodiscard]] std::unique_ptr<grid> make_grid(int rows, int columns);

}  // namespace widgets

#endif