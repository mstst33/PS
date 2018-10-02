#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

#define GRID 4
#define MAX_WORD_LEN 8
#define ALL_DIRECTIONS 8

char dr[ALL_DIRECTIONS] = {-1, -1, -1, 0, 0, 1, 1, 1};
char dc[ALL_DIRECTIONS] = {-1, 0, 1, -1, 1, -1, 0, 1};
char wScore[MAX_WORD_LEN] = {0, 0, 1, 1, 2, 3, 5, 11};

class Boggle_Board
{
public:
    char board[GRID][GRID];
    bool visit[GRID][GRID];
    int max_score;
    string longest_word;
    unordered_set<string> words_count;

    Boggle_Board() { init_board(); }

    void init_board()
    {
        for(int i = 0; i < GRID; ++i)
        {
            for(int j = 0; j < GRID; ++j)
            {
                this->board[i][j] = 0;
                this->visit[i][j] = false;
            }
        }

        this->max_score = 0;
        this->longest_word = "";
        words_count.clear();
    }

    void sumScore(const int wlen) { if(wlen <= MAX_WORD_LEN) this->max_score += wScore[wlen - 1]; }

    bool foundWord(string& w)
    {
        // 단어를 찾으면 우선 그 단어가 Set에 있는지 판별한다
        if(words_count.find(w) == words_count.end())
        {
            // 얻을 수 있는 최고 점수, 가장 긴 단어, 찾은 단어 개수를 갱신한다
            sumScore(w.length());
            words_count.emplace(w);
            if(w.length() > longest_word.length()) longest_word = w;
            else if(w.length() == longest_word.length())
            {
                if(longest_word > w) longest_word = w;
            }
        }
        else return true;

        return false;
    }

    void printResult()
    {
        printf("%d %s %d\n", this->max_score, this->longest_word.c_str(), (int) this->words_count.size());
    }
};

class Node
{
public:
    char c;
    char level;
    int stars;
    int foundStars;
    Node* parent;
    unordered_map<char, Node> children; // Strict Rule 에서는 Hash 함수를 만들어야 한다

    Node() : c(0), level(0), stars(0), foundStars(0), parent(nullptr) {}
    Node(const char ch, const char lv, Node* p) : c(ch), level(lv), stars(0), foundStars(0), parent(p) {}
};

class Trie
{
public:
    Node root;
    char endT;

    Trie() : root(0, 0, nullptr), endT('*') {}

    void registerWords(const char w[])
    {
        Node* node = &this->root;

        for(int i = 0; w[i] != '\0'; ++i)
        {
            // 현재 Tree Level에 해당 character가 등록되어 있지 않으면 등록하고 다음 Level로 넘어간다
            if(node->children.find(w[i]) == node->children.end()) node->children.emplace(w[i], Node(w[i], (node->level + 1), node));
            node = &node->children[w[i]];
        }

        // Trie에 단어 등록을 종료하면 끝에 '*' 붙이고 '*' 개수를 증가시킨다
        if(node->children.find(endT) == node->children.end())
        {
            node->children.emplace(endT, Node(endT, (node->level + 1), node));
            increaseStar(node);
        }
    }

    void increaseStar(Node* node)
    {
        Node* tmp = node;
        
        // 현재 노드부터 root 노드까지 거슬러 올라가며 '*' 개수를 증가시킨다
        while(tmp->parent != nullptr)
        {
            ++tmp->stars;
            tmp = tmp->parent;
        }
    }

    void increaseFoundStars(Node* node)
    {
        Node* tmp = node;
        
        // 현재 노드부터 root 노드까지 거슬러 올라가며 찾은 '*' 개수를 증가시킨다
        while(tmp->parent != nullptr)
        {
            ++tmp->foundStars;
            tmp = tmp->parent;
        }
    }

    void clearFoundStars(Node* node)
    {
        if(node == nullptr) return;
        else node->foundStars = 0;

        for(auto it = node->children.begin(); it != node->children.end(); ++it) clearFoundStars(&it->second);
    }

    void clearFoundStarsWrapper() { clearFoundStars(&this->root); }

    void searchWords(Boggle_Board& b, Node* n, string w, const int row, const int col)
    {
        // Character가 Trie 자식 중에 없을 경우 바로 반환한다
        int ch = b.board[row][col];
        if(n->children.find(ch) == n->children.end()) return;

        // 이미 찾은 단어면 더 탐색할 필요 없다
        Node* child = &n->children[ch];
        if(child->stars == child->foundStars) return;

        b.visit[row][col] = true;
        w.push_back(ch);

        // 현재 Trie의 자식이 '*' 일 경우 단어를 찾았다 !
        if(child->children.find(endT) != child->children.end())
        {
            // 새로운 단어라면 등록하고 찾은 별들을 등록한다
            bool exist = b.foundWord(w);
            if(!exist) increaseFoundStars(child);

            // 더이상 찾을 단어가 없으면 더 탐색할 필요 없다
            if(child->stars == child->foundStars)
            {
                b.visit[row][col] = false;
                return;
            }
        }
        
        // 최대 단어 길이 미만이면 해당 Character 주변 전방위를 방문한다
        if(child->level < MAX_WORD_LEN)
        {
            for(int i = 0; i < ALL_DIRECTIONS; ++i)
            {
                int r = row + dr[i];
                int c = col + dc[i];

                // Board 배열 범위를 벗어나는 위치와 이미 방문한 곳은 무시한다
                // Trie Node의 다음 문자들이 포함되어 있지 않으면 또한 무시한다
                if((r < 0) || (c < 0) || (r >= GRID) || (c >= GRID) || b.visit[r][c]) continue;
                else if(child->children.find(b.board[r][c]) == child->children.end()) continue;
                else searchWords(b, child, w, r, c);
            }
        }

        b.visit[row][col] = false;
    }
    
    void searchWordsWrapper(Boggle_Board& b)
    {
        for(int i = 0; i < GRID; ++i)
        {
            for(int j = 0; j < GRID; ++j) searchWords(b, &this->root, "", i, j);
        }
    }

    void print_trie(Node* node)
    {
        if(node == nullptr) return;

        printf("lv[%d] : %c (%d / %d)\n", node->level, node->c, node->foundStars, node->stars);
        if(node->c == endT) printf("\n");

        for(auto it = node->children.begin(); it != node->children.end(); ++it) print_trie(&it->second);
    }

    void print() { print_trie(&this->root); }
};

class Boggle
{
public:
    Trie trie;
    Boggle_Board b;

    Boggle() {}
};

void findWordsInBoggle(Boggle& boggle)
{
    // Trie를 참조하여 단어를 찾고 결과를 보여준다
    boggle.trie.searchWordsWrapper(boggle.b);
    boggle.trie.clearFoundStarsWrapper();
    boggle.b.printResult();
    boggle.b.init_board();
}

int main()
{
    Boggle boggle;
    char tmp[MAX_WORD_LEN * 2] = {0};
    int input = 0;

    scanf("%d", &input);
    for(int i = 0; i < input; ++i)
    {
        scanf("%s", tmp);
        boggle.trie.registerWords(tmp);
    }

    scanf("%d", &input);
    for(int k = 0; k < input; ++k)
    {
        for(char i = 0; i < GRID; ++i)
        {
            scanf("%s", tmp);
            for(char j = 0; j < GRID; ++j) boggle.b.board[i][j] = tmp[j];
        }

        findWordsInBoggle(boggle);
    }

    return 0;
}
