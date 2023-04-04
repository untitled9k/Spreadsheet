#include "Cell.h"

void Cell::setColor(Color color){
    this->color = color;
}

Cell::Color Cell::getColor() const{
    return this->color;
}

void Cell::reSet(){
    this->color = WHITE;
}

std::string DateCell::getValue() const{
    return std::to_string(m_day) + "/" + std::to_string(m_month) + "/" + std::to_string(m_year);
}

DateCell DateCell::toData(const std::string& str){
    int day = stoi(str.substr(0, 2));
    int month = stoi(str.substr(3, 2));
    int year = stoi(str.substr(6, 4));
    return DateCell(year, month, day);
}

std::string DoubleCell::getValue() const {
    return std::to_string(m_value);
}

void DoubleCell::setValue(const double value){
    this->m_value = value;
}

void DoubleCell::reSet(){
    Cell::reSet();
    this->m_value = 0.0;
}

std::string IntCell::getValue() const {
    return std::to_string(m_value);
}

void IntCell::setValue(const int value){
    this->m_value = value;
}

void IntCell::reSet(){
    Cell::reSet();
    this->m_value = 0.0;
}

std::string StrCell::getValue() const {
    return m_value;
}

void StrCell::setValue(const std::string value){
    this->m_value = std::move(value);
}

void StrCell::reSet(){
    Cell::reSet();
    this->m_value.clear();
}
