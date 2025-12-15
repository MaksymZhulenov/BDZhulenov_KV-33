#include "Controller.h"
#include <iostream>
#include <sstream>

Controller::Controller(const char* conn) : model(conn), view() {}

void Controller::main_run() {
    bool running = true;
    while (running) {
        try {
            int c = getMainMenuChoice();
            if (c == 7) running = false;
            else if (c == 1) handleShowData();
            else if (c == 2) handleAddData();
            else if (c == 3) handleUpdateData();
            else if (c == 4) handleDeleteData();
            else if (c == 5) handleGenerateData();
            else if (c == 6) handleSearchData();
            else view.displayStatus(Status::INVALID_CHOICE);
        }
        catch (const std::exception& e) {
            view.displayError(e.what());
        }
    }
}

int Controller::getMainMenuChoice() { view.displayMainMenu(); return view.getIntInput("Choice: "); }
int Controller::getShowMenuChoice() { view.displayShowMenu(); return view.getIntInput("Choice: "); }
int Controller::getAddMenuChoice() { view.displayAddMenu(); return view.getIntInput("Choice: "); }
int Controller::getUpdateMenuChoice() { view.displayUpdateMenu(); return view.getIntInput("Choice: "); }
int Controller::getGenerateMenuChoice() { view.displayGenerateMenu(); return view.getIntInput("Choice: "); }
int Controller::getSearchMenuChoice() { view.displaySearchMenu(); return view.getIntInput("Choice: "); }

void Controller::handleShowData() {
    bool running = true;
    while (running) {
        int c = getShowMenuChoice();
        switch (c) {
        case 1: model.printAllResearchers(); break;
        case 2: model.printAllDisciplines(); break;
        case 3: model.printAllPublications(); break;
        case 4: model.printAllFiles(); break;
        case 5: model.printAllLicenses(); break;
        case 6: model.printAllAuthorships(); break;
        case 7: 
            model.printAllResearchers(); model.printAllDisciplines();
            model.printAllPublications(); model.printAllFiles();
            model.printAllLicenses(); model.printAllAuthorships();
            break;
        case 8: running = false; break;
        default: view.displayStatus(Status::INVALID_CHOICE);
        }
    }
}

void Controller::handleAddData() {
    int c = getAddMenuChoice();
    switch (c) {
    case 1: handleAddResearcher(); break;
    case 2: handleAddPublication(); break;
    case 3: handleAddFile(); break;
    case 4: handleAddAuthorship(); break;
    case 5: handleAddDiscipline(); break;
    case 6: handleAddLicense(); break;
    case 7: break;
    default: view.displayStatus(Status::INVALID_CHOICE);
    }
}

void Controller::handleAddResearcher() {
    model.addResearcher(view.getInput("First Name: "), view.getInput("Last Name: "), view.getInput("Degree: "), view.getInput("Email: "));
    view.displayStatus(Status::INPUT_SUCCESS);
}
void Controller::handleAddDiscipline() {
    model.addDiscipline(view.getInput("Name: "), view.getInput("Code: "), view.getInput("Desc: "));
    view.displayStatus(Status::INPUT_SUCCESS);
}
void Controller::handleAddLicense() {
    model.addLicense(view.getInput("Name: "), view.getInput("Type: "), view.getIntInput("Price: "), view.getInput("Desc: "));
    view.displayStatus(Status::INPUT_SUCCESS);
}
void Controller::handleAddPublication() {
    model.addPublication(view.getIntInput("Discipline ID: "), view.getIntInput("License ID: "),
        view.getInput("Title: "), view.getInput("Abstract: "), view.getInput("Date (YYYY-MM-DD): "), 1, view.getInput("DOI: "));
    view.displayStatus(Status::INPUT_SUCCESS);
}
void Controller::handleAddFile() {
    model.addFile(view.getIntInput("Pub ID: "), view.getInput("Name: "), view.getInput("Format: "), view.getIntInput("Size: "));
    view.displayStatus(Status::INPUT_SUCCESS);
}
void Controller::handleAddAuthorship() {
    model.addAuthorship(view.getIntInput("Researcher ID: "), view.getIntInput("Pub ID: "), view.getInput("Role: "));
    view.displayStatus(Status::INPUT_SUCCESS);
}

void Controller::handleUpdateData() {
    int c = getUpdateMenuChoice();
    switch (c) {
    case 1: handleUpdateResearcher(); break;
    case 2: handleUpdatePublication(); break;
    case 3: handleUpdateFile(); break;
    case 4: break;
    default: view.displayStatus(Status::INVALID_CHOICE);
    }
}
void Controller::handleUpdateResearcher() {
    model.updateResearcher(view.getIntInput("ID: "), view.getInput("First: "), view.getInput("Last: "), view.getInput("Degree: "), view.getInput("Email: "));
    view.displayStatus(Status::UPDATE_SUCCESS);
}
void Controller::handleUpdatePublication() {
    model.updatePublication(view.getIntInput("ID: "), view.getInput("Title: "), view.getIntInput("Ver: "), view.getInput("DOI: "));
    view.displayStatus(Status::UPDATE_SUCCESS);
}
void Controller::handleUpdateFile() {
    model.updateFile(view.getIntInput("ID: "), view.getInput("Name: "), view.getIntInput("Size: "));
    view.displayStatus(Status::UPDATE_SUCCESS);
}

void Controller::handleDeleteData() {
    string table = view.getInput("Table name (researcher, publication, file...): ");
    string col = view.getInput("ID Column (researcher_id...): ");
    int id = view.getIntInput("ID to delete: ");
    model.deleteData(table, col, id);
    view.displayStatus(Status::DELETE_SUCCESS);
}

void Controller::handleGenerateData() {
    int c = getGenerateMenuChoice();
    int n = view.getIntInput("Count: ");
    switch (c) {
    case 1: model.generateDisciplines(n); break;
    case 2: model.generateLicenses(n); break;
    case 3: model.generateResearchers(n); break;
    case 4: model.generatePublications(n); break;
    case 5: model.generateFiles(n); break;
    case 6: model.generateAuthorships(n); break;
    default: break;
    }
    view.displayStatus(Status::GENERATE_SUCCESS);
}

void Controller::handleSearchData() {
    int c = getSearchMenuChoice();
    double t = 0;
    if (c == 1) {
        t = model.searchPublicationsByDateAndTitle(view.getInput("Start Date: "), view.getInput("End Date: "), view.getInput("Title Part: "));
    }
    else if (c == 2) {
        t = model.searchFilesByFormatAndSize(view.getInput("Format (pdf/doc): "), view.getIntInput("Min Size: "), view.getIntInput("Max Size: "));
    }
    else if (c == 3) {
        t = model.searchResearchersByDiscipline(view.getInput("Discipline Name: "));
    }
    view.showExecutionTime(t);
}