#include <string>

class Cell{
public:
    enum Color {WHITE, RED, BLUE, YELLOW};
    virtual std::string getValue() const = 0;
    void setColor(Color color);
    Color getColor() const;
    virtual void reSet();
    virtual ~Cell(){}; 
protected:
    Cell() = default;
private:
    Color color = WHITE;
};

class DateCell : public Cell {
    public:
        DateCell(int day, int month, int year) : m_day(day), m_month(month), m_year(year) {}
        std::string getValue() const override;
        static DateCell toData(const std::string& str);
        ~DateCell() {};
    private:
        int m_day;
        int m_month;
        int m_year;
};

class DoubleCell : public Cell {
    public:
        DoubleCell(){m_value = 0.0;};
        DoubleCell(double value) : m_value{value} {};
        std::string getValue() const override;
        void setValue(const double value);
        void reSet() override;
        ~DoubleCell(){};
    private:
        double m_value;
};

class IntCell : public Cell {
    public:
        IntCell(){m_value = 0;};
        IntCell(int value) : m_value{value} {};
        std::string getValue() const override;
        void setValue(const int value);
        void reSet() override;
        ~IntCell(){};
    private:
        int m_value;
};

class StrCell : public Cell {
    public:
        StrCell(){};
        StrCell(std::string value) : m_value{std::move(value)} {};
        std::string getValue() const override;
        void setValue(const std::string value);
        void reSet() override;
        ~StrCell(){};
    private:
        std::string m_value;
};