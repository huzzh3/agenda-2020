#include <iostream>
#include <string>
#include "../include/User.hpp"
using namespace std;

User::User(const string &t_userName,  const string &t_userPassword,
           const string &t_userEmail, const string &t_userPhone) {

               this->m_name = t_userName;
               this->m_password = t_userPassword;
               this->m_email = t_userEmail;
               this->m_phone = t_userPhone;
}

User::User(const User &t_user) {

    this->m_name = t_user.m_name;
    this->m_password = t_user.m_password;
    this->m_email = t_user.m_email;
    this->m_phone = t_user.m_phone;
}

string User::getName() const {

    return this->m_name;
}

void User::setName(const string &t_name) {

    this->m_name = t_name;
}

string User::getPassword() const{

    return this->m_password;
}

void User::setPassword(const string &t_password) {

    this->m_password = t_password;
}

string User::getEmail() const {

    return this->m_email;
}

void User::setEmail(const string &t_mail) {

    this->m_email = t_mail;
}

string User::getPhone() const {

    return this->m_phone;
}

void User::setPhone(const string &t_phone) {

    this->m_phone = t_phone;
}