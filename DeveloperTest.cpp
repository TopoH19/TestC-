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
        cerr << "Error to parse JSON: " << e.what() << endl;
    }
}

//method to parse all the data employee and after that add the employee information to the vector
void splitXml(const std::string& string_xml, std::vector<EmployeeInformation>& employees) {
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_string(string_xml.c_str());
    if (!result) {
        std::cerr << "Error with the XML file: " << result.description() << std::endl;
        return;
    }
    try {
        for (pugi::xml_node employee_node : doc.select_nodes("//employee")) {
            pugi::xml_node userName_node = employee_node.child("userName");
            pugi::xml_node id_node = employee_node.child("id");
            pugi::xml_node department_node = employee_node.child("department");
            pugi::xml_node salary_node = employee_node.child("salary");

            if (userName_node && id_node && department_node && salary_node) {
                EmployeeInformation employee;
                employee.userName = userName_node.text().get();
                employee.id = id_node.text().as_int();
                employee.department = department_node.text().get();
                employee.salary = salary_node.text().as_double();
                employees.push_back(employee);
            } else {
                std::cerr << "Data Imcomplete" << std::endl;
            }
        }
    } catch (const pugi::xml_parse_error& e) {
        std::cerr << "Error to parse XML: " << e.what() << std::endl;
    }
}

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
