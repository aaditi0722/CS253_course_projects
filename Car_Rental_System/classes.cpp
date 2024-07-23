#include "classes.hpp"

//function for reading a csv file which is the database format, this is executed at the time of user login only 
void readfile(string fname, string type, vector<vector<string>> &car_db, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db){
    vector<string> row;
    string line, word;
    fstream file (fname,ios::in);
    if(file.is_open()){
        while(getline(file, line)){
            row.clear();
            stringstream str(line);
            while(getline(str, word, ',')) {row.push_back(word);}
            if(type=="1") customer_db.push_back(row);
            else if(type=="2") employee_db.push_back(row);
            else if(type=="3") manager_db.push_back(row);
            else if(type=="4") car_db.push_back(row);
        }
    }
    else cout<<"Could not open the file\n";
    file.close();
}

//function for writing to back to a cvs file, this is executed at the time of user logout only
void writefile(vector<vector<string>> &par, string fname){
    fstream fout(fname, ios::out);
    fout.clear();
    for (auto x : par){
        for (auto y : x){
            fout << y;
            if (y != x.back()){
                fout << ",";
            }    
        }
        fout<<"\n";
    }
}

//function for printing car data when requested by the user
void print_car_data(vector<vector<string>> &car_db){
    int c=1;
    for(auto x:car_db){
        cout<<c<<". ";
        //printing car id, car model, car condition, car rate per day and availability status
        cout<<"Car id :"<<x[0]<<endl;//id
        cout<<"Model :"<<x[1]<<endl;//model
        cout<<"Condition :"<<x[2]<<endl;//condition
        cout<<"Availability :"<<x[3]<<endl;//availability
        cout<<"Rate per day :"<<x[6]<<endl;//rate per day
        c++;
        cout<<"\n";
    }
} 

//function for printing car data when requested by the manager
void print_car_data_manager(vector<vector<string>> &car_db){
    int c=1;
    for(auto x:car_db){
        cout<<c<<". ";
        //printing car id, car model, car condition, car rate per day and availability status
        cout<<"Car id : "<<x[0]<<endl;//id
        cout<<"Model : "<<x[1]<<endl;//model
        cout<<"Condition : "<<x[2]<<endl;//condition
        cout<<"Availability : "<<x[3]<<endl;//availability
        if(x[4]!="*") cout<<"Rentee : "<<x[4]<<endl;//rentee
        else cout<<"Rentee : None"<<endl;
        cout<<"Rate per day : "<<x[6]<<endl;//rate per day
        cout<<"Number of days rented for : "<<x[7]<<endl;
        c++;
        cout<<"\n";
    }
}

void customer :: display_customer_menu(string id, vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db){
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\nYou have been logged in as customer\n";
    cout<<"Press 1 to see all the cars\n";
    cout<<"Press 2 to view cars issued by you\n";
    cout<<"Press 3 to view the total dues\n";
    cout<<"Press 4 to issue a car\n";
    cout<<"Press 5 to return a car\n";
    cout<<"Press 6 to clear your dues\n";
    cout<<"Press 7 to logout\n";
    cout<<"---------------------------------------------------------------------\n";
    char C;
    cin>>C;
    string car_id, number_of_days;
    //we store all required parameters of the logged in user so that repetitive opening of the database is avoided
    for(int i=0; i<customer_db.size(); i++){
        if(customer_db[i][0]==id){
            this->id=id;
            this->name=customer_db[i][1];
            this->customer_record=customer_db[i][3];
            this->total_dues=customer_db[i][4];
        }
    }
    User u;
    switch(C){
        case '1':
            u.see_all_cars(car_db); 
            this->display_customer_menu(id, car_db, employee_db, customer_db, manager_db);
            break; 
        case '2':
            u.see_rented_cars(id, car_db);
            this->display_customer_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '3':
            cout<<"Your total dues is "<<this->total_dues<<endl;
            this->display_customer_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '4': 
            u.rent_car(id, "1", this->max_customer_rent_days, car_db, employee_db, customer_db, this->customer_record);
            this->display_customer_menu(id, car_db, employee_db, customer_db, manager_db);        
            break;
        case '5':
            cout<<"Enter the id of the car you want to return : ";
            cin>>car_id;
            u.return_car(id, car_id, "1", car_db, employee_db, customer_db);
            this->display_customer_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '6':
            u.clear_fine_amount(id,"1", employee_db, customer_db);
            cout<<"Your dues of "<<this->total_dues<<" has been cleared!\n";
            this->total_dues="0";
            this->display_customer_menu(id, car_db, employee_db, customer_db, manager_db);
            break;           
        case '7':
            u.logout(car_db, employee_db, customer_db, manager_db);
            break;
        default :
            cout<<"Please enter a valid option.\n";
            this->display_customer_menu(id, car_db, employee_db, customer_db, manager_db);
    }
}

