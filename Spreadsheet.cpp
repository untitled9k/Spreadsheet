#include "Spreadsheet.h"
#include <iostream>
#include <fstream>
#include <utility>

Spreadsheet::Spreadsheet(size_t row = 0, size_t col = 0): row_{row}, col_{col}
{
    if(row_ > 0 && col_ > 0 ){
        try{
            mCells = new Cell**[row_];
            for (size_t i = 0; i < row_; ++i){
                try{   
                    mCells[i] = new Cell*[col_];
                    for(size_t j = 0; j < col_; ++j)
                        mCells[i][j] = nullptr;
                }
                catch(const std::bad_alloc& ex){
                    std::cout << ex.what() << std::endl;
                    for (size_t i = 0; i < row; ++i){
                        delete[] mCells[i];
                        mCells[i] = nullptr;
                    }
                    delete[] mCells;
                    mCells = nullptr;   
                    row_ = 0;
                    col_ = 0;
                }
            }
        }
        catch(const std::bad_alloc& ex){
            std::cout << ex.what() << std::endl;
            delete[] mCells;
            mCells = nullptr;
            row_ = 0;
            col_ = 0;
        }
    }else
        mCells = nullptr;
}

Spreadsheet::~Spreadsheet(){
    if (mCells != nullptr){
        for (size_t i = 0; i < row_; i++){
            if (mCells[i] != nullptr){
                for (size_t j = 0; j < col_; j++)
                    delete mCells[i][j];
                delete[] mCells[i];
                mCells[i] = nullptr;
            }
        }
        delete[] mCells;
        mCells = nullptr;
    }
}

Spreadsheet::Spreadsheet(const Spreadsheet& src) : row_{src.row_}, col_{src.col_}
{
    mCells = new Cell**[row_];
    if(mCells != NULL){
        for (size_t i = 0; i < row_; ++i)
        {
            mCells[i] = new Cell*[col_];
            if(mCells != NULL){
                for (size_t j = 0; j < col_; ++j)
                {
                    mCells[i][j] = nullptr;
                    if (src.mCells[i][j] != nullptr)
                    {
                        if (typeid(*src.mCells[i][j]) == typeid(DoubleCell)){
                            mCells[i][j] = new DoubleCell{std::stod(src.mCells[i][j]->getValue())};
                        }
                        else if (typeid(*src.mCells[i][j]) == typeid(IntCell)){
                            mCells[i][j] = new IntCell{std::stoi(src.mCells[i][j]->getValue())};
                        }
                        else if (typeid(*src.mCells[i][j]) == typeid(StrCell)){
                            mCells[i][j] = new StrCell{src.mCells[i][j]->getValue()};
                        }
                        else if (typeid(*src.mCells[i][j]) == typeid(DateCell)){
                            mCells[i][j] = new DateCell(DateCell::toData(src.mCells[i][j]->getValue()));
                        }
                    }
                }
            }
            else{
                std::cout << "Bad allocation!" << std::endl;
                for (size_t i = 0; i < row_; ++i)
                    mCells[i] = nullptr;
                row_ = 0;
                col_ = 0;
            } 
        }
    }
    else{
        std::cout << "Bad allocation!" << std::endl;
        mCells = nullptr;
        row_ = 0;
        col_ = 0;
    }
}

Spreadsheet& Spreadsheet::operator=(const Spreadsheet& rhs){
    if (this != &rhs){
        Spreadsheet temp{rhs};
        swap(temp);
    }
    return *this;
}

Spreadsheet::Spreadsheet(Spreadsheet&& other) noexcept : row_{std::move(other.row_)},
    col_{std::move(other.col_)},
    mCells{std::move(other.mCells)}{
    other.mCells = nullptr;
}

Spreadsheet& Spreadsheet::operator=(Spreadsheet&& rhs) noexcept{
    if (this != &rhs){
        swap(rhs);   
	}                                                     
    return *this;
}
void Spreadsheet::swap(Spreadsheet& first, Spreadsheet& second) noexcept{
    first.swap(second);
}

void Spreadsheet::swap(Spreadsheet& other) noexcept{
    swap(*this, other);
}

void Spreadsheet::swapRows(size_t row1, size_t row2){
    if (row1 >= row_ || row2 >= row_){
         std::cout << "Invalid row index" << std::endl;
    }
    std::swap(mCells[row1], mCells[row2]);
}

void Spreadsheet::swapColumns(size_t col1, size_t col2){
    if (col1 >= col_ || col2 >= col_){
        std::cout <<"Column index is out of range"<< std::endl;
    }
    for (size_t i = 0; i < row_; ++i){
        std::swap(mCells[i][col1], mCells[i][col2]);
    }
}
size_t Spreadsheet::getrow_() const{
    return row_;
}

size_t Spreadsheet::getcol_() const{
    return col_;
}

void Spreadsheet::setCellAt(const size_t row, const size_t col, int intcell){
    verifyCoordinate(row,col);
    if(mCells[row][col] == nullptr)
        mCells[row][col] = new IntCell(intcell);
    else{
        delete mCells[row][col];
        mCells[row][col] = nullptr;
    }
}

