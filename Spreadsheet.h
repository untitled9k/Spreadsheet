#include "Cell.h"
#include <string>

class Spreadsheet{
private:
    Cell ***mCells{nullptr};
    size_t row_ {0};
    size_t col_ {0};
public:
    Spreadsheet(){};
    Spreadsheet(const size_t row, const size_t col);
    Spreadsheet(const Spreadsheet& src);
    Spreadsheet& operator=(const Spreadsheet& rhs);
    Spreadsheet(Spreadsheet&& other) noexcept;
    Spreadsheet& operator=(Spreadsheet&& rhs) noexcept;
    ~Spreadsheet();
    void swap(Spreadsheet& other) noexcept;
    void swap(Spreadsheet& first, Spreadsheet& second) noexcept;
    void setCellAt(const size_t row, const size_t col, int input);
    void setCellAt(const size_t row, const size_t col, double input);
    void setCellAt(const size_t row, const size_t col, std::string input);
    Cell* getCellAt(const size_t row, const size_t col) const;
    size_t getrow_() const;
    size_t getcol_() const;
    void addRow(size_t nRow);
    void removeRow(size_t nRow);
    void addCol(size_t nCol);
    void removeCol(size_t nCol);
    void swapRows(size_t row1, size_t row2);
    void swapColumns(size_t col1, size_t col2);
    void savetoFile(std::ostream& output);  
    void verifyCoordinate(size_t x, size_t y) const;
};