void employee :: display_employee_menu(string id, vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db){
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\nYou have been logged in as employee\n";
    cout<<"Press 1 to see all the cars\n";
    cout<<"Press 2 to view cars issued by you\n";
    cout<<"Press 3 to view the dues\n";
    cout<<"Press 4 to issue a car\n";
    cout<<"Press 5 to return a car\n";
    cout<<"Press 6 to clear your dues\n";
    cout<<"Press 7 to logout\n";
    cout<<"---------------------------------------------------------------------\n";
    char c;
    cin>>c;
    string car_id, number_of_days;
    //we store all required parameters of the logged in user so that repetitive opening of the database is avoided
    for(int i=0; i<employee_db.size(); i++){
        if(employee_db[i][0]==id){
            this->id=id;
            this->name=employee_db[i][1];
            this->customer_record=employee_db[i][3];
            this->total_dues=employee_db[i][4];
        }
    }
    User u;
    switch(c){
        case '1':
            u.see_all_cars(car_db);
            this->display_employee_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '2':
            u.see_rented_cars(id, car_db);
            this->display_employee_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '3':
            cout<<"Your total dues is "<<this->total_dues<<endl;
            this->display_employee_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '4':
            u.rent_car(id,"2", this->max_employee_rent_days, car_db, employee_db, customer_db, this->customer_record);
            this->display_employee_menu(id, car_db, employee_db, customer_db, manager_db);      
            break;
        case '5':
            cout<<"Enter the id of the car you want to return : ";
            cin>>car_id;
            u.return_car(id, car_id, "2", car_db, employee_db, customer_db);
            this->display_employee_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '6':
            u.clear_fine_amount(id,"2", employee_db, customer_db);
            cout<<"Your dues of "<<this->total_dues<<" has been cleared!\n";
            this->total_dues="0";
            this->display_employee_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '7': 
            u.logout(car_db, employee_db, customer_db, manager_db);
            break;
        default :
            cout<<"Please enter a valid option.\n";
            this->display_employee_menu(id, car_db, employee_db, customer_db, manager_db);
    }
}

//menu that is displayed first when the code runs
void User :: display_menu(){
    string c;
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\n\nWelcome to the Car renting system!!!\n\n";
    cout<<"1. Press 1 to log in : \n";
    cout<<"2. Press 2 to exit\n";
    cout<<"---------------------------------------------------------------------\n";
    cin>>c;
    if(c=="1"){ 
        User u;
        u.login();
    }
    else if(c=="2"){
        cout<<"Thanks for using the system !";
        exit(1);
    }
    else{
        cout<<"Please enter a valid input! Press 1 to exit, 2 to retry:";
        string s;
        cin >>s;
        if(s=="1") return;
        else if(s=="2") this->display_menu();
        else cout<<"Byeee!\n";
    } 
}

