#include <iostream>
#include "../include/Meeting.hpp"
using namespace std;

Meeting::Meeting(const string &t_sponsor,
                 const vector<string> &t_participator,
                 const Date &t_startTime, const Date &t_endTime,
                 const string &t_title) {

        this->m_sponsor = t_sponsor;
        (this->m_participators) = t_participator;
        this->m_startDate = t_startTime;
        this->m_endDate = t_endTime;
        this->m_title = t_title;
}

Meeting::Meeting(const Meeting &t_meeting) {

    this->m_sponsor = t_meeting.m_sponsor;
    (this->m_participators).assign((t_meeting.m_participators).begin(), 
                                   (t_meeting.m_participators).end());
    this->m_startDate = t_meeting.m_startDate;
    this->m_endDate = t_meeting.m_endDate;
    this->m_title = t_meeting.m_title;
}

string Meeting::getSponsor(void) const {

    return this->m_sponsor;
}

void Meeting::setSponsor(const string &t_sponsor) {

    this->m_sponsor = t_sponsor;
}

vector<string> Meeting::getParticipator(void) const {

    return this->m_participators;
}

void Meeting::setParticipator(const vector<string> &t_participators) {

    (this->m_participators).assign(t_participators.begin(), t_participators.end());
}

void Meeting::addParticipator(const string &t_participator) {

    (this->m_participators).push_back(t_participator);
}

void Meeting::removeParticipator(const string &t_participator) {

    for(auto iter = (this->m_participators).begin();
        iter != (this->m_participators).end();) {

            if(*iter == t_participator) {
                iter = (this->m_participators).erase(iter);
            }
            else {
                iter++;
            }
        }
}

Date Meeting::getStartDate(void) const {

    return this->m_startDate;
}

void Meeting::setStartDate(const Date &t_startTime) {

    this->m_startDate = t_startTime;
}

Date Meeting::getEndDate(void) const {

    return this->m_endDate;
}

void Meeting::setEndDate(const Date &t_endTime) {

    this->m_endDate = t_endTime;
}

string Meeting::getTitle(void) const {

    return this->m_title;
}

void Meeting::setTitle(const string &t_title) {

    this->m_title = t_title;
}

bool Meeting::isParticipator(const string &t_username) const{

    for(vector<string>::const_iterator iter = m_participators.begin();
        iter != m_participators.end();
        iter++) {

            if(*iter == t_username) {
                return true;
            }
    }

    return false;
}