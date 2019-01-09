#include <iostream>
#include <string>
#include <vector>
#define HASH_SIZE 701

using namespace std;

struct UserData {
    string username;
    int password_hash;
};

int calc_hash(string str)
{
    int hash_num = 0;
    for (int i = 0; i < str.size(); i++) {
        hash_num += ((int)str[str.size() - i - 1] * (1 << i)) % HASH_SIZE;
        hash_num %= HASH_SIZE;
    }
    return hash_num;
}

int main(int argc, char const* argv[])
{
    vector<UserData> database;

    while (true) {
        char command;
        cout << "Command? (u=signup i=signin w=withdraw d=database q=quit) : ";
        cin >> command;

        switch (command) {
        case 'u': {
            string username;
            string password;
            cout << "[Sign up]\n";
            cout << "UserName : ";
            cin >> username;
            cout << "Password : ";
            cin >> password;
            database.push_back(UserData{ username, calc_hash(password) });

            break;
        }

        case 'i': {
            bool username_found = false;

            string username;
            string password;
            int correct_hash;
            cout << "[Sign in]\n";

            while (true) {
                cout << "UserName : ";
                cin >> username;

                for (int i = 0; i < database.size(); i++) {
                    if (database[i].username == username) {
                        username_found = true;
                        correct_hash = database[i].password_hash;
                        break;
                    }
                }

                if (username_found) {
                    break;
                } else {
                    cout << "No User\n";
                    continue;
                }
            }

            while (true) {
                cout << "Password : ";
                cin >> password;
                int password_hash = calc_hash(password);

                if (password_hash == correct_hash) {
                    cout << "Login Succeed!\n";
                    break;
                } else {
                    cout << "Incorrect password\n";
                }
            }

            break;
        }

        case 'w': {
            bool username_found = false;
            int data_index;

            string username;
            string password;
            int correct_hash;
            cout << "[Withdraw]\n";

            while (true) {
                cout << "UserName : ";
                cin >> username;

                for (int i = 0; i < database.size(); i++) {
                    if (database[i].username == username) {
                        username_found = true;
                        data_index = i;
                        correct_hash = database[i].password_hash;
                        break;
                    }
                }

                if (username_found) {
                    break;
                } else {
                    cout << "No User\n";
                    continue;
                }
            }

            while (true) {
                cout << "Password : ";
                cin >> password;
                int password_hash = calc_hash(password);

                if (password_hash == correct_hash) {
                    database.erase(database.begin() + data_index);
                    cout << "Withdraw Succeed!\n";
                    break;
                } else {
                    cout << "Incorrect password\n";
                }
            }

            break;
        }

        case 'd': {
            cout << "[Data base]\nUSERNAME\tPASSWORD_HASH\n";
            for (int i = 0; i < database.size(); i++) {
                cout << database[i].username << "\t" << database[i].password_hash << "\n";
            }
            break;
        }

        case 'q': {
            return 0;
        }

        default:
            break;
        }

        cout << "\n";
    }

    return 0;
}
