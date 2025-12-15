#include "View.h"
#include "Model.h"  
#include <iostream>

using std::string;

void View::showMessage(const string& message) {
    std::cout << message << std::endl;
}

string View::getInput(const string& prompt) {
    string input;
    std::cout << prompt;
    std::getline(std::cin >> std::ws, input);
    return input;
}

int View::getIntInput(const string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(1024, '\n');
            showMessage("ERROR: Please enter a valid integer.");
        }
        else {
            std::cin.ignore(1024, '\n');
            return value;
        }
    }
}

void View::displayMainMenu() {
    showMessage("\n--- MAIN MENU ---");
    showMessage("1. View Data");
    showMessage("2. Add Data");
    showMessage("3. Update Data");
    showMessage("4. Delete Data");
    showMessage("5. Generate Data");
    showMessage("6. Advanced Search");
    showMessage("7. Exit");
}

void View::displayShowMenu() {
    showMessage("\n--- 1. VIEW DATA ---");
    showMessage("1. Show Researchers");     
    showMessage("2. Show Disciplines");      
    showMessage("3. Show Publications");     
    showMessage("4. Show Files");            
    showMessage("5. Show Licenses");         
    showMessage("6. Show Authorship Links"); 
    showMessage("7. Show ALL Tables");        
    showMessage("8. Back");
}

void View::displayAddMenu() {
    showMessage("\n--- ADD DATA ---");
    showMessage("1. Add Researcher");
    showMessage("2. Add Publication");
    showMessage("3. Add File");
    showMessage("4. Add Authorship Link");
    showMessage("5. Add Discipline");
    showMessage("6. Add License");
    showMessage("7. Back");
}

void View::displayUpdateMenu() {
    showMessage("\n--- UPDATE DATA ---");
    showMessage("1. Edit Researcher");
    showMessage("2. Edit Publication");
    showMessage("3. Edit File");
    showMessage("4. Back");
}

void View::displayGenerateMenu() {
    showMessage("\n--- GENERATE DATA ---");
    showMessage("1. Generate Disciplines");
    showMessage("2. Generate Licenses");
    showMessage("3. Generate Researchers");
    showMessage("4. Generate Publications (Requires Disc/Lic)");
    showMessage("5. Generate Files (Requires Pubs)");
    showMessage("6. Generate Authorship (Requires Res/Pubs)");
    showMessage("7. Back");
}

void View::displaySearchMenu() {
    showMessage("\n--- ADVANCED SEARCH ---");
    showMessage("1. Publications by Date Range & Title");
    showMessage("2. Files by Format & Size Range");
    showMessage("3. Researchers in Discipline (Complex Join)");
    showMessage("4. Back");
}

void View::displaySectionTitle(const string& title) {
    showMessage("\n--- " + title + " ---");
}

void View::displayStatus(Status s, const string& detail) {
    switch (s) {
    case Status::OK:                     break;
    case Status::INPUT_SUCCESS:          showMessage("Data added successfully."); break;
    case Status::UPDATE_SUCCESS:         showMessage("Record updated successfully."); break;
    case Status::DELETE_SUCCESS:         showMessage("Record deleted successfully."); break;
    case Status::GENERATE_SUCCESS:       showMessage(detail + " records generated successfully."); break;
    case Status::INVALID_CHOICE:         showMessage("Invalid choice. Please try again."); break;
    case Status::INVALID_INPUT_GENERAL:  showMessage("Invalid input: " + detail); break;
    case Status::INVALID_INPUT_NUMBER:   showMessage("Invalid number entered."); break;
    case Status::INVALID_INPUT_DATE:     showMessage("Invalid date format. Use YYYY-MM-DD."); break;
    case Status::DELETE_FAILED_FK:       showMessage("ERROR: Cannot delete record, it is referenced by other tables."); break;
    case Status::DELETE_FAILED_GENERAL:  showMessage("ERROR: Deletion failed. " + detail); break;
    case Status::ADD_FAILED_FK:          showMessage("ERROR: Cannot add record. Referenced ID not found. " + detail); break;
    case Status::ADD_FAILED_GENERAL:     showMessage("ERROR: Failed to add record. " + detail); break;
    case Status::UPDATE_FAILED_GENERAL:  showMessage("ERROR: Failed to update record. " + detail); break;
    case Status::GENERATE_FAILED_DEPENDENCY: showMessage("ERROR: Cannot generate data. Generate prerequisite data first."); break;
    case Status::DB_CONNECTION_ERROR:    showMessage("CRITICAL ERROR: Database connection failed. " + detail); break;
    case Status::DB_QUERY_ERROR:         showMessage("DATABASE ERROR: " + detail); break;
    case Status::UNKNOWN_ERROR:          showMessage("An unknown critical error occurred."); break;
    default:                             showMessage("An unspecified status occurred."); break;
    }
}

void View::showExecutionTime(double time_ms) {
    std::cout << "\n[i] Query execution time: " << time_ms << " ms" << std::endl;
}

void View::displayError(const string& error_message) {
    showMessage("\n!!! ERROR !!!");
    showMessage(error_message);
}