//user login function
void User :: login(){
    string id,password; 
    string type;
    cout<<"Enter login type(1 for customer || 2 for employee || 3 for manager) : ";
    cin.ignore();
    getline(cin,type);
    vector<vector<string>> file;
    vector<vector<string>> car_db; // the below four 2-d vectors will contain a copy of all four databases and the changes will be written to the csv databases at logout only
    vector<vector<string>> employee_db;
    vector<vector<string>> customer_db; 
    vector<vector<string>> manager_db; 
    readfile("customer_data.csv", "1", car_db, employee_db, customer_db, manager_db);
    readfile("employee_data.csv", "2", car_db, employee_db, customer_db, manager_db);
    readfile("manager_data.csv", "3", car_db, employee_db, customer_db, manager_db);
    if(type=="1") {
        file = customer_db;  
    }
    if(type=="2") {
        file = employee_db; 
    }
    if(type=="3") {
        file = manager_db;  
    }
    else if(type!="1" && type!="2"&& type!="3"){
        cout<<"You did not enter a valid input! Press 1 to retry, 2 to exit : "; // ensuring the login is secure
        string s;
        cin >>s;
        if(s=="1"){
            this->login();
            return;
        } 
        else if(s=="2") return;
        else{
            cout<<"Byeee!\n";
            return;
        } 
    } 
    cout<<"Enter your id : ";
    cin>>id;
    cout<<"Enter the password : ";
    cin>>password;
    int count=0;
    for(int i=0; i<file.size(); i++){
        if(file[i][0]==id){
            count=1;
            if(file[i][2]==password){
                cout<<"Welcome "<<file[i][1]<<". You have logged in successfully.\n";
                count=2;
            }
            else {
                while(password!=file[i][2]){ 
                    cout<<"\n You entered the wrong password. Press 1 to re-enter the password and 2 to exit : ";
                    string c;
                    cin>>c;
                    if(c=="1"){
                        cout<<"Enter the password : ";
                        cin>>password;
                        if(password==file[i][2]) count++;
                    }
                    else if(c=="2"){
                        cout<<"Exiting...\n";
                        return;
                    }
                    else{
                        cout<<"\nPlease enter a valid input.\n";
                    }
                }
            }
            if(count==2) break;
        }
    }
    if(count==0){
        cout<<"No user found!\n";
        if(type=="1") {
            cout<<"For new registartion, press 1, to exit press 2 : "; //if the user(customer) doesnt exist already, he has an option to make a new registartion
            string s;
            cin >>s;
            if(s=="1"){
                    manager m;
                    m.add_user(employee_db, customer_db, manager_db);
                    writefile(customer_db, "customer_data.csv");
                    writefile(employee_db, "employee_data.csv");
                    writefile(manager_db, "manager_data.csv");
                }
            
            else if(s=="2") {
                cout<<"Exiting...\n";
            }
        }
        this->display_menu();
    }
    else if(count==2){
        car_db.clear();
        readfile("car_data.csv", "4", car_db, employee_db, customer_db, manager_db);
        customer c;
        employee e;
        manager m;
        if(type=="1"){
            c.display_customer_menu(id, car_db, employee_db, customer_db, manager_db);
        }
        else if(type=="2"){
            e.display_employee_menu(id, car_db, employee_db, customer_db, manager_db);
        }
        else if(type=="3"){
            m.display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
        }
    }
}
//add car data as seen by the user(customer and employee)
void User :: see_all_cars(vector<vector<string>> &car_db){
    print_car_data(car_db);
}

//add car data as seen by the manager
void manager :: see_all_cars_manager(vector<vector<string>> &car_db){
    print_car_data_manager(car_db);
}

//for renting a car
void User :: rent_car(string id, string type, string max_rent_days, vector<vector<string>> &car_db, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, string customer_record){
    string car_id, number_of_days;
    int to_add=0, fl=0, count=0, car_price_per_day;
    cout<<"Enter the id of the car you want to rent : ";
    cin.ignore();
    getline(cin,car_id);
    cout<<"Enter the number of days you want to rent the car for : ";
    cin>>number_of_days;
    if(number_of_days > max_rent_days){
        cout<<"You can only rent for a maximum of "<<max_rent_days<<" days!\n";
        rent_car(id, type, max_rent_days, car_db, employee_db, customer_db, customer_record);
        return;
    }
    vector<vector<string>> copy;
    if(type=="1"){                  //loading appropriate database according to the type of user
        copy=customer_db;
    }
    else if(type=="2"){
        copy=employee_db; 
    }
    for(int i=0;i<car_db.size();i++){
        if(car_db[i][4]==id){
            count++;
        }
    }
    if(count>5){        // if the user already has >5 rented cars
        cout<<"You can't issue more than 5 cars !\n\n";
    }
    else if(stoi(customer_record) < (decent_user_record)) {         //if the user has a bad customer record
        cout<<"Sorry! We cannot rent you a car based on your past behaviour! Please try some time later.\n";
        to_add=1; //this will be used later in the function to eventually normalize the penalty of the customer with a bad customer_record
    }
    else{       
        for(int i=0;i<car_db.size();i++){
            if(car_db[i][0]==car_id && car_db[i][3]=="yes"){
                car_price_per_day = stoi(car_db[i][6]);
                fl=1;
                cout<<"Car is available!\n"; 
                car_db[i][3]="no";
                car_db[i][4]=id;
                car_db[i][5]=to_string(time(0));
                car_db[i][7]=number_of_days;
                cout<<"An amount of "<<(car_price_per_day)*stoi(number_of_days)<<" units has been added to your dues.\nPlease return the car after "<<stoi(number_of_days)<<" days.\n";
                cout<<"Car succesfully issued\n";
                break;
            }
        }
        if(fl==1){
            for(int i=0;i<copy.size();i++){
                if(copy[i][0]==id){
                    int amount=stoi(copy[i][4]);
                    if(type=="2"){
                        amount+=car_price_per_day*stoi(number_of_days)*(1-(employee_discount)/100); //employee is given a discount
                    }
                    else amount+=car_price_per_day*stoi(number_of_days);
                    copy[i][4]=to_string(amount);
                    break;
                }
            }
        }
        else if(fl==0) cout<<"Car not available\n";
    }
    if(to_add==1){      //step to normalize the user wiith a bad customer record
        for(int i=0; i<copy.size(); i++){
            if(copy[i][0]==id){
                copy[i][3]= to_string(stoi(copy[i][3]) + amount_to_normalize);
                break;
            }
        }            
    } 
    if(type=="1"){
        customer_db=copy;
    }
    else if(type=="2"){
        employee_db=copy;
    }
}   

