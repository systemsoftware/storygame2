// Build with CLion 243.22562.155 for Education

#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Room {
public:
    string desc;
    string choice1, choice2;
    int nextRoom1, nextRoom2;
    bool clearAfter;

    Room(const string& d, const string& c1, const string& c2, const int& nr1, const int& nr2, const bool& ca = false)
        : desc(d), choice1(c1), choice2(c2), nextRoom1(nr1), nextRoom2(nr2), clearAfter(ca) {}
};


class Game {
    vector<Room> rooms;
    int currentRoom;
    int sanity;
    int knowledge;
    vector<string> inventory;

public:
    Game() : currentRoom(0), sanity(100), knowledge(0) {}

    void add(const Room& room) {
        rooms.push_back(room);
    }

    void start() {
        while (currentRoom != -1) {
            show();
        }
    }

private:
    void show() {
        if (currentRoom >= rooms.size()) {
            cout << "Invalid room. Ending story." << endl;
            currentRoom = -1;
            return;
        }

        const Room& room = rooms[currentRoom];
        cout << endl << room.desc << endl << endl;

        if (room.choice1.empty()) {
            cout << "=============================================" << endl;
            cout << "Game Over" << endl;
            cout << "Your Final Stats:" << endl;
            cout << "Sanity: " << sanity << " | Knowledge: " << knowledge << endl;
            cout << "Inventory: ";
            if (inventory.empty()) {
                cout << "None";
            } else {
                for (const string& item : inventory) {
                    cout << item;
                    if (item != inventory.back()) {
                        cout << ", ";
                    }
                }
            }
            cout << endl << "=============================================" << endl;
            currentRoom = -1;
            return;
        }

        cout << "Sanity: " << sanity << " | Knowledge: " << knowledge << endl;
        cout << "Inventory: ";
        if (inventory.empty()) {
            cout << "None";
        } else {
            for (const string& item : inventory) {
                cout << item;
                if (item != inventory.back()) {
                    cout << ", ";
                }
            }
        }

        cout << endl << endl;

        cout << "1) " << room.choice1 << endl;
        cout << "2) " << room.choice2 << endl;

        int choice;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            handleChoice(room.nextRoom1);
        } else if (choice == 2) {
            handleChoice(room.nextRoom2);
        } else {
            cout << "1 or 2 only. Try again." << endl;
        }
    }

    void handleChoice(const int nextRoom) {

        bool eventHappened = false;

        if (random() % 5 == 0) {
            eventHappened = true;
            cout << "A strange event occurs! Your sanity decreases slightly." << endl;
            sanity -= 10;
        }

        if (random() % 8 == 0) {
            if (eventHappened) return;
            eventHappened = true;
            cout << "You feel a sense of dread. Your sanity decreases slightly." << endl;
            sanity -= 5;
        }

        if (random() % 4 == 0) {
            if (eventHappened) return;
            eventHappened = true;
            cout << "You have a moment of clarity. Your sanity increases slightly." << endl;
            sanity += 5;
        }

        if (random() % 6 == 0) {
            if (eventHappened) return;
            eventHappened = true;
            cout << "You find a hidden item. Your knowledge increases slightly." << endl;
            knowledge += 5;
        }

        if (random() % 15 == 0) {
            if (eventHappened) return;
            eventHappened = true;
            cout << "You have a moment of insight. Your knowledge increases slightly." << endl;
            knowledge += 10;
        }

        if (sanity <= 0) {
            if (eventHappened) cout << "That event was the final straw. Your sanity has reached 0. You have lost your mind and the game ends." << endl;
            else cout << "Your sanity has reached 0. You have lost your mind and the game ends." << endl;
            currentRoom = -1;
            return;
        }

        if (knowledge >= 100) {
            cout << "You have gained enough knowledge to solve the mysteries of Solaris. You win the game!" << endl;
            cout << "The mystery is that the planet is a sentient being that can create physical manifestations based on the memories and emotions of visitors, but its methods are beyond human understanding. These manifestations are a reflection of one's innermost thoughts and desires, and are both real and unreal at the same time." << endl;
            currentRoom = -1;
            return;
        }

        if (nextRoom >= 0 && nextRoom < rooms.size()) {
            const Room& room = rooms[nextRoom];

            if (room.desc.find("manifestations") != string::npos) {
                if (find(inventory.begin(), inventory.end(), "Research Notes") == inventory.end()) {
                    inventory.push_back("Research Notes");
                }
                knowledge += 10;
                cout << "You found Research Notes. Knowledge increased!" << endl;
            }

            if (room.desc.find("Hari") != string::npos && currentRoom == 5) {
                sanity -= 20;
                cout << "Seeing Hari has shaken your sanity. Sanity decreased!" << endl;
            }

            if (room.desc.find("brainwaves") != string::npos) {
                if (find(inventory.begin(), inventory.end(), "Brainwave Device") == inventory.end()) {
                    inventory.push_back("Brainwave Device");
                }
                knowledge += 20;
                cout << "You found Brainwave Device. Knowledge increased!" << endl;
            }

            if (room.desc.find("self-destruct") != string::npos) {
                if (find(inventory.begin(), inventory.end(), "Self-Destruct Code") == inventory.end()) {
                    inventory.push_back("Self-Destruct Code");
                }
                knowledge += 30;
                cout << "You found Self-Destruct Code. Knowledge increased!" << endl;
            }

            currentRoom = nextRoom;

            if (room.clearAfter) {
                cout << "\033c";
            }
        } else {
            cout << "The path is unclear, but you continue your journey." << endl;
            currentRoom = nextRoom;
        }
    }
};

