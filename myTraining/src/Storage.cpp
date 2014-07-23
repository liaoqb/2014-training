  // <Copyright liaoqb> [Copyright 2014.6.30]
#include"Storage.h"
#include <algorithm>
#include <functional>
#include <fstream>
#include <list>
#include <string>
#include <cmath>

  // the file name
const char* fpath = "agenda.data";

  // read data from the file
Storage::Storage() {
  readFromFile(fpath);
}

Storage* Storage::instance_ = NULL;

  // instance function
Storage* Storage::getInstance() {
  if (instance_ == NULL) {
    instance_ = new Storage();
  }

  return instance_;
}

Storage::~Storage() {
  /*
  if (instance_ != NULL) {
    delete instance_;
  }
  */
  instance_ = NULL;

    // write to file when exiting
  writeToFile(fpath);
}

  // creat user succeed!
void Storage::createUser(const User& user) {
  userList_.push_back(user);
}

std::list<User> Storage::queryUser(std::function<bool(const User&)> filter) {
  std::list<User> users;

  for_each(userList_.begin(), userList_.end(), [&filter, &users](User& user) {
    if (filter(user)) {
      users.push_back(user);
    }
  });  // template function

  return users;
}

int Storage::updateUser(std::function<bool(const User&)> filter,
    std::function<void(User&)> switcher) {
  int count = 0;

  for_each(userList_.begin(), userList_.end(), [&filter,
      &switcher, &count](User& user) {
    if (filter(user)) {
      switcher(user);
      count++;
    }
  });

  return count;
}

int Storage::deleteUser(std::function<bool(const User&)> filter) {
  int count = 0;

  [&filter, &count, this](std::list<User>::iterator biter,
      std::list<User>::iterator eiter) {
    std::list<User>::iterator iter = biter;

    while (iter != eiter) {
      if (filter(*iter)) {
        iter = userList_.erase(iter);
        count++;
      } else {
        iter++;
      }
    }
  } (userList_.begin(), userList_.end());

  return count;
}

void Storage::createMeeting(const Meeting& meeting) {
  meetingList_.push_back(meeting);
}

std::list<Meeting> Storage::queryMeeting(
  std::function<bool(const Meeting&)> filter) {
  std::list<Meeting> meetings;

  for_each(meetingList_.begin(), meetingList_.end(),
      [&filter, &meetings](Meeting& meeting) {
    if (filter(meeting)) {
      meetings.push_back(meeting);
    }
  });

  return meetings;
}

int Storage::updateMeeting(std::function<bool(const Meeting&)> filter,
    std::function<void(Meeting&)> switcher) {
  int count = 0;

  for_each(meetingList_.begin(), meetingList_.end(),
      [&filter, &switcher, &count](Meeting& meeting) {
    if (filter(meeting)) {
      switcher(meeting);
      count++;
    }
  });

  return count;
}

int Storage::deleteMeeting(std::function<bool(const Meeting&)>
    filter) {
  int count = 0;

  [&filter, &count, this](std::list<Meeting>::iterator biter,
      std::list<Meeting>::iterator eiter) {
    std::list<Meeting>::iterator iter = biter;

    while (iter != eiter) {
      if (filter(*iter)) {
        iter = meetingList_.erase(iter);
        count++;
      } else {
        iter++;
      }
    }
  } (meetingList_.begin(), meetingList_.end());

  return count;
}

  // store message everytime
bool Storage::sync(void) {
  if (userList_.empty() && meetingList_.empty()) {
    return readFromFile(fpath);
  } else {
    return writeToFile(fpath);
  }
}

  // read from file
