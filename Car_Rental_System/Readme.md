# CS253-Rent-me-a-car
This repository contains an on-terminal car renting system!
# Running 
To run the program, execute the following on the terminal
```
g++ main.cpp classes.cpp -o code
./code
```
# Structure 
* The declarations of the classes and their functions reside in [classes.hpp](classes.hpp)
* The definitions of those declared in [classes.hpp](classes.hpp) are written in [classes.cpp](classes.cpp)
* [classes.hpp](classes.hpp) has then been included in [main.cpp](main.cpp) and a simple function has been written to deploy the program.
# Databases
* Customer data is stored in [customer_data.csv](customer_data.csv), employee data in [employee_data.csv](employee_data.csv) and manager data in [manager_data.csv](manager_data.csv).
* Columns in [customer_data.csv](customer_data.csv) and [employee_data.csv](employee_data.csv) have the following fields:
  * User_id
  * User_name
  * Password
  * User_record
  * Total_dues
* Columns in [manager_data.csv](manager_data.csv) have the following fields:
  * id
  * manager_name
  * Password
* Car data is stored in [car_cata.csv](car_data.csv) with the columns representing the following fields:
  * Car id
  * Car model
  * Car condition
  * Car availability(either "yes" or "no")
  * User id of rentee
  * Time measure of when the car was rented(using chrono library)
  * Price rate per day
  * Number of days the car is rented for
# Assumptions 
* Initially all databases have 5 entries each. One can use the id ```cus1``` with password ```123``` to login as customer, id ```emp1``` with password ```123``` to login as employee and id ```man1``` with password to login as a manager.
* Any user can rent upto a maximum of 5 cars. This can be modified in User class in [classes.cpp](classes.cpp).
* User record is changed according to the follwoing logic :
  * If the user makes a delay in return :  User record += coeffiecient_1 * delay_in_days + coefficient_2 * damage_to_car.
  * If no delay is made, User record += reward_to_punctual.
* When the user record goes below a certain threshold(decent_user_threshold), that user is blacklisted and not allowed to rent a car. If the user attempts to rent a car, his/her user record is incremented by amount_to_normalize units. This ensures that no user gets blacklisted permanently.
* reward_to_punctual, coeffiecient1, coeffiecient2, amount_to_normalize, decent_user_threshold have been defined in User class in [classes.cpp](classes.cpp).
* For ease of testing, duration of one day is set to 30 seconds. This can be changed User class in [classes.cpp](classes.cpp).
* Atleast one manager must be present at all times in order to add other customers and employees.
