#include "date.hpp"

Date::Date()
    : day{0}, month{0}, year{0}
{}

Date::Date(const int d, const int m, const int y)
    : day{d}, month{m}, year{y}
{}

Date::~Date()
{}

bool Date::valid() const
{
    if (year < MinYear) return false;
    if (month > MaxMonth or month < MinMonth) return false;
    if (day > MaxDay or day < MinDay) return false;
    if ((day == MaxDay) and (month == Months::February  or
                             month == Months::April     or
                             month == Months::June      or
                             month == Months::September or
                             month == Months::November))
        return false;
    if (day == 30 and month == Months::February) return false;
    if ((day == 29 and month == Months::February) and not is_leap_year()) return false;
    return true;
}

bool Date::is_leap_year() const
{
    if (year % 4 != 0) return false;
    else if (year % 100 == 0) return true;
    else if (year % 400 != 0) return false;
    else return true;
}

int Date::get_day() const
{
    return day;
}

int Date::get_month() const
{
    return month;
}

int Date::get_year() const
{
    return year;
}

void Date::set_day(const int day)
{
    this->day = day;
}

void Date::set_month(const int month)
{
    this->month = month;
}

void Date::set_year(const int year)
{
    this->year = year;
}

Date& Date::operator++()
{
    day++;
    if (day > MaxDay) {
        day = MinDay;
        month++;
        if (month > MaxMonth) {
            month = MinMonth;
            year++;
        }
    }
    return *this;
}

Date  Date::operator++(int)
{
    return ++(*this);
}

Date& Date::operator--()
{
    day--;
    if (day < MinDay) {
        day = MonthLength[month-1];
        day = (month-1 == Months::February and is_leap_year()) ? day+1 : day;
        month--;
        if (month < MinMonth) {
            month = MaxMonth;
            year--;
        }
    }
    return *this;
}

Date  Date::operator--(int)
{
    return --(*this);
}

std::string Date::debug_string() const
{
    std::string daystr   = std::to_string(day);
    std::string monthstr = std::to_string(month);
    std::string yearstr  = std::to_string(year);

    return "["+daystr+"-"+monthstr+"-"+yearstr+"]";
}

// Out of class functions:

bool operator ==(const Date& lhs, const Date& rhs)
{
    if ((lhs.get_day()   == rhs.get_day())   and
        (lhs.get_month() == rhs.get_month()) and
        (lhs.get_year()  == rhs.get_year())) return true;
    return false;
}

bool operator !=(const Date& lhs, const Date& rhs)
{
    return not (lhs == rhs);
}

bool operator <(const Date& lhs, const Date& rhs)
{
    if ((lhs.get_year()  < rhs.get_year()) or
        (lhs.get_year() == rhs.get_year() and lhs.get_month() <  rhs.get_month()) or
        (lhs.get_year() == rhs.get_year() and lhs.get_month() == rhs.get_month() and lhs.get_day() < rhs.get_day()))
        return true;
    return false;
}

bool operator >(const Date& lhs, const Date& rhs)
{
    if ((lhs.get_year()  > rhs.get_year()) or
        (lhs.get_year() == rhs.get_year() and lhs.get_month() >  rhs.get_month()) or
        (lhs.get_year() == rhs.get_year() and lhs.get_month() == rhs.get_month() and lhs.get_day() > rhs.get_day()))
        return true;
    return false;
}

bool operator <=(const Date& lhs, const Date& rhs)
{
    return not (lhs > rhs);
}

bool operator >=(const Date& lhs, const Date& rhs)
{
    return not (lhs < rhs);
}

std::ostream& operator<<(std::ostream& os, const Date& rhs)
{
    return os << rhs.debug_string();
}
