#include <iostream>
#include <string>
#include "../include/AgendaService.hpp"
using namespace std;

AgendaService::AgendaService() {
   startAgenda(); // new m_storage in it
}

AgendaService::~AgendaService() {
    quitAgenda(); // delete m_storage in it 
}

bool AgendaService::userLogIn(const string &userName, const string &password) {
    if(userName == "") {return false;};

    list<User> temp = listAllUsers();
    for(auto i = temp.begin(); i != temp.end(); i++){
        if((*i).getName() == userName && (*i).getPassword() == password){
            return true;
        }
    }
    return false;
}

bool AgendaService::userRegister(const string &userName, const string &password,
                                 const string &email, const string &phone) {
    if(userName == "" || password == "") {return false;};
    
    list<User> temp = listAllUsers();
    for(auto i = temp.begin(); i != temp.end(); i++) {
        if((*i).getName() == userName) {
            return false;
        }
    }
    User u(userName, password, email, phone);
    
    m_storage->createUser(u);
    return true;
}

bool AgendaService::deleteUser(const std::string &userName, const std::string &password){
    if(userName == "" || password == "") {return false;};
    if(!userLogIn(userName, password)) {
        return false;
    }
    //you need to check the password and the username!
    int flag = m_storage->deleteUser([&](const User &a){
        if(a.getName() == userName && a.getPassword() == password){
            return true;
        }
        return false;
    });

    if(flag == 0) {
        return false;
    }
    else {
        m_storage->deleteMeeting([&](const Meeting &a){
            if(a.getSponsor() == userName){
                return true;
            }
            return false;
        });
        m_storage->updateMeeting([&](const Meeting &a){
            if(a.isParticipator(userName)) {
                return true;
            }
            return false;
        },
        [&](Meeting& b){
            b.removeParticipator(userName);
        });

        m_storage->deleteMeeting([&](const Meeting& a){
            if(a.getParticipator().size() == 0) {
                return true;
            }
            return false;
        });
        return true;
    }
}

list<User> AgendaService::listAllUsers(void) const {
    list<User> output;
    output = m_storage->queryUser([&](const User &a){return true;});
    return output;
}

bool AgendaService::createMeeting(const std::string &userName, const std::string &title,
                     const std::string &startDate, const std::string &endDate,
                     const std::vector<std::string> &participator) {
    Date start(startDate);
    Date end(endDate);
    if(!Date::isValid(start) || !Date::isValid(end)) {
        return false;
    }
    if(start.getYear() == 0 || end.getYear() == 0) {
        return false;
    }
    if(userName == "" || title == "" || participator.size() == 0) {
        return false;
    }

    list<Meeting> temp;
    temp = m_storage->queryMeeting([&](const Meeting &a){
        if(a.getTitle() == title) {
            return true;
        }
        return false;
    });

    if(temp.size() != 0){
        cout << "[create meeting] there are the same title meeting!" << endl;
        return false;
    }

    if(start >= end) {
        cout << "[create meeting] time is error" << endl;
        return false;
    }

    vector<string> all_man = participator;
    all_man.push_back(userName);

    list<User> u = m_storage->queryUser([&](const User& a) {
        for(auto i = all_man.begin(); i != all_man.end(); i++) {
            if((*i) == a.getName()){
                return true;
            }
        }
        return false;
    });
    if(u.size() != all_man.size()) {
         cout << "[create meeting] somebody isn't in system" << endl;
         return false;
    }

    for(auto i = participator.begin(); i != participator.end(); i++) {
        if((*i) == userName) {
            return false;
        }
    }

    for(auto i = all_man.begin(); i != all_man.end(); i++) {
        list<Meeting> m = m_storage->queryMeeting([&](const Meeting& a){
            if(a.getSponsor() == (*i) || a.isParticipator((*i))) {
                if((end <= a.getStartDate()) || (start >= a.getEndDate())) {
                    return false;
                }
                return true;
            }
            else {
                return false;
            }
        });
        if(m.size() != 0) {
            cout << "[create meeting] somebody time is occupied" << endl;
            return false;
        }
    }
    Meeting m(userName, participator, start, end, title);
    m_storage->createMeeting(m);
    return true;
}

