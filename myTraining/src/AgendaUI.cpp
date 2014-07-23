  // <Copyright liaoqb> [Copyright 2014.7.1]
#include"AgendaUI.h"
#include <string>
#include <iomanip>
#include <list>

AgendaUI::AgendaUI() {
  userName_ = "";
  userPassword_ = "";

  startAgenda();
}

void AgendaUI::startAgenda(void) {
  std::cout << "------------------------Agenda-----------------\n"
            << "Action :\n"
            << "l  - log in Agenda by user name and password\n"
            << "r  - register an Agenda account\n"
            << "q  - quit Agenda\n"
            << "-----------------------------------------------\n\n";

  agendaService_.startAgenda();
}

void AgendaUI::OperationLoop(void) {
  std::string op = "";
  do {
    if (userName_ == "") {
      std::cout << "Agenda : ~$ ";
    } else {
      std::cout << "Agenda@" << userName_ << " : # ";
    }

    op = getOperation();
  } while (!executeOperation(op));
}

std::string AgendaUI::getOperation() {
  std::string op;

  std::cin >> op;
  std::cout << std::endl;

  return op;
}

bool AgendaUI::executeOperation(std::string op) {
  if (op == "l") {
    userLogIn();
    return true;
  } else if (op == "r") {
    userRegister();
    return true;
  } else if (op == "q") {
    quitAgenda();
    return true;
  } else if (op == "o") {
    userLogOut();
    return true;
  } else if (op == "dc") {
    deleteUser();
    return true;
  } else if (op == "lu") {
    listAllUsers();
    return true;
  } else if (op == "cm") {
    createMeeting();
    return true;
  } else if (op == "la") {
    listAllMeetings();
    return true;
  } else if (op == "las") {
    listAllSponsorMeetings();
    return true;
  } else if (op == "lap") {
    listAllParticipateMeetings();
    return true;
  } else if (op == "qm") {
    queryMeetingByTitle();
    return true;
  } else if (op == "qt") {
    queryMeetingByTimeInterval();
    return true;
  } else if (op == "dm") {
    deleteMeetingByTitle();
    return true;
  } else if (op == "da") {
    deleteAllMeetings();
    return true;
  } else {
    return false;
  }
}

void AgendaUI::userLogIn(void) {
  std::string name, password;
  std::cout << "[log in] [user name] [password]\n" << "[log in] ";
  std::cin >> name >> password;
  if (agendaService_.userLogIn(name, password)) {
    std::cout << "[log in] succeed!\n"
              << "------------------------Agenda---------------\n"
              << "Action :\n"
              << "o  - log out Agenda\n"
              << "dc  - delete Agenda account\n"
              << "lu  - list all Agenda user\n"
              << "cm  - create a meeting\n"
              << "la  - list all meetings\n"
              << "las  - list all sponsor meetings\n"
              << "lap  - list all participator meetings\n"
              << "qm  - query meeting by title\n"
              << "qt  - query meeting by time interval\n"
              << "dm  - delete meeting by title\n"
              << "da  - delete all meetings\n"
              << "---------------------------------------------\n";
    userName_ = name;
    userPassword_ = password;
  } else {
    std::cout << "[error] log in fail!\n";
  }
  OperationLoop();
}

void AgendaUI::userRegister(void) {
  std::cout << "[register] [user name] [password] [email] [phone]\n"
            << "[registor] ";
  std::string name, password, email, phone;
  std::cin >> name >> password >> email >> phone;
  if (agendaService_.userRegister(name, password, email, phone)) {
    std::cout << "[register] succeed!\n";
  } else {
    std::cout << "[error] register fail!\n";
  }
  OperationLoop();
}

void AgendaUI::quitAgenda(void) {
  agendaService_.quitAgenda();
}

void AgendaUI::userLogOut(void) {
  std::cout << "-----------------------Agenda------------------\n"
            << "Action :\n"
            << "l - log in Agenda by user name and password\n"
            << "r - register an Agenda account\n"
            << "q - quit Agenda\n"
            << "-----------------------------------------------\n";
  userName_ = "";
  userPassword_ = "";
  OperationLoop();
}

void AgendaUI::deleteUser(void) {
  if (agendaService_.deleteUser(userName_, userPassword_)) {
    std::cout << "[delete agenda account] succeed!\n";
    userName_ = "";
    userPassword_ = "";
  } else {
    std::cout << "[error] delete agenda account fail!\n";
  }
  OperationLoop();
}

