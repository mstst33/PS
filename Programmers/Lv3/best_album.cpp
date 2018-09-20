#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

class Song
{
public:
    int id;
    int play;

    Song() : id(0), play(0) {};
    Song(const int _id, const int _play) : id(_id), play(_play) {};
};

class BestSongs
{
public:
    vector<Song> s;
    int plays;
    
    BestSongs() : plays(0) {};
    BestSongs(const int _id, const int _play)
    {
        s.emplace_back(_id, _play);
        plays = _play;
    }
};

vector<int> solution(vector<string> genres, vector<int> plays) {
    vector<int> answer;
    vector<BestSongs> v;
    unordered_map<string, BestSongs> um;
    
    // 해시맵에 장르별 곡 정보를 넣는다
    for(int i = 0; i < genres.size(); ++i)
    {
        if(um.find(genres[i]) == um.end()) um.emplace(genres[i], BestSongs(i, plays[i]));
        else
        {
            um[genres[i]].s.emplace_back(i, plays[i]);
            um[genres[i]].plays += plays[i];
        }
    }
    
    // 장르별 곡 정보를 장르별 곡 총 재생수로 정렬한다
    for(auto m : um) v.emplace_back(m.second);
    sort(v.begin(), v.end(), [](const BestSongs& a, const BestSongs& b) { return a.plays > b.plays; });

    for(auto bs : v)
    {
        // 한 장르 내에 각각의 곡 재생 수가 높은 것으로 정렬하고 그 중에 최대 2개를 뽑는다
        sort(bs.s.begin(), bs.s.end(), [](const Song& a, const Song& b) { 
            if(a.play == b.play) return a.id < b.id;
            else return a.play > b.play; });

        answer.push_back(bs.s[0].id);
        if(bs.s.size() > 1) answer.push_back(bs.s[1].id);
    }
    
    return answer;
}
