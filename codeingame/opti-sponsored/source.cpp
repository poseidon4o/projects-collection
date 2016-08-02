#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>
#include <unordered_set>
#include <utility>
#include <sstream>
using namespace std;

#define LOG(...) { fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#define ACTION(...) { fprintf(stdout, __VA_ARGS__); fprintf(stdout, "\n");}

struct coord_t {
    coord_t(int x, int y) : x(x), y(y) {}
    union {
        int data[2];
        struct { int x, y; };
        struct { int first, second; };
    };
};

bool operator==(const coord_t & l, const coord_t & r) {
    return l.x == r.x && l.y == r.y;
}

namespace std
{
    template<> struct hash<coord_t>
    {
        typedef coord_t argument_type;
        typedef std::size_t result_type;
        result_type operator()(const argument_type & s) const
        {
            result_type const h1(std::hash<int>()(s.x));
            result_type const h2(std::hash<int>()(s.y));
            return h1 ^ (h2 << 1); // or use boost::hash_combine
        }
    };
}

typedef vector<coord_t> state_t;

// E == UP
// A == DOWN
// C == LEFT
// D == RIGHT
// B == stay

enum dir_t : char {
    DOWN  = 'A',
    STAY  = 'B',
    LEFT  = 'C',
    RIGHT = 'D',
    UP    = 'E',
    INVALID = 'X',
};

dir_t invert(dir_t d) {
    switch (d)
    {
    case DOWN: return UP;
    case STAY: return INVALID;
    case LEFT: return RIGHT;
    case RIGHT: return LEFT;
    case UP: return DOWN;
    case INVALID:
    default: return INVALID;
    }
}

const char * dirToStr(dir_t d) {
    switch (d)
    {
    case DOWN: return "DOWN";
    case STAY: return "STAY";
    case LEFT: return "LEFT";
    case RIGHT: return "RIGHT";
    case UP: return "UP";
    case INVALID: return "INVALID";
    default: return "UNKNOWN";
    }
}

char dirToC(dir_t d) {
    char c = static_cast<char>(d);
    if (c < 'A' || c > 'E') {
        LOG("INVALID dir to action %c", c);
        exit(1);
    }
    return c;
}

dir_t cToDir(char c) {
    dir_t d = static_cast<dir_t>(c);
    if (d < DOWN || d > UP) {
        LOG("INVALID action to dir %c", c);
        exit(1);
    }
    return d;
}

struct field_t {
    enum cell_t {
        empty = '.',
        wall = '#',
        free = '_',
    };

    const char * cellType(cell_t cell) {
        switch (cell)
        {
        case field_t::empty: return "empty";
        case field_t::wall: return "wall";
        case field_t::free: return "free";
        default: return "NONE";
        };
    };

    typedef vector<cell_t> row_t;

    field_t(int w, int h) : m_data(w, row_t(h, empty)) {
        dfs.m_init = false;
    }

    bool isEnemy(int x, int y, state_t & st) {
        for (int c = 0; c < st.size(); ++c) {
            if (st[c].first == x && st[c].second == y) {
                return true;
            }
        }
        return false;
    }

    char atField(int x, int y, state_t & st) {
        for (int c = 0; c < st.size(); ++c) {
            if (st[c].first == x && st[c].second == y) {
                if (m_data[x][y] == wall) {
                    LOG("[%d,%d] is %s and has %c on it", x, y, cellType(wall), 'A' + c);
                }
                return 'A' + c;
            }
        }
        return m_data[x][y];
    }

    void print(state_t & st) {
        stringstream data;
        for (int c = 0; c < m_data.size(); ++c) {
            for (int r = 0; r < m_data[c].size(); ++r) {
                data << atField(c, r, st);
            }
            data << endl;
        }
        LOG(data.str().c_str());
        LOG("");
    }

    void update(int x, int y, char val) {
        switch (val)
        {
        case '_': return update(x, y, free);
        case '#': return update(x, y, wall);
        default: LOG("WTF %c input to update [%d,%d]", val, x, y);
        }
    }

