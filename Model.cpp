#include "Model.h"
#include <soci/postgresql/soci-postgresql.h>
#include <soci/rowset.h>
#include <iostream>
#include <iomanip>

namespace soci
{
    template<> struct type_conversion<Researcher> {
        typedef values base_type;
        static void from_base(values const& v, indicator, Researcher& r) {
            r.id = v.get<int>("researcher_id"); r.first_name = v.get<string>("first_name");
            r.last_name = v.get<string>("last_name"); r.degree = v.get<string>("degree");
            r.email = v.get<string>("email");
        }
    };
    template<> struct type_conversion<Discipline> {
        typedef values base_type;
        static void from_base(values const& v, indicator, Discipline& d) {
            d.id = v.get<int>("discipline_id"); d.name = v.get<string>("name");
            d.code = v.get<string>("code"); d.desc = v.get<string>("description");
        }
    };
    template<> struct type_conversion<License> {
        typedef values base_type;
        static void from_base(values const& v, indicator, License& l) {
            l.id = v.get<int>("license_id"); l.name = v.get<string>("license_name");
            l.type = v.get<string>("access_type"); l.price = v.get<double>("price");
            l.desc = v.get<string>("description");
        }
    };
    template<> struct type_conversion<Publication> {
        typedef values base_type;
        static void from_base(values const& v, indicator, Publication& p) {
            p.id = v.get<int>("publication_id"); p.disc_id = v.get<int>("discipline_id");
            p.lic_id = v.get<int>("license_id"); p.title = v.get<string>("title");
            p.abstract = v.get<string>("abstract"); p.pub_date = v.get<std::tm>("publish_date");
            p.version = v.get<int>("version"); p.doi = v.get<string>("doi");
        }
    };
    template<> struct type_conversion<File> {
        typedef values base_type;
        static void from_base(values const& v, indicator, File& f) {
            f.id = v.get<int>("file_id"); f.pub_id = v.get<int>("publication_id");
            f.name = v.get<string>("file_name"); f.format = v.get<string>("format");
            f.size = v.get<int>("size"); f.upload_date = v.get<std::tm>("upload_date");
        }
    };
    template<> struct type_conversion<Authorship> {
        typedef values base_type;
        static void from_base(values const& v, indicator, Authorship& a) {
            a.id = v.get<int>("authorship_id"); a.res_id = v.get<int>("researcher_id");
            a.pub_id = v.get<int>("publication_id"); a.role = v.get<string>("role");
        }
    };
}

static std::string truncate(std::string str, size_t width) {
    if (str.length() > width) return str.substr(0, width - 3) + "...";
    return str;
}

static string tmToStringHelper(std::tm t) {
    char buffer[20];
    if (std::strftime(buffer, sizeof(buffer), "%Y-%m-%d", &t)) return string(buffer);
    return "N/A";
}

Model::Model(const string& conn_string) {
    try {
        sql.open(soci::postgresql, conn_string);
        sql << "SET lc_messages = 'English'";
        checkDbConnection();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("DB Connection Failed: " + string(e.what()));
    }
}

Model::~Model() { if (sql.is_connected()) sql.close(); }

void Model::checkDbConnection() {
    if (!sql.is_connected()) throw std::runtime_error("Database connection lost.");
}

long long Model::getLastId(const string& table, const string& id_col) {
    long long last_id = 0;
    sql << "SELECT COALESCE(MAX(" + id_col + "), 0) FROM public." + table, soci::into(last_id);
    return last_id;
}

std::tm Model::stringToTm(const string& date_str) {
    std::tm t = {};
    if (date_str.length() < 10) throw std::runtime_error("Invalid date. Use YYYY-MM-DD");
    t.tm_year = std::stoi(date_str.substr(0, 4)) - 1900;
    t.tm_mon = std::stoi(date_str.substr(5, 2)) - 1;
    t.tm_mday = std::stoi(date_str.substr(8, 2));
    return t;
}

void Model::printAllResearchers() {
    std::cout << "\n--- RESEARCHERS TABLE ---\n";
    soci::rowset<Researcher> rs = (sql.prepare << "SELECT * FROM public.researcher ORDER BY researcher_id");
    std::cout << std::left
        << std::setw(5) << "ID"
        << std::setw(30) << "Full Name"
        << std::setw(20) << "Degree"
        << std::setw(30) << "Email" << "\n";
    std::cout << string(90, '-') << "\n";

    for (const auto& r : rs) {
        std::cout << std::left
            << std::setw(5) << r.id
            << std::setw(30) << (r.first_name + " " + r.last_name)
            << std::setw(20) << r.degree
            << std::setw(30) << r.email << "\n";
    }
}

