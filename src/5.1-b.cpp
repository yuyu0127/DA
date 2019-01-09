#include <iostream>
#include <string>
#define HASH_SIZE 701

int hash(std::string str)
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
    std::string str_list[HASH_SIZE];

    while (true) {
        bool error = false;
        char command;
        std::cout << "command? (a=add r=remove s=search q=quit) : ";
        std::cin >> command;

        switch (command) {
        case 'a': {
            std::string str;
            std::cout << "string to add? : ";
            std::cin >> str;
            int hash_num = hash(str);
            int hash_num_init = hash_num;

            while (!str_list[hash_num].empty()) {
                // 既に全く同じ文字列が登録されている時はbreak
                if (str_list[hash_num] == str) {
                    std::cout << "Already exists!\n";
                    error = true;
                    break;
                }

                // 既に同じハッシュに別の文字列が登録されている時は次が空いているか確認
                std::cout << "Collision! (hash=" << hash_num << " " << str_list[hash_num] << ")\n";
                hash_num++;
                hash_num %= HASH_SIZE;
                if (hash_num == hash_num_init) {
                    std::cout << "Hash overflow!\n";
                    error = true;
                    break;
                }
            }
            if (error) {
                break;
            }
            std::cout << "Add succeed! (hash=" << hash_num << ")\n";
            str_list[hash_num] = str;

            break;
        }

        case 'r': {
            std::string str;
            std::cout << "string to remove? : ";
            std::cin >> str;
            int hash_num = hash(str);
            int hash_num_init = hash_num;

            std::cout << "hash=" << hash_num << "\n";

            while (str_list[hash_num] != str) {
                hash_num++;
                hash_num %= HASH_SIZE;
                if (hash_num == hash_num_init) {
                    std::cout << "Not found\n";
                    error = true;
                    break;
                }
            }
            if (error) {
                break;
            }
            std::cout << "Remove succeed! (hash=" << hash_num << ")\n";

            break;
        }

        case 's': {
            std::string str;
            std::cout << "string to search? : ";
            std::cin >> str;
            int hash_num = hash(str);
            int hash_num_init = hash_num;
            std::cout << "hash=" << hash_num << "\n";

            while (str_list[hash_num] != str) {
                hash_num++;
                hash_num %= HASH_SIZE;
                if (hash_num == hash_num_init) {
                    std::cout << "Not found\n";
                    error = true;
                    break;
                }
            }
            if (error) {
                break;
            }
            std::cout << "Found! (hash=" << hash_num << ")\n";

            break;
        }

        case 'q': {
            return 0;
        }

        default:
            break;
        }

        std::cout << "\n";
    }

    return 0;
}
