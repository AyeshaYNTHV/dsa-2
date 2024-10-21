#include <iostream>
#include <fstream>
#include <queue>
#include <string>
#include <deque>
#include <unordered_map>

using namespace std;

struct Entity {
    string role;
    string name;
};

void writeToFile(deque<deque<Entity>> entities2D) {
    ofstream file("people.txt");
    if (file.is_open()) {
        for (auto& roleQueue : entities2D) {
            while (!roleQueue.empty()) {
                file << roleQueue.front().role << endl;
                file << roleQueue.front().name << endl;
                roleQueue.pop_front();
            }
        }
        file.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

void displayFile() {
    ifstream file("people.txt");
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            cout << line << endl;
        }
        file.close();
    }
    else {
        cout << "Unable to open file" << endl;
    }
}

int main() {
    int count;
    cout << "Enter the total number of entities: ";
    cin >> count;

    unordered_map<string, deque<Entity>> roleMap;
    roleMap["parent"] = deque<Entity>();
    roleMap["teacher"] = deque<Entity>();
    roleMap["student"] = deque<Entity>();

    for (int i = 0; i < count; i++) {
        string role, name;
        cout << "Enter entity " << i + 1 << " type (student, teacher, parent): ";
        cin >> role;
        cout << "Enter entity " << i + 1 << " name: ";
        cin >> name;

        if (roleMap.find(role) != roleMap.end()) {
            roleMap[role].push_back({ role, name });
        }
        else {
            cout << "Invalid role entered!" << endl;
        }
    }

    deque<deque<Entity>> entities2D;
    entities2D.push_back(roleMap["parent"]);
    entities2D.push_back(roleMap["teacher"]);
    entities2D.push_back(roleMap["student"]);

    writeToFile(entities2D);

    cout << "Contents of people.txt:" << endl;
    displayFile();

    return 0;
}
