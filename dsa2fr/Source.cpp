#include <iostream>
#include <fstream>
#include <stack>
#include <string>

using namespace std;

struct Entity {
    string role;
    string name;
};

void writeToFile(stack<Entity>& entities) {
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

    stack<Entity> entities;

    for (int i = 0; i < count; i++) {
        string role, name;
        cout << "Enter entity " << i + 1 << " type (student, teacher, parent): ";
        cin >> role;
        cout << "Enter entity " << i + 1 << " name: ";
        cin >> name;

        stack<Entity> tempStack;

        while (!entities.empty() && (
            (role == "student" && entities.top().role != "student") ||
            (role == "teacher" && entities.top().role == "parent")
            )) {
            tempStack.push(entities.top());
            entities.pop();
        }

        entities.push({ role, name });

        while (!tempStack.empty()) {
            entities.push(tempStack.top());
            tempStack.pop();
        }
    }

    writeToFile(entities);

    cout << "Contents of people.txt:" << endl;
    displayFile();

    return 0;
}
