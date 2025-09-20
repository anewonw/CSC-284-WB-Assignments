// CSC 284
// Unit 2 Assignment 2: Fix this Code!
// Andrew Dasch

#include <iostream>
#include <vector>

using namespace std;


class TrafficLight {
private:

    enum lightNumber { Red = 0, Green = 1, Yellow = 2 };
    vector<string> m_lightColor { "Red","Green","Yellow" };
    
public:
    void changeLight(const int numTimes) {
        int lightCounter = Red;
        for (int i = 0; i < numTimes; i++) {
            cout << m_lightColor[lightCounter] << endl;
            lightCounter++;
            if (lightCounter == 3)
                lightCounter = Red;
        }
    }

};


void ch(int c) {
    int x = 0;
    for (int i = 0; i < c; i++) {
        cout << v[x] << endl;
        x++;
        if (x == 3)x = 0;
    }
}

int main() {
    int n;
    cout << "how many?:";
    cin >> n;
    ch(n);
}