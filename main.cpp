#include <iostream>
#include <string>
#include <string.h>
#include <fstream>
#include <list>
#include <cstring>

using namespace std;

int checformat(string config)
{
    int len;

    len = config.length();
    if (len < 5 || (len >= 5 && (config.substr(len - 4, len )) != ".xml"))
    {
        cout << "Wrong config file name!\n";
        return (1);
    }
    return (0);
}

string removechar(string str, char c)
{
    int i;
    int len;
    string tmp;

    len = str.length();
    i = 0;
    while (str.c_str()[i] && str[i] == c)
         i++;
    str = str.c_str() + i;
    while (len > 0 && str[len - 1] == c)
         len--;
    str[len] = '\0';
    str = str.c_str();
    return (str);
}

int check_name(string *str, string name)
{
    int len;
    int i;

    len = str->length();
    if (len && (*str)[len - 1] && (*str)[len - 1] != '"')
         return (1);
    i = 0;
    while ((*str)[i] && name[i])
    {
        if ((*str)[i] != name[i])
            return(1);
        i++;
    }
    return (0);
}

string removechars(string line, string chars)
{
    int i;

    i = 0;
    while(chars[i])
    {
        line = removechar(line, chars[i]);
        i++;
    }
    return(line);
}

string str_trim(string str, string trim)
{
    int i;
    int len;

    i = 0;
    len = str.length();
    while (str[i] == trim[i])
        i++;
    if (len)
        str[len - 1] = '\0';
    str = str.c_str() + i;
    return (str);
}

int check_arg(string *arg1, string *arg2, string *arg3)
{
    string  source;
    string  dest;
    string  fname;

    if (!check_name(arg1, "source_path=\""))
        source = *arg1;
    else if (!check_name(arg1, "destination_path=\""))
        dest = *arg1;
    else if (!check_name(arg1, "file_name=\""))
        fname = *arg1;
    else
        return (1);
    if (!check_name(arg2, "source_path=\""))
        source = *arg2;
    else if (!check_name(arg2, "destination_path=\""))
        dest = *arg2;
    else if (!check_name(arg2, "file_name=\""))
        fname = *arg2;
    else
        return (1);
    if (!check_name(arg3, "source_path=\""))
        source = *arg3;
    else if (!check_name(arg3, "destination_path=\""))
        dest = *arg3;
    else if (!check_name(arg3, "file_name=\""))
        fname = *arg3;
    else
        return (1);
    if (source == dest || source == fname || dest == fname)
        return (1);
    source = str_trim(source, "source_path=\"");
    dest = str_trim(dest, "destination_path=\"");
    fname = str_trim(fname, "file_name=\"");
    *arg1 = source;
    *arg2 = dest;
    *arg3 = fname;
    return (0);
}

void skipspaces(ifstream &file, string *line)
{
    *line = removechars(*line, "\n\v\t\f\r ");
    while (*line == "")
    {
        getline(file, *line);
        *line = removechars(*line, "\n\v\t\f\r ");
    }
    *line = removechars(*line, "\n\v\t\f\r ");
}

string get_arg(ifstream &file, string *line)
{
    getline(file, *line);
    skipspaces(file, line);
    return (*line);
}

int main()
{
    string config;
    string arg1;
    string arg2;
    string arg3;
    string *args;
    list<string*> MyL;
    list<string*>::iterator i;

    cout << "Enter the name of the config file in xml format:\n";
    cin >> config;
    if (checformat(config))
        return (0);
    ifstream file(config);
    string line;
    string tmp;
    getline(file, line);
    skipspaces(file, &line);
    if (line == "<config>")
    {
        while (getline(file, line))
        {
            skipspaces(file, &line);
            if (line == "<file")
            {
                arg1 = get_arg(file, &line);
                arg2 = get_arg(file, &line);
                arg3 = get_arg(file, &line);
                if (check_arg(&arg1, &arg2, &arg3))
                {
                    cout << "Wrong config file!\n";
                    exit(0);
                }
                args = new string[3];
                args[0]=arg1;
                args[1]=arg2;
                args[2]=arg3;
                MyL.push_back(args);
                getline(file, line);
                skipspaces(file, &line);
                if (line != "/>")
                {
                    cout << "Wrong config file!\n";
                    exit(0);
                }                
            }
            else if(line == "</config>")
                ;
            else
            {
                cout << "Wrong config file!\n";
                exit(0);
            }
        }
    }
    file.close();
    ifstream in;
    ofstream out;
    cout<<"\n";
    for (i = MyL.begin(); i != MyL.end() ; i++)
    {
        in.open((*i)[0] + "/" +(*i)[2]);
        out.open((*i)[1] + "/" + (*i)[2]);
        if (in.is_open())
        {
            if (out.is_open())
            {
                cout<<"Copying file \""<<(*i)[2]<<"\"\n";
                out<<in.rdbuf();
                cout<<"Done!\n\n";
                in.close();
                out.close();
            }
            else
            {  
                cout<<"Wrong a destination_path: "<<(*i)[1]<<endl;
                cout<<strerror(errno)<<endl<<endl;
                in.close();
                continue ;
            }
        }
        else
        {
            if (out.is_open())
                out.close();
            cout<<"Wrong a file: "<<(*i)[2]<<endl;
            cout<<strerror(errno)<<endl<<endl;
            continue ;
        }
    }
    cout<<"All done!\n";
    exit(0);
}
