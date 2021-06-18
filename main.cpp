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

int check_name(string *str, string name)
{
    int len;
    int i;
    cout<<"44\n";
                    //cout<<"45\n";//----------------
    len = str->length();
                    //cout<<"47\n";//----------------
    if (len && (*str)[len - 1] && (*str)[len - 1] != '"')
    {
         //cout << "48 Wrong config file!\n";
         return (1);
    }
                    //cout<<"53\n";
    i = 0;
    while ((*str)[i] && name[i])
    {               //cout<<"53\n";
        if ((*str)[i] != name[i])
        {
            //cout << "55 Wrong config file!\n";
            return(1);
        }
                        // else if (!q && (((*str)[i] != name[i]) || ((*str)[i + 1] && (*str)[i + 1] != name[i + 1])))
                        // {
                        // cout << "60 Wrong config file!\n";
                        // //  cout<<"57 "<<int((*str)[i + 1])<<endl;
                        // //   cout<<"58 "<<name[i + 1]<<endl;
                        //     return(1);
                        // }
        i++;
    }
    // (*str)[len] = '\0';
    // *str = (*str).c_str() + i;
    return (0);
}

string removechars(string line, string chars)
{
    int i;

    i = 0;
    while(chars[i])
    {
       // cout<<"101 "<<(int)chars[i]<<endl;
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
    {               //cout<<"53\n";
       
                        // else if (!q && (((*str)[i] != name[i]) || ((*str)[i + 1] && (*str)[i + 1] != name[i + 1])))
                        // {
                        // cout << "60 Wrong config file!\n";
                        // //  cout<<"57 "<<int((*str)[i + 1])<<endl;
                        // //   cout<<"58 "<<name[i + 1]<<endl;
                        //     return(1);
                        // }
        i++;
    }
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
        cout<<"105 \n";
    if (!check_name(arg2, "source_path=\""))
        source = *arg2;
    else if (!check_name(arg2, "destination_path=\""))
        dest = *arg2;
    else if (!check_name(arg2, "file_name=\""))
        fname = *arg2;
    else
        return (1);
        cout<<"114\n";
    if (!check_name(arg3, "source_path=\""))
        source = *arg3;
    else if (!check_name(arg3, "destination_path=\""))
        dest = *arg3;
    else if (!check_name(arg3, "file_name=\""))
        fname = *arg3;
    else
        return (1);
    cout<<"123\n";
    cout<<"source "<<source<<" dest "<<dest<<" fname "<<fname<<endl;
    if (source == dest || source == fname || dest == fname)
        return (1);
    source = str_trim(source, "source_path=\"");
    dest = str_trim(dest, "destination_path=\"");
    fname = str_trim(fname, "file_name=\"");

    // if (check_name(arg1, "source_path=\"") || check_name(arg2, "destination_path=\"") || check_name(arg3, "file_name=\""))
    // {
    //     cout << "103 Wrong config file!\n";
    //     return (1);
    // }   
     cout<<"source "<<source<<" dest "<<dest<<" fname "<<fname<<endl;
    cout<<source<<" "<<dest<<" "<< fname<<endl;
    return (0);
}

int check_file(string *arg1, string *arg2, string *arg3)
{
    int s_len;
    int d_len;
    int f_len;

    s_len = arg1->length();
    d_len = arg2->length();
    f_len = arg3->length();
    // arg1.erase(arg1.find(" "), 1);
    // arg1.erase(arg2.find(" "), 1);
    // arg1.erase(arg3.find(" "), 1);
    *arg1 = removechars(*arg1, "\n\v\t\f\r ");
    *arg2 = removechars(*arg2, "\n\v\t\f\r ");
    *arg3 = removechars(*arg3, "\n\v\t\f\r ");
                    cout<<"101\n";
    if (check_arg(arg1, arg2, arg3))
    {
        cout << "103 Wrong config file!\n";
        return (1);
    }
    
                    cout<<"107\n";
    // cout<<"49*"<<(*arg1)[arg1->length() - 1]<<"*\n";
    // cout<<"49*"<<(*source)<<"*\n";
    // cout<<"50*"<<*arg2<<"*\n";
    // cout<<"51*"<<*arg3<<"*\n";

    // if (s_len < 5 || (len >= 5 && (config.substr(len - 4, len )) != ".xml"))
    // {
    //     cout << "Wrong config file name!\n";
    //     return (1);
    // }
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
}
int main()
{
    string config;
    string arg1;
    string arg2;
    string arg3;

    cout << "Enter the name of the config file in xml format:\n";
    cin >> config;
    if (checformat(config))
        return (0);

    ifstream file(config);
    string line;
    string tmp;
    while (getline(file, line))
    {
                            //skipspaces(file, line);
                            // cout<<"131\n";
                            //    cout<<"97 "<<line<<endl<<"98 <config>\n";
                            //line = removechars(line, "\n\v\t\f\r ");
        skipspaces(file, &line);
                            //     tmp = "<config>";
                            // cout<<"102 line = "<<line.c_str()<<" tmp = "<<line.c_str()<<" line lengt = "<<line.length()<<" tmp length = "<<tmp.length()<<endl;
                            //  int ii = 0;
                            // while (ii <= line.length())
                            // {
                            //     cout<<"131 "<<(int)(line[ii])<<endl;
                            //     ii++;
                            // }
                            //  cout<<"141\n";
                            // if(line == "")
                            //     cout<<"line = NULL\n";
                            // int leng = line.length();
                            // cout<<"141 "<<leng<<endl;

        if (line== "<config>")//!check_name(&line,"<config>", 0))//line == "<config>")//line.c_str() && strcmp(line.c_str(), "<config>"))// line == "<config>") .compare()  (temp1.compare(temp2) ==0 0 !line.compare("<config>"))
        {
            getline(file, line);
                            // line = removechars(line, "\n\v\t\f\r ");
                            // while (line == "")
                            // {
                            //     skipspaces(file, line);
                            //     getline(file, line);
                            //     line = removechars(line, "\n\v\t\f\r ");
                            // }
            skipspaces(file, &line);
                            // cout<<"154 "<<line<<endl;
                            // cout<<"161\n";
                            // if(line == "")
                            //     cout<<"line = NULL\n";
                            // int leng = line.length();
                            // cout<<"165 "<<leng<<endl;

            if (line == "<file")
            {
                                // cout<<"104 "<<line<<endl;
                getline(file, arg1);
                skipspaces(file, &arg1);
                                // cout<<"104 "<<line<<endl;
                                // line = removechars(line, "\n\v\t\f\r ");
                getline(file, arg2);
                skipspaces(file, &arg2);
                                // cout<<"104 "<<line<<endl;
                                // line = removechars(line, "\n\v\t\f\r ");
                getline(file, arg3);
                skipspaces(file, &arg3);
                                // cout<<"191 "<<arg3<<endl;
                                // line = removechars(line, "\n\v\t\f\r ");
                if (check_file(&arg1, &arg2, &arg3))
                    return (1);
                getline(file, line);
                skipspaces(file, &line);
                                // cout<<"104 "<<line<<endl;
                                //line = removechars(line, "\n\v\t\f\r ");
                if (line != "/>")
                {
                    cout << "163 Wrong config file!\n";
                    return (0);
                }
            }
            else
            {
                cout << "178 Wrong config file!\n";
                return (0);
            }

        }
        else if(line == "</config>")
            ;
        else
        {
            cout << "175 Wrong config file!\n";
            return (0);
        }
    }
}
