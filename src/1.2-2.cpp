#include <iostream>

char to_char(int num) {
    switch (num) {
        case 0:
            return 'a';
        case 1:
            return 'b';
        case 2:
            return 'c';
        default:
            return '_';
    }
}

void hanoi(char from, char to, char spare, int disk_count) {
    if (disk_count > 0) {
        hanoi(from, spare, to, disk_count-1);
        std::cout << "move disk_count#" << disk_count << " from " << from << " to " << to << std::endl;
        hanoi(spare, to, from, disk_count-1);
    }
}

int main(int argc, char const *argv[])
{
    int disk_count;
    std::cout << "円盤の枚数 : ";
    std::cin >> disk_count;
    if (disk_count <= 0) {
        std::cout << "1以上の整数を入力してください" << std::endl;
    }
    hanoi('a', 'c', 'b', disk_count);
    return 0;
}