int main() {
    Game story;

    cout << "\033c";

    cout << "Welcome to the Solaris! This is based on the 1972 film directed by Andrei Tarkovsky, which is based on the novel by Stanisław Lem." << endl;

    cout << "The film is available on YouTube: https://www.youtube.com/watch?v=Z8ZhQPaw4rE" << endl << endl;

    cout << "=============================================" << endl << endl;

    cout << "You are Kris Kelvin, a psychologist, tasked to uncover the mysteries of Solaris." << endl;

    story.add(Room(
        "You are at your family’s home in rural Russia and are preparing for a mission to a space station orbiting the planet Solaris.",
        "Begin your journey to Solaris", "Stay on Earth", 1, 14, true));

    story.add(Room(
        "You arrive at the space station orbiting Solaris. You are greeted by Dr. Snaut and Dr. Sartorius, the two scientists who have been studying the planet.",
        "Explore the station", "Return to Earth", 2, 8));

    story.add(Room(
        "You explore the station, which is in a state of chaos. One scientist, Dr. Gibarian, is dead, and the other two scientists, Dr. Snaut and Dr. Sartorius, are acting strangely.",
        "Talk to Dr. Snaut", "Talk to Dr. Sartorius", 3, 4));

    story.add(Room(
        "You decide to talk to Dr. Snaut. He seems emotionally unstable and tells you that the planet Solaris has been sending strange manifestations to the station.",
        "Investigate these manifestations", "Talk to Dr. Sartorius", 5, 4));

    story.add(Room(
        "You decide to talk to Dr. Sartorius. He is cold and distant, and tells you that they think Solaris is trying to communicate with them through manifestations.",
        "Investigate these manifestations", "Talk to Dr. Snaut", 5, 3));

    story.add(Room(
        "You investigate the manifestations. They are strange and seem to be based on your memories. Suddenly see your late wife, Hari, who died years ago. She is alive and seems to be real.",
        "Accept Hari as real", "Reject Hari as an illusion", 6, 7, true));

    story.add(Room(
        "You accept Hari as real and try to live with her on the station. However, you soon realize that she is just a manifestation and cannot replace the real Hari.",
        "Leave the station", "Stay on the station", 8, 9));

    story.add(Room(
        "You reject Hari as an illusion and focus on solving the mystery of Solaris. You decide to continue studying the planet.",
        "Continue studies", "End mission", 9, 8));

    story.add(Room(
        "You leave Solaris, never to return. The memories of the planet and its manifestations will haunt you forever.",
        "", "", -1, -1));

    story.add(Room(
        "You decide to continue your studies of Solaris, hoping to understand the planet and its manifestations. The mysteries of Solaris will continue to fascinate you. Dr. Snaut suggests sending your brainwaves to the planet to communicate with it.",
        "Agree to the experiment", "Refuse the experiment", 10, 13, true));

    story.add(Room(
        "You agree to the experiment and send your brainwaves to Solaris. You experience strange visions and communicate with the planet in a way that is beyond human comprehension. The mysteries of Solaris remain unsolved, but you have made a connection with the planet. This experiment make you want to...",
        "Stay on the station", "Destroy the station", 11, 12));

    story.add(Room(
        "You decide to stay and surrender to the unknown. You find yourself back at your countryside home. You think this is a construct of Solaris, but you don't care. You are happy to be with Hari again.",
        "", "", -1, -1));

    story.add(Room(
        "You decide to destroy the station and end the experiments with Solaris. You set the station to self-destruct and escape in a shuttle. As you watch the station explode, you feel a sense of relief and freedom.",
        "", "", -1, -1));

    story.add(Room(
        "You refuse the experiment and return to Earth. You try to move on from the memories of Solaris, but the mysteries of the planet continue to haunt you.",
        "", "", -1, -1));

    story.add(Room(
        "You decide to stay on Earth and not go on the mission to Solaris. You try to move on with your life, but you will always wonder about the mysteries of the planet.",
        "", "", -1, -1));

    story.start();

    return 0;
}