//function to return rented car
void User :: return_car(string id,string car_id, string user_type, vector<vector<string>> &car_db, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db){
    string car_condition;
    string past_car_condition;
    int delay_in_days=0;
    cout<<"Enter the condition of the car in a scale of 1-10(1 for worst conditon and 10 for best : ";
    cin >>car_condition;
    if(car_condition > "10" || car_condition <"1"){         //making the code secure from invalid inputs
        cout<<"Please enter a vaid value for car_condition!\n";
        this->return_car(id, car_id, user_type, car_db, employee_db, customer_db);
        return;
    }
    int flag=0;
    int fine=0;
    for(int i=0; i<car_db.size(); i++){
        if(car_db[i][0]==car_id){
            flag=1;
            if(car_db[i][4]==id){
                flag=2;
                int curtime = time(0);
                int isstime = stoi(car_db[i][5]);
                if((curtime-isstime)/duration_of_day_seconds > stoi(car_db[i][7])){
                    delay_in_days = ((curtime-isstime)/duration_of_day_seconds - stoi(car_db[i][7]));
                    fine+=2*delay_in_days*stoi(car_db[i][6]);       //charged double the normal rate for extra days
                    cout<<"Delay in return = "<<delay_in_days<<" days."<<endl;
                    cout<<"Fine = "<<fine<<endl;
                }
                cout<<"Car returned successfully!\n";
                car_db[i][4]="*";       //car is not rented to anyone now
                car_db[i][5]="*";       //car has no issued date now
                car_db[i][3]="yes";         //car is now available for others to book
                past_car_condition = car_db[i][2];
                car_db[i][2]=car_condition;         //condition of the returned car as reported by the user
                car_db[i][7]="0";
                break;
            }     
        }
    }
    if(flag==0){
        cout<<"Invalid car details!\n";
        return;
    } 
    else if(flag==1){
        cout<<"This car is not rented to you!\n";
        return;
    }
    vector<vector<string>> copy;
    if(user_type=="1") copy=customer_db;
    else if(user_type=="2") copy=employee_db;
    for(int i=0; i<copy.size(); i++){
        if(copy[i][0]==id) {
            copy[i][4] = to_string( stoi(copy[i][4]) + fine);
            copy[i][3] = to_string(stoi(copy[i][3]) - coefficient1*(delay_in_days) - coefficient2* (stoi(past_car_condition)-stoi(car_condition)));       //changing customer_record when user suffers a fine
            if(delay_in_days==0 && stoi(past_car_condition)-stoi(car_condition)>=0){        //incrementing user record by 10 when he doesnt suffer a fien
                copy[i][3]=to_string(stoi(copy[i][3])+reward_to_punctual);
            }
        }
    }
    if(user_type=="1") customer_db=copy;
    else if(user_type=="2") employee_db=copy;
}

