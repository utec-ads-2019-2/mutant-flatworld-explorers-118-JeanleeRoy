#include <string>
#include <vector>
#include <map>

using namespace std;

bool in_lost (int, int);

vector<int> Lost;
map <string, char> combs {{"ER", 'S'}, {"EL", 'N'}, {"SR", 'W'}, {"SL", 'E'},
                          {"WR", 'N'}, {"WL", 'S'}, {"NR", 'E'}, {"NL", 'W'}};

int main(int argc, char const *argv[]) {
    int x, y, x_limit, y_limit;
    char orien;
    scanf("%d %d", &x_limit, &y_limit);

    while (scanf("%d %d %c", &x, &y, &orien) != EOF) {
        bool lost = false;
        int prevx, prevy;
        char moves[100] = "";
        string concat;
        scanf("%s", moves);
        for (int i = 0; i < 100; ++i) {
            if (moves[i] == 'F') {
                prevx = x; prevy = y;
                x = (orien == 'E') ? ++x : (orien == 'W') ? --x : x;
                y = (orien == 'N') ? ++y : (orien == 'S') ? --y : y;
                if (x > x_limit || x < 0 || y > y_limit || y < 0) {
                    if (in_lost(prevx, prevy)) {
                        x = prevx;
                        y = prevy;
                        continue;
                    } else {
                        Lost.push_back(prevx);
                        Lost.push_back(prevy);
                        lost = true; break;
                    }
                }
            } 
            else if (moves[i] == 'R' || moves[i] == 'L') {
                string  o(1, orien), m(1, moves[i]);
                concat = o + m;
                orien = combs.at(concat);
            }
        }
        if (lost) printf("%d %d %c LOST\n", prevx, prevy, orien);
        else printf("%d %d %c\n", x, y, orien);
    }
    return 0;
}

bool in_lost (int x, int y) {
    for (int i = 0; i < Lost.size()/2; ++i)
        if (x == Lost[i*2] && y == Lost[i*2+1])// && orien == Lost_orien[i])
            return true;
    return false;
}
