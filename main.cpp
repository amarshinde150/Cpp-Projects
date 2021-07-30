#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Registration {
protected:
    /** Variables **/
    string name;
    string email;
    string password;

    /** Methods **/
    bool checkAvailabilityOfEmail();
    bool checkCorrectnessOfEmail();
    bool checkPasswordStrength();
    bool writeToFile();
    void encryptPassword(); //yet in development Phase
public:
    Registration();
    Registration(string realName,string realEmail,string realPassword);
    Registration(string realEmail,string realPassword);
    void readInput();
};

class Login:public Registration {
public:
    bool checkCorrectnessOfPassword();
    Login(string realEmail,string realPassword):Registration(realEmail,realPassword){}
    Login();
    void readInput();
};


/******************** Definition of methods of Registration ***********************/
Registration:: Registration(){
    ofstream fout;
    fout.open("usersLogin.txt",ios::app);
    fout.close();
}
Registration ::Registration(string realName,string realEmail,string realPassword) {
    ofstream fout;
    fout.open("usersLogin.txt",ios::app);
    fout.close();
    name = realName;
    email= realEmail;
    password = realPassword;
    while(true) {
        bool written;
        written = writeToFile();
        if(written) {
            cout<<endl<<endl<<"Successfully Registered!!!!!!!"<<endl<<endl;
            break;
        } else {
            cout<<"Error while writing to file\nTry again...."<<endl;
            readInput();
        }
    }
}

void Registration::readInput() {
    cout<<"Enter your name:"<<endl;
    cin>>name;
    bool x=false;
    do {
        if(x){
            cout<<"email is already used..."<<endl;
            x=false;
        }
        cout<<"Enter your email:"<<endl;
        cin>>email;
    } while(!(checkCorrectnessOfEmail()) ||  (x=(checkAvailabilityOfEmail())));

    do{

    cout<<"Enter your password:"<<endl;
    cin>>password;
    }while(!checkPasswordStrength());
    Registration(name,email,password);
}

bool Registration:: checkAvailabilityOfEmail() {
    ifstream fin;
    fin.open("usersLogin.txt");
    while(!fin.eof()) {
        Registration temp;
        fin>>temp.name>>temp.email>>temp.password;
        if( email.compare(temp.email)==0) {
            fin.close();
            return true;
        } else {
            continue;
        }

    }

    fin.close();
    return false;
}

bool Registration:: checkCorrectnessOfEmail() {
    string tempEmail=email;
    int check=0;
    for(int i=0; i<tempEmail.length(); i++) {
        if(tempEmail[i]=='@') {
            check++;
        } else if(tempEmail[i]=='.') {
            check++;
        }
    }
    if(check>=2) {
        return true;
    } else {
        cout<<"wrong email formate"<<endl;
        return false;
    }
}

bool Registration:: checkPasswordStrength(){
    string tempPassword=password;
    if(tempPassword.length()<6)
    {
        cout<<"Password should be more than five digits"<<endl;
        return false;
    }
    int characters=0,digits=0,symbols=0;
    for(int i=0;i<tempPassword.length();i++){
        if((tempPassword[i]>='a' && tempPassword[i]<='z' )||(tempPassword[i]>='A' && tempPassword[i]<='Z' )){
            characters++;
        }
    }

    for(int i=0;i<tempPassword.length();i++){
        if((tempPassword[i]>='0' && tempPassword[i]<='9' )){
            digits++;
        }
    }

    for(int i=0;i<tempPassword.length();i++){
        if(!(tempPassword[i]>='0' && tempPassword[i]<='9' ) && !((tempPassword[i]>='a' && tempPassword[i]<='z' )||(tempPassword[i]>='A' && tempPassword[i]<='Z' ))){
            symbols++;
        }
    }
    if(symbols>0 && characters>0 && digits>0){
        return true;
    }
    cout<<"Password should contain at least one symbol, one charcter, one digit"<<endl;
    return false;
}

bool Registration:: writeToFile() {
    ofstream fout;
    fout.open("usersLogin.txt",ios::app);
    fout<<name<<" "<<email<<" "<<password<<endl;
    fout.close();
    return true;
}

/******************** Definition of methods of Login ***********************/
Login:: Login(){
    ofstream fout;
    fout.open("usersLogin.txt",ios::app);
    fout.close();
}
void Login:: readInput(){
    int trigger=1;
    do{
        if(trigger==0){
            cout<<"Email is not registered..."<<endl;
        }
        trigger=0;
        cout<<"Enter email:"<<endl;
        cin>>email;
    }while(!checkAvailabilityOfEmail());
    do{

    cout<<"Enter password:"<<endl;
    cin>>password;
    }while(!checkCorrectnessOfPassword());
}

bool Login:: checkCorrectnessOfPassword(){
    ifstream fin;
    fin.open("usersLogin.txt");
    Login temp;
    while(!fin.eof())
    {
        fin>>temp.name>>temp.email>>temp.password;
        if(!email.compare(temp.email))
        {
            if(password==temp.password){
                cout<<endl<<"Logged in successfully..."<<endl;
                return true;
            }
            else{
                cout<<"wrong password!!!"<<endl;
                return false;
            }
        }
    }
    return false;
}

int main() {
    Registration r;
    Login l;
    int choice;
    cout<<"WELCOME TO LOGIN AND REGISTRATION SYSTEM -by Amar Shinde"<<endl<<endl;
    while(true){
        cout<<"1.Create account"<<endl<<"2.Login"<<endl<<"any other number to exit"<<endl;
        cin>>choice;
        if(choice==1){

            r.readInput();
        }
        else if(choice == 2){
            l.readInput();
            break;
        }
        else{
            break;
        }
    }
    return 0;
}
