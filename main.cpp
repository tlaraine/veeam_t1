#include <iostream>
#include <string>
#include <string.h>
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

int check_name(string *str, string name, int q)
{
    int len;
    int i;

    len = str->length();
    if (q && (*str)[len - 1] != '"')
    {
         cout << "42 Wrong config file!\n";
         return (1);
    }
    while ((*str)[i] && name[i])
    {
        if (q && (*str)[i] != name[i])
        {
            cout << "42 Wrong config file!\n";
            return(1);
        }
        else if (!q && (((*str)[i] != name[i]) || ((*str)[i + 1] && (*str)[i + 1] != name[i + 1])))
         {
             cout << "42 Wrong config file!\n";
            //  cout<<"57 "<<int((*str)[i + 1])<<endl;
            //   cout<<"58 "<<name[i + 1]<<endl;
             return(1);

         }
        i++;
    }
    return (0);
}

string removechars(string line, string chars)
{
    int i;
    while(chars[i])
    {
        cout<<"101 "<<(int)chars[i]<<endl;
        line = removechar(line, chars[i]);
        i++;
    }
    return(line);

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
    *source = removechars(*source, "\n\v\t\f\r ");
    *dest = removechars(*dest, "\n\v\t\f\r ");
    *fname = removechars(*fname, "\n\v\t\f\r ");
    if (check_name(source, "source_path=\"", 1) || check_name(dest, "destination_path=\"", 1) || check_name(fname, "file_name=\"", 1))
        return (1);
    cout<<"49*"<<(*source)[source->length() - 1]<<"*\n";
    cout<<"49*"<<(*source)<<"*\n";
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
    string tmp;
    while (getline(file, line))
     {
    //    cout<<"97 "<<line<<endl<<"98 <config>\n";
         line = removechars(line, "\n\v\t\f\r ");
    //     tmp = "<config>";
       // cout<<"102 line = "<<line.c_str()<<" tmp = "<<line.c_str()<<" line lengt = "<<line.length()<<" tmp length = "<<tmp.length()<<endl;
    //  int ii = 0;
    // while (ii <= line.length())
    // {
    //     cout<<"131 "<<(int)(line[ii])<<endl;
    //     ii++;
    // }


         if (line== "<config>")//!check_name(&line,"<config>", 0))//line == "<config>")//line.c_str() && strcmp(line.c_str(), "<config>"))// line == "<config>") .compare()  (temp1.compare(temp2) ==0 0 !line.compare("<config>"))
        {
            getline(file, line);
            line = removechars(line, "\n\v\t\f\r ");
            //cout<<"102 "<<line<<endl;
            if (line == "<file")
            {
                //cout<<"104 "<<line<<endl;
                getline(file, source);
                // line = removechars(line, "\n\v\t\f\r ");
                getline(file, dest);
                // line = removechars(line, "\n\v\t\f\r ");
                getline(file, fname);
                // line = removechars(line, "\n\v\t\f\r ");
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
