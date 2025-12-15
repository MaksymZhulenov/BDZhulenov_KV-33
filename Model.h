#pragma once
#include <soci/soci.h>
#include <ctime>
#include <vector>

using std::string;

struct Researcher { int id; string first_name, last_name, degree, email; };
struct Discipline { int id; string name, code, desc; };
struct License { int id; string name, type; double price; string desc; };
struct Publication { int id, disc_id, lic_id; string title, abstract; std::tm pub_date; int version; string doi; };
struct File { int id, pub_id; string name, format; int size; std::tm upload_date; };
struct Authorship { int id, res_id, pub_id; string role; };

class Model {
private:
    soci::session sql;
    long long getLastId(const string& table, const string& id_col);
    void checkDbConnection();
    std::tm stringToTm(const string& date_str);

public:
    Model(const string& conn_string);
    ~Model();

    void printAllResearchers();
    void printAllDisciplines();
    void printAllLicenses();
    void printAllPublications();
    void printAllFiles();
    void printAllAuthorships();

    void addResearcher(const string& f_name, const string& l_name, const string& deg, const string& email);
    void addDiscipline(const string& name, const string& code, const string& desc);
    void addLicense(const string& name, const string& type, double price, const string& desc);
    void addPublication(int disc_id, int lic_id, const string& title, const string& abstract, const string& date_str, int ver, const string& doi);
    void addFile(int pub_id, const string& name, const string& fmt, int size);
    void addAuthorship(int res_id, int pub_id, const string& role);

    void updateResearcher(int id, const string& f_name, const string& l_name, const string& deg, const string& email);
    void updatePublication(int id, const string& title, int version, const string& doi);
    void updateFile(int id, const string& name, int size);

    void deleteData(const string& table_name, const string& id_col, int id);

    void generateResearchers(int count);
    void generateDisciplines(int count);
    void generateLicenses(int count);
    void generatePublications(int count);
    void generateFiles(int count);
    void generateAuthorships(int count);

    double searchPublicationsByDateAndTitle(const string& start_date, const string& end_date, const string& title_part);
    double searchFilesByFormatAndSize(const string& format, int min_size, int max_size);
    double searchResearchersByDiscipline(const string& discipline_name);
};