void AgendaUI::listAllUsers(void) {
  std::cout << "[list all users]\n\n"
            << "name      email               phone\n";
  std::list<User> users = agendaService_.listAllUsers();
  std::list<User>::iterator iter = users.begin();
  for (; iter != users.end(); iter++) {
    std::cout << std::left << std::setw(10) << iter->getName()
              << std::setw(20) << iter->getEmail() << std::setw(10)
              << iter->getPhone() << std::endl;
  }
  OperationLoop();
}

void AgendaUI::createMeeting(void) {
  std::string title, participator, stime, etime;
  std::cout << "[create meeting] [title] [participator] "
            << "[start time<yyyy-mm-dd/hh:mm>] "
            << "[end time<yyyy-mm-dd/hh:mm>]\n"
            << "[create meeting] ";

  std::cin >> title >> participator >> stime >> etime;

  if (agendaService_.createMeeting(userName_, title,
      participator, stime, etime)) {
    std::cout << "[create meeting] succeed!\n\n";
  } else {
    std::cout << "[create meeting] fail!\n\n";
  }
  OperationLoop();
}

void AgendaUI::listAllMeetings(void) {
  std::cout << "[list all meetings]\n\n";
  std::cout << "title     sponsor   participator   start time"
            << "          end time\n";

  std::list<Meeting> meetings = agendaService_.listAllMeetings(userName_);
  printMeetings(meetings);

  OperationLoop();
}

void AgendaUI::listAllSponsorMeetings(void) {
  std::cout << "[list all sponsor meetings]\n\n";
  std::cout << "title     sponsor   participator   start time"
            << "          end time\n";

  std::list<Meeting> meetings = agendaService_.listAllSponsorMeetings(userName_);
  printMeetings(meetings);

  OperationLoop();
}

void AgendaUI::listAllParticipateMeetings(void) {
  std::cout << "[list all participate meetings]\n\n";
  std::cout << "title     sponsor   participator   start time"
            << "          end time\n";

  std::list<Meeting> meetings = agendaService_.listAllParticipateMeetings(userName_);
  printMeetings(meetings);

  OperationLoop();
}

void AgendaUI::queryMeetingByTitle(void) {
  std::cout << "[query meeting] [title]:\n"
            << "[query meeting] ";

  std::string title;
  std::cin >> title;

  std::cout << "title     sponsor   participator   start time"
            << "          end time\n";

  std::list<Meeting> meeting = agendaService_.meetingQuery(userName_, title);

  printMeetings(meeting);

  OperationLoop();
}

void AgendaUI::queryMeetingByTimeInterval(void) {
  std::cout << "[query meeting] [start time<yyyy-mm-dd/hh:mm>] "
            << "[end time<yyyy-mm-dd/hh:mm>]\n"
            << "[query meeting] ";

  std::string sdate, edate;
  std::cin >> sdate >> edate;
  std::cout << "title     sponsor   participator   start time"
            << "          end time\n";
  std::list<Meeting> meetings = agendaService_.meetingQuery(userName_, sdate, edate);

  printMeetings(meetings);

  OperationLoop();
}

void AgendaUI::deleteMeetingByTitle(void) {
  std::cout << "[delete meeting] [title]\n"
            << "[deletestring meeting] ";

  std::string title;
  std::cin >> title;

  if (agendaService_.deleteMeeting(userName_, title)) {
    std::cout << "[delete meeting by title] succeed!\n";
  } else {
    std::cout << "[error] delete meeting fail!\n";
  }

  OperationLoop();
}

void AgendaUI::deleteAllMeetings(void) {
  if (agendaService_.deleteAllMeetings(userName_)) {
    std::cout << "[delete all meetings] succeed!\n";
  } else {
    std::cout << "[error] delete all meetings fail!\n";
  }

  OperationLoop();
}

void AgendaUI::printMeetings(std::list<Meeting> meetings) {
  std::list<Meeting>::iterator iter;
  std::string sdate, edate;
  iter = meetings.begin();

  for (; iter != meetings.end(); iter++) {
    sdate = iter ->getStartDate().dateToString(iter->getStartDate());
    edate = iter ->getEndDate().dateToString(iter->getEndDate());

    std::cout << std::left << std::setw(10) << iter->getTitle()
              << std::setw(10) << iter->getSponsor() << std::setw(15)
              << iter->getParticipator() << std::setw(20) << sdate
              << std::setw(20) << edate << std::endl;
  }
}

