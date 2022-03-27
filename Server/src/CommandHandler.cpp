#include "CommandHandler.hpp"

using namespace std;

vector <ConnectedUser> connected_users;
int users_size , connected_users_size;


const string currentDateTime() {
    time_t     now = time(0);
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    return buf;
}

void writelog(string filetext) 
{
    ofstream myfile;
    myfile.open ("log.txt", fstream::app);
    myfile << filetext;
    myfile.close();
}


long GetFileSize(string filename)
{
    struct stat stat_buf;
    int rc = stat(filename.c_str(), &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}

vector<string> CommandHandler::get_command(char buf[MAX_BUFFER_SIZE] , int fd)
{
    vector<string> result;
    ConnectedUser* connected_user = UserManager::get_user_by_fd(fd);
    if (connected_user == nullptr)
    {
        result.push_back("500: Error");
        result.push_back("");
        return result;
    }
    if (buf[0] == 'u' && buf[1] == 's' && buf[2] == 'e' && buf[3] == 'r')
    {
        string uname = "";
        int cnt = 5;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                uname += buf[cnt];
            cnt++;
        }
        if (uname == "")
        {
            result.push_back("501: Syntax error in parameters or arguments.");
            result.push_back("");
            return result;
        }
        if (connected_user->get_is_username_entered() != false)
        {
            result.push_back("503: Bad sequence of commands.");
            result.push_back("");
            return result;
        }
        User* user = UserManager::find_user_by_username(uname);
        if (user == nullptr)
        {
            result.push_back("430: Invalid username or password");
            result.push_back("");
            return result;
        }
        connected_user->set_user(user);
        connected_user->set_is_username_entered(true);
        connected_user->set_is_password_entered(false);
        connected_user->set_current_directory("");
        result.push_back("331: User name okay,need password.");
        result.push_back("");
        writelog("user connected " + currentDateTime() + '\n');
        return result;        
    }
    else if (buf[0] == 'p' && buf[1] == 'a' && buf[2] == 's' && buf[3] == 's')
    {
        string pass = "";
        int cnt = 5;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                pass += buf[cnt];
            cnt++;
        }
        if (pass == "")
        {
            result.push_back("501: Syntax error in parameters or arguments.");
            result.push_back("");
            return result;
        }
        if (connected_user->get_is_passsword_entered() != false)
        {
            result.push_back("503: Bad sequence of commands.");
            result.push_back("");
            return result;
        }
        if (connected_user->get_user()->get_password() != pass)
        {
            result.push_back("430: Invalid username or password.");
            result.push_back("");
            return result;
        }
        connected_user->set_is_username_entered(true);
        connected_user->set_is_password_entered(true);
        result.push_back("230: User looged in, proceed. Logged out if appropriate.");
        result.push_back("");
        writelog("user login " + currentDateTime() + '\0');
        return result;
    }
    else if (!(connected_user->get_is_username_entered() && connected_user->get_is_passsword_entered()))   //user logined
    {
        result.push_back("332: Need account for login.");
        result.push_back("");
        return result;
    }
    else if (buf[0] == 'p' && buf[1] == 'w' && buf[2] == 'd')
    {
        string directory = "257: " + exec("pwd");
        result.push_back(directory);
        result.push_back("");
        return result;
    }
    else if (buf[0] == 'm' && buf[1] == 'k' && buf[2] == 'd')
    {
        string path = "";
        int cnt = 4;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                path += buf[cnt];
            cnt++;
        }
        if (path == "")
        {
            result.push_back("501: Syntax error in parameters or arguments.");
            result.push_back("");
            return result;
        }
        string cmd = "mkdir " + path;
        string directory = "257: " + exec(cmd.c_str()) + " created.\n";
        result.push_back(directory);
        result.push_back("");
        return result;
    }
    else if (buf[0] == 'd' && buf[1] == 'e' && buf[2] == 'l' && buf[3]=='e')
    {
        int cnt = 8;
        string name = "";
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                name += buf[cnt];
            cnt++;
        }
        if (name == "")
        {
            result.push_back("501: Syntax error in parameters or arguments.");
            result.push_back("");
            return result;
        }
        if (buf[5]=='-' && buf[6]=='f')
        {
            for(int i=0 ; i < files.size();i++)
                if (files[i] == name)
                    if (!connected_user->get_user()->is_admin_user())
                    {
                        result.push_back("550: File unavailable.");
                        result.push_back("");
                        return result;
                    }
            string cmd="rm " + name;
            string directory = exec(cmd.c_str());
            result.push_back("250: " + name + " deleted.");
            result.push_back("");
            return result;
        }
        else if (buf[5]=='-' && buf[6]=='d')
        {
            string cmd="rm -r " + name;
            string directory = exec(cmd.c_str());
            result.push_back("250: " + name + " deleted.");
            result.push_back("");
            return result;
        }
        else
        {
            result.push_back("501: Syntax error in parameters or arguments.");
            result.push_back("");
            return result;
        }
    }
    else if (buf[0] == 'l' && buf[1] == 's')          // badan send ro dar run server bbrim ---- dar yek khat ham bashad
    {
        string result_ls = exec("ls");
        result.push_back("226: List transfer done.");
        result.push_back(result_ls);
        return result;
    }
    else if (buf[0] == 'c' && buf[1] == 'w' && buf[2] == 'd')       // check shavad
    {
        int cnt = 4;
        string directory = "";
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                directory += buf[cnt];
            cnt++;
        }
        // if (directory == "")
        // {
        //     result.push_back("501: Syntax error in parameters or arguments.");
        //     result.push_back("");
        //     return result;
        // }
        string cmd = "cd " + directory ;
        string message = exec(cmd.c_str());
        connected_user->set_current_directory(directory);
        result.push_back("250: Successful change.");
        result.push_back("");
        return result;
    }
    else if (buf[0] == 'r' && buf[1] == 'e' && buf[2] == 'n' && buf[3] == 'a' && buf[4] == 'm' && buf[5] == 'e') 
    {
        int cnt = 7;
        string from , to;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                from += buf[cnt];
            cnt++;
        }
        cnt ++;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                to += buf[cnt];
            cnt++;
        }
        if (from == "" || to == "")
        {
            result.push_back("501: Syntax error in parameters or arguments.");
            result.push_back("");
            return result;
        }
        for(int i=0 ; i < files.size();i++)
            if (files[i] == from)
                if (!connected_user->get_user()->is_admin_user())
                {
                    result.push_back("550: File unavailable.");
                    result.push_back("");
                    return result;
                }
        string cmd = "mv " + from + " " + to ;
        string message = exec(cmd.c_str());
        result.push_back("250: Successful change.");
        result.push_back("");
        return result;
    }
    else if (buf[0] == 'r' && buf[1] == 'e' && buf[2] == 't' && buf[3] == 'r')
    {
        string name = "" , contents = "";
        int cnt = 5;
        while (cnt < MAX_BUFFER_SIZE && buf[cnt]!= ' ' && buf[cnt]!= '\0')
        {
            if (buf[cnt]!= ' ')
                name += buf[cnt];
            cnt++;
        }
        if (name == "")
        {
            result.push_back("501: Syntax error in parameters or arguments.");
            result.push_back("");
            return result;
        }
        for(int i=0 ; i < files.size();i++)
            if (files[i] == name)
                if (!connected_user->get_user()->is_admin_user())
                {
                    result.push_back("550: File unavailable.");
                    result.push_back("");
                    return result;
                }
        User* user = connected_user->get_user();
        long sz = GetFileSize(name) / 1000 ;
        cout << "size is " << sz << " KB" << endl;
        if (user->get_available_size() < sz)
        {
            result.push_back("425: Can't open data connection.");
            result.push_back("");
            return result;
        }      
        else {
            user->decrease_available_size(sz);
            string myText;
            ifstream MyReadFile(name);
            while (getline (MyReadFile, myText)) {
              contents += myText;
              contents += '\n';
            }
            MyReadFile.close();
            result.push_back("226: Successful Download.");
            result.push_back(contents);
            return result;
        }
    }
    else if (buf[0] == 'h' && buf[1] == 'e' && buf[2] == 'l' && buf[3] == 'p') 
    {
        string help = "";
        help += "214\n" ;
        help += "USER [name], Its argument is used to specify the user's string. It is used for user authentication.\n" ;
        help += "Pass [pass], Used for entering your password after you have entered your username to login.\n" ;
        help += "PWD, to show current directory and path.\n" ;
        help += "MKD [directory_path], to make a directory in given path.\n" ;
        help += "dele -f [filename], to delete a file with given name from current directory.\n";
        help += "dele -d [directory_path], to delete a directory given by its argument.\n" ;
        help += "ls, to show contents of the current directory.\n";
        help += "CWD [path], to change current directory to the give directory.\n" ;
        help += "rename [from] [to], renames the file with name 'from' to a file with name 'to'.\n";
        help += "retr [name], for downloading the file with giben name , but you need to have enough available_size for downloading the file.\n";
        help += "help, This command gives you commands list with an explanation.\n" ;
        help += "quit, It is used to sign out from the server.\n";
        result.push_back(help);
        result.push_back("");
        return result;
    }
    else if (buf[0] == 'q' && buf[1] == 'u' && buf[2] == 'i' && buf[3] == 't') 
    {
        connected_user->set_is_username_entered(false);
        connected_user->set_is_password_entered(false);
        connected_user->set_user(nullptr);
        result.push_back("221: Successful Quit.");
        result.push_back("");
        return result;
    }
}