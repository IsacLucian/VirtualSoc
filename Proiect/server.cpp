#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <map>
#include <sqlite3.h> 
#include <functional>
#include <vector>
#include <pthread.h>
#include <unistd.h>

using namespace std;

string null = "[null]";
const int hsize = 30;
const int size = 1024;
const char* Database = "database.db";
const char* Tables = "CREATE TABLE user (id INTEGER PRIMARY KEY, admin INTEGER, profil INTEGER, nume TEXT, prenume TEXT, email TEXT, parola TEXT, username TEXT)"
                     "CREATE TABLE postari (id INTEGER PRIMARY KEY, mesaj TEXT, id_user INTEGER, username TEXT, tip INTEGER, data TEXT)"
                     "CREATE TABLE mesaje (id INTEGER PRIMARY KEY, writer INTEGER, reader INTEGER, data TEXT, mesaj TEXT)"
                     "CREATE TABLE prietenii (id INTEGER PRIMARY KEY, id_1 INTEGER, id_2 INTEGER, close INTEGER)"
                     "CREATE TABLE grupuri (id INTEGER PRIMARY KEY, nume TEXT)"
                     "CREATE TABLE membri (id INTEGER PRIMARY KEY, id_grup INTEGER, id_membru INTEGER, username_membru TEXT)";

// @ la final = campul este string (sa stiu cand adaug '' la query)
const vector<string> userModel = {"id", "admin", "profil", "nume@", "prenume@", "email@", "parola@", "username@"};
const vector<string> postariModel = {"id", "mesaj@", "id_user", "username@", "tip", "data@"};
const vector<string> mesajeModel = {"id", "writer", "reader", "data@", "mesaj@"};
const vector<string> prieteniiModel = {"id", "id_1", "id_2", "close"};
const vector<string> grupuriModel = {"id", "nume@"};
const vector<string> membriModel = {"id", "id_grup", "id_membru", "username_membru@"};

pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;


struct Thread
{
    int client;         //client socket
    long long userId;         //id user conectat
    string username;    
};

sqlite3 *db;
map <pthread_t, Thread> threads;
map <string, vector<string> > tabel = {
    {"user", userModel},
    {"postari", postariModel},
    {"mesaje", mesajeModel},
    {"prietenii", prieteniiModel},
    {"grupuri", grupuriModel},
    {"membri", membriModel}
};

string Select(vector<string> info, int id) {
    string model = info[0];
    string query = "SELECT * FROM " + model;

    if(!(id == -1 && info.size() == 1))
    {
        query = query + " WHERE";
        if(id != -1)
            query = query + " id IN (" + to_string(id) + ") AND";
        
        if(info.size() > 1)
        {
            for(int i = 1; i < (tabel[model]).size(); i++)
            {
                if(info[i] == null)
                    continue;

                auto at = (tabel[model])[i].find('@');
                query = query + " " + (tabel[model])[i].substr(0, at) + " IN (";

                if(at != string::npos)
                {
                    size_t pos = 0;
                    while((pos = info[i].find(",", pos)) != string::npos)
                    {
                        info[i].replace(pos, string(",").length(), string("','"));
                        pos += string("','").length();
                    }
                    info[i].insert(0, 1, '\'');
                    info[i].push_back('\'');
                }

                query = query + info[i];

                query = query + ") AND";


            }
        }
        query.erase(query.length() - 4);
    }

    sqlite3_stmt* stmt;
    sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, 0);

    string response("");
    while(sqlite3_step(stmt) != SQLITE_DONE)
    {
        response = response + "{\n";
        if(id == -1)    // pentru login
            id = sqlite3_column_int(stmt, 0);

        for(int i = 0; i < (tabel[model]).size(); i++)
        {
            auto at = (tabel[model])[i].find('@');
            response = response + (tabel[model])[i].substr(0, at)
                        + ":" + string(reinterpret_cast<const char*>(sqlite3_column_text(stmt, i)));    // (e const unsigned char* rezultatul si nu merge convertit la string)
            response = response + "\n";
        }
        response = response + "}\n";
    }

    if(info.size() > 1)
    {
        if(model == "user" && info[6] != null && !response.empty())  // 6 e campul parolei => daca e diff de null atunci avem login
        {
            int found = 0;
            for(auto x : threads)
                if(x.second.userId == id) 
                {
                    found = 1;
                    break;
                }

            if(found)
                return "Found"; // sunt deja logat

            pthread_t self = pthread_self();
            threads[self].userId = id;
            threads[self].username = info[userModel.size() - 1];
        }
    }

    return (response.empty() ? null : response);
}

string Insert(vector<string> info, int id) {
    string model = info[0];
    string query = "INSERT INTO " + model + " (";
    
    for(int i = 1; i < (tabel[model]).size(); i++)
    {
        auto at = (tabel[model])[i].find('@');

        query = query + (tabel[model])[i].substr(0, at) + ",";
    }

    query.pop_back();
    query = query + ") VALUES (";

    for(int i = 1; i < info.size(); i++)
    {
        auto at = (tabel[model])[i].find('@');
        if(at != string::npos)
            query = query + "'";

        query = query + info[i];

        if(at != string::npos)
            query = query + "'";

        query = query + ",";
    }

    query.pop_back();
    query = query + ");";
    if(sqlite3_exec(db, query.c_str(), NULL, NULL, NULL))
        return "Eroare la insert";

    if(info[0] == "user")   // am register
    {
        // sectiune critica (mai multe threaduri pot apela last_insert_rowid = probabil se strica)
        pthread_t self = pthread_self();
        pthread_mutex_lock(&mlock);
        threads[self].userId = sqlite3_last_insert_rowid(db);
        threads[self].username = info[userModel.size() - 1];
        pthread_mutex_unlock(&mlock);

        return ("Success" + to_string(threads[self].userId));
    }

    return "Success";
}

