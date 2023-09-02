#include <SFML/Graphics.hpp>
#include <iostream>

typedef struct {
  bool state;
  int neighbour_count;
  int age;
} CellState;

using namespace std;

uint WINDOW_HEIGHT = 480, WINDOW_WIDTH = 640;

void conway_rule(vector<vector<CellState>> &world) {
  // REVIEW https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life
  // * Any live cell with fewer than two live neighbours dies, as if by
  // underpopulation.
  // * Any live cell with two or three live neighbours lives on
  // to the next generation.
  // * Any live cell with more than three live neighbours
  // dies, as if by overpopulation.
  // * Any dead cell with exactly three live
  // neighbours becomes a live cell, as if by reproduction.

  for (int i = 0; i < 48; i++) {
    for (int j = 0; j < 64; j++) {
      CellState &cell = world.at(i).at(j);
      // NOTE DIES
      if (cell.state == true &&
          (cell.neighbour_count < 2 || cell.neighbour_count > 3)) {
        cell.state = false;
        vector<vector<int>> neigh = {{0, -1},  {0, 1},   {-1, 0},  {+1, 0},
                                     {+1, +1}, {+1, -1}, {-1, +1}, {-1, -1}};

        for (auto c : neigh) {
          int row = i + c[0];
          int col = j + c[1];
          if (0 <= row && row < 48 && 0 <= col && col < 64) {
            world.at(row).at(col).neighbour_count--;
          }
        }
      }

      if (cell.state == false && cell.neighbour_count == 3) {
        cell.state = true;
        vector<vector<int>> neigh = {{0, -1},  {0, 1},   {-1, 0},  {+1, 0},
                                     {+1, +1}, {+1, -1}, {-1, +1}, {-1, -1}};
        for (auto c : neigh) {
          int row = i + c[0];
          int col = j + c[1];
          if (0 <= row && row < 48 && 0 <= col && col < 64) {
            world.at(row).at(col).neighbour_count++;
          }
        }
      }
    }
  }
}

bool random_bool() {
  float r = (float)rand() / (float)RAND_MAX;
  if (r < 0.5)
    return false;
  else
    return true;
}

int main(int argc, char *argv[]) {
  sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Test");

  vector<vector<CellState>> world(48, vector<CellState>(64));

  for (int i = 0; i < 48; i++) {
    for (int j = 0; j < 64; j++) {
      CellState &cell = world.at(i).at(j);
      // cell.state = random_bool();
      if (random_bool()) {
        cell.state = true;
        vector<vector<int>> neigh = {{0, -1},  {0, 1},   {-1, 0},  {+1, 0},
                                     {+1, +1}, {+1, -1}, {-1, +1}, {-1, -1}};

        for (auto c : neigh) {
          int row = i + c[0];
          int col = j + c[1];
          if (0 <= row && row < 48 && 0 <= col && col < 64) {
            world.at(row).at(col).neighbour_count++;
          }
        }
      } else {
        cell.state = false;
      }
    }
  }

  // for (auto &row : world) {
  //   for (CellState &cell : row) {
  //     cell.state = random_bool();
  //   }
  // }

  // cout << "Counter : " << counter << endl; // 64 // 3072
  // (* 64 48)

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
        if (world[i][j].state) {
          sf::RectangleShape rec(sf::Vector2f(10.0f, 10.0f));
          rec.setPosition(sf::Vector2f(10.f * j, 10.f * i));
          // rec.setFillColor(sf::Color(150, 0, 50, 255));
          // rec.setFillColor(sf::Color::Cyan);
          window.draw(rec);
        }
      }
    }

    conway_rule(world);
    sf::sleep(sf::milliseconds(100));
    // Draw
    // window.draw(rec1);
    // window.draw(rec2);

    // Display the content
    window.display();
  }

  return 0;
}
