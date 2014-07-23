  // <Copyright liaoqb> [Copyright 2014.6.30]
#include"Date.h"
#include <string>
#include <sstream>

  // init class
Date::Date() {
  year_ = month_ = day_ = hour_ = minute_ = 0;
}

Date::Date(int y, int m, int d, int h, int mi) {
  year_ = y;
  month_ = m;
  day_ = d;
  hour_ = h;
  minute_ = mi;
}

int Date::getYear(void) const {
  return year_;
}  // return year

void Date::setYear(int year) {
  year_ = year;
}  // set year

int Date::getMonth(void) const {
  return month_;
}

void Date::setMonth(int month) {
  month_ = month;
}

int Date::getDay(void) const {
  return day_;
}

void Date::setDay(int day) {
  day_ = day;
}

int Date::getHour(void) const {
  return hour_;
}

void Date::setHour(int hour) {
  hour_ = hour;
}

int Date::getMinute(void) const {
  return minute_;
}

void Date::setMinute(int minute) {
  minute_ = minute;
}

  // detect the class wheather valid
bool Date::isValid(Date date) {
  if (date.year_ > 9999 || date.year_ < 1000) {
    return false;
  } else if (date.month_ > 12 || date.month_ < 0) {
    return false;
  } else if (date.hour_ > 23 || date.hour_ < 0) {
    return false;
  } else if (date.minute_ > 59 || date.minute_ < 0) {
    return false;
  } else {
    if (date.day_ <= 0) {
      return false;
    } else {
      int p[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
      int r[13] = {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

      if (date.year_ % 400 == 0 || (date.year_ % 4 == 0 &&
          date.year_ % 100 != 0)) {
        if (r[date.month_] < date.day_) {
          return false;
        }
      } else {
        if (p[date.month_] < date.day_) {
          return false;
        }
      }
    }

    return true;
  }
}

  // convert string to class Date
Date Date::stringToDate(std::string dateString) {
  Date date;

  date.year_ = (dateString[0] - '0') * 1000 + (dateString[1] - '0') * 100 +
  (dateString[2] - '0') * 10 + (dateString[3] - '0');

  date.month_ = (dateString[5] - '0') * 10 + (dateString[6] - '0');
  date.day_ = (dateString[8] - '0') * 10 + (dateString[9] - '0');
  date.hour_ = (dateString[11] - '0') * 10 + (dateString[12] - '0');
  date.minute_ = (dateString[14] - '0') * 10 + (dateString[15] - '0');

  return date;
}

  // convert class Date to string
std::string Date::dateToString(Date date) {
  std::string str = "";
  std::stringstream temp;

  temp << date.year_;
  temp << '-';

  if (date.month_ < 10) {
    temp << '0';
  }
  temp << date.month_;
  temp << '-';

  if (date.day_ < 10) {
    temp << '0';
  }
  temp << date.day_;
  temp << '/';

  if (date.hour_ < 10) {
    temp << '0';
  }
  temp << date.hour_;
  temp << ':';

  if (date.minute_ < 10) {
    temp << '0';
  }
  temp << date.minute_;

  str += temp.str();

  return str;
}

  // =
Date& Date::operator=(const Date& date) {
  year_ = date.year_;
  month_ = date.month_;
  day_ = date.day_;
  hour_ = date.hour_;
  minute_ = date.minute_;

  return *this;
}

  // equal
bool Date::operator==(const Date& date) const {
  return (year_ == date.year_ && month_ == date.month_ &&
      day_ == date.day_ && hour_ == date.hour_ && minute_ == date.minute_);
}

bool Date::operator>(const Date& date) const {
  if (year_ > date.year_) {
    return true;
  } else if (year_ == date.year_ && month_ > date.month_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_
      && day_ > date.day_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_ &&
      day_ == date.day_ && hour_ > date.hour_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_ &&
      day_ == date.day_ && hour_ == date.hour_ &&
      minute_ > date.minute_) {
    return true;
  } else {
    return false;
  }
}

bool Date::operator<(const Date& date) const {
  if (year_ < date.year_) {
    return true;
  } else if (year_ == date.year_ && month_ < date.month_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_
      && day_ < date.day_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_ &&
      day_ == date.day_ && hour_ < date.hour_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_ &&
      day_ == date.day_ && hour_ == date.hour_ &&
      minute_ < date.minute_) {
    return true;
  } else {
    return false;
  }
}

bool Date::operator>=(const Date& date) const {
  if (year_ > date.year_) {
    return true;
  } else if (year_ == date.year_ && month_ > date.month_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_
      && day_ > date.day_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_ &&
      day_ == date.day_ && hour_ > date.hour_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_ &&
      day_ == date.day_ && hour_ == date.hour_ &&
      minute_ >= date.minute_) {
    return true;
  } else {
    return false;
  }
}

bool Date::operator<=(const Date& date) const {
  if (year_ < date.year_) {
    return true;
  } else if (year_ == date.year_ && month_ < date.month_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_
      && day_ < date.day_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_ &&
      day_ == date.day_ && hour_ < date.hour_) {
    return true;
  } else if (year_ == date.year_ && month_ == date.month_ &&
      day_ == date.day_ && hour_ == date.hour_ &&
      minute_ <= date.minute_) {
    return true;
  } else {
    return false;
  }
}
