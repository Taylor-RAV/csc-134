/**
 * @file mazebuilder_plus.cpp
 * @author James Taylor
 * @brief M6HW1: MazeBuilder with Dijkstra Pathfinding
 * * CORE FEATURE: Random Maze Generation (Sidewinder Algorithm).
 * EXTRA FEATURE: Shortest Path Calculation (Dijkstra's Algorithm).
 * * Usage:
 * - Arrows to move.
 * - 'P' to toggle the calculated Shortest Path to the exit.
 * - 'S' to interact/talk.
 */

#include <iostream>
#include <vector>
#include <random>
#include <ctime>
#include <algorithm>
#include <conio.h>
#include <map>
#include <queue>
#include <iomanip>
#include <windows.h>
using namespace std;


enum Direction {
    NORTH = 1,
    SOUTH = 2,
    EAST = 4,
    WEST = 8
};

const Direction OPPOSITES[] = {
    (Direction)0, SOUTH, NORTH, (Direction)0, WEST, (Direction)0, (Direction)0, (Direction)0, EAST
};


class Cell {
private:
    int row, col;
    int links;

public:
    Cell(int r, int c) : row(r), col(c), links(0) {}
    int getRow() const { return row; }
    int getCol() const { return col; }
    bool linked(Direction dir) const { return (links & dir) != 0; }
    void link(Direction dir) { links |= dir; }
};

class Grid {
private:
    int rows, cols;
    vector<vector<Cell>> cells;
    mt19937 rng;

public:
    Grid(int r, int c) : rows(r), cols(c) {
        rng.seed(static_cast<unsigned int>(time(nullptr)));
        for (int r_idx = 0; r_idx < rows; r_idx++) {
            vector<Cell> row_vec;
            for (int c_idx = 0; c_idx < cols; c_idx++) {
                row_vec.emplace_back(r_idx, c_idx);
            }
            cells.push_back(row_vec);
        }
    }

    int getRows() const { return rows; }
    int getCols() const { return cols; }
    bool isValid(int r, int c) const { return r >= 0 && r < rows && c >= 0 && c < cols; }
    Cell& at(int r, int c) { return cells[r][c]; }
    const Cell& at(int r, int c) const { return cells[r][c]; }

    void linkCells(int r1, int c1, Direction dir) {
        int r2 = r1 + (dir == NORTH ? -1 : (dir == SOUTH ? 1 : 0));
        int c2 = c1 + (dir == EAST ? 1 : (dir == WEST ? -1 : 0));
        if (isValid(r2, c2)) {
            at(r1, c1).link(dir);
            at(r2, c2).link(OPPOSITES[dir]);
        }
    }

    int random(int min, int max) {
        uniform_int_distribution<int> dist(min, max);
        return dist(rng);
    }
};

/**
 * @brief Resets the console cursor to (0,0) without clearing the screen.
 * This prevents the "shaking" effect caused by system("cls").
 */
void resetCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = { 0, 0 };
    SetConsoleCursorPosition(hOut, coord);
}

/**
 * @brief Hides the blinking console cursor for a cleaner look.
 */
void hideCursor() {
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO cursorInfo;
    GetConsoleCursorInfo(hOut, &cursorInfo);
    cursorInfo.bVisible = false;
    SetConsoleCursorInfo(hOut, &cursorInfo);
}

class SidewinderMaze {
public:
    /**
     * @brief Generates a maze using the Sidewinder algorithm.
     * This algorithm processes the grid row by row, creating runs of cells.
     * It eliminates the "straight right passage" bias found in Binary Tree.
     */
    static void generate(Grid& grid) {
        for (int r = 0; r < grid.getRows(); r++) {
            vector<pair<int, int>> run;

            for (int c = 0; c < grid.getCols(); c++) {
                run.push_back({r, c});

                bool at_eastern_boundary = (c == grid.getCols() - 1);
                bool at_northern_boundary = (r == 0);

                // Decide whether to close the run
                bool should_close_run = at_eastern_boundary || (!at_northern_boundary && grid.random(0, 1) == 0);

                if (should_close_run) {
                    if (!at_northern_boundary) {
                        // Pick a random member of the current run and link it North
                        int member_index = grid.random(0, run.size() - 1);
                        pair<int, int> member = run[member_index];
                        grid.linkCells(member.first, member.second, NORTH);
                    }
                    run.clear();
                } else {
                    // Continue the run by linking East
                    grid.linkCells(r, c, EAST);
                }
            }
        }
    }
};


class DijkstraPathfinder {
public:
    // Calculates distances from a root cell to all others using Breadth-First Search
    static map<pair<int, int>, int> calculateDistances(Grid& grid, int startR, int startC) {
        map<pair<int, int>, int> distances;
        queue<pair<int, int>> q;

        distances[{startR, startC}] = 0;
        q.push({startR, startC});

        while (!q.empty()) {
            pair<int, int> current = q.front();
            q.pop();

            Cell& cell = grid.at(current.first, current.second);
            Direction dirs[] = {NORTH, SOUTH, EAST, WEST};

            for (Direction d : dirs) {
                if (cell.linked(d)) {
                    int nr = current.first + (d == NORTH ? -1 : (d == SOUTH ? 1 : 0));
                    int nc = current.second + (d == EAST ? 1 : (d == WEST ? -1 : 0));

                    if (distances.find({nr, nc}) == distances.end()) {
                        distances[{nr, nc}] = distances[current] + 1;
                        q.push({nr, nc});
                    }
                }
            }
        }
        return distances;
    }