    void update(int x, int y, cell_t val) {
        if (x < 0 || y < 0 || x >= m_data.size() || y >= m_data[0].size()) {
            return;
        }

        if (m_data[x][y] != empty && m_data[x][y] != val) {
            LOG("[%d,%d] set to %s but was %s", x, y, cellType(val), cellType(m_data[x][y]));
        }

        m_data[x][y] = val;
    }

    struct dfs_state_t {
        int idx;
        dir_t from;
    };

    void dfs_init() {
        if (dfs.m_init) {
            return;
        }
        dfs.m_init = true;
        dfs.m_state.push({ 0, INVALID });
    }

    char dfs_step(int x, int y, state_t & state) {
        static coord_t steps[4] = {
            { 0, 1 },{ 0, -1 },{ 1, 0 },{ -1, 0 }
        };

        dir_t step_map[4] = { RIGHT, LEFT, DOWN, UP };

        if (dfs.m_state.empty()) {
            LOG("dfs_step(%d, %d) STATE EMPTY", x, y);
            exit(1);
        }

        auto & st = dfs.m_state.top();
        dfs.m_visited.insert(coord_t{ x, y });

        LOG("dfs_step(%d, %d) [marked as visited], state {%d, %c} size(%d)", x, y, st.idx, st.from, dfs.m_state.size());

        for (/**/; st.idx < 4; ++st.idx) {
            auto tx = x + steps[st.idx].x;
            auto ty = y + steps[st.idx].y;

            LOG("disp [%d, %d] -> [%d, %d] = %s", steps[st.idx].x, steps[st.idx].y, tx, ty, cellType(m_data[tx][ty]));

            if (!isEnemy(tx, ty, state) && m_data[tx][ty] == free && dfs.m_visited.find(coord_t{tx, ty}) == dfs.m_visited.end()) {

                LOG("found empty field %d, pushing state", st.idx);

                // push new state on stack with iter 0
                // and how we got there map[idx]
                // return where we go
                dfs.m_state.push({ 0, step_map[st.idx] });
                return dirToC(step_map[st.idx]);
            }
        }

        // we are here so finished this iter
        // go back 1 lvl, and pop state
        LOG("iter ended, poping state back %c", st.from);
        auto to = invert(st.from);
        dfs.m_state.pop();
        return dirToC(to);
    }

    row_t & operator[](int c) {
        return m_data[c];
    }

    struct {
        bool m_init;
        stack<dfs_state_t> m_state;
        unordered_set<coord_t, hash<coord_t>> m_visited;
    } dfs;
    vector<row_t> m_data;
};



int main()
{
    int width;
    cin >> width; cin.ignore();
    int height;
    cin >> height; cin.ignore();
    int figCount;
    cin >> figCount; cin.ignore();

    cerr << width << " " << height << " " << figCount << endl;

    int left = 8;
    int up = 12;

    field_t F(width, height);

    F.dfs_init();

    // game loop
    while (1) {
        string f1, f2, f3, f4;
        cin >> f1; cin.ignore(); cin >> f2; cin.ignore();
        cin >> f3; cin.ignore(); cin >> f4; cin.ignore();

        char U = f1[0], R = f2[0], D = f3[0], L = f4[0];

        state_t moves;

        for (int i = 0; i < figCount - 1; i++) {
            int a, b;
            cin >> a >> b; cin.ignore();
            moves.push_back(coord_t(a, b));
            F.update(a, b, field_t::cell_t::free);
        }
        //   U
        //  L.R
        //   D

        int x, y;
        cin >> x >> y;
        moves.push_back(coord_t(x, y));

        F.update(x - 1, y, L);
        F.update(x + 1, y, R);

        F.update(x, y + 1, D);
        F.update(x, y - 1, U);

        F.print(moves);

        auto toWhere = F.dfs_step(x, y, moves);
        LOG("Moving %s", dirToStr(cToDir(toWhere)));

        ACTION("%c", toWhere);
    }
}