bool AgendaService::addMeetingParticipator(const std::string &userName,
                              const std::string &title,
                              const std::string &participator){
    if(userName == "" ||title == "" ||participator == "") {
        return false;
    }
    list<User> u = m_storage->queryUser([&](const User& a){
        if(a.getName() == participator || a.getName() == userName) {
            return true;
        }
        return false;
    });
    if(u.size() != 2) {
        return false;
    }

    int flag = m_storage->updateMeeting([&](const Meeting &a){
        if(a.getSponsor() == userName && a.getTitle() == title) {
            Date start = a.getStartDate();
            Date end = a.getEndDate();
            string startDate = Date::dateToString(start);
            string endDate = Date::dateToString(end);

            list<Meeting> m = m_storage->queryMeeting([&](const Meeting& a){
                if(a.getSponsor() == participator || a.isParticipator(participator)) {
                    if((end <= a.getStartDate()) || (start >= a.getEndDate())) {
                        return false;
                    }
                    return true;
                }
                else {
                    return false;
                }
            });

            if(m.size() != 0) {
                return false;
            }
            return true;
        }
        return false;
    },
    [&](Meeting& b){
        b.addParticipator(participator);
    });

    if(flag == 0) {
        return false;
    }
    return true;
}

bool AgendaService::removeMeetingParticipator(const std::string &userName,
                                 const std::string &title,
                                 const std::string &participator) {
    int flag = m_storage->updateMeeting([&](const Meeting &a){
        if(a.getSponsor() == userName && a.getTitle() == title && a.isParticipator(participator)) {
            return true;
        }
        return false;
    },
    [&](Meeting& b){
        b.removeParticipator(participator);
    });

    m_storage->deleteMeeting([&](const Meeting& a){
        if(a.getParticipator().size() == 0) {
            return true;
        }
        return false;
    });

    if(flag == 0){
        return false;
    }
    return true;
}

bool AgendaService::quitMeeting(const std::string &userName, const std::string &title) {
    int flag = m_storage->updateMeeting([&](const Meeting& a){
        if(a.getTitle() == title && a.isParticipator(userName)) {
            return true;
        }
        return false;
    },
    [&](Meeting& b){
        b.removeParticipator(userName);
    });

    m_storage->deleteMeeting([&](const Meeting& a){
        if(a.getParticipator().size() == 0) {
            return true;
        }
        return false;
    });
    if(flag == 0) {
        return false;
    }
    return true;
}

list<Meeting> AgendaService::meetingQuery(const std::string &userName, const std::string &title) const {
    list<Meeting> output;
    output = m_storage->queryMeeting([&](const Meeting& a){
        if((a.getSponsor() == userName || a.isParticipator(userName)) && a.getTitle() == title) {
            return true;
        }
        return false;
    });
    return output;
}

std::list<Meeting> AgendaService::meetingQuery(const std::string &userName,
                                  const std::string &startDate,
                                  const std::string &endDate) const {
    Date start(startDate);
    Date end(endDate);
    if(!Date::isValid(start) || !Date::isValid(end)) {
        list<Meeting> t;
        return t;
    }

    if(start > end) {
        list<Meeting> m;
        return m;
    }
    list<Meeting> output;
    output = m_storage->queryMeeting([&](const Meeting &a){
        if((a.getSponsor() == userName || a.isParticipator(userName))){
            if((end < a.getStartDate()) || (start > a.getEndDate())) {
                return false;
            }
            return true;
        }
        else {
            return false;
        }
    });
    return output;
}

list<Meeting> AgendaService::listAllMeetings(const std::string &userName) const {
    list<Meeting> output;
    output = m_storage->queryMeeting([&](const Meeting a){
        if(a.getSponsor() == userName || a.isParticipator(userName)) {
            return true;
        }
        return false;
    });
    return output;
}

std::list<Meeting> AgendaService::listAllSponsorMeetings(const std::string &userName) const {
    list<Meeting> output;
    output = m_storage->queryMeeting([&](const Meeting a){
        if(a.getSponsor() == userName) {
            return true;
        }
        return false;
    });
    return output;
}

std::list<Meeting> AgendaService::listAllParticipateMeetings(const std::string &userName) const{
    list<Meeting> output;
    output = m_storage->queryMeeting([&](const Meeting a){
        if(a.isParticipator(userName)) {
            return true;
        }
        return false;
    });
    return output;
}

bool AgendaService::deleteMeeting(const std::string &userName, const std::string &title){

    int flag = m_storage->deleteMeeting([&](const Meeting a){
        if(a.getSponsor() == userName && a.getTitle() == title) {
            return true;
        }
        return false;
    });
    if(flag == 0){
        return false;
    }
    return true;
}

bool AgendaService::deleteAllMeetings(const std::string &userName){
    m_storage->deleteMeeting([&](const Meeting &a) {return a.getSponsor() == userName;});
    return true;
}

void AgendaService::startAgenda(void) {
    m_storage = Storage::getInstance();
}

void AgendaService::quitAgenda(void) {
    m_storage->sync();
}