//function for user to see the cars rented by him along with the days remainig for return
void User :: see_rented_cars(string id, vector<vector<string>> &car_db){
    int count=1;
    for(int i=0;i<car_db.size();i++){
        if(car_db[i][3]=="no"){                 
            if(car_db[i][4]==id){        
                int return_rent=stoi(car_db[i][7])-(-stoi(car_db[i][5])+time(0))/duration_of_day_seconds;
                if(count==1) cout<<"Car model \t\t\t Car id \t\t\t Car to be returned in \t\t\t Price rate per day\n";
                cout<<count<<". ";
                count++;
                cout<<car_db[i][1]<<"\t\t\t\t "<<car_db[i][0]<<" \t\t\t\t"<<return_rent<<" days"<<" \t\t\t\t"<<car_db[i][6]<<endl;
            }
        }
    }
    if(count==1) cout<<"You haven't issued any cars as of now.\n\n";
}

void User :: logout(vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db){
    writefile(car_db, "car_data.csv");
    writefile(customer_db, "customer_data.csv");
    writefile(employee_db, "employee_data.csv");
    writefile(manager_db, "manager_data.csv");
    cout<<"Logging out...\n";
    User u; 
    u.display_menu();
}

//function that allows the user to clear his/her dues
void User :: clear_fine_amount(string id, string type_user, vector<vector<string>> &employee_db, vector<vector<string>> &customer_db){
    vector<vector<string>> copy;
    if(type_user=="1"){
        copy = customer_db;
    }
    else if(type_user=="2"){
        copy = employee_db;
    }
    else {
        cout<<"Some error occured\n";
        return;
    }
    for(int i=0; i<copy.size(); i++){
            if(copy[i][0]==id){
                copy[i][4] = "0";
                break;
            }
        }
    if(type_user=="1"){
        customer_db=copy;
    }
    else if(type_user=="2"){
        employee_db=copy;
    }
    return;
}

void manager :: display_manager_menu(string id, vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db){
    cout<<"---------------------------------------------------------------------\n";
    cout<<"\nWelcome "<<id<<"! You are logged in as manager.\n\n";
    cout<<"Press 1 to add a user\n";
    cout<<"Press 2 to update a user\n";
    cout<<"Press 3 to delete a user\n";
    cout<<"Press 4 to add a car\n";
    cout<<"Press 5 to update a car\n";
    cout<<"Press 6 to delete a car\n";
    cout<<"Press 7 to see all users and their rented cars\n";
    cout<<"Press 8 to view all cars data\n";
    cout<<"Press 9 to logout\n";
    cout<<"---------------------------------------------------------------------\n";
    char c;
    cin>>c;
    manager m;
    User u;
    string type,uid;
    switch(c){
        case '1':
            m.add_user(employee_db, customer_db, manager_db);
            m.display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '2':
            m.update_user(car_db, employee_db, customer_db);
            m.display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '3':
            m.delete_user(car_db, employee_db, customer_db);
            m.display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '4':
            m.add_car(car_db);
            m.display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '5':
            m.update_car(car_db, employee_db, customer_db);
            m.display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '6':
            m.delete_car(car_db, employee_db, customer_db);
            m.display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '7':
            cout<<"Enter the type of user you wish to check records for : 1 for customer, 2 for employee :";
            cin.ignore();
            getline(cin,type);
            if(type !="1" && type!="2"){
                cout<<"\nPlease enter proper type of records to be viewed.\n";
                this->display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
                return;
            }
            m.see_all_cars_rentee(type, car_db, employee_db, customer_db); 
            m.display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '8':
            m.see_all_cars_manager(car_db);
            m.display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        case '9':
            u.logout(car_db, employee_db, customer_db, manager_db);
            m.display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
            break;
        default :
            cout<<"Please enter a valid option.\n";
            m.display_manager_menu(id, car_db, employee_db, customer_db, manager_db);
    }
}