void Spreadsheet::setCellAt(const size_t row, const size_t col, double doubleCell){
    verifyCoordinate(row,col);
    if(mCells[row][col] == nullptr)
        mCells[row][col] = new DoubleCell(doubleCell);
    else{
        delete mCells[row][col];
        mCells[row][col] = nullptr;
        mCells[row][col] = new DoubleCell(doubleCell);
    }
}

void Spreadsheet::setCellAt(const size_t row, const size_t col, std::string stringcell){
    verifyCoordinate(row,col);
    if(mCells[row][col] == nullptr){
        bool is_date = true;
        for (char c : stringcell) {
            if (!isdigit(c) && c != '-' && c != '/' && c != '.') {
                is_date = false;
                break;
            }
        }
        if(is_date){
            mCells[row][col] = new DateCell(DateCell::toData(stringcell));
        }
        else
            mCells[row][col] = new StrCell(stringcell);
        }
    else{
        delete mCells[row][col];
        mCells[row][col] = nullptr;
        bool is_date = true;
        for (char c : stringcell) {
            if (!isdigit(c) && c != '-' && c != '/' && c != '.') {
                is_date = false;
                break;
            }
        }
        if(is_date){
            mCells[row][col] = new DateCell(DateCell::toData(stringcell));
        }
        else
            mCells[row][col] = new StrCell(stringcell);
    }
    
}

Cell* Spreadsheet::getCellAt(const size_t row, const size_t col) const{
    verifyCoordinate(row,col);
    if(mCells[row][col] != nullptr){
        return mCells[row][col];
    }
    return nullptr;
}

void Spreadsheet::addRow(size_t nRow)
{  
    if (nRow > row_)
        std::cout << "Index out of range";
    Cell*** tempCells = new Cell**[row_ + 1];
    if(tempCells != NULL){
        for(size_t i = 0; i < row_+ 1; ++i){
            if(i < nRow){ 
                tempCells[i] = mCells[i];
            }
            else if (i == nRow){
                tempCells[i] = new Cell*[col_];
                if(mCells != NULL){
                    for(size_t j = 0; j < col_; ++j ){
                        tempCells[i][j] = nullptr;   
                    }
                }
                else{
                    std::cout << "Bad allocation!" << std::endl;
                    for (size_t i = 0; i < row_; ++i)
                        tempCells[i] = nullptr;
                    row_ = 0;
                    col_ = 0;
                }
            }else
                tempCells[i] = mCells[i - 1];
        }
    }
    else{
        std::cout << "Bad allocation!" << std::endl;
        tempCells = nullptr;
        row_ = 0;
        col_ = 0;
    }
    delete[] mCells;
    mCells = tempCells;
    ++row_;      
}

void Spreadsheet::removeRow(size_t nRow){  
    if (nRow > row_)
        std::cout << "Index out of range";
    Cell*** tempCells = new Cell**[row_ - 1];
    if(tempCells != NULL){
        for(size_t i = 0; i < row_; ++i){
            if(i < nRow){
                tempCells[i] = mCells[i];
            }
            else if (i == nRow){
            continue;
            }
            else
            tempCells[i-1] = mCells[i];  
        }
        delete[]mCells;
        mCells = tempCells;
        --row_; 
    }
    else{
        std::cout << "Bad allocation!" << std::endl;
        tempCells = nullptr;
        row_ = 0;
        col_ = 0;
    }   
}

void Spreadsheet::addCol(size_t nCol){
    if(nCol > col_)
        std::cout <<"Invalid column index";
    for (int i = 0; i < row_; ++i){
        Cell** tempCol = new Cell*[ col_ + 1];
        if(tempCol != NULL){
            for (int j = 0; j < col_ + 1; ++j){
                if(j < nCol){
                    tempCol[j] = mCells[i][j];
                }
                else if (j == nCol){
                    tempCol[j] = new StrCell();
                }
                else 
                    tempCol[j] = mCells[i][j - 1];    
            }    
            delete[] mCells[i];
            mCells[i] = tempCol;
        }
    }
    ++col_; 
}

void Spreadsheet::removeCol(size_t nCol)
{
    if(nCol >= col_)
        std::cout <<"Invalid column index";
    for (size_t i = 0; i < row_; ++i){
        Cell** tempCol = new Cell*[col_ - 1];
        if(tempCol != NULL){
            for (size_t j = 0; j < col_; ++j){
            if(j < nCol){
                tempCol[j] = mCells[i][j];
            }
            else if (j == nCol){
                continue;
            }
            else
                tempCol[j-1] = mCells[i][j];    
        }
        delete[] mCells[i];
        mCells[i] = tempCol;
        }
        else{
            std::cout << "Bad allocation!" << std::endl;
            for (size_t i = 0; i < row_; ++i)
                tempCol[i] = nullptr;
            row_ = 0;
            col_ = 0;
        }
    }
    --col_;  
}

void Spreadsheet::savetoFile(std::ostream& output){
    for(int i = 0; i < row_; ++i){
        for(int j = 0; j < col_;++j){
            output << (*mCells[i][j]).getValue() << "\t";
        }
        output << "\n";
    }
}

void Spreadsheet::verifyCoordinate(size_t row, size_t col) const{
    if (row >= row_ || col >= col_) 
        throw std::invalid_argument("Invalid row or column size");
}











