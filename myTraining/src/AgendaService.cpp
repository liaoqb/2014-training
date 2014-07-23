  // <Copyright liaoqb> [Copyright 2014.7.1]
#include"AgendaService.h"
#include <list>
#include <string>

AgendaService::AgendaService() {
  startAgenda();
}

AgendaService::~AgendaService() {
  quitAgenda();
  if (storage_ != NULL) {
    delete storage_;
  }

  storage_ = NULL;
}

bool AgendaService::userLogIn(std::string userName, std::string password) {
  auto f = [&userName, &password](const User& user) -> bool {
    if (user.getName() == userName && user.getPassword() == password) {
      return true;
    } else {
      return false;
    }
  };

  if (!(storage_ -> getInstance() -> queryUser(f)).empty()) {
    return true;
  } else {
    return false;
  }
}

bool AgendaService::userRegister(std::string userName, std::string password,
    std::string email, std::string phone) {
  auto f = [&userName](const User& user) -> bool {
    if (user.getName() == userName) {
      return true;
    } else {
      return false;
    }
  };

  if ((storage_ -> getInstance() -> queryUser(f)).empty()) {
    User user(userName, password, email, phone);
    storage_ -> getInstance() -> createUser(user);
    return true;
  } else {
    return false;
  }
}

bool AgendaService::deleteUser(std::string userName, std::string password) {
  auto f = [&userName, &password](const User& user) ->
    bool {  // function to control user
    if (user.getName() == userName && user.getPassword() == password) {
      return true;
    } else {
      return false;
    }
  };

  /*
  auto t = [&userName](const Meeting& meeting) -> bool {
    if (meeting.getSponsor() == userName) {  // if sponsor meeting is null
        // maybe destroy the rules, take care
      return true;
    } else {
      return false;
    }
  };
  */

  if (storage_ ->getInstance() -> deleteUser(f) != 0) {
    auto dm = [&userName](const Meeting& meeting) -> bool {
      if (meeting.getParticipator() == userName ||
          meeting.getSponsor() == userName) {
        return true;
      } else {
        return false;
      }
    };

    storage_ ->getInstance() ->deleteMeeting(dm);

    return true;
  } else {
    return false;
  }
}

std::list<User> AgendaService::listAllUsers(void) {
  auto f = [](const User& user) -> bool {
    user.getName();  // ignored warning
    return true;
  };

  return storage_ -> getInstance() -> queryUser(f);
}

bool AgendaService::createMeeting(std::string userName, std::string title,
    std::string participator, std::string startDate,
    std::string endDate) {
  Date sdate = Date::stringToDate(startDate);
  Date edate = Date::stringToDate(endDate);

  if (!Date::isValid(sdate) || !Date::isValid(edate) || sdate >= edate) {
    return false;
  } else {
    auto querySponsor = [&userName](const User& user) -> bool {
      if (user.getName() == userName) {
        return true;
      } else {
        return false;
      }
    };

    auto queryPartticipator = [&participator](const User& user) -> bool {
      if (user.getName() == participator) {
        return true;
      } else {
        return false;
      }
    };

    auto queryTimeConflict = [&userName,
         &participator, &sdate, &edate, &title
         ](const Meeting& meeting) -> bool {
      if (meeting.getSponsor() == userName || meeting.getParticipator()
          == participator || meeting.getSponsor() == participator ||
          meeting.getParticipator() == userName) {
        if (meeting.getTitle() == title) {
          return true;
        } else if (!(meeting.getStartDate() >= edate || meeting.getEndDate() <=
            sdate)) {
          return true;
        } else {
          return false;
        }
      } else {
        return false;
      }
    };

    if (!(storage_ ->getInstance() ->queryUser(querySponsor)).empty()
        && !(storage_ ->getInstance() ->queryUser(queryPartticipator)).empty()
        && (storage_ ->getInstance() ->
        queryMeeting(queryTimeConflict)).empty()) {
      Meeting meeting(userName, participator, sdate, edate, title);
      storage_ ->getInstance() ->createMeeting(meeting);
      return true;
    } else {
      return false;
    }
  }
}

std::list<Meeting> AgendaService::meetingQuery(std::string
    userName, std::string title) {
  auto f = [&userName, &title](const Meeting& meeting) -> bool {
    if (meeting.getSponsor() == userName ||
        meeting.getParticipator() == userName) {
      if (meeting.getTitle() == title) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  };

  return storage_ ->getInstance() ->queryMeeting(f);
}


  // maybe wrong, take care
std::list<Meeting> AgendaService::meetingQuery(std::string userName,
    std::string startDate, std::string endDate) {
  Date sdate = Date::stringToDate(startDate);
  Date edate = Date::stringToDate(endDate);

  auto f = [&userName, &sdate, &edate](const Meeting& meeting) -> bool {
    if (!Date::isValid(sdate) || !Date::isValid(edate) || sdate >= edate) {
      return false;
    } else if (meeting.getSponsor() == userName || meeting.getParticipator()
        == userName) {
      if (!(meeting.getStartDate() > edate || meeting.getEndDate()
            < sdate)) {
        return true;
      } else {
        return false;
      }
    } else {
      return false;
    }
  };

  return storage_ ->getInstance() ->queryMeeting(f);
}

std::list<Meeting> AgendaService::listAllMeetings(std::string userName) {
  auto f = [&userName](const Meeting& meeting) -> bool {
    if (meeting.getSponsor() == userName ||
        meeting.getParticipator() == userName) {
      return true;
    } else {
      return false;
    }
  };

  return storage_ ->getInstance() ->queryMeeting(f);
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(std::string userName) {
  auto f = [&userName](const Meeting& meeting) -> bool {
    if (meeting.getSponsor() == userName) {
      return true;
    } else {
      return false;
    }
  };

  return storage_ ->getInstance() ->queryMeeting(f);
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(std::string
    userName) {
  auto f = [&userName](const Meeting& meeting) -> bool {
    if (meeting.getParticipator() == userName) {
      return true;
    } else {
      return false;
    }
  };

  return storage_ ->getInstance() ->queryMeeting(f);
}

bool AgendaService::deleteMeeting(std::string userName, std::string title) {
  auto f = [&userName, &title](const Meeting& meeting) -> bool {
    if (meeting.getSponsor() == userName && meeting.getTitle() == title) {
      return true;
    } else {
      return false;
    }
  };

  return storage_ ->getInstance() ->deleteMeeting(f);
}

bool AgendaService::deleteAllMeetings(std::string userName) {
  auto f = [&userName](const Meeting& meeting) -> bool {
    if (meeting.getSponsor() == userName) {
      return true;
    } else {
      return false;
    }
  };

  return storage_ ->getInstance() ->deleteMeeting(f);
}

void AgendaService::startAgenda() {
  storage_ = Storage::getInstance();
  storage_ ->getInstance() ->sync();
}

void AgendaService::quitAgenda() {
  storage_ ->getInstance() ->sync();
}