void manager :: add_user(vector<vector<string>> &employee_db, vector<vector<string>> &customer_db, vector<vector<string>> &manager_db){ 
    int flag=0;
    cout<<"Please enter the details of the new user : \n";
    string _name, _id, _password, _type;
    cout<<"Enter type of the user to be registered: 1 for customer, 2 for employee, 3 for manager : ";
    cin.ignore();
    getline(cin,_type);
    if(_type!="1" && _type!="2" && _type!="3"){
        cout<<"\nPlease enter proper type of user to be registered!\n";
        return;
    }
    cout<<"Enter id: ";
    cin>>_id;
    if(_type=="1"){
        for(int i=0; i<customer_db.size(); i++){
            if(customer_db[i][0]==_id){
                cout<<"User with same customer id already exists! Please try a different customer id.\nEnter id: ";
                cin >>_id;
            }
        }
    }
    else if(_type=="2"){
        for(int i=0; i<employee_db.size(); i++){
            if(employee_db[i][0]==_id){
                cout<<"User with same customer id already exists! Please try a different customer id.\nEnter id: ";
                cin >>_id;
            }
        }
    }
    cout<<"Enter name : ";
    cin>>_name;
    cout<<"Enter password : ";
    cin>>_password;
    vector<string> row;
    if(_type=="1"){
        row.push_back(_id);
        row.push_back(_name);
        row.push_back(_password);
        row.push_back(this->default_customer_record);
        row.push_back("0");
        customer_db.push_back(row); 
        flag=1;
    }
    else if(_type=="2"){
        row.push_back(_id);
        row.push_back(_name);
        row.push_back(_password);
        row.push_back(this->default_employee_record);
        row.push_back("0");
        employee_db.push_back(row);
        flag=1;
    }
    else if(_type=="3"){
        row.push_back(_id);
        row.push_back(_name);
        row.push_back(_password);
        manager_db.push_back(row);
        flag=1;
    }
    if(flag) cout<<"New user has been added.\n";
    else cout<<"New user cannot be added.\n";
    return;
}

void manager :: add_car(vector<vector<string>> &car_db){
    cout<<"Please enter the details of the new Car : \n";
    string id,model,condition, price_rate_per_day;
    cout<<"Enter id : ";
    cin.ignore();
    getline(cin,id);
    for(int i=0; i<car_db.size(); i++){
            if(car_db[i][0]==id){
                cout<<"Car with same id already exists! Please try a different car id.\n";
                this->add_car(car_db);
                return;
            }
        }
    cout<<"Enter model : ";
    cin>>model;
    cout<<"Enter current condition of the car : ";
    cin>>condition;
    cout<<"Enter rent rate per day : ";
    cin >>price_rate_per_day;
    vector<string> row;
    row.push_back(id);
    row.push_back(model);
    row.push_back(condition);
    row.push_back("yes");
    row.push_back("*");
    row.push_back("*");
    row.push_back(price_rate_per_day);
    row.push_back("0");
    car_db.push_back(row);
    cout<<"New car has been added.\n";
}
void manager :: delete_car(vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db){
    string car_id;
    cout<<"Enter id of the car to be deleted : ";
    cin>>car_id;
    int found=0;
    for(int i=0;i<car_db.size();i++){
        if(car_db[i][0]==car_id){
            found=1;
            if(car_db[i][3]=="no") {
                cout<<"Warning! This car is rented to someone. \nTo delete, press 1, to exit, press 2.";
                string x;
                cin >>x;
                if(x=="2"){
                    cout<<"Cancelling deletion...\n";
                    return;
                } 
            }
            car_db.erase(car_db.begin()+i,car_db.begin()+i+1);
            break;
        }
    }
    if(found==0) cout<<"Car not found.\n";
    else cout<<"Car has been deleted successfully!\n";
}

void manager :: delete_user(vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db){
    string uid, type;
    cout<<"Enter the type of user to be deleted: 1 for customer, 2 for employee: ";
    cin.ignore();
    getline(cin, type);
    if(type!="1" && type!="2"){
        cout<<"\nPlease enter proper type of user to be deleted!\n";
        return;
    }
    cout<<"Enter the user id of the user to be deleted : ";
    cin>>uid;
    int found=0;
    vector<vector<string>> copy;
    if(type=="1"){
        copy=customer_db;
    }
    else if(type=="2"){
       copy=employee_db;
    }
    for(int i=0;i<car_db.size();i++){
        if(car_db[i][4]==uid){
            cout<<"Warning! This user still has unreturned cars. To still delete this user, press 1, to exit press 2 : ";
            string x;
            cin >>x;
            if(x=="2") return;
            car_db[i][3]="yes";//changing availability of the rented car to yes
            car_db[i][4]="*";
            break;
        }
    }
    for(int i=0;i<copy.size();i++){
        if(copy[i][0]==uid){
            found=1;
            copy.erase(copy.begin()+i,copy.begin()+i+1);
            break;
        }
    }
    if(found==0) cout<<"User not found.\n";
    else cout<<"User deleted successfully!\n";
    if(type=="1"){
        customer_db=copy;
    }
    if(type=="2"){
       employee_db=copy;
    }
}

