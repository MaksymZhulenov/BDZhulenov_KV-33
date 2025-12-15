#pragma once
#include <iostream>

using std::string;

enum class Status {
    OK,
    INPUT_SUCCESS,
    UPDATE_SUCCESS,
    DELETE_SUCCESS,
    GENERATE_SUCCESS,
    INVALID_CHOICE,
    INVALID_INPUT_GENERAL,
    INVALID_INPUT_NUMBER,
    INVALID_INPUT_DATE,
    DELETE_FAILED_FK,
    DELETE_FAILED_GENERAL,
    ADD_FAILED_FK,
    ADD_FAILED_GENERAL,
    UPDATE_FAILED_GENERAL,
    GENERATE_FAILED_DEPENDENCY,
    DB_CONNECTION_ERROR,
    DB_QUERY_ERROR,
    UNKNOWN_ERROR
};

class View {
public:
    void showMessage(const string& message);
    string getInput(const string& prompt);
    int getIntInput(const string& prompt);

    void displayMainMenu();
    void displayShowMenu();
    void displayAddMenu();
    void displayUpdateMenu();
    void displayGenerateMenu();
    void displaySearchMenu();
    void displaySectionTitle(const string& title);

    void displayStatus(Status s, const string& detail = "");
    void showExecutionTime(double time_ms);
    void displayError(const string& error_message);
};