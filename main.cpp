#include <iostream>
#include <string>
#include <fstream>
#include "Spreadsheet.h"
#include <utility>

int main()
{ 
    std::ofstream file("spreadsheet.txt");
    if(!file.is_open()){
        std::cout << "ERROR! File didn't open";
        return 1;
    }
    Spreadsheet sh(3,3);
    sh.setCellAt(0, 0, "Hello");
    sh.setCellAt(0, 1, 9);
    sh.setCellAt(0, 2, 6.66);
    sh.setCellAt(1, 0,"world");
    sh.setCellAt(1, 1, 11);
    sh.setCellAt(1, 2, 9.9);
    sh.setCellAt(2, 0, "Kate");
    sh.setCellAt(2, 1, "dw");
    sh.setCellAt(2, 2, "09.05.1995");
    sh.getCellAt(0, 0)->setColor(Cell::RED);
    sh.getCellAt(2, 2)->setColor(Cell::YELLOW);
    sh.addRow(2);
    sh.addCol(1);
    sh.removeCol(1);
    sh.removeRow(2);
    sh.swapRows(1,2);
    sh.swapColumns(2,0);
    Cell* cell;
    for (int i = 0; i < sh.getrow_(); ++i) {
        for (int j = 0; j < sh.getcol_(); ++j) {
            cell = sh.getCellAt(i, j);
            if(cell != nullptr)
                std::cout << cell->getValue() << cell->getColor() << "\t";
        }
        std::cout << std::endl;
        
    }
    
   sh.savetoFile(file);
   file.close();
   cell = nullptr;
   delete cell;

}
