#include <iostream>
#include <fstream>
#include <queue>
#include <string>

using namespace std;

struct Entity {
    string role;
    string name;
};

struct CompareEntity {
    bool operator()(const Entity& e1, const Entity& e2) {
        if (e1.role == "parent" && (e2.role == "teacher" || e2.role == "student")) return false;
        if (e1.role == "teacher" && e2.role == "student") return false;
        return true; 
    }
};

void writeToFile(priority_queue<Entity, deque<Entity>, CompareEntity> entities) {
    ofstream file("people.txt");
    if (file.is_open()) {
        while (!entities.empty()) {
            file << entities.top().role << endl;
            file << entities.top().name << endl;
            entities.pop();
        }
        file.close();
    }
    else {
        cout << "Unable to open file";
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
        cout << "Unable to open file";
    }
}

int main() {
    int count;
    cout << "Enter the total number of entities: ";
    cin >> count;

    priority_queue<Entity, deque<Entity>, CompareEntity> entities;

    for (int i = 0; i < count; i++) {
        string role, name;
        cout << "Enter entity " << i + 1 << " type (student, teacher, parent): ";
        cin >> role;
        cout << "Enter entity " << i + 1 << " name: ";
        cin >> name;

        entities.push({ role, name });
    }

    writeToFile(entities);

    cout << "Total people:\n";
    displayFile();

    return 0;
}
