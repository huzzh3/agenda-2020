#include "../include/AgendaUI.hpp"
#include <string>
#include <iostream>
#include <cstring>
#include <iomanip>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
using namespace std;


void sig_handler(int sig) {
    cout << "\nexit the system, please waiting for saving" << endl;
    exit(sig);
}

AgendaUI::AgendaUI() {
    startAgenda(); //start the system
}

void AgendaUI::OperationLoop(void) {
    // it will provide the basic menu
    string operation;
    do {
        cout << endl;
        cout << "-------------------------------------Agenda-------------------------------------" << endl;
        cout << "Action :" << endl;
        cout << "l    - log in Agenda by user name and password" << endl;
        cout << "r    - register an Agenda account" << endl;
        cout << "q    - quit Agenda" << endl;
        cout << "--------------------------------------------------------------------------------" << endl;
        cout << endl;
        cout << "Agenda :~$ ";
        signal(SIGINT,sig_handler);

        cin >> operation;
        if(operation == "l") {
            userLogIn();
        }
        else if(operation == "r") {
            userRegister();
        }
        else if(operation == "q") {
            quitAgenda();
        }
        
    }while(operation != "q");
}

void AgendaUI::startAgenda(void) {
    //start the system
    //you need to give system control power, m_agendaService
    m_agendaService.startAgenda();
}

string AgendaUI::getOperation() {
    //catch operation
    cout << "-------------------------------------Agenda-------------------------------------" << endl;
    cout << "Action :" << endl;
    cout << "o    - log out Agenda" << endl;
    cout << "dc   - delete Agenda account" << endl;
    cout << "lu   - list all Agenda account" << endl;
    cout << "cm   - create a meeting" << endl;
    cout << "amp  - add meeting participator" << endl;
    cout << "rmp  - remove meeting participator" << endl;
    cout << "rqm  - request to quit meeting" << endl;
    cout << "la   - list all meetings" << endl;
    cout << "las  - list all sponsor meetings" << endl;
    cout << "lap  - list all participator meetings" << endl;
    cout << "qm   - query meeting by title" << endl;
    cout << "qt   - query meeting by time interval" << endl;
    cout << "dm   - delete meeting by title" << endl;
    cout << "da   - delete all meetings" << endl;
    cout << "--------------------------------------------------------------------------------" << endl;
    cout << endl;
    cout << "Agenda@pear :~# " ;
    signal(SIGINT,sig_handler);
    string operation;
    cin >> operation;
    return operation;
}

