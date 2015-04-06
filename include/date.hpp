#pragma once

#include <iostream>
#include <exception>


const int MonthLength[13] = {31,31,28,31,30,31,30,31,31,30,31,30,31};

enum Months { padding,      //  0
              January,      //  1
              February,     //  2
              March,        //  3
              April,        //  4
              May,          //  5
              June,         //  6
              August,       //  7
              September,    //  8
              October,      //  9
              November,     // 10
              December };   // 12

/**
 * \brief The Date class provides useful contexts to abstract a date.
 */
class Date
{
public:
    Date();
    Date(const int d, const int m, const int y);
    ~Date();

    /**
     * \brief valid checks wether the current Date is valid.
     * @return true if the Date is correct. false otherwise.
     */
    bool valid(void) const;

    /**
     * \brief is_leap_year checks id the current year is a leap year.
     * @return true if the Year is leap. false otherwise.
     */
    bool is_leap_year() const;

    int get_day() const;
    int get_month() const;
    int get_year() const;

    void set_day(const int day);
    void set_month(const int month);
    void set_year(const int year);

    /**
     * \brief operator ++ Pre-Increments the current date
     * \pre The actual date must be valid
     * \return The next date.
     */
    Date& operator ++();

    /**
     * \brief operator ++ Post-Increments the current date
     * \pre The actual date must be valid
     * \return The next date.
     */
    Date  operator ++(int);

    /**
     * \brief operator -- Pre-Decrements the current date
     * \pre The actual date must be valid
     * \return The previous date.
     */
    Date& operator --();

    /**
     * \brief operator -- Post-Decrements the current date
     * \pre The actual date must be valid
     * \return The previous date.
     */
    Date  operator --(int);

    /**
     * \brief debug_string Make a string containing the date for debugging pourpouses.
     * \return a std::string of form [day-month-year]
     */
    std::string debug_string() const;

private:
    int day;
    int month;
    int year;

    const int MinDay   = 1;
    const int MaxDay   = 31;
    const int MinMonth = 1;
    const int MaxMonth = 12;
    const int MinYear  = 0;
};

bool operator ==(const Date& lhs, const Date& rhs);
bool operator !=(const Date& lhs, const Date& rhs);
bool operator  <(const Date& lhs, const Date& rhs);
bool operator  >(const Date& lhs, const Date& rhs);
bool operator <=(const Date& lhs, const Date& rhs);
bool operator >=(const Date& lhs, const Date& rhs);

std::ostream& operator <<(std::ostream& os, const Date& rhs);