    // Backtracks from the exit to the start to find the shortest path
    static vector<pair<int, int>> findShortestPath(Grid& grid, int startR, int startC, int endR, int endC) {
        map<pair<int, int>, int> distances = calculateDistances(grid, startR, startC);
        vector<pair<int, int>> path;

        pair<int, int> current = {endR, endC};
        path.push_back(current);

        while (current.first != startR || current.second != startC) {
            Cell& cell = grid.at(current.first, current.second);
            Direction dirs[] = {NORTH, SOUTH, EAST, WEST};

            for (Direction d : dirs) {
                if (cell.linked(d)) {
                    int nr = current.first + (d == NORTH ? -1 : (d == SOUTH ? 1 : 0));
                    int nc = current.second + (d == EAST ? 1 : (d == WEST ? -1 : 0));

                    if (distances.count({nr, nc}) && distances[{nr, nc}] < distances[current]) {
                        current = {nr, nc};
                        path.push_back(current);
                        break;
                    }
                }
            }
        }
        return path;
    }
};


struct GameState {
    int px = 0, py = 0;
    int ex, ey;
    bool showPath = false;
    bool won = false;
    string author = "James Taylor";
};

bool onPath(int r, int c, const vector<pair<int, int>>& path) {
    for (auto const& p : path) {
        if (p.first == r && p.second == c) return true;
    }
    return false;
}

void render(Grid& grid, GameState& state, const vector<pair<int, int>>& path) {
    resetCursor();
    cout << "=================================================" << endl;
    cout << " MAZEBUILDER PLUS | AUTHOR: " << state.author << endl;
    cout << " ALGORITHM: Sidewinder (Reduced Bias)" << endl;
    cout << " GOAL: Reach the exit [E]. Press [P] for Dijkstra Path." << endl;
    cout << "=================================================" << endl;

    for (int r = 0; r < grid.getRows(); r++) {
        // North boundaries
        for (int c = 0; c < grid.getCols(); c++) {
            cout << "+";
            cout << (grid.at(r, c).linked(NORTH) ? "   " : "---");
        }
        cout << "+" << endl;

        // Cell contents and West/East boundaries
        for (int c = 0; c < grid.getCols(); c++) {
            cout << (grid.at(r, c).linked(WEST) ? " " : "|");

            if (r == state.py && c == state.px) cout << " @ ";
            else if (r == state.ey && c == state.ex) cout << " E ";
            else if (state.showPath && onPath(r, c, path)) cout << " . ";
            else cout << "   ";
        }
        cout << "|" << endl;
    }

    for (int c = 0; c < grid.getCols(); c++) cout << "+---";
    cout << "+" << endl;
    cout << "\n [Arrows] Move  [P] Toggle Path  [S] Talk  [ESC] Quit   " << endl; // Added spaces to overwrite previous text
}


int main() {
    hideCursor();    int rows = 12, cols = 18;
    Grid grid(rows, cols);
    SidewinderMaze::generate(grid);

    GameState state;
    state.ex = cols - 1; state.ey = rows - 1;

    vector<pair<int, int>> path = DijkstraPathfinder::findShortestPath(grid, 0, 0, state.ey, state.ex);

    while (!state.won) {
        render(grid, state, path);

        int ch = _getch();
        if (ch == 27) break;
        if (tolower(ch) == 'p') state.showPath = !state.showPath;
        if (tolower(ch) == 's') {
            system("cls"); // We still use cls here because it's a completely different screen
            cout << "--- MESSAGE ---" << endl;
            cout << "James Taylor's Maze Logic: Sidewinder generation " << endl;
            cout << "removes the vertical straight-path bias." << endl;
            cout << "Dijkstra's algorithm ensures the solution is valid." << endl;
            system("pause");
            system("cls"); // Clear before going back to the smooth rendering loop
        }

        int nx = state.px, ny = state.py;
        Direction moveDir;
        bool validMove = false;

        if (ch == 0 || ch == 224) {
            switch (_getch()) {
                case 72: ny--; moveDir = NORTH; validMove = true; break; // UP
                case 80: ny++; moveDir = SOUTH; validMove = true; break; // DOWN
                case 75: nx--; moveDir = WEST;  validMove = true; break; // LEFT
                case 77: nx++; moveDir = EAST;  validMove = true; break; // RIGHT
            }
        }

        if (validMove && grid.isValid(ny, nx)) {
            if (grid.at(state.py, state.px).linked(moveDir)) {
                state.px = nx;
                state.py = ny;
            }
        }

        if (state.px == state.ex && state.py == state.ey) state.won = true;
    }

    if (state.won) {
        system("cls");
        cout << "==========================================" << endl;
        cout << " CONGRATULATIONS, JAMES TAYLOR!          " << endl;
        cout << " You reached the exit of the Sidewinder maze." << endl;
        cout << " Pathfinding algorithm verified success.  " << endl;
        cout << "==========================================" << endl;
    }

    return 0;
}