bool Storage::readFromFile(const char *fpath) {
  if (fpath == NULL) {
    return false;
  } else {
    std::ifstream fin;

    fin.open(fpath, std::ios::in);

      // if no exist
    if (!fin.is_open())
      return false;

    if (fin.peek() != EOF) {
      char buffer[200];

      fin.getline(buffer, 195, '}');

        // split first
      std::string userStr = buffer;
      int userNumber = 0;

      for (int i = userStr.size() - 1; i >= 0; --i) {
        if (userStr[i] == ':')
          break;

          // find number
        userNumber += (userStr[i] - 48) *
        static_cast<int>(pow(10, userStr.size() - 1 - i));
      }  // the total number of user

      for (int i = 0; i < userNumber; ++i) {
        std::string name = "";
        std::string password = "";
        std::string email = "";
        std::string phone = "";
        std::string temp = "";

          // split name
        fin.getline(buffer, 195, ':');
        fin.getline(buffer, 195, ',');

        temp = buffer;

        for (unsigned int i = 1; i < temp.size() - 1; ++i) {
          name += temp[i];
        }

          // split password
        fin.getline(buffer, 195, ':');
        fin.getline(buffer, 195, ',');

        temp = buffer;

        for (unsigned int i = 1; i < temp.size() - 1; ++i) {
          password += temp[i];
        }

        fin.getline(buffer, 195, ':');
        fin.getline(buffer, 195, ',');

        temp = buffer;

        for (unsigned int i = 1; i < temp.size() - 1; ++i) {
          email += temp[i];
        }

        if (email == "NULL")
          email = "";

        fin.getline(buffer, 195, ':');
        fin.getline(buffer, 195, '}');

        temp = buffer;

        for (unsigned int i = 1; i < temp.size() - 1; ++i) {
          phone += temp[i];
        }

        if (phone == "NULL")
          phone = "";

        User user(name, password, email, phone);
        userList_.push_back(user);
      }
    }

    if (fin.peek() != EOF) {
      char buffer[200];

      fin.getline(buffer, 195, '}');

      std::string meetingStr = buffer;
      int meetingNumber = 0;

      for (int i = meetingStr.size() - 1; i >= 0; --i) {
        if (meetingStr[i] == ':')
          break;

        meetingNumber += (meetingStr[i] - 48) *
        static_cast<int>(pow(10, meetingStr.size() - 1 - i));
      }  // the total number of meeting

      for (int i = 0; i < meetingNumber; ++i) {
        std::string sponsor = "";
        std::string participator = "";
        std::string sdate = "";
        std::string edate = "";
        std::string title = "";
        std::string temp = "";

        fin.getline(buffer, 195, ':');
        fin.getline(buffer, 195, ',');

        temp = buffer;

        for (unsigned int i = 1; i < temp.size() - 1; ++i) {
          sponsor += temp[i];
        }

        fin.getline(buffer, 195, ':');
        fin.getline(buffer, 195, ',');

        temp = buffer;

        for (unsigned int i = 1; i < temp.size() - 1; ++i) {
          participator += temp[i];
        }

        fin.getline(buffer, 195, ':');
        fin.getline(buffer, 195, ',');

        temp = buffer;

        for (unsigned int i = 1; i < temp.size() - 1; ++i) {
          sdate += temp[i];
        }

        fin.getline(buffer, 195, ':');
        fin.getline(buffer, 195, ',');

        temp = buffer;

        for (unsigned int i = 1; i < temp.size() - 1; ++i) {
          edate += temp[i];
        }

        fin.getline(buffer, 195, ':');
        fin.getline(buffer, 195, '}');

        temp = buffer;

        for (unsigned int i = 1; i < temp.size() - 1; ++i) {
          title += temp[i];
        }

        Meeting meeting(sponsor, participator, Date::stringToDate(sdate),
        Date::stringToDate(edate), title);
        meetingList_.push_back(meeting);
      }
    }

  fin.close();

  return true;
  }
}

bool Storage::writeToFile(const char *fpath) {
  if (fpath == NULL) {
    return false;
  } else {
    std::ofstream fout;

    fout.open(fpath, std::ios::out);

    if (!fout.is_open())
      return false;

      // take care of the string
    fout << "{collection:\"User\",total:" << userList_.size() << "}\n";

    for (std::list<User>::iterator iter = userList_.begin();
         iter != userList_.end(); ++iter) {
      fout << "{name:\"" << iter -> getName()
           << "\",password:\"" << iter -> getPassword()
           << "\",email:\"";

      if (iter -> getEmail() == "") {
        fout << "NULL";
      } else {
        fout << iter -> getEmail();
      }

      fout << "\",phone:\"";

      if (iter -> getPhone() == "") {
        fout << "NULL\"}\n";
      } else {
        fout << iter -> getPhone() << "\"}\n";
      }
    }

    fout << "{collection:\"Meeting\",total:" << meetingList_.size() << "}\n";

    for (std::list<Meeting>::iterator iter =
         meetingList_.begin();
         iter != meetingList_.end(); ++iter) {
      fout << "{sponsor:\"" << iter -> getSponsor()
           << "\",participator:\""
           << iter -> getParticipator() << "\",sdate:\""
           << Date::dateToString(iter -> getStartDate())
           << "\",edate:\"" << Date::dateToString(iter ->
              getEndDate()) << "\",title:\""
           << iter -> getTitle() << "\"}\n";
    }

    fout.close();

    return true;
  }
}
