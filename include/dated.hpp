#pragma once

#include <vector>
#include <utility>
#include <date.hpp>


template <typename T>
class Dated
{
public:
    Dated();
    ~Dated();

    Dated(const Dated<T>& rhs);
    Dated<T>& operator =(const Dated<T>& rhs);

    Dated(Dated<T>&& other);
    Dated<T>& operator =(Dated<T>&& other);

    bool empty() const;
    int size() const;
    Date date_at(const int t) const;
    T element_at(const int t) const;
    T element_at(const Date& d) const;

    bool contains(const Date& d) const;
    //T current_element_at(const Date& d) const;

    std::vector<Date>::iterator first_date() const;
    std::vector<Date>::iterator last_date() const;
    typename std::vector<T>::iterator first_element() const;
    typename std::vector<T>::iterator last_element() const;

    const std::vector<Date>& get_dates();
    const std::vector<T>& get_elements();

    int index_of_date(const Date& d) const;
    //int index_of_last_date_before(const date& d) const; // these are useful functions
    //int index_of_first_date_after(const date& d) const;

    //void remove(const date&);         // removing one or more elements
    //void remove_between_including_end_points(const date&, const date&);
    //void remove_between(const date&, const date&);
    //void remove_before(const date&);
    //void remove_after(const date&);

private:
    std::vector<Date> dates;
    std::vector<T> elements;
};

template <typename T>
Dated<T>::Dated()
{}

template <typename T>
Dated<T>::~Dated()
{}

template <typename T>
Dated<T>::Dated(const Dated<T>& rhs)
    : dates{rhs.dates},
      elements{rhs.elements}
{}

template <typename T>
Dated<T>& Dated<T>::operator=(const Dated<T>& rhs)
{
    if (this == &rhs) // self assign check
        return *this;

    dates    = rhs.dates;
    elements = rhs.elements;

    return *this;
}

template <typename T>
Dated<T>::Dated(Dated<T>&& other)
    : dates{std::move(other.dates)},
      elements{std::move(other.elements)}
{}

template <typename T>
Dated<T>& Dated<T>::operator=(Dated<T>&& other)
{
    if (this == &other) // self assign check
        return *this;

    dates    = std::move(other.dates);
    elements = std::move(other.elements);

    return *this;
}

template <typename T>
bool Dated<T>::empty() const
{
    return dates.size() == 0;
}

template <typename T>
int Dated<T>::size() const
{
    return static_cast<int>(dates.size());
}

template <typename T>
Date Dated<T>::date_at(const int t) const
{
    if (t < 0 or t >= size())
        throw std::out_of_range("index 't' out of range");
    return dates[t];
}

template <typename T>
T Dated<T>::element_at(const int t) const
{
    if (t < 0 or t >= size())
        throw std::out_of_range("index 't' out of range");
    return elements[t];
}

template <typename T>
T Dated<T>::element_at(const Date& d) const
{
    if (not contains(d))
        throw std::invalid_argument("Date 'd' not pressent");
    return elements[index_of_date(d)];
}

template <typename T>
bool Dated<T>::contains(const Date &d) const
{
    return std::binary_search(first_date(), last_date(), d);
}

template <typename T>
std::vector<Date>::iterator Dated<T>::first_date() const
{
    return dates.begin();
}

template <typename T>
std::vector<Date>::iterator Dated<T>::last_date() const
{
    return dates.end();
}

template <typename T>
typename std::vector<T>::iterator Dated<T>::first_element() const
{
    return elements.begin();
}

template <typename T>
typename std::vector<T>::iterator Dated<T>::last_element() const
{
    return elements.end();
}

template <typename T>
const std::vector<Date>& Dated<T>::get_dates()
{
    return dates;
}

template <typename T>
const std::vector<T>& Dated<T>::get_elements()
{
    return elements;
}

template <typename T>
int Dated<T>::index_of_date(const Date& d) const
{
    if (not d.valid()) throw std::invalid_argument("Date 'd' not valid");
    if (not contains(d)) throw std::invalid_argument("Date 'd' not present");
    for (int t = 0; t < size(); ++t)
        if (dates[t] == d) return t;
    return 0;
}


// Out of class functions:
