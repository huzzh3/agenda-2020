#include <iostream>
#include <fstream>
#include "../include/Path.hpp"
#include "../include/Storage.hpp"
using namespace std;

void trim(string& str) {
    str.erase(0, str.find_first_not_of("\""));
    str.erase(str.find_last_not_of("\"")+1);
}

vector<string> handleParticipators(string src) {
    vector<string> output;
    int i = 0;
    while (i < src.size()) {
        if (src[i] == '&') { 
            i++;
        }
        else {
            int k = i;
            string temp = "";
            while(src[k] != '&' && k < src.size()) {
                temp += src[k];
                k++;
            }
            output.push_back(temp);
            i = k;
        }
    }
    return output;
}

string makelist(vector<string> src) {
    if (src.size() == 0) {
        string s = "";
        return s;
    }

    string output;
    int i = 0;
    for (i = 0; i < src.size() - 1; i++) {
        output += src[i];
        output += "&";
    }
    output += src[i];

    return output;
}

shared_ptr<Storage> Storage::m_instance = nullptr;  //initial m_instance 

Storage::Storage() {
    m_dirty = false;
    readFromFile();
} //the construct don't need to implement, for it is private

// used for delete ""




bool Storage::readFromFile(void) {
    ifstream users_myfile; //used to read users.csv
    ifstream meetings_myfile; // used to read meetings.csv

    users_myfile.open(Path::userPath); // read users.csv by Path
    meetings_myfile.open(Path::meetingPath); //read meetings.csv by Path

    // if open fail, return false
    if (users_myfile.is_open() == false || meetings_myfile.is_open() == false) {
        users_myfile.close();
        meetings_myfile.close();
        return false;
    }

    //now the file open successfully

    string temp;//used for get data
    
    while(getline(users_myfile, temp)) {
        //if getline is empty
        
        if(temp.size() == 0) {
            continue;
        }
        // now data can't be empty
        
        int i = 0; // used to scan data
        string name, password, email, phone;//used for store

        //first store username
        while(temp[i] != ',') {
            name += temp[i];
            i++;
        }
        i += 1;
        //ps you need to delete ""
        

        //second store password
        while(temp[i] != ',') {
            password += temp[i];
            i++;
        }
        i += 1;
        //ps you need to delte ""
        

        //third store email
        while(temp[i] != ',') {
            email += temp[i];
            i++;
        }
        i += 1;
        //ps you need to delte ""
        

        //last store phone
        // there aren't any other ',' you need to use other method
        while(i < temp.size()) {
            phone += temp[i];
            i++;
        }
        i += 1;
        trim(name);
        trim(password);
        trim(email);
        trim(phone);
        User u(name, password, email, phone);
        (this->m_userList).push_back(u);
    }

    // now read over, you need to store user
    

    //store user over
    string temp1;
    while(getline(meetings_myfile, temp1)) {
        if(temp1.size() == 0) {
            continue;
        }

        int i= 0;
        string sponsor, participators;
        string startDate, endDate, title;

        while(temp1[i] != ',') {
            sponsor += temp1[i];
            i++;
        }
        i += 1;

        while(temp1[i] != ',') {
            participators += temp1[i];
            i++;
        }
        i += 1;

        while(temp1[i] != ',') {
            startDate += temp1[i];
            i++;
        }
        i += 1;

        while(temp1[i] != ',') {
            endDate += temp1[i];
            i++;
        }
        i += 1;

        //last store
        // there aren't any other ',' you need to use other method
        while(i < temp1.size()) {
            title += temp1[i];
            i++;
        }
        trim(sponsor);
        trim(participators);
        trim(startDate);
        trim(endDate);
        trim(title);

        //now need to handle participators_string to divide it into a vector


        //you need to change the string into date
        Date start(startDate);
        Date end(endDate);

        Meeting m(sponsor, handleParticipators(participators), start, end, title);
        (this->m_meetingList).push_back(m);
        //input meeting over
    }

    users_myfile.close();
    meetings_myfile.close();
    return true;
}