void manager :: update_user(vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db){
    int fl=0;
    string upid, user_type;
    string new_field;
    cout<<"Enter the type of the user you want to update: 1 for customer, 2 for employee: ";
    cin >>user_type;
    if(user_type!="1" && user_type!="2"){
        cout<<"\nPlease enter proper type of user to be deleted!\n";
        return;
    }
    cout<<"Enter the id of the user you want to update : ";
    cin>>upid;
    cout<<"Enter the serial number of the field you want to update : \n";
    cout<<"1. ID\n";
    cout<<"2. Name of the User\n";
    char c;
    cin>>c;
    vector<vector<string>> copy;
    if(user_type=="1"){
        copy=customer_db;
    }
    else if(user_type=="2"){
        copy=employee_db;
    }
    for(int i=0;i<copy.size();i++){
        if(copy[i][0]==upid){
            fl=1;
            if(c=='1' || c=='2') cout<<"Enter the new value of the field : ";
            cin.ignore();
            getline(cin,new_field);
            if(c=='1'){
                fl=2;
                copy[i][0]=new_field;
            }
            else if(c=='2'){ 
                copy[i][1]=new_field;
                fl=2;
            }
            else{
                cout<<"Invalid input!\n\n";
            }
            break;
        }
    }
    if(user_type=="1"){
        customer_db=copy;
    }
    else if(user_type=="2"){
        employee_db=copy;
    }
    if(fl==2) cout<<"User updated\n";
    else if(fl==0) cout<<"User was not found.\n\n";
}

void manager :: update_car(vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db){
    string isbn_no;
    cout<<"Enter the id number of the car you want to update : ";
    cin>>id;
    cout<<"Enter the serial number of the field you want to update : \n";
    cout<<"1. id of the Car\n";
    cout<<"2. Mode of the Car\n";
    cout<<"3. Condition of the Car\n";
    cout<<"4. Availability of the Car\n";
    cout<<"5. Rentee(person whom it is rented to) of the Car\n";
    cout<<"6. Price per day to be paid for rent of the Car\n :: ";
    char c;
    cin>>c;
    if(c!='1' && c!='2' &&c!='3' && c!='4' && c!='5' && c!='6'){
        cout<<"\nPlease enter proper serial number of the field to be modified!\n";
        return;
    }
    int fl=0;
    string new_field;
    for(int i=0;i<car_db.size();i++){
        if(car_db[i][0]==id){
            fl=1;
            cout<<"Enter the new value of the field : ";
            cin.ignore();
            getline(cin,new_field);
            if(c=='1'){
                car_db[i][0]=new_field;
            }
            else if(c=='2'){
                car_db[i][1]=new_field;
            }
            else if(c=='3'){
                car_db[i][2]=new_field;
            }
            else if(c=='4'){
                car_db[i][3]=new_field;
            }
            else if(c=='5'){
                car_db[i][4]=new_field;
            }
            else if(c=='6'){
                car_db[i][6]=new_field;
            }
            else{
                cout<<"Invalid input!\n\n";
            }
            break;
        }
    }
    if(fl==0) cout<<"Car was not found.\n\n";
    else cout<<"Car updated\n";
}

void manager :: see_all_cars_rentee(string type, vector<vector<string>> &car_db,  vector<vector<string>> &employee_db, vector<vector<string>> &customer_db){
    vector<vector<string>> copy;
    if(type=="1") copy=customer_db;
    else copy=employee_db;
    int count=0;
    for(int i=0;i<copy.size();i++){
        vector<string> to_list;
        for(int j=0; j<car_db.size(); j++){
            if(car_db[j][4]==copy[i][0]){
                to_list.push_back(car_db[j][0]);
            }
        }
        cout<<"User id: "<<copy[i][0]<<" | \n";
        if(to_list.size()==0) cout<<"Cars rented : None\n";
        else{
            for(auto a: to_list){
                cout<<"Cars rented : "<< a<<" | "<<endl;
            }
        }
        cout<<endl;
    }
}