bool AgendaUI::executeOperation(std::string t_operation) {
    cout << endl;
    if (t_operation == "o") {
        userLogOut();
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return false;
    }
    else if (t_operation == "dc") {
        deleteUser();
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return false;
    }
    else if (t_operation == "lu") {
        listAllUsers();
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else if (t_operation == "cm") {
        createMeeting();
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else if (t_operation == "amp") {
        cout << "[add participator] " << "[meeting title] " << "[participator username]" << endl;
        cout << "[add participator] " ;
        string meeting_title;
        cin >> meeting_title;
        string participator_name;
        cin >> participator_name;
        
        if (m_agendaService.addMeetingParticipator(m_userName, meeting_title, participator_name)) {
            cout << "[add participator] succeed!" << endl;
        }
        else {
            cout << "[add participator] error!" << endl;
        }
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else if (t_operation == "rmp") {
        cout << "[remove participator] " << "[meeting title] " << "[participator username]" << endl;
        cout << "[remove participator] " ;
        string meeting_title;
        string participator_name;
        cin >> meeting_title;
        cin >> participator_name;
        
        if (m_agendaService.removeMeetingParticipator(m_userName, meeting_title, participator_name)) {
            cout << "[remove participator] succeed!" << endl;
        }
        else {
            cout << "[remove participator] error!" << endl;
        }

        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else if (t_operation == "rqm") {
        cout << "[quit meeting] " << "[meeting title]" << endl;
        cout << "[quit meeting] ";
        string meeting_title;
        cin >> meeting_title;

        if(m_agendaService.quitMeeting(m_userName, meeting_title)) {
            cout << "[quit meeting] succeed!" << endl;
        }
        else {
            cout << "[quit meeting] error!" << endl;
        }
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else if (t_operation == "la") {
        listAllMeetings();
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else if (t_operation == "las") {
        listAllSponsorMeetings();
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else if (t_operation == "lap") {
        listAllParticipateMeetings();
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else if (t_operation == "qm") {
        queryMeetingByTitle();
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else if (t_operation == "qt") {
        queryMeetingByTimeInterval();
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else if (t_operation == "dm") {
        deleteMeetingByTitle();
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else if(t_operation == "da") {
        deleteAllMeetings();
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
    else {
        cout << "input error!" << endl;
        cout << "please input any letter to go back" ;
        string op;
        cin >> op;
        return true;
    }
}

void AgendaUI::userLogIn(void) {
    cout << "[log in] [username] [password]" << endl;
    cout << "[log in] " ;
    string username;
    string password;
    cin >> username;
    cin >> password;

    if(m_agendaService.userLogIn(username, password)) {
        m_userName = username;
        m_userPassword = password;
        cout << "[log in] succeed!" << endl;
        while(executeOperation(getOperation())) {}
    }
    else {
        cout << "[log in] Password error or user donesn't exist" << endl;
    }
}
void AgendaUI::userRegister(void) {
    cout << "[register] [username] [password] [email] [phone]" << endl;
    cout << "[register] " ;

    string username;
    string password;
    string email;
    string phone;
    cin >> username >> password >> email >> phone;

    if(m_agendaService.userRegister(username, password, email, phone)) {
        cout << "[register] succeed!" << endl;
    }
    else {
        cout << "[register] This username has been registered!" << endl;
    }
}

void AgendaUI::userLogOut(void) {
}

void AgendaUI::quitAgenda(void) {
    m_agendaService.quitAgenda();
}

void AgendaUI::deleteUser(void) {
    if(m_agendaService.deleteUser(m_userName, m_userPassword)) {
        cout << "[delete agenda account] succeed!" << endl;
    }
}

void AgendaUI::listAllUsers(void) {
    cout << "[list all users]" << endl;
    cout << endl;

    cout << left << setw(15) << "name" << left << setw(25) << "email" << "phone" << endl;
    
    list<User> all_users = m_agendaService.listAllUsers();
    for(auto it = all_users.begin(); it != all_users.end(); it++) {
        cout << left << setw(15) << (*it).getName() << left << setw(25) << (*it).getEmail() << (*it).getPhone() << endl;
    }
}

void AgendaUI::createMeeting(void) {
    cout << "[create meeting] [the number of participators]" << endl;
    cout << "[create meeting] " ;
    int participators_num = 0;
    cin >> participators_num;
    vector<string> participators;

    for(int i = 1; i <= participators_num; i++) {
        cout << "[create meeting] [please enter the participator " << i << " ]" << endl;
        cout << "[create meeting] " ;
        string participators_name;
        cin >> participators_name;
        participators.push_back(participators_name);
    }

    cout << "[create meeting] [title][start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]" << endl;
    cout << "[create meeting] " ;
    string title;
    string startTime;
    string endTime;
    cin >> title >> startTime >> endTime;    

    if(m_agendaService.createMeeting(m_userName, title, startTime, endTime, participators) == 1) {
        cout << "[create meeting] succeed!" << endl;
    }
    else {
        cout << "[create meeting] error!" << endl;
    }
}

void AgendaUI::listAllMeetings(void) {
    cout << "[list all meeting]" << endl;
    cout << endl;

    list<Meeting> meetings = m_agendaService.listAllMeetings(m_userName);
    printMeetings(meetings);
}

void AgendaUI::listAllSponsorMeetings(void) {
    cout << "[list all sponsor meetings]" << endl;
    cout << endl;

    list<Meeting> meetings = m_agendaService.listAllSponsorMeetings(m_userName);
    printMeetings(meetings);
}

void AgendaUI::listAllParticipateMeetings(void) {
    cout << "[list all participator meetings]" << endl;
    cout << endl;

    list<Meeting> meetings = m_agendaService.listAllParticipateMeetings(m_userName);
    printMeetings(meetings);
}

void AgendaUI::queryMeetingByTitle(void) {
    cout << "[query meeting] [title]:" << endl;
    cout << "[query meeting] " ;
    string title;
    cin >> title;

    list<Meeting> meeting = m_agendaService.meetingQuery(m_userName, title);
    printMeetings(meeting);
}

void AgendaUI::queryMeetingByTimeInterval(void) {
    cout << "[query meetings] [start time(yyyy-mm-dd/hh:mm)] [end time(yyyy-mm-dd/hh:mm)]:" << endl;
    cout << "[query meetings] " ;
    string start, end;
    cin >> start >> end;
    cout << "[query meetings]" << endl;

    list<Meeting> meetings = m_agendaService.meetingQuery(m_userName, start, end);
    printMeetings(meetings);
}

void AgendaUI::deleteMeetingByTitle(void) {
    cout << "[delete meeting] [title]" << endl;
    cout << "[delete meeting] ";
    string title;
    cin >> title;

    if(m_agendaService.deleteMeeting(m_userName, title)) {
        cout << "[delete meeting] succeed!" << endl;
    }
    else {
        cout << "[delete meeting] error!" << endl;
    }
}

void AgendaUI::deleteAllMeetings(void) {
    m_agendaService.deleteAllMeetings(m_userName);
    cout << "[delete all meeting] succeed!" << endl;
}

string getParticipator(vector<string> str) {
    if(str.size() == 0) {
        return "";
    }
    string ret;
    int i = 0;
    for(i = 0; i < str.size() - 1; i++) {
        ret += str[i];
        ret += ",";
    }
    ret += str[i];

    return ret;
}
void AgendaUI::printMeetings(std::list<Meeting> t_meetings) {
    cout << left << setw(15) << "title" << left << setw(12) << "sponsor" << setw(20) << "start time" << left << setw(20) << "end time" << left << setw(15) << "participators" << endl;

    for(auto it = t_meetings.begin(); it != t_meetings.end(); it++) {
        cout << left << setw(15) << (*it).getTitle() << left << setw(12) << (*it).getSponsor() << setw(20) << Date::dateToString((*it).getStartDate()) ;
        cout << left << setw(20) << Date::dateToString((*it).getEndDate()) << left << setw(15) << getParticipator((*it).getParticipator()) << endl;
    }
}