void Model::printAllDisciplines() {
    std::cout << "\n--- DISCIPLINES TABLE ---\n";
    soci::rowset<Discipline> rs = (sql.prepare << "SELECT * FROM public.discipline ORDER BY discipline_id");
    std::cout << std::left << std::setw(5) << "ID" << std::setw(10) << "Code" << std::setw(40) << "Name" << "\n";
    std::cout << string(60, '-') << "\n";

    for (const auto& d : rs) {
        std::cout << std::left << std::setw(5) << d.id << std::setw(10) << d.code << std::setw(40) << d.name << "\n";
    }
}

void Model::printAllPublications() {
    std::cout << "\n--- PUBLICATIONS TABLE ---\n";
    soci::rowset<Publication> rs = (sql.prepare << "SELECT * FROM public.publication ORDER BY publication_id");
    for (const auto& p : rs) {
        std::cout << "ID: " << p.id
            << " | Date: " << tmToStringHelper(p.pub_date)
            << " | DOI: " << p.doi << "\n"
            << "   Title: " << p.title << "\n";
    }
}

void Model::printAllFiles() {
    std::cout << "\n--- FILES TABLE ---\n";
    soci::rowset<File> rs = (sql.prepare << "SELECT * FROM public.file ORDER BY file_id");
    std::cout << std::left << std::setw(5) << "ID" << std::setw(35) << "File Name" << std::setw(10) << "Size(KB)" << std::setw(8) << "PubID" << "\n";
    std::cout << string(65, '-') << "\n";

    for (const auto& f : rs) {
        std::cout << std::left << std::setw(5) << f.id
            << std::setw(35) << f.name
            << std::setw(10) << f.size
            << std::setw(8) << f.pub_id << "\n";
    }
}

void Model::printAllAuthorships() {
    std::cout << "\n--- AUTHORSHIP LINKS TABLE ---\n";
    soci::rowset<soci::row> rs = (sql.prepare <<
        "SELECT a.authorship_id, r.last_name, p.title, a.role FROM public.authorship a "
        "JOIN public.researcher r ON a.researcher_id = r.researcher_id "
        "JOIN public.publication p ON a.publication_id = p.publication_id");

    std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "Researcher" << std::setw(40) << "Publication" << std::setw(15) << "Role" << "\n";
    std::cout << string(85, '-') << "\n";

    for (const auto& r : rs) {
        std::cout << std::left << std::setw(5) << r.get<int>(0)
            << std::setw(20) << r.get<string>(1)
            << std::setw(40) << r.get<string>(2)
            << std::setw(15) << r.get<string>(3) << "\n";
    }
}

void Model::printAllLicenses() {
    std::cout << "\n--- LICENSES TABLE ---\n";
    soci::rowset<License> rs = (sql.prepare << "SELECT * FROM public.license ORDER BY license_id");
    std::cout << std::left << std::setw(5) << "ID" << std::setw(20) << "Name" << std::setw(15) << "Type" << std::setw(10) << "Price" << "\n";
    std::cout << string(55, '-') << "\n";
    for (const auto& l : rs) {
        std::cout << std::left << std::setw(5) << l.id << std::setw(20) << l.name << std::setw(15) << l.type << std::setw(10) << l.price << "\n";
    }
}

void Model::addResearcher(const string& f_name, const string& l_name, const string& deg, const string& email) {
    sql << "INSERT INTO public.researcher (first_name, last_name, degree, email) VALUES (:f, :l, :d, :e)",
        soci::use(f_name), soci::use(l_name), soci::use(deg), soci::use(email);
}

void Model::addDiscipline(const string& name, const string& code, const string& desc) {
    sql << "INSERT INTO public.discipline (name, code, description) VALUES (:n, :c, :d)",
        soci::use(name), soci::use(code), soci::use(desc);
}

void Model::addLicense(const string& name, const string& type, double price, const string& desc) {
    sql << "INSERT INTO public.license (license_name, access_type, price, description) VALUES (:n, :t, :p, :d)",
        soci::use(name), soci::use(type), soci::use(price), soci::use(desc);
}

