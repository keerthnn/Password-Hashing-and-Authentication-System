#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <bits/stdc++.h>
using namespace std;

class student
{
public:
    string usn;
    string Fname;
    string Lname;
    string branch;
    string sem;
    string phoneNumber;
    float cgpa;
    string dob;
    string address;
    string s;
    string h = "", g = "", m, e, u, h1, g1;
    int a, b = 0, c = 0, a1, b1 = 0, c1 = 0;
    string password;
    string password1;
    string buffer;
    string usn_list[100];
    int Address_list[100];
    int count;

    void read_data();
    void pack();
    void disp();
    void write_to_file();
    void create_index();
    void remove(string);
    void search(string);
    int search_index(string);
    string extract_usn();
    void sort_index();
};

void student::read_data()
{
    cout << "USN: ";
    cin >> usn;
    cout << "First name: ";
    cin >> Fname;
    cout << "Last name: ";
    cin >> Lname;
    cout << "Branch: ";
    cin >> branch;
    cout << "Semester: ";
    cin >> sem;
    cout << "Phone Number: ";
    cin >> phoneNumber;
    cout << "CGPA: ";
    cin >> cgpa;
    cout << "Date of Birth (DOB): ";
    cin >> dob;
    cin.ignore();
    cout << "Address: ";
    getline(cin, address);

    cout << "Password: ";
    cin >> password;

    s = "salt";
    password.append(s);
    a = password.length();
    g.erase();
    for (int i = 0; i < password.length(); i++)
    {
        b = (password.at(i) + a) % (2 * a);
        h = to_string(b);
        c = c + b;
        g.append(h);
    }
    password = g;
}

void student::pack()
{
    string temp;
    buffer.erase();
    buffer += usn + "|" + Fname + "|" + Lname + "|" + branch + "|" + sem + "|" + phoneNumber + "|" + to_string(cgpa) + "|" + dob + "|" + address + "|" + password + "$\n";
    password.erase();
}

void student::write_to_file()
{
    int pos;
    fstream file;
    file.open("one.txt", ios::out | ios::app);
    pos = file.tellp();
    file << buffer;
    file.close();
    usn_list[++count] = usn;
    Address_list[count] = pos;
    sort_index();
}

string student::extract_usn()
{
    string usn;
    int i = 0;
    usn.erase();
    while (buffer[i] != '|')
        usn += buffer[i++];
    return usn;
}

void student::create_index()
{
    fstream file;
    int pos;
    string usn;
    count = -1;
    file.open("one.txt", ios::in);
    while (!file.eof())
    {
        pos = file.tellg();
        buffer.erase();
        getline(file, buffer);
        if (buffer[0] != '*')
        {
            if (buffer.empty())
                break;
            usn = extract_usn();
            usn_list[++count] = usn;
            Address_list[count] = pos;
        }
    }
    file.close();
    sort_index();
    buffer.erase();
}

void student::disp()
{
    int i;
    cout << endl
         << "INDEX FILE" << endl;
    for (i = 0; i <= count; i++)
        cout << endl
             << usn_list[i] << " is at position: " << Address_list[i];
    cout << "\n";
}

void student::sort_index()
{
    int i, j, temp_Address;
    string temp_usn;
    for (i = 0; i <= count; i++)
    {
        for (j = i + 1; j <= count; j++)
        {
            if (usn_list[i] > usn_list[j])
            {
                temp_usn = usn_list[i];
                usn_list[i] = usn_list[j];
                usn_list[j] = temp_usn;
                temp_Address = Address_list[i];
                Address_list[i] = Address_list[j];
                Address_list[j] = temp_Address;
            }
        }
    }
    for (i = 0; i <= count; i++)
    {
        cout << usn_list[i] << "\t" << Address_list[i] << "\n";
    }
}

int student::search_index(string key)
{
    int low = 0, high = count, mid = 0, flag = 0, pos;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (usn_list[mid] == key)
        {
            flag = 1;
            break;
        }
        if (usn_list[mid] > key)
            high = mid - 1;
        if (usn_list[mid] < key)
            low = mid + 1;
    }
    if (flag)
        return mid;
    else
        return -1;
}

void student::search(string key)
{
    int pos = 0, address, j = 0;
    fstream file;
    buffer.erase();
    password.erase();
    password1.erase();
    pos = search_index(key);
    if (pos == -1)
        cout << endl
             << "Username does not exist" << endl;
    else if (pos >= 0)
    {
        file.open("one.txt");
        address = Address_list[pos];
        file.seekp(address, ios::beg);
        getline(file, buffer);
        cout << "\nEnter the password: ";
        cin >> password1;

        s = "salt";
        password1.append(s);
        a1 = password1.length();
        g1.erase();
        for (int i = 0; i < password1.length(); i++)
        {
            b1 = (password1.at(i) + a1) % (2 * a1);
            h1 = to_string(b1);
            c1 = c1 + b1;
            g1.append(h1);
        }
        password1 = g1;

        cout << "Checking password....\n";
        m.erase();
        for (int i = 0; i < buffer.length() - 1; i++)
        {
            if (j == 9)
            {
                e = buffer.at(i);
                m.append(e);
            }
            if (buffer.at(i) == '|')
            {
                j++;
            }
            if (buffer.at(i) == '$')
            {
                break;
            }
        }

        if (password1 == m)
        {
            cout << "Login successful\n"
                 << buffer;
        }
        else
        {
            cout << "Incorrect password\n";
        }
        file.close();
    }
}

void student::remove(string key)
{
    int pos = 0, i, address;
    fstream file;
    pos = search_index(key);
    if (pos >= 0)
    {
        file.open("one.txt", ios::out | ios::in);
        address = Address_list[pos];
        file.seekp(address, ios::beg);
        file.put('*');
        file.close();
        cout << "\nRecord Deleted: ";
        for (i = pos; i < count; i++)
        {
            usn_list[i] = usn_list[i + 1];
            Address_list[i] = Address_list[i + 1];
        }
        count--;
    }
    else
        cout << "Record not found\n";
}

int main()
{
    int choice, count, i;
    string key;
    student s1;
    s1.create_index();

    while (1)
    {
        cout << "\nMain Menu\n--------\n1. Signup\n2. Login\n3. Delete\n4. Display\n5. Exit\n---------\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            count = 1;
            for (i = 0; i < count; i++)
            {
                cout << "Data\n\n";
                s1.read_data();
                s1.pack();
                s1.write_to_file();
            }
            break;
        case 2:
            system("clear");
            cout << "\nEnter the USN: ";
            cin >> key;
            s1.search(key);
            break;
        case 3:
            cout << "\nEnter the USN: ";
            cin >> key;
            s1.remove(key);
            break;
        case 4:
            cout << "RECORDS";
            s1.disp();
            break;
        case 5:
            return 0;
        default:
            cout << "\n\nWrong choice\n";
            break;
        }
    }
}
