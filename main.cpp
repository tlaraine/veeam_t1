#include <iostream>
#include <string>
#include <fstream>

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

    len = str.length();
    i = 0;
    while(str.c_str()[i] && str[i] == c)
         i++;
    str = str.c_str() + i;
    return (str);
}

int check_name(string *str, string name) 
{
    int len;

    len = str->length();
    if ((*str)[len - 1] != '"')
    {
         cout << "42 Wrong config file!\n";
         return (1);
    }

    return (0);
}
int check_file(string *source, string *dest, string *fname)
{
    int s_len;
    int d_len;
    int f_len;

    s_len = source->length();
    d_len = dest->length();
    f_len = fname->length();
    // source.erase(source.find(" "), 1);
    // source.erase(dest.find(" "), 1);
    // source.erase(fname.find(" "), 1);
    *source = removechar(*source, ' ');
    *dest = removechar(*dest, ' ');
    *fname = removechar(*fname, ' ');
    if (check_name(source, "source_path=\"") || check_name(dest, "destination_path=\"") || check_name(fname, "file_name=\""))
        return (1);
    cout<<"49*"<<(*source)[source->length() - 1]<<"*\n";
    cout<<"50*"<<*dest<<"*\n";
    cout<<"51*"<<*fname<<"*\n";
  
    // if (s_len < 5 || (len >= 5 && (config.substr(len - 4, len )) != ".xml"))
    // {
    //     cout << "Wrong config file name!\n";
    //     return (1);
    // }  
    return (0);
}

int main()
{
    string config;
    string source;
    string dest;
    string fname;

    cout << "Enter the name of the config file in xml format:\n";
    cin >> config;
    if (checformat(config))
        return (0);

    ifstream file(config);
    string line;
    while (getline(file, line))
    {
        if (line.c_str() && line == "<config>")
        {
            getline(file, line);
            if (line.c_str() && line == "    <file")
            {
                getline(file, source);
                getline(file, dest);
                getline(file, fname);
                if (check_file(&source, &dest, &fname))
                    return (1);
            }
            else
            {
                cout << "71 Wrong config file!\n";
                return (0); 
            }
                cout<<line<<endl;
        }
        else 
        {
            cout << "78 Wrong config file!\n";
            return (0);
        }
    }
}