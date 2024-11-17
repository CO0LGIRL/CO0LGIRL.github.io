#include "grid.hpp"
#include <numeric>

namespace widgets {

grid::grid(int rows, int columns)
    : m_rows(rows),
      m_columns(columns),
      m_children(rows),
      m_column_widths(columns, 0),
      m_row_heights(rows, 0),
      m_width(0),
      m_height(0) {
    for (auto &row : m_children) {
        row.reserve(columns);
        for (int c = 0; c < columns; ++c) {
            row.emplace_back();
        }
    }
    update_layout();
}

widget *grid::get(int row, int column) const {
    if (row < 0 || row >= m_rows || column < 0 || column >= m_columns) {
        return nullptr;
    }
    return m_children[row][column].get();
}

widget *grid::add(std::unique_ptr<widget> child, int row, int column) {
    if (row < 0 || column < 0 || column >= m_columns || row >= m_rows) {
        return nullptr;
    }
    set_parent(this, child.get());
    m_children[row][column] = std::move(child);
    update_layout();
    return m_children[row][column].get();
}

std::unique_ptr<widget> grid::remove(int row, int column) {
    if (row < 0 || column < 0 || column >= m_columns || row >= m_rows) {
        return nullptr;
    }
    set_parent(nullptr, m_children[row][column].get());
    std::unique_ptr<widget> removed = std::move(m_children[row][column]);
    update_layout();
    return removed;
}

void grid::update_layout() {
    std::fill(m_column_widths.begin(), m_column_widths.end(), 0);
    std::fill(m_row_heights.begin(), m_row_heights.end(), 0);
    for (int row = 0; row < m_rows; row++) {
        for (int column = 0; column < m_columns; column++) {
            if (m_children[row][column] != nullptr) {
                if (m_children[row][column]->height() > m_row_heights[row]) {
                    m_row_heights[row] = m_children[row][column]->height();
                }
                if (m_children[row][column]->width() >
                    m_column_widths[column]) {
                    m_column_widths[column] = m_children[row][column]->width();
                }
            }
        }
    }
    m_width =
        std::accumulate(m_column_widths.begin(), m_column_widths.end(), 0);
    m_height = std::accumulate(m_row_heights.begin(), m_row_heights.end(), 0);
}

widget *grid::child_at(int x, int y) {
    if (x >= 0 && x < width() && y >= 0 && y < height()) {
        int current_x = 0;
        int current_y = 0;
        int row = -1;
        int column = -1;
        for (int current_row = 0; current_row < m_rows; current_row++) {
            if (y >= current_y && y < current_y + m_row_heights[current_row]) {
                row = current_row;
                break;
            }
            current_y += m_row_heights[current_row];
        }
        for (int current_column = 0; current_column < m_columns; current_column++) {
            if (x >= current_x && x < current_x + m_column_widths[current_column]) {
                column = current_column;
                break;
            }
            current_x += m_column_widths[current_column];
        }
        if (row == -1 || column == -1) {
            return nullptr;
        }
        if (m_children[row][column] != nullptr) {
           return m_children[row][column]->child_at(x - current_x, y - current_y);
       }
    }
    return nullptr;
}

[[nodiscard]] std::unique_ptr<grid> make_grid(int rows, int columns) {
    return std::make_unique<grid>(rows, columns);
}

}  // namespace widgets