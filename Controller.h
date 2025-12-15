#pragma once
#include "Model.h"
#include "View.h"

class Controller {
public:
    Controller(const char* db_connection_string);
    void main_run();

private:
    Model model;
    View view;

    int getMainMenuChoice();
    int getShowMenuChoice();
    int getAddMenuChoice();
    int getUpdateMenuChoice();
    int getGenerateMenuChoice();
    int getSearchMenuChoice();

    void handleShowData();
    void handleAddData();
    void handleUpdateData();
    void handleDeleteData();
    void handleGenerateData();
    void handleSearchData();

    void handleAddResearcher();
    void handleAddDiscipline();
    void handleAddLicense();
    void handleAddPublication();
    void handleAddFile();
    void handleAddAuthorship();

    void handleUpdateResearcher();
    void handleUpdatePublication();
    void handleUpdateFile();

    void handleSearch1();
    void handleSearch2();
    void handleSearch3();
};