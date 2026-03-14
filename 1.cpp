#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Base Game Object
class GameObject {
protected:
    string name;

public:
    GameObject(string n) {
        name = n;
    }

    virtual void update() {
        cout << name << " updating..." << endl;
    }

    virtual void render() {
        cout << name << " rendering..." << endl;
    }
};

// Player Class
class Player : public GameObject {
private:
    int x, y;

public:
    Player(string n) : GameObject(n) {
        x = 0;
        y = 0;
    }

    void move(char input) {
        if(input == 'w') y++;
        if(input == 's') y--;
        if(input == 'a') x--;
        if(input == 'd') x++;

        cout << "Player Position: (" << x << "," << y << ")" << endl;
    }

    void update() override {
        cout << "Player updating position..." << endl;
    }
};

// Input Handler
class InputHandler {
public:
    char getInput() {
        char input;
        cout << "Enter command (w/a/s/d to move, q to quit): ";
        cin >> input;
        return input;
    }
};

// Game Engine
class GameEngine {
private:
    vector<GameObject*> objects;
    bool running;

public:
    GameEngine() {
        running = true;
    }

    void addObject(GameObject* obj) {
        objects.push_back(obj);
    }

    void update() {
        for(auto obj : objects) {
            obj->update();
        }
    }

    void render() {
        for(auto obj : objects) {
            obj->render();
        }
    }

    void stop() {
        running = false;
    }

    bool isRunning() {
        return running;
    }
};

int main() {

    GameEngine engine;
    InputHandler input;

    Player player("Hero");
    GameObject enemy("Enemy");

    engine.addObject(&player);
    engine.addObject(&enemy);

    while(engine.isRunning()) {

        char command = input.getInput();

        if(command == 'q') {
            engine.stop();
            break;
        }

        player.move(command);

        engine.update();
        engine.render();

        cout << "----------------------" << endl;
    }

    cout << "Game Over!" << endl;

    return 0;
}