string Update(vector<string> info, int id) {
    string model = info[0];
    string query = "UPDATE " + model + " SET ";

    for(int i = 1; i < (tabel[model]).size(); i++)
    {
        if(info[i] == null)
            continue;

        auto at = (tabel[model])[i].find('@');

        query = query + (tabel[model])[i].substr(0, at) + "=";

        if(at != string::npos)
            query = query + "'";

        query = query + info[i];

        if(at != string::npos)
            query = query + "'";

        query = query + ",";
    }
    query.pop_back();

    query = query + " WHERE id=" + to_string(id) + ";";

    if(sqlite3_exec(db, query.c_str(), NULL, NULL, NULL))
        return "Eroare la update";

    return "Success";
}

string Delete(vector<string> info, int id) {
    string model = info[0];
    string query = "DELETE FROM " + model + " WHERE id=" + to_string(id) + ";";

    if(sqlite3_exec(db, query.c_str(), NULL, NULL, NULL))
        return "Eroare la delete";

    return "Success";
}

map <string, function<string(vector<string>, int)> > db_requests = {
    {"select", Select},
    {"insert", Insert},
    {"update", Update},
    {"delete", Delete}
};

void Handle() {
    int sd;
    pthread_t self = pthread_self();
    Thread info = threads[self];

    if(sqlite3_open(Database, &db) != SQLITE_OK)
    {
        perror ("Eroare la sqlite3_open().\n");
        return;
    }

    int id, ind, i;
    char *pch;
    string functie;
    vector <string> parametri;
    char buffer[size], header[hsize], mes[size];

    while(1)
    {
        memset(mes, 0, sizeof(mes));
        if((sd = read(info.client, mes, sizeof(mes))) <= 0)
        {
            if(sd == -1)
                perror ("Eroare la read().\n");
            break;
        }
        
        memset(header, 0, sizeof(header));
        memset(buffer, 0, sizeof(buffer));
        
        for(ind = 0; mes[ind] != '\n'; ind++)
            header[ind] = mes[ind];

        if(strcmp(header, "exit") == 0)
            break;

        if(strcmp(header, "logout") == 0)
        {
            threads[self].userId = -1;
            threads[self].username = "";
            continue; 
        }

        ind++;
        i = 0;
        for(;mes[ind]; ind++)
            buffer[i++] = mes[ind];

        cout << header << "\n" << buffer << "\n";

        // header = tabel@functie#id (id poate sa nu existe)
        id = -1;
        string aux(header);
        parametri.clear();
        int pos = aux.find("@");
        parametri.push_back(aux.substr(0, pos));    // parametri[0] = numele tabelului
        functie = aux.substr(pos + 1);

        if((pos = functie.find("#")) != string::npos) // am id 
        {
            id = stoi(functie.substr(pos + 1));
            functie = functie.substr(0, pos);
        }
        pch = strtok(buffer, "\n");
        while(pch != NULL)
        {
            string aux(pch);
            parametri.push_back(aux);
            pch = strtok(NULL, "\n");
        }

        string ans = db_requests[functie](parametri, id);

        if(write(info.client, ans.c_str(), strlen(ans.c_str())) < 0)
        {
            perror ("Eroare la write().\n");
            break;
        }

    }

    sqlite3_close(db);
    close(info.client);
    pthread_mutex_lock(&mlock);
    threads.erase(self);    //sectiune critica?
    pthread_mutex_unlock(&mlock);

    pthread_exit(0);
}


struct Server
{
    int sd;

    Server() {
        sd = -1;
    }

    int CreateSoc(int port) {

        struct sockaddr_in server;

        if((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            perror ("Eroare la socket().\n");
            return -1;
        }

        int opt = 1;
        setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

        bzero(&server, sizeof(server));
        server.sin_family = AF_INET;
        server.sin_addr.s_addr = htonl(INADDR_ANY);
        server.sin_port = htons(port);

        if(bind(sd, (struct sockaddr *) &server, sizeof(struct sockaddr)) == -1)
        {
            perror ("Eroare la bind().\n");
            return -1;
        }

        if(listen(sd, 5) == -1)
        {
            perror("Error on listen():");
            return -1;
        }

        printf("Astept clienti\n");
        return 0;
    }

    int Accept() {
        struct sockaddr_in from;
        int len = sizeof(from);
        int client;

        if((client = accept(sd, (struct sockaddr *) &from, (socklen_t *) &len)) == -1)
        {
            perror ("Eroare la accept().\n");
            return -1;
        }

        printf("S-a conectat un client\n");
        return client;
    }

    static void *treat(void *arg) {
        pthread_detach(pthread_self());
        Handle();
        return NULL;
    }

    int CreateThread(int client) {
        
        pthread_t th;
        Thread info;

        info.userId = -1;
        info.username = "";
        info.client = client;

        pthread_mutex_lock(&mlock);

        if(pthread_create(&th, NULL, &treat, NULL))
        {
            perror ("Eroare la pthread_create().\n");
            return -1;
        }

        threads[th] = info;
        pthread_mutex_unlock(&mlock);
        return 0;
    }
};

int main(int argc, char *argv[]) 
{
    int fd;
    Server server;
    
    if(argc != 2)
    {
        printf("Introdu portul\n");
        return 0;
    }

    if(server.CreateSoc(atoi(argv[1])) == -1)
        return 0;

    while(1)
    {
        fd = server.Accept();
        server.CreateThread(fd);
    }

    return 0;
}