void Model::addPublication(int disc_id, int lic_id, const string& title, const string& abstract, const string& date_str, int ver, const string& doi) {
    std::tm p_date = stringToTm(date_str);
    sql << "INSERT INTO public.publication (discipline_id, license_id, title, abstract, publish_date, version, doi) "
        "VALUES (:did, :lid, :ti, :ab, :dt, :v, :doi)",
        soci::use(disc_id), soci::use(lic_id), soci::use(title), soci::use(abstract), soci::use(p_date), soci::use(ver), soci::use(doi);
}

void Model::addFile(int pub_id, const string& name, const string& fmt, int size) {
    std::tm now = {}; time_t t = time(0); localtime_s(&now, &t);
    sql << "INSERT INTO public.file (publication_id, file_name, format, size, upload_date) VALUES (:pid, :nm, :fmt, :sz, :dt)",
        soci::use(pub_id), soci::use(name), soci::use(fmt), soci::use(size), soci::use(now);
}

void Model::addAuthorship(int res_id, int pub_id, const string& role) {
    sql << "INSERT INTO public.authorship (researcher_id, publication_id, role) VALUES (:rid, :pid, :rl)",
        soci::use(res_id), soci::use(pub_id), soci::use(role);
}

void Model::updateResearcher(int id, const string& f_name, const string& l_name, const string& deg, const string& email) {
    sql << "UPDATE public.researcher SET first_name = :f, last_name = :l, degree = :d, email = :e WHERE researcher_id = :id",
        soci::use(f_name), soci::use(l_name), soci::use(deg), soci::use(email), soci::use(id);
}
void Model::updatePublication(int id, const string& title, int version, const string& doi) {
    sql << "UPDATE public.publication SET title = :t, version = :v, doi = :d WHERE publication_id = :id",
        soci::use(title), soci::use(version), soci::use(doi), soci::use(id);
}
void Model::updateFile(int id, const string& name, int size) {
    sql << "UPDATE public.file SET file_name = :n, size = :s WHERE file_id = :id",
        soci::use(name), soci::use(size), soci::use(id);
}
void Model::deleteData(const string& table_name, const string& id_col, int id) {
    try {
        sql << "DELETE FROM public." + table_name + " WHERE " + id_col + " = :id", soci::use(id);
    }
    catch (const std::exception& e) {
        throw std::runtime_error("Deletion failed (likely Foreign Key constraint): " + string(e.what()));
    }
}

void Model::generateResearchers(int count) {
    sql << R"(
        INSERT INTO public.researcher (first_name, last_name, degree, email)
        SELECT 
        'Name_' || (RANDOM()*1000)::int, 'Surname_' || (RANDOM()*1000)::int,
        (ARRAY['Bachelor','Master','PhD','Doctor'])[floor(random()*4+1)],
        'user' || n || '@science.org'
        FROM generate_series(1, :count) AS s(n)
    )", soci::use(count);
}
void Model::generateDisciplines(int count) {
    sql << R"(
        INSERT INTO public.discipline (name, code, description)
        SELECT 
        'Discipline ' || n, (100 + n)::text, 'Auto-generated description'
        FROM generate_series(1, :count) AS s(n)
    )", soci::use(count);
}
void Model::generateLicenses(int count) {
    sql << R"(
        INSERT INTO public.license (license_name, access_type, price, description)
        SELECT 
        'License-' || n, (ARRAY['Open','Closed','Restricted'])[floor(random()*3+1)],
        (random() * 100)::numeric(5,2), 'Terms...'
        FROM generate_series(1, :count) AS s(n)
    )", soci::use(count);
}
void Model::generatePublications(int count) {
    sql << R"(
        INSERT INTO public.publication (discipline_id, license_id, title, abstract, publish_date, version, doi)
        SELECT 
        (SELECT discipline_id FROM public.discipline ORDER BY RANDOM() LIMIT 1),
        (SELECT license_id FROM public.license ORDER BY RANDOM() LIMIT 1),
        'Scientific Study #' || n, 'Abstract content...',
        NOW() - (random() * 3650 * '1 day'::interval), 1, '10.1000/gen-' || n
        FROM generate_series(1, :count) AS s(n)
    )", soci::use(count);
}
void Model::generateFiles(int count) {
    sql << R"(
        INSERT INTO public.file (publication_id, file_name, format, size, upload_date)
        SELECT 
        (SELECT publication_id FROM public.publication ORDER BY RANDOM() LIMIT 1),
        'file_' || n || '.pdf', 'pdf', (random()*5000)::int, NOW()
        FROM generate_series(1, :count) AS s(n)
    )", soci::use(count);
}
void Model::generateAuthorships(int count) {
    sql << R"(
        INSERT INTO public.authorship (researcher_id, publication_id, role)
        SELECT 
        (SELECT researcher_id FROM public.researcher ORDER BY RANDOM() LIMIT 1),
        (SELECT publication_id FROM public.publication ORDER BY RANDOM() LIMIT 1),
        (ARRAY['Author','Co-Author','Editor'])[floor(random()*3+1)]
        FROM generate_series(1, :count) AS s(n)
        ON CONFLICT DO NOTHING
    )", soci::use(count);
}

