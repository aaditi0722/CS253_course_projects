#ifndef CLASSES_HPP
#define CLASSES_HPP

#include<iostream>
#include <vector>
#include<string>
#include <chrono>
#include <fstream>     
#include <iostream>    
#include <sstream> 
using namespace std;

void readfile(string fname, string type, vector<vector<string>> &car_db, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db);
void writefile(vector<vector<string>> &par, string fname);
void print_car_data(vector<vector<string>> &car_db);
void print_car_data_manager(vector<vector<string>> &car_db);

//base class
class User{
    private:
        string password;
    public:
        string id;
        int decent_user_record = 5; 
        float employee_discount=15;
        int duration_of_day_seconds = 30;//for a day there should be 86400 seconds. For purpose of testing this has been set to 30 seconds :)
        int coefficient1 = 1; //consumer_record is changed by -(coefficient1*delay + coefficient2*(negative change in car condition))
        int coefficient2 = 1;
        int amount_to_normalize = 5; //amount by which a customer_record is incremented with when he has a below decent customer_record and wants to rent a car
        int reward_to_punctual = 10;  // user_record is incrementd by this value when he reurns a car in good condition without a delay
        void display_menu();
        void login();
        void logout( vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db);
        void see_all_cars(vector<vector<string>> &car_db);
        void see_rented_cars(string id, vector<vector<string>> &car_db);
        void return_car(string id, string car_id, string user_type, vector<vector<string>> &car_db, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db);
        void rent_car(string id, string type, string max_customer_rent_days, vector<vector<string>> &car_db, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, string customer_record);
        void clear_fine_amount(string id, string type_user, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db);
};

//derived classes of user class, contains functions and variables relevent for a customer
class customer : public User{
    private:
        int Fine_amount;
    public:
        string id;
        string name;
        string customer_record;
        string total_dues;
        int decent_customer_record = 7;
        string max_customer_rent_days = "30";
        void display_customer_menu(string id, vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db);
};

//derived classes of user class, contains functions and variables relevent for a employee
class employee : public User{
    private:
        int Fine_amount;
    public:
        string id;
        string name;
        string customer_record;
        string total_dues;
        int decent_employee_record = 7;
        string max_employee_rent_days="30";
        void display_employee_menu(string id, vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db);
};

//derived classes of user class, contains functions and variables relevent for a manager
class manager : public User{
    public:
        string default_customer_record = "10";
        string default_employee_record = "10";
        void display_manager_menu(string id, vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db);
        void see_all_cars_rentee(string type, vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db);
        void see_all_cars_manager(vector<vector<string>> &car_db);
        void add_user(vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db);
        void update_user(vector<vector<string>> &car_db, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db);
        void delete_user(vector<vector<string>> &car_db, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db);
        void add_car(vector<vector<string>> &car_db);
        void update_car(vector<vector<string>> &car_db, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db);
        void delete_car(vector<vector<string>> &car_db, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db);   
};

#endif // CLASSES_HPP