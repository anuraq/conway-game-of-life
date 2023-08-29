#include <SFML/Graphics.hpp>
#include <iostream>
#include <random>

using namespace std;

uint WINDOW_HEIGHT = 480, WINDOW_WIDTH = 640;

bool random_bool() {
  float r = (float)rand() / RAND_MAX;
  if (r < 0.5)
    return false;
  else
    return true;
}

int main(int argc, char *argv[]) {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test");

  vector<vector<char>> world(48, vector<char>(64));

  for (auto &row : world) {
    for (auto &cell : row) {
      cell = random_bool() ? '0' : '1';
    }
  }

  // int counter = 0;
  // for (auto i : world) {
  //   for (auto j : i) {
  //     cout << "Random Number : " << j << endl;
  //     // counter++;
  //   }
  // }
  // cout << "Counter : " << counter << endl; // 64 // 3072
  // (* 64 48)

  // sf::RectangleShape rec2(sf::Vector2f(10.0f, 10.0f));
  // rec2.setFillColor(sf::Color::Cyan);
  // rec2.setPosition(sf::Vector2f(10.0f, 10.0f));

  // Main loop
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

    // Clear the window
    window.clear(sf::Color::Black);

    for (int i = 0; i < 48; i++) {
      for (int j = 0; j < 64; j++) {
        if (world[i][j] == '1') {
          sf::RectangleShape rec(sf::Vector2f(10.0f, 10.0f));
          rec.setPosition(sf::Vector2f(10.f * j, 10.f * i));
          window.draw(rec);
        }
      }
    }

    // Draw
    // window.draw(rec1);
    // window.draw(rec2);

    // Display the content
    window.display();
  }

  return 0;
}
