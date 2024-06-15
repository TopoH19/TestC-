#include <iostream>
#include <fstream>
#include <vector>
#include <pluginxml.hpp>
#include <json.hpp>
#include <jsoncpp/json/json.h>
#include <regex>
#include "nlohmann/json.hpp" 

using json = nlohmann::json;

using namespace std;


int main(int argc, string employee){
    std::vector<employeeInformation> employees;
    // if document type is true means that we have to exceute all the steps for json document, else xml
    bool documentType = documentType(employee);
    if(documentType == true){
        splitJson(employee,employees);
    }else{
        //splitXml(employee,employees);
    }
    
    averageSalary(employees);
    
    highestSalary(employees);
    
    sortByID(employees);
    return 0;
}

//method to validate if the string received is a json and return true it does. if return false we already know that is a xml 
bool documentType(const std::string& str){
    std::regex jsonRegex("\\{.*\\}");
    return std::regex_match(str, jsonRegex);
}

//information of the user
struct employeeInformation {
    std::string userName;
    int id;
    std::string department;
    double salary;
};

//method to parse all the data employee and after that add the employee information to the vector
void splitJson(const string& string_json, vector<employeeInformation>& employees){
    try {
        json j = json::parse(string_json);
        if (j.find("userName") != j.end() && j.find("id") != j.end() && j.find("department") != j.end() && j.find("salary") != j.end()) {
            employeeInformation employee;
            employee.userName = j["userName"];
            employee.id = j["id"];
            employee.department = j["department"];
            employee.salary = j["salary"];
            employees.push_back(employee);
        } else {
            cerr << "Data incomplete" << endl;
        }
    } catch (const json::parse_error& e) {
        cerr << "Error al parsear JSON: " << e.what() << endl;
    }
}

//method to parse all the data employee and after that add the employee information to the vector
/*

*/

//Method to calculate the average salary for all the employees
double averageSalary(const std::vector<employeeInformation>& employees){
    double averageSalary;
    if (employees.empty()){
        averageSalary = 0.0;
    }else{
        for (int i = 0; i < employees.size(); i++) {
            averageSalary += employees.salary;
        }
        averageSalary = averageSalary/employees.size();
    }
    return averageSalary;
}

//Method to validate the highest salary and return the data of the highest paid
employeeInformation highestSalary(const std::vector<employeeInformation>& employees){
    double highestSalary = 0.0;
    employeeInformation highestPaid;
    if(employees.empty()){
        employeeInformation highestPaid = null;
    }else{
        for (int i = 0; i < employees.size(); i++) {
            if(employees.salary > highestSalary){
                highestSalary = employees.salary;
                employeeInformation highestPaid = (employees.name,employees.id,employees.department,employees.salary);
            }
        }
    }
    return highestPaid;
}

//method to sort all the employees
void sortByID(std::vector<employeeInformation>& employees){
    std::sort(employees.begin(), employees.end(),[](const employees.id& a, const employee.id& b) {
        return a.id < b.id;
    });
}