double Model::searchPublicationsByDateAndTitle(const string& start_date, const string& end_date, const string& title_part) {
    std::tm t1 = stringToTm(start_date);
    std::tm t2 = stringToTm(end_date);
    string pattern = "%" + title_part + "%";
    int count = 0;

    clock_t start = clock();
    soci::rowset<Publication> rs = (sql.prepare <<
        "SELECT * FROM public.publication WHERE title LIKE :p AND publish_date BETWEEN :d1 AND :d2",
        soci::use(pattern), soci::use(t1), soci::use(t2));

    std::cout << "\n================ SEARCH RESULTS (PUBLICATIONS) ================\n";
    // Виводимо більш детальну інформацію, як у View Data
    for (const auto& p : rs) {
        std::cout << "[ID: " << p.id << "] " << p.title << "\n"
            << "      Date: " << tmToStringHelper(p.pub_date)
            << " | DOI: " << p.doi
            << " | Ver: " << p.version << "\n";
        std::cout << string(60, '-') << "\n";
        count++;
    }

    if (count == 0) std::cout << "No matches found.\n";

    clock_t end = clock();
    return (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
}

double Model::searchFilesByFormatAndSize(const string& format, int min_size, int max_size) {
    string pattern = "%" + format + "%";
    int count = 0;
    clock_t start = clock();

    soci::rowset<File> rs = (sql.prepare <<
        "SELECT * FROM public.file WHERE format LIKE :f AND size BETWEEN :min_s AND :max_s",
        soci::use(pattern), soci::use(min_size), soci::use(max_size));

    std::cout << "\n================ SEARCH RESULTS (FILES) ================\n";
    std::cout << std::left << std::setw(5) << "ID"
        << std::setw(35) << "File Name"
        << std::setw(10) << "Format"
        << std::setw(10) << "Size(KB)"
        << std::setw(8) << "PubID" << "\n";
    std::cout << string(70, '-') << "\n";

    for (const auto& f : rs) {
        std::cout << std::left << std::setw(5) << f.id
            << std::setw(35) << f.name
            << std::setw(10) << f.format
            << std::setw(10) << f.size
            << std::setw(8) << f.pub_id << "\n";
        count++;
    }

    if (count == 0) std::cout << "No matches found.\n";

    clock_t end = clock();
    return (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
}

double Model::searchResearchersByDiscipline(const string& discipline_name) {
    string pattern = "%" + discipline_name + "%";
    int count = 0;
    clock_t start = clock();

    soci::rowset<soci::row> rs = (sql.prepare <<
        R"(
            SELECT DISTINCT r.first_name, r.last_name, d.name 
            FROM public.researcher r
            JOIN public.authorship a ON r.researcher_id = a.researcher_id
            JOIN public.publication p ON a.publication_id = p.publication_id
            JOIN public.discipline d ON p.discipline_id = d.discipline_id
            WHERE d.name LIKE :dp
        )", soci::use(pattern));

    std::cout << "\n================ SEARCH RESULTS (RESEARCHERS) ================\n";
    std::cout << std::left << std::setw(20) << "First Name"
        << std::setw(20) << "Last Name"
        << std::setw(30) << "Discipline Context" << "\n";
    std::cout << string(70, '-') << "\n";

    for (const auto& row : rs) {
        std::cout << std::left << std::setw(20) << row.get<string>(0)
            << std::setw(20) << row.get<string>(1)
            << std::setw(30) << row.get<string>(2) << "\n";
        count++;
    }

    if (count == 0) std::cout << "No matches found.\n";

    clock_t end = clock();
    return (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
}