bool Storage::writeToFile(void) {
    ofstream users_myfile;
    ofstream meetings_myfile;
    users_myfile.open(Path::userPath, ios::out);//open file
    meetings_myfile.open(Path::meetingPath, ios::out);

    //if open failed
    if (users_myfile.is_open() == false|| meetings_myfile.is_open() == false) {
        users_myfile.close();
        meetings_myfile.close();
        return false;
    }

    //open successfully, now write user data into file
    for (auto iter = m_userList.begin(); iter != m_userList.end(); iter++) {
        string temp;

        temp += "\"" + (*iter).getName() + "\"" + "," +
                       "\"" + (*iter).getPassword() + "\"" + "," +
                       "\"" + (*iter).getEmail() + "\"" + "," +
                       "\"" + (*iter).getPhone() + "\"" + "\n";
        users_myfile << temp;
    }
    //put in users over

    for (list<Meeting>::iterator iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
        string temp;

        Date d1= (*iter).getStartDate();
        Date d2 = (*iter).getEndDate();
        string start, end;
        start = d1.dateToString(d1);
        end = d2.dateToString(d2);
        string par = makelist((*iter).getParticipator());

        temp += "\"" + (*iter).getSponsor() + "\"" + ",";
        //now need to handle participator
        temp += "\"" + par + "\"" + ",";
        
        
        temp += "\"" + start + "\"" + ",";
        temp += "\"" + end + "\"" + ",";
        temp += "\"" + (*iter).getTitle() + "\"" + "\n";

        meetings_myfile << temp;
    }

    users_myfile.close();
    meetings_myfile.close();
    return true;
}

shared_ptr<Storage> Storage::getInstance(void) {
    if (NULL == m_instance) {
        m_instance = shared_ptr<Storage>(new Storage); //create a new ptr
    }
    return m_instance;
}

Storage::~Storage() {
    sync(); // when it is deconstructed, store it
}

void Storage::createUser(const User &t_user) {
    for(auto iter = m_userList.begin(); iter != m_userList.end(); iter++) {
        if ((*iter).getName() == t_user.getName()) {
            return;
        }
    }

    m_userList.push_back(t_user);
    m_dirty = true;
}

list<User> Storage::queryUser(function<bool (const User &)> filter) const {
    list<User> User_fit; //used for store the users fitted the condition

    for (list<User>::const_iterator iter = m_userList.begin(); iter != m_userList.end(); iter++) {
        if(filter(*iter)) { // if it fits the condition
            User_fit.push_back(*iter);
        }
    }

    return User_fit;
}

int Storage::updateUser(function<bool (const User &)> filter, function<void (User &)> switcher) {
    int count = 0;

    for (auto iter = m_userList.begin(); iter != m_userList.end(); iter++) {
        if(filter(*iter)) { // if it fits the condition
            switcher(*iter);
            count++;
        }
    }
    m_dirty = true;
    return count;
}

int Storage::deleteUser(std::function<bool(const User &)> filter) {
    int count = 0;
    for (auto iter = m_userList.begin(); iter != m_userList.end();) {
        if (filter(*iter)) {
            iter = m_userList.erase(iter);
            count++;
        }
        else {
            iter++;
        }
    }
    m_dirty = true;
    return count;
}

void Storage::createMeeting(const Meeting &t_meeting) {
    for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
        if ((*iter).getTitle() == t_meeting.getTitle()) {
            return;
        }
    }
    m_meetingList.push_back(t_meeting);
    m_dirty = true;
}

list<Meeting> Storage::queryMeeting(function<bool(const Meeting &)> filter) const{
    list<Meeting> Meeting_fit;

    for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
        if (filter(*iter)) {
            Meeting_fit.push_back(*iter);
        }
    }

    return Meeting_fit;
}

int Storage::updateMeeting(std::function<bool(const Meeting &)> filter,std::function<void(Meeting &)> switcher) {
    int count = 0;

    for (auto iter = m_meetingList.begin(); iter != m_meetingList.end(); iter++) {
        if (filter(*iter)) {
            switcher(*iter);
            count++;
        }
    }
    m_dirty = true;
    return count;
}

int Storage::deleteMeeting(std::function<bool(const Meeting &)> filter) {
    int count = 0;

    for (auto iter = m_meetingList.begin(); iter != m_meetingList.end();) {
        if (filter(*iter)) {
            iter = m_meetingList.erase(iter);
            count++;
        }
        else {
            iter++;
        }
    }
    m_dirty = true;
    return count;
}

bool Storage::sync(void) {
    if (m_dirty == true) {
        m_dirty = false;
        writeToFile();
    }

    return true;
}