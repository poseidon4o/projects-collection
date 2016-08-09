#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <utility>
#include <sstream>
#include <bitset>
#include <memory>
using namespace std;

#define LOG(...) { fprintf(stderr, __VA_ARGS__); fprintf(stderr, "\n");}
#define ERR(...) { LOG(__VA_ARGS__); exit(1); }


struct coord_t {
    coord_t(int x = -1, int y = -1) : x(x), y(y) {}
    int x, y;
};

bool operator==(const coord_t & l, const coord_t & r) {
    return l.x == r.x && l.y == r.y;
}

bool operator!=(const coord_t & l, const coord_t & r) {
    return !(l == r);
}

coord_t operator+(const coord_t & l, const coord_t & r) {
    return coord_t(l.x + r.x, l.y + r.y);
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
typedef bitset<32> movemap_t;
struct state_t {
    vector<coord_t> m_items;
    const movemap_t * m_map;

    state_t(const movemap_t &m) : m_map(&m) {

    }

    void add(coord_t ps) {
        m_items.push_back(ps);
    }

    void add(int x, int y) {
        m_items.push_back(coord_t(x, y));
    }

    const coord_t & player() const {
        return m_items.back();
    }

    int size() const {
        return m_items.size();
    }

    coord_t & back() {
        return m_items.back();
    }

    coord_t & at(int idx) {
        return m_items.at(idx);
    }

    const coord_t & at(int idx) const {
        return m_items.at(idx);
    }

    const coord_t & operator[](int idx) {
        return m_items[idx];
    }

    bool isMoving(int c) {
        return m_map && m_map->any() ? m_map->test(c) : true;
    }

    bool isEnemy(int x, int y) {
		coord_t at(x, y);
        for (int c = 0; c < m_items.size() - 1; ++c) {
            if (m_items[c] == at) {
                return true;
            }
        }
        return false;
    }

    void print() {
        for (int c = 0; c < m_items.size(); ++c) {
            LOG("%c at [%d,%d]", 'A' + c, m_items[c].x, m_items[c].y);
        }
    }
};


// E == LEFT
// A == RIGHT
// C == UP
// D == DOWN
// B == stay

enum dir_t : char {
    RIGHT = 'A',
    STAY = 'B',
    UP = 'C',
    DOWN = 'D',
    LEFT = 'E',
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

void ACTION(dir_t d) {
    fprintf(stdout, "%c\n", dirToC(d));
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

    struct bool_map_t {
        typedef uint8_t data_t;

        vector<vector<data_t>> m_data;
        data_t                 m_alloc;

        struct bm_handle_t;
        typedef shared_ptr<bm_handle_t> map_slice_t;

        bool_map_t(int w, int h) : m_data(w, vector<data_t>(h, 0)), m_alloc(0) {}

        map_slice_t takeSlice() {
            for (int c = 0; c < sizeof(data_t) * 8; ++c) {
                if (((m_alloc >> c) & 1) == 0) {
                    m_alloc |= 1 << c;
                    return map_slice_t(new bm_handle_t(this, c));
                }
            }
            ERR("Too few slices in map width [%d]", sizeof(data_t) * 8);
        }

        struct bm_handle_t {
            bool_map_t * owner;
            int idx;

            bm_handle_t(bool_map_t * own, int idx) : owner(own), idx(idx) {}

            void set(int x, int y) {
                owner->m_data[x][y] |= 1 << idx;
            }

            void clear(int x, int y) {
                owner->m_data[x][y] &= ~(1 << idx);
            }

            bool check(int x, int y) {
                return (owner->m_data[x][y] >> idx) & 1;
            }

            void set(coord_t pos) {
                set(pos.x, pos.y);
            }

            void clear(coord_t pos) {
                clear(pos.x, pos.y);
            }

            bool check(coord_t pos) {
                return check(pos.x, pos.y);
            }

            ~bm_handle_t() {
                for (int c = 0; c < owner->m_data.size(); ++c) {
                    for (int r = 0; r < owner->m_data[c].size(); ++r) {
                        clear(c, r);
                    }
                }
                owner->m_alloc &= ~(1 << idx);
            }
        };
    };



    field_t(int w, int h) : m_data(w, row_t(h, empty)), m_state(nullptr), m_visited_map(w, h), m_last_avg_dist(1e99) {
        dfs.m_init = false;
        dfs.m_visited = m_visited_map.takeSlice();
    }

    void setState(const state_t * state) {
        m_state = state;
    }

    int BFSDist(coord_t from, coord_t to) {
        static coord_t steps[4] = { { 0, 1 },{ 0, -1 },{ 1, 0 },{ -1, 0 } };

        struct dist_pair_t {
            coord_t pos;
            int len;
        };

        queue<dist_pair_t> Q;
        Q.push(dist_pair_t({ from, 0 }));

        auto visited = m_visited_map.takeSlice();

        while (!Q.empty()) {
            auto cur = Q.front(); Q.pop();
            if (cur.pos == to) {
                return cur.len;
            }

            visited->set(cur.pos);

            for (int c = 0; c < 4; ++c) {
                auto next = wrap(cur.pos + steps[c]);

                if (isInside(next) && !visited->check(next) && m_data[next.x][next.y] == free) {
                    Q.push(dist_pair_t({ next, cur.len + 1 }));
                }
            }
        }

        return -1;
    }

    int closestEnemyTo(state_t & state, coord_t pos) {
        int bestDist = 1e99;
        int idx = -1;

        for (int c = 0; c < state.size() - 1; ++c) {
            if (!state.isMoving(c)) {
                continue;
            }
            auto dist = BFSDist(pos, state[c]);
            if (dist != -1 && dist < bestDist) {
                bestDist = dist;
                idx = c;
            }
        }

        if (idx != -1) {
            return bestDist;
        }

        for (int c = 0; c < state.size() - 1; ++c) {
            if (!state.isMoving(c)) {
                continue;
            }
            auto dist = abs(pos.x - state[c].x) + abs(pos.y - state[c].y);
            if (dist < bestDist) {
                idx = c;
                bestDist = dist;
            }
        }

        return bestDist;
    }

    cell_t operator()(int x, int y) {
        if (!isInside(coord_t(x, y))) {
            ERR("Checking [%d,%d] for value and it is OUTSIDE [%d,%d]", x, y, m_data.size(), m_data[0].size());
        }

        coord_t pos(x, y);
        if (m_state) {
            for (int c = 0; c < m_state->size(); ++c) {
                if (pos == m_state->at(c)) {
                    if (m_data[x][y] == wall) {
                        ERR("[%d,%d] is '%s' and has '%c' on it", x, y, cellType(wall), 'A' + c);
                    }
                    return cell_t('A' + c);
                }
            }
        }

        return m_data[x][y];
    }

    void print() {
        stringstream data;
        for (int c = 0; c < m_data.size(); ++c) {
            for (int r = 0; r < m_data[c].size(); ++r) {
                data << (char)(*this)(c, r);
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
        default: ERR("WTF %c input to update [%d,%d]", val, x, y);
        }
    }

    void update(int x, int y, cell_t val) {
		coord_t pos = wrap(coord_t(x, y));
		if (!isInside(pos)) {
			return;
		}

        if (m_data[pos.x][pos.y] != empty && m_data[pos.x][pos.y] != val) {
            ERR("[%d,%d] set to '%s' but was '%s'", x, y, cellType(val), cellType(m_data[pos.x][pos.y]));
        }

        m_data[pos.x][pos.y] = val;
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

    dir_t dfs_step(state_t & state) {
        static coord_t steps[4] = { { 0, 1 },{ 0, -1 },{ 1, 0 },{ -1, 0 } };
        static dir_t step_map[4] = { RIGHT, LEFT, DOWN, UP };

        if (dfs.m_state.empty()) {
            ERR("dfs_step(%d, %d) STATE EMPTY", state.player().x, state.player().y);
        }

        auto & st = dfs.m_state.top();
        dfs.m_visited->set(state.player());

        //LOG("dfs_step(%d, %d) [marked as visited], state {%d, %c} size(%d)", state.player().x, state.player().y, st.idx, st.from, dfs.m_state.size());

        for (/**/; st.idx < 4; ++st.idx) {
            auto to = wrap(state.player() + steps[st.idx]);
            if (!isInside(to)) {
                continue;
            }

            //LOG("disp [%d, %d] -> [%d, %d] = %s", steps[st.idx].x, steps[st.idx].y, to.x, to.y, cellType(m_data[to.x][to.y]));

            if (!state.isEnemy(to.x, to.y) && m_data[to.x][to.y] == free && !dfs.m_visited->check(to)) {

                //LOG("found empty field %d, pushing state", st.idx);

                // push new state on stack with iter 0
                // and how we got there map[idx]
                // return where we go
                dfs.m_state.push({ 0, step_map[st.idx] });
                return step_map[st.idx];
            }
        }

        // we are here so finished this iter
        // go back 1 lvl, and pop state
        //LOG("iter ended, poping state back %c", st.from);
        auto to = invert(st.from);
        dfs.m_state.pop();

        if (to == INVALID) {
            to = STAY;
            dfs.m_state.push({ 0, INVALID });
            dfs.m_visited.reset();
            dfs.m_visited = m_visited_map.takeSlice();
        }

        return to;
    }

    bool isInside(coord_t pos) {
        return pos.x >= 0 && pos.x < m_data.size() && pos.y >= 0 && pos.y <= m_data[0].size();
    }

	// makes the pos wrap around edges
	coord_t W(coord_t pos) {
		const int width = m_data.size();
		const int height = m_data[0].size();

		pos.x = pos.x % width;
		pos.y = pos.y % height;

		pos.x += pos.x < 0 ? width : 0;
		pos.y += pos.y < 0 ? height : 0;

		return pos;
	}

	coord_t wrap(coord_t pos) {
		return W(pos);
	}

    dir_t best_step(state_t &state) {
        static coord_t steps[5] = { { 0, 1 },{ 0, -1 },{ 1, 0 },{ -1, 0 },{ 0, 0 } };
        static dir_t step_map[5] = { RIGHT, LEFT, DOWN, UP, STAY };

        const auto & pl = state.player();

        float avgDist = 0.f;
        int closest = 1e99;
        int cnt = 0;
        for (int c = 0; c < state.size() - 1; ++c) {
            if (state.isMoving(c)) {
                auto tDist = BFSDist(pl, state[c]);
                if (tDist == -1) {
                    tDist = abs(pl.x - state[c].x) + abs(pl.y - state[c].y);
                }
                closest = min(closest, tDist);
                avgDist += tDist;
                ++cnt;
            }
        }

        avgDist /= float(cnt);

        const bool doDFS = closest > 5;
        //LOG("AVG: %f, last AVG %f, moving visible enemies %d [%d] -> %s!", avgDist, m_last_avg_dist, closest, cnt, doDFS ? "EXPLORING" : "RUNNING");
        LOG(doDFS ? "EXPLORING" : "RUNNING");

        m_last_avg_dist = avgDist;

        if (doDFS) {
            return dfs_step(state);
        }

        float bestDist = 0;

        typedef vector<coord_t> path_t;
        auto bfs_visited = m_visited_map.takeSlice();

        auto appendPath = [](path_t p, coord_t c) {
            p.push_back(c);
            return p;
        };

        //LOG("Starting BFS to find furthest point");
        path_t bestPos;
        queue<path_t> q;
        q.push(path_t(1, pl));

        while (!q.empty()) {
            auto cur = q.front(); q.pop();

            auto dist = closestEnemyTo(state, cur.back());;
            if (dist > bestDist) {
                bestDist = dist;
                bestPos = cur;
            }

            for (int c = 0; c < 4; ++c) {
                auto nPos = wrap(steps[c] + cur.back());

                if (isInside(nPos) && m_data[nPos.x][nPos.y] == free && !state.isEnemy(nPos.x, nPos.y) && !bfs_visited->check(nPos)) {
                    bfs_visited->set(nPos);
                    q.push(appendPath(cur, nPos));
                }
            }
        }

        //LOG("Best place to go [%d,%d] -> [%d,%d], path len: %d", pl.x, pl.y, bestPos.back().x, bestPos.back().y, bestPos.size());
        if (bestPos.size() > 1) {
            for (int c = 0; c < 4; ++c) {
                auto check = wrap(steps[c] + pl);
                if (bestPos[1] == check) {
                    return step_map[c];
                }
            }
        }

        //LOG("WTF cant find what is paths second step's direction");
        return STAY;
    }

    row_t & operator[](int c) {
        return m_data[c];
    }

    struct {
        bool m_init;
        stack<dfs_state_t> m_state;
        bool_map_t::map_slice_t m_visited;
    } dfs;

    float          m_last_avg_dist;
    vector<row_t>  m_data;
    const state_t *m_state;
    bool_map_t     m_visited_map;
};

int main()
{
    int width, height, figCount;

    cin >> width; cin.ignore();
    cin >> height; cin.ignore();
    cin >> figCount; cin.ignore();

	LOG("W:%d H:%d  PL:%d", width, height, figCount);

    field_t F(width, height);
    F.dfs_init();

    movemap_t movingPlayers(0);
    state_t prev_state(movingPlayers);
    bool startTrack = false;

    // game loop
    while (1) {
        string f1, f2, f3, f4;
        cin >> f1; cin.ignore(); cin >> f2; cin.ignore();
        cin >> f3; cin.ignore(); cin >> f4; cin.ignore();

        char U = f1[0], R = f2[0], D = f3[0], L = f4[0];
        swap(U, L);
        swap(D, R);

        state_t moves(movingPlayers);

        int x, y;
        for (int c = 0; c < figCount; c++) {
            cin >> x >> y; cin.ignore();
            swap(x, y);

            moves.add(coord_t(x, y));
            F.update(x, y, field_t::cell_t::free);

            //if (startTrack) {
            //    LOG("%c [%d, %d] -> [%d,%d]", 'A' + c, prev_state[c].x, prev_state[c].y, a, b);
            //}
        }

        if (startTrack) {
            for (int c = 0; c < moves.size(); ++c) {
                if (moves[c] != prev_state[c]) {
                    movingPlayers[c] = true;
                }
            }
        }
        F.setState(&moves);
        F.print();

        F.update(x - 1, y, L);
        F.update(x + 1, y, R);

        F.update(x, y + 1, D);
        F.update(x, y - 1, U);

        auto toWhere = F.best_step(moves);
        LOG("%s", dirToStr(toWhere));

        ACTION(toWhere);
        startTrack = true;
        prev_state = moves;


        F.setState(nullptr);
    }
}
