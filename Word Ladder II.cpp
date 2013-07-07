// Word Ladder II.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <vector>
#include <string>
#include <queue>
#include <climits>
#include <unordered_set>
#include <unordered_map>
#include <functional>

using namespace std;

// typedef pair<int, int>  node_info;  // first is the distance, second is the prev node id for current node;
//template<class T, class container, class cmp>
//class priority_queue
//{
//public:
//	typedef typename container::value_type value_type;
//	typedef typename container::size_type size_type;
//	typedef typename container::const_reference const_reference;
//
//    priority_queue() : c(), comp() {}
//
//    bool empty() const
//    {
//        return (c.empty());
//    }
//
//    size_type size() const
//    {
//        return (c.size());
//    }
//
//    const_reference top() const
//    {
//        return (c.front());
//    }
//
//    void push(const value_type& _Val)
//    {
//        c.push_back(_Val);
//        push_heap(c.begin(), c.end(), comp);
//    }
//
//    void pop()
//    {
//        pop_heap(c.begin(), c.end(), comp);
//        c.pop_back();
//    }
//
//protected:
//    container c;	// the underlying container
//    cmp comp;	// the comparator functor
//};

class Solution {
private:
    typedef unordered_set<int> adjcent_list;

    struct node_info
    {
        node_info(size_t i, size_t dist = UINT_MAX) : id(i), distance(dist), paths() {}

        void set_distance(size_t dist) { distance = dist; }
        size_t get_distance() const { return distance; }

        void                  add_path(size_t id) { paths.push_back(id); }
        const vector<size_t>& get_path() const { return paths; }

        bool operator >(const node_info& rhs) const
        {
            return this->distance > rhs.distance;
        }

        size_t id;
        size_t distance;
        vector<size_t> paths;
    };

    struct node_info_greater
    {
        bool operator ()(node_info*& left, node_info*& right) const
        {
            return *left > *right;
        }
    };

    vector<string> vertexes;                    // 顶点id到顶点名称的映射
    unordered_map<string, size_t> name2id;      // 顶点名称到id的映射
    vector<adjcent_list> adjcent_lists;          // 顶点id到邻接表的映射
    vector<node_info>    vertex_info;

public:
    void erase()
    {
        vertexes.erase(vertexes.begin(), vertexes.end());
        name2id.erase(name2id.begin(), name2id.end());
        adjcent_lists.erase(adjcent_lists.begin(), adjcent_lists.end());
        vertex_info.erase(vertex_info.begin(), vertex_info.end());
    }

    void build(const string& start, const string& end, unordered_set<string>& dict)
    {
        if (dict.find(start) != dict.end())
        {
            dict.erase(start);
        }

        if (dict.find(end) == dict.end())
        {
            dict.insert(end);
        }

        adjcent_lists.resize(dict.size() + 1);
        vertex_info.reserve(dict.size() + 1);
        vertexes.reserve(dict.size() + 1);

        vertexes.push_back(start);

        vertexes.insert(vertexes.end(), dict.begin(), dict.end());
        for (size_t i = 0; i < vertexes.size(); ++i)
        {
            name2id[vertexes[i]] = i;
            vertex_info.push_back(node_info(i));
        }
        vertex_info[0].set_distance(1);

        size_t word_size = start.size();
        for (size_t i = 0; i < vertexes.size(); ++i)
        {
            string tmp = vertexes[i];
            for (size_t j = 0; j < word_size; ++j)
            {
                char backup = tmp[j];
                for (char ch = 'a'; ch <= 'z'; ++ch)
                {
                    if (backup != ch)
                    {
                        tmp[j] = ch;
                        if (dict.find(tmp) != dict.end())
                        {
                            adjcent_lists[i].insert(name2id[tmp]);
                        }
                    }
                }
                tmp[j] = backup;
            }
        }
    }

    void dumpResult(const node_info* ni, vector<string>& tmp, vector<vector<string>>& result)
    {
        const vector<size_t>& path = ni->get_path();
        if (path.size() == 0)
        {
            result.push_back(vector<string>(tmp.rbegin(), tmp.rend()));
            return;
        }

        for (size_t i = 0; i < path.size(); ++i)
        {
            tmp.push_back(vertexes[path[i]]);
            dumpResult(&vertex_info[path[i]], tmp, result);
            tmp.pop_back();
        }
    }

    void bfs(const string& end, vector<vector<string>>& result)
    {
        vector<char> used(vertexes.size());

        priority_queue<node_info*, vector<node_info*>, node_info_greater> processingQueue;
        processingQueue.push(&vertex_info[0]);

        while (!processingQueue.empty())
        {
            node_info* ni = processingQueue.top();
            processingQueue.pop();

            if ('\0' != used[ni->id])
            {
                continue;
            }

            if (vertexes[ni->id] == end)
            {
                vector<string> tmp;
                tmp.push_back(vertexes[ni->id]);
                dumpResult(ni, tmp, result);
                tmp.pop_back();
                return;
            }

            used[ni->id] = char(1);
            adjcent_list& adjcent_list = adjcent_lists[ni->id];
            size_t ni_dist = ni->get_distance();

            for (auto i = adjcent_list.begin(); i != adjcent_list.end(); ++i)
            {
                node_info* adj_ni = &vertex_info[*i];
                size_t adj_ni_dist = adj_ni->get_distance();

                if (adj_ni_dist == UINT_MAX)
                {
                    adj_ni->set_distance(ni_dist + 1);
                    adj_ni->add_path(ni->id);

                    processingQueue.push(adj_ni);
                }
                else if (ni_dist + 1 == adj_ni_dist)
                {
                    adj_ni->add_path(ni->id);
                }
            }
        }
    }


    vector<vector<string>> findLadders(const string& start, const string& end, unordered_set<string> &dict) {
        // Start typing your C/C++ solution below
        // DO NOT write int main() function

        vector<vector<string>> result;
        erase();        

        build(start, end, dict);
        bfs(end, result);

        return result;
    }
};

void print(const vector<vector<string>>& result)
{
    printf("[");
    for (size_t i = 0; i < result.size(); ++i)
    {
        printf(i ? " [" : "[");
        for (size_t j = 0; j < result[i].size(); ++j)
        {
            printf(j ? "," : "");
            printf(result[i][j].c_str());
        }
        printf("]");
    }
    printf("]\n");
}

int _tmain(int argc, _TCHAR* argv[])
{
    Solution s;
    unordered_set<string> dict;
    /*
    "a", "c", ["a","b","c"]	[["c","c"],["c","c"],["c","c"]]	[["a","c"]]	

    "hot", "dog", ["hot","dog"]	[]	[]	

    "hot", "dog", ["hot","dog","dot"]	[["dog","dog"]]	[["hot","dot","dog"]]	

    "hot", "dot", ["hot","dot","dog"]	[["dot","dot"]]	[["hot","dot"]]	

    "hot", "dog", ["hot","cog","dog","tot","hog","hop","pot","dot"]	[["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"],["dog","dog"]]	[["hot","dot","dog"],["hot","hog","dog"]]	

    "hot", "dog", ["hot","dog","cog","pot","dot"]	[["dog","dog"],["dog","dog"],["dog","dog"]]	[["hot","dot","dog"]]	

    "hit", "cog", ["hot","cog","dot","dog","hit","lot","log"]	[["cog","cog"],["cog","cog"],["cog","cog"],["cog","cog"],["cog","cog"],["cog","cog"],["cog","cog"],["cog","cog"]]	[["hit","hot","dot","dog","cog"],["hit","hot","lot","log","cog"]]	

    "hit", "cog", ["hot","hit","cog","dot","dog"]	[["cog","cog"]]	[["hit","hot","dot","dog","cog"]]	

    "red", "tax", ["ted","tex","red","tax","tad","den","rex","pee"]	[["tax","tax"],["tax","tax"],["tax","tax"],["tax","tax"],["tax","tax"],["tax","tax"],["tax","tax"]]	[["red","ted","tad","tax"],["red","ted","tex","tax"],["red","rex","tex","tax"]]	

    "lost", "cost", ["most","fist","lost","cost","fish"]	[["cost","cost"],["cost","cost"],["cost","cost"]]	[["lost","cost"]]	

    "lost", "miss", ["most","mist","miss","lost","fist","fish"]	[["miss","miss"]]	[["lost","most","mist","miss"]]	

    "leet", "code", ["lest","leet","lose","code","lode","robe","lost"]	[["code","code"]]	[["leet","lest","lost","lose","lode","code"]]	

    "talk", "tail", ["talk","tons","fall","tail","gale","hall","negs"]	[]	[]	

    "catch", "choir", ["tours","awake","goats","crape","boron","payee","waken","cares","times","piled","maces","cuter","spied","spare","mouse","minty","theed","sprat","veins","brian","crown","years","drone","froth","foggy","laura","sears","shunt","gaunt","hovel","staff","child","arson","haber","knows","rubes","czars","pawed","whine","treed","bauer","jodie","timed","flits","robby","gooks","yawls","purse","veeps","tints","taped","raced","shaft","modes","dykes","slims","parts","emile","frail","salem","jives","heave","bayer","leech","clipt","yanks","wilds","hikes","cilia","spiel","mulls","fetal","homed","drown","suite","defer","oaken","flail","zippy","burke","slued","mowed","manes","verse","serra","bruno","spoke","mikes","hafts","breed","sully","croce","boers","chair","thong","pulse","pasta","perot","fices","shies","nadir","every","diets","roads","cones","tuned","globs","graft","stall","royal","fixes","north","pikes","slack","vests","quart","crawl","tangs","calks","mayor","filmy","barns","block","hoods","storm","cedes","emote","tacks","skirt","horsy","mawed","moray","wring","munch","hewed","hooke","batch","drawl","berth","sport","welch","jeans","river","tabby","amens","stump","cause","maced","hiker","spays","dusty","trail","acorn","zooms","puked","clown","sands","kelli","stein","rawer","water","dolts","momma","fluky","scots","pupil","halls","toady","pored","latch","shags","union","tamps","stead","ryder","knoll","cacao","damns","charm","frank","draws","gowns","risen","saxes","lucks","avert","yolks","clime","wedge","ruses","famed","sabik","gravy","anion","veils","pyres","raspy","lofts","tress","showy","percy","rices","taker","roger","yeats","baked","ayers","fazes","curly","shawn","clare","paine","ranks","hocks","berta","plays","parks","tacos","onion","skeet","acton","lamer","teals","reset","steal","maven","sored","fecal","harsh","totem","swoop","rough","jokes","mires","weird","quits","damps","touts","fling","sarah","peeps","waxen","traps","mange","swell","swoon","catch","mower","bonny","finds","yards","pleas","filed","smelt","drams","vivid","smirk","whigs","loafs","opens","meter","hakes","berms","whack","donny","faint","peace","libby","yates","purer","wants","brace","razed","emend","bards","karyn","japed","fated","missy","punks","humps","steak","depth","brunt","hauls","craws","blast","broom","tones","ousts","wires","peeks","ruffs","crack","monte","worth","spans","tonic","runny","erick","singe","maine","casts","jello","realm","haste","utter","bleat","kasey","palms","solos","hoagy","sweep","loner","naves","rhine","acmes","cadet","dices","saris","mauro","fifty","prows","karat","dowel","frays","shorn","sails","ticks","train","stars","stork","halts","basal","glops","beset","rifer","layla","lathe","daffy","jinns","snide","groin","kelly","zincs","fryer","quilt","drama","shook","swami","hulls","swazi","danes","axons","those","lorry","plath","prime","faces","crock","shake","borer","droop","derek","shirk","styed","frown","jells","slows","lifts","jeers","helms","turds","dross","tired","rimes","beats","dingo","crews","bides","loins","furry","shana","wises","logos","aural","light","pings","belch","campy","swish","sangs","nerds","boggy","skies","weals","snags","joyed","mamet","miser","leaks","ramos","tract","rends","marks","taunt","sissy","lipid","beach","coves","fates","grate","gloss","heros","sniff","verve","tells","bulge","grids","skein","clout","leaps","males","surfs","slips","grave","boats","tamed","muled","meier","lower","leafy","stool","reich","rider","iring","ginny","flaks","chirp","tonga","chest","ollie","foxes","links","alton","darth","drier","sated","rails","gyros","green","jenna","cures","veals","sense","sworn","roses","aides","loses","rival","david","worms","stand","track","dales","noyes","fraud","shock","sward","pluto","biked","roans","whiny","halve","bunts","spilt","gamey","deeds","oozed","ruder","drano","sages","fewer","maize","aimed","bails","poole","hunts","shari","champ","shuns","jonah","faced","spook","harry","lagos","peale","nacho","saint","power","chaff","shard","cocky","irate","tummy","withe","forks","bates","stuns","turfs","coped","coups","vince","helps","facet","fezes","outer","cheek","tried","sumps","fakes","fonds","yearn","brays","flute","fetid","beyer","mamma","topic","bouts","trend","gorey","hills","swaps","sexes","cindy","ruler","kited","gaits","shank","cloys","stuck","purus","musks","gouge","brake","biker","layer","lilly","bills","seven","flyer","phase","wowed","beaus","cokes","chimp","spats","mooch","dried","hulks","shift","galen","wiped","clops","decal","nopes","huffs","lades","sunny","foyer","gusty","wormy","chips","focus","pails","solid","ariel","gamed","diver","vying","sacks","spout","sides","agave","bandy","scant","coils","marci","marne","swank","basil","shine","nines","clues","fuzes","jacks","robin","pyxes","later","silas","napes","homes","baled","dames","abuse","piker","coots","tiles","bents","pearl","booty","hells","dusky","glare","scale","pales","leary","scull","bimbo","mossy","apron","manet","opted","kusch","shiny","argos","hoped","towns","bilbo","slums","skull","shale","mandy","scows","speed","eager","lards","crows","merry","anted","faxed","leave","fargo","creek","comas","golda","baize","easts","plied","rared","ashed","doted","bunin","bonds","yarns","latin","right","worst","sixes","gabby","begun","upend","giant","tykes","creak","manor","bosom","riced","dimly","holes","stunt","parsi","peers","snell","mates","jules","rusty","myles","yules","sades","hobbs","booth","clean","liven","gamer","howdy","stray","riser","wisps","lubes","tubes","rodeo","bigot","tromp","pimps","reeve","pumps","dined","still","terms","hines","purrs","roast","dooms","lints","sells","swims","happy","spank","inset","meany","bobby","works","place","brook","haded","chide","slime","clair","zeros","britt","screw","ducal","wroth","edger","basie","benin","unset","shade","doers","plank","betsy","bryce","cross","roped","weans","bliss","moist","corps","clara","notch","sheep","weepy","bract","diced","carla","locks","sawed","covey","jocks","large","pasts","bumps","stile","stole","slung","mooed","souls","dupes","fairs","lined","tunis","spelt","joked","wacky","moira","strut","soled","pints","axing","drank","weary","coifs","wills","gibes","ceded","gerry","tires","crazy","tying","sites","trust","dover","bolds","tools","latex","capet","lanky","grins","brood","hitch","perts","dozes","keels","vault","laius","chung","deres","glove","corms","wafer","coons","ponce","tumid","spinx","verge","soggy","fleas","middy","saiph","payer","nukes","click","limps","oared","white","chart","nasty","perth","paddy","elisa","owing","gifts","manna","ofter","paley","fores","sough","wanda","doggy","antic","ester","swath","spoon","lamas","meuse","hotel","weedy","quads","paled","blond","flume","pried","rates","petal","rover","marsh","grief","downy","pools","buffs","dunne","cruel","finny","cosby","patch","polly","jerks","linen","cider","visas","beard","mewed","spill","trots","tares","pured","prior","build","throe","wends","baned","mario","misty","golds","lacey","slags","jived","finis","inner","money","skews","sunks","fined","bauds","lapel","class","berne","rabin","roils","hyped","styes","evans","towed","hawed","allow","modal","ports","erich","rills","humid","hooks","sedge","shirt","nippy","fundy","runes","smile","dolly","tisha","byers","goths","sousa","mimed","welts","hoots","shown","winds","drays","slams","susan","frogs","peach","goody","boned","chewy","eliza","peary","pyxed","tiled","homer","tokes","verdi","mabel","rolls","laden","loxed","phony","woods","brine","rooks","moods","hired","sises","close","slops","tined","creel","hindu","gongs","wanes","drips","belly","leger","demon","sills","chevy","brads","drawn","donna","glean","dying","sassy","gives","hazes","cores","kayla","hurst","wheat","wiled","vibes","kerry","spiny","wears","rants","sizer","asses","duked","spews","aired","merak","lousy","spurt","reeds","dared","paged","prong","deere","clogs","brier","becks","taken","boxes","wanna","corny","races","spuds","jowls","mucks","milch","weest","slick","nouns","alley","bight","paper","lamps","trace","types","sloop","devon","pedal","glint","gawky","eaves","herbs","felts","fills","naval","icing","eking","lauds","stats","kills","vends","capes","chary","belle","moats","fonts","teems","wards","bated","fleet","renal","sleds","gases","loony","paced","holst","seeds","curie","joist","swill","seats","lynda","tasks","colts","shops","toted","nuder","sachs","warts","pupal","scalp","heirs","wilma","pansy","berra","keeps","menus","grams","loots","heels","caste","hypes","start","snout","nixes","nests","grand","tines","vista","copes","ellis","narks","feint","lajos","brady","barry","trips","forth","sales","bests","hears","twain","plaid","hated","kraft","fared","cubit","jayne","heats","chums","pangs","glows","lopez","vesta","garbo","ethel","blood","roams","mealy","clunk","rowed","hacks","davit","plane","fuses","clung","fitch","serer","wives","lully","clans","kinks","spots","nooks","plate","knits","greet","loads","manic","scone","darin","pills","earth","gored","socks","fauna","ditch","wakes","savvy","quiet","nulls","sizes","diana","mayan","velds","dines","punch","bales","sykes","spiky","hover","teats","lusts","ricky","think","culls","bribe","pairs","month","cored","packs","lobes","older","hefts","faxes","cased","swain","bawdy","troop","woven","stomp","swags","beads","check","shill","broad","souse","pouch","lived","iambs","teaks","clams","outed","maxed","plain","sappy","cabal","penal","shame","budge","offed","kooks","gybed","basin","thoth","arced","hypos","flows","fetch","needs","davis","jared","bongo","added","sames","randy","tunes","jamar","smash","blows","grows","palmy","miler","chins","viola","tower","cream","molls","cello","sucks","fears","stone","leans","zions","nutty","tasha","ratty","tenet","raven","coast","roods","mixes","kmart","looms","scram","chapt","lites","trent","baron","rasps","ringo","fazed","thank","masts","trawl","softy","toils","romes","norma","teens","blank","chili","anise","truss","cheat","tithe","lawns","reese","slash","prate","comet","runts","shall","hosed","harpy","dikes","knock","strip","boded","tough","spend","coats","husky","tyree","menes","liver","coins","axles","macho","jawed","weeps","goods","pryor","carts","dumps","posts","donor","daunt","limbo","books","bowls","welds","leper","benny","couch","spell","burst","elvin","limbs","regal","loyal","gaily","blade","wheal","zests","seine","hubby","sheen","tapes","slugs","bench","lungs","pipes","bride","selma","berry","burns","skins","bowen","gills","conan","yucky","gauls","voled","crust","jerky","moans","plump","sided","disks","gleam","larry","billy","aloud","match","udder","rises","wryer","deter","cling","brisk","lever","chaps","tansy","gland","rocky","lists","joins","tubed","react","farsi","dopes","chats","olsen","stern","gully","youth","wiles","slink","cooke","arise","bores","maims","danny","rives","rusts","plots","loxes","troys","cleat","waxes","booze","haven","dilly","shaun","gasps","rains","panda","quips","kings","frets","backs","arabs","rhino","beets","fiber","duffy","parry","sever","hunks","cheap","beeps","fifes","deers","purls","hello","wolfs","stays","lands","hawks","feels","swiss","tyros","nerve","stirs","mixed","tombs","saves","cater","studs","dorky","cinch","spice","shady","elder","plato","hairs","newts","slump","boots","lives","walls","spunk","bucks","mined","parch","disco","newel","doris","glues","brawn","abner","piked","laxes","bulky","moran","cozen","tinge","dowry","snare","sagan","harms","burch","plows","sunni","fades","coach","girls","typed","slush","saver","bulls","grass","holed","coven","dukes","ocher","texan","cakes","gilts","jenny","salon","divas","maris","costs","sulla","lends","gushy","pears","teddy","huffy","sited","rhone","euler","solve","grace","snarl","taste","sally","allay","suers","bogey","pooch","songs","cameo","molts","snipe","cargo","forge","reins","hoses","crams","fines","tings","wings","spoor","twice","waxed","mixer","bongs","stung","gages","yelps","croci","corks","bolls","madge","honer","riled","camus","trick","bowed","overt","steed","ripes","stave","crick","great","scott","scald","point","finch","bulks","chant","kiddo","cover","drunk","sered","dicky","wider","saith","mutts","blind","lyres","sized","darby","rebel","zones","title","yawns","laths","sting","taine","paris","route","livia","roots","belay","daubs","spoof","camel","colds","foist","saned","doles","slays","woody","leads","stout","caper","erika","lance","earns","vines","mercy","antis","terri","messy","lords","shims","serfs","jinni","caged","threw","rainy","bumpy","arias","wails","romeo","gorge","dolls","risks","skyed","fumes","payed","mites","choir","piles","scene","flake","solon","brahe","bikes","dawes","goofs","payne","cried","slavs","hives","snack","cribs","aways","fired","swarm","pumas","paved","smith","gooey","liefs","safer","banes","slake","doled","dummy","gazed","heaps","loped","scoff","crash","balmy","hexed","lunch","guide","loges","alien","rated","stabs","whets","blest","poops","cowls","canes","story","cunts","tusks","pinto","scats","flier","chose","brute","laked","swabs","preps","loose","merle","farms","gapes","lindy","share","floes","scary","bungs","smart","craps","curbs","vices","tally","beret","lenny","waked","brats","carpi","night","junes","signs","karla","dowdy","devil","toned","araby","trait","puffy","dimer","honor","moose","synch","murks","doric","muted","quite","sedan","snort","rumps","teary","heard","slice","alter","barer","whole","steep","catty","bidet","bayes","suits","dunes","jades","colin","ferry","blown","bryon","sways","bayed","fairy","bevel","pined","stoop","smear","mitty","sanes","riggs","order","palsy","reels","talon","cools","retch","olive","dotty","nanny","surat","gross","rafts","broth","mewls","craze","nerdy","barfs","johns","brims","surer","carve","beers","baker","deena","shows","fumed","horde","kicky","wrapt","waits","shane","buffy","lurks","treat","savor","wiper","bided","funny","dairy","wispy","flees","midge","hooch","sired","brett","putty","caked","witch","rearm","stubs","putts","chase","jesus","posed","dates","dosed","yawed","wombs","idles","hmong","sofas","capek","goner","musts","tangy","cheer","sinks","fatal","rubin","wrest","crank","bared","zilch","bunny","islet","spies","spent","filth","docks","notes","gripe","flair","quire","snuck","foray","cooks","godly","dorms","silos","camps","mumps","spins","cites","sulky","stink","strap","fists","tends","adobe","vivas","sulks","hasps","poser","bethe","sudan","faust","bused","plume","yoked","silly","wades","relay","brent","cower","sasha","staci","haves","dumbs","based","loser","genes","grape","lilia","acted","steel","award","mares","crabs","rocks","lines","margo","blahs","honda","rides","spine","taxed","salty","eater","bland","sweat","sores","ovens","stash","token","drink","swans","heine","gents","reads","piers","yowls","risky","tided","blips","myths","cline","tiers","racer","limed","poled","sluts","chump","greek","wines","mangy","fools","bands","smock","prowl","china","prove","oases","gilda","brews","sandy","leers","watch","tango","keven","banns","wefts","crass","cloud","hunch","cluck","reams","comic","spool","becky","grown","spike","lingo","tease","fixed","linda","bleep","funky","fanny","curve","josie","minds","musty","toxin","drags","coors","dears","beams","wooer","dells","brave","drake","merge","hippo","lodge","taper","roles","plums","dandy","harps","lutes","fails","navel","lyons","magic","walks","sonic","voles","raped","stamp","minus","hazel","clods","tiffs","hayed","rajah","pared","hates","makes","hinds","splay","flags","tempe","waifs","roved","dills","jonas","avers","balds","balks","perms","dully","lithe","aisha","witty","ellie","dived","range","lefty","wined","booby","decor","jaded","knobs","roded","moots","whens","valet","talks","blare","heeds","cuing","needy","knees","broke","bored","henna","rages","vises","perch","laded","emily","spark","tracy","tevet","faith","sweet","grays","teams","adder","miffs","tubae","marin","folds","basis","drugs","prick","tucks","fifth","treks","taney","romps","jerry","bulgy","anton","codes","bones","quota","turns","melts","croat","woken","wried","leash","spacy","bless","lager","rakes","pukes","cushy","silks","auden","dotes","hinge","noisy","coked","hiked","garth","natty","novel","peeve","macaw","sloth","warns","soles","lobed","aimee","toads","plugs","chasm","pries","douse","ruled","venus","robes","aglow","waves","swore","strum","stael","seeps","snots","freed","truck","hilly","fixer","rarer","rhyme","smugs","demos","ships","piped","jumpy","grant","dirty","climb","quell","pulps","puers","comte","kirks","waver","fever","swear","straw","serum","cowed","blent","yuppy","ropes","conks","boozy","feeds","japes","auger","noons","wench","tasty","honed","balms","trams","pasha","mummy","tides","shove","shyer","trope","clash","promo","harem","never","humus","burks","plans","tempi","crude","vocal","lames","guppy","crime","cough","rural","break","codex","baggy","camry","muses","exile","harte","evens","uriel","bombs","wrens","goren","clark","groom","tinny","alias","irwin","ruddy","twins","rears","ogden","joker","shaky","sodas","larch","lelia","longs","leeds","store","scars","plush","speck","lamar","baser","geeky","wilda","sonny","gummy","porch","grain","testy","wreck","spurs","belie","ached","vapid","chaos","brice","finks","lamed","prize","tsars","drubs","direr","shelf","ceres","swops","weirs","vader","benet","gurus","boors","mucky","gilds","pride","angus","hutch","vance","candy","pesky","favor","glenn","denim","mines","frump","surge","burro","gated","badge","snore","fires","omens","sicks","built","baits","crate","nifty","laser","fords","kneel","louse","earls","greed","miked","tunic","takes","align","robed","acres","least","sleek","motes","hales","idled","faked","bunks","biped","sowed","lucky","grunt","clear","flops","grill","pinch","bodes","delta","lopes","booms","lifer","stunk","avery","wight","flaps","yokel","burgs","racks","claus","haled","nears","finns","chore","stove","dunce","boles","askew","timid","panic","words","soupy","perks","bilge","elias","crush","pagan","silts","clive","shuck","fulls","boner","claws","panza","blurb","soaks","skips","shape","yells","raved","poppy","lease","trued","minks","estes","aisle","penes","kathy","combo","viper","chops","blend","jolly","gimpy","burma","cohan","gazer","drums","gnaws","clone","drain","morns","wages","moths","slues","slobs","warps","brand","popes","triad","ounce","stilt","shins","greer","hodge","minos","tweed","sexed","alger","floss","timer","steve","birch","known","aryan","hedge","fully","jumps","bites","shots","curer","board","lenin","corns","dough","named","kinda","truce","games","lanes","suave","leann","pesos","masks","ghats","stows","mules","hexes","chuck","alden","aping","dives","thurs","nancy","kicks","gibed","burly","sager","filly","onset","anons","yokes","tryst","rangy","pours","rotes","hided","touch","shads","tonya","finer","moors","texas","shoot","tears","elope","tills"]
    */
    dict.clear();
    string m[] = {"tours","awake","goats","crape","boron","payee","waken","cares","times","piled","maces","cuter","spied","spare","mouse","minty","theed","sprat","veins","brian","crown","years","drone","froth","foggy","laura","sears","shunt","gaunt","hovel","staff","child","arson","haber","knows","rubes","czars","pawed","whine","treed","bauer","jodie","timed","flits","robby","gooks","yawls","purse","veeps","tints","taped","raced","shaft","modes","dykes","slims","parts","emile","frail","salem","jives","heave","bayer","leech","clipt","yanks","wilds","hikes","cilia","spiel","mulls","fetal","homed","drown","suite","defer","oaken","flail","zippy","burke","slued","mowed","manes","verse","serra","bruno","spoke","mikes","hafts","breed","sully","croce","boers","chair","thong","pulse","pasta","perot","fices","shies","nadir","every","diets","roads","cones","tuned","globs","graft","stall","royal","fixes","north","pikes","slack","vests","quart","crawl","tangs","calks","mayor","filmy","barns","block","hoods","storm","cedes","emote","tacks","skirt","horsy","mawed","moray","wring","munch","hewed","hooke","batch","drawl","berth","sport","welch","jeans","river","tabby","amens","stump","cause","maced","hiker","spays","dusty","trail","acorn","zooms","puked","clown","sands","kelli","stein","rawer","water","dolts","momma","fluky","scots","pupil","halls","toady","pored","latch","shags","union","tamps","stead","ryder","knoll","cacao","damns","charm","frank","draws","gowns","risen","saxes","lucks","avert","yolks","clime","wedge","ruses","famed","sabik","gravy","anion","veils","pyres","raspy","lofts","tress","showy","percy","rices","taker","roger","yeats","baked","ayers","fazes","curly","shawn","clare","paine","ranks","hocks","berta","plays","parks","tacos","onion","skeet","acton","lamer","teals","reset","steal","maven","sored","fecal","harsh","totem","swoop","rough","jokes","mires","weird","quits","damps","touts","fling","sarah","peeps","waxen","traps","mange","swell","swoon","catch","mower","bonny","finds","yards","pleas","filed","smelt","drams","vivid","smirk","whigs","loafs","opens","meter","hakes","berms","whack","donny","faint","peace","libby","yates","purer","wants","brace","razed","emend","bards","karyn","japed","fated","missy","punks","humps","steak","depth","brunt","hauls","craws","blast","broom","tones","ousts","wires","peeks","ruffs","crack","monte","worth","spans","tonic","runny","erick","singe","maine","casts","jello","realm","haste","utter","bleat","kasey","palms","solos","hoagy","sweep","loner","naves","rhine","acmes","cadet","dices","saris","mauro","fifty","prows","karat","dowel","frays","shorn","sails","ticks","train","stars","stork","halts","basal","glops","beset","rifer","layla","lathe","daffy","jinns","snide","groin","kelly","zincs","fryer","quilt","drama","shook","swami","hulls","swazi","danes","axons","those","lorry","plath","prime","faces","crock","shake","borer","droop","derek","shirk","styed","frown","jells","slows","lifts","jeers","helms","turds","dross","tired","rimes","beats","dingo","crews","bides","loins","furry","shana","wises","logos","aural","light","pings","belch","campy","swish","sangs","nerds","boggy","skies","weals","snags","joyed","mamet","miser","leaks","ramos","tract","rends","marks","taunt","sissy","lipid","beach","coves","fates","grate","gloss","heros","sniff","verve","tells","bulge","grids","skein","clout","leaps","males","surfs","slips","grave","boats","tamed","muled","meier","lower","leafy","stool","reich","rider","iring","ginny","flaks","chirp","tonga","chest","ollie","foxes","links","alton","darth","drier","sated","rails","gyros","green","jenna","cures","veals","sense","sworn","roses","aides","loses","rival","david","worms","stand","track","dales","noyes","fraud","shock","sward","pluto","biked","roans","whiny","halve","bunts","spilt","gamey","deeds","oozed","ruder","drano","sages","fewer","maize","aimed","bails","poole","hunts","shari","champ","shuns","jonah","faced","spook","harry","lagos","peale","nacho","saint","power","chaff","shard","cocky","irate","tummy","withe","forks","bates","stuns","turfs","coped","coups","vince","helps","facet","fezes","outer","cheek","tried","sumps","fakes","fonds","yearn","brays","flute","fetid","beyer","mamma","topic","bouts","trend","gorey","hills","swaps","sexes","cindy","ruler","kited","gaits","shank","cloys","stuck","purus","musks","gouge","brake","biker","layer","lilly","bills","seven","flyer","phase","wowed","beaus","cokes","chimp","spats","mooch","dried","hulks","shift","galen","wiped","clops","decal","nopes","huffs","lades","sunny","foyer","gusty","wormy","chips","focus","pails","solid","ariel","gamed","diver","vying","sacks","spout","sides","agave","bandy","scant","coils","marci","marne","swank","basil","shine","nines","clues","fuzes","jacks","robin","pyxes","later","silas","napes","homes","baled","dames","abuse","piker","coots","tiles","bents","pearl","booty","hells","dusky","glare","scale","pales","leary","scull","bimbo","mossy","apron","manet","opted","kusch","shiny","argos","hoped","towns","bilbo","slums","skull","shale","mandy","scows","speed","eager","lards","crows","merry","anted","faxed","leave","fargo","creek","comas","golda","baize","easts","plied","rared","ashed","doted","bunin","bonds","yarns","latin","right","worst","sixes","gabby","begun","upend","giant","tykes","creak","manor","bosom","riced","dimly","holes","stunt","parsi","peers","snell","mates","jules","rusty","myles","yules","sades","hobbs","booth","clean","liven","gamer","howdy","stray","riser","wisps","lubes","tubes","rodeo","bigot","tromp","pimps","reeve","pumps","dined","still","terms","hines","purrs","roast","dooms","lints","sells","swims","happy","spank","inset","meany","bobby","works","place","brook","haded","chide","slime","clair","zeros","britt","screw","ducal","wroth","edger","basie","benin","unset","shade","doers","plank","betsy","bryce","cross","roped","weans","bliss","moist","corps","clara","notch","sheep","weepy","bract","diced","carla","locks","sawed","covey","jocks","large","pasts","bumps","stile","stole","slung","mooed","souls","dupes","fairs","lined","tunis","spelt","joked","wacky","moira","strut","soled","pints","axing","drank","weary","coifs","wills","gibes","ceded","gerry","tires","crazy","tying","sites","trust","dover","bolds","tools","latex","capet","lanky","grins","brood","hitch","perts","dozes","keels","vault","laius","chung","deres","glove","corms","wafer","coons","ponce","tumid","spinx","verge","soggy","fleas","middy","saiph","payer","nukes","click","limps","oared","white","chart","nasty","perth","paddy","elisa","owing","gifts","manna","ofter","paley","fores","sough","wanda","doggy","antic","ester","swath","spoon","lamas","meuse","hotel","weedy","quads","paled","blond","flume","pried","rates","petal","rover","marsh","grief","downy","pools","buffs","dunne","cruel","finny","cosby","patch","polly","jerks","linen","cider","visas","beard","mewed","spill","trots","tares","pured","prior","build","throe","wends","baned","mario","misty","golds","lacey","slags","jived","finis","inner","money","skews","sunks","fined","bauds","lapel","class","berne","rabin","roils","hyped","styes","evans","towed","hawed","allow","modal","ports","erich","rills","humid","hooks","sedge","shirt","nippy","fundy","runes","smile","dolly","tisha","byers","goths","sousa","mimed","welts","hoots","shown","winds","drays","slams","susan","frogs","peach","goody","boned","chewy","eliza","peary","pyxed","tiled","homer","tokes","verdi","mabel","rolls","laden","loxed","phony","woods","brine","rooks","moods","hired","sises","close","slops","tined","creel","hindu","gongs","wanes","drips","belly","leger","demon","sills","chevy","brads","drawn","donna","glean","dying","sassy","gives","hazes","cores","kayla","hurst","wheat","wiled","vibes","kerry","spiny","wears","rants","sizer","asses","duked","spews","aired","merak","lousy","spurt","reeds","dared","paged","prong","deere","clogs","brier","becks","taken","boxes","wanna","corny","races","spuds","jowls","mucks","milch","weest","slick","nouns","alley","bight","paper","lamps","trace","types","sloop","devon","pedal","glint","gawky","eaves","herbs","felts","fills","naval","icing","eking","lauds","stats","kills","vends","capes","chary","belle","moats","fonts","teems","wards","bated","fleet","renal","sleds","gases","loony","paced","holst","seeds","curie","joist","swill","seats","lynda","tasks","colts","shops","toted","nuder","sachs","warts","pupal","scalp","heirs","wilma","pansy","berra","keeps","menus","grams","loots","heels","caste","hypes","start","snout","nixes","nests","grand","tines","vista","copes","ellis","narks","feint","lajos","brady","barry","trips","forth","sales","bests","hears","twain","plaid","hated","kraft","fared","cubit","jayne","heats","chums","pangs","glows","lopez","vesta","garbo","ethel","blood","roams","mealy","clunk","rowed","hacks","davit","plane","fuses","clung","fitch","serer","wives","lully","clans","kinks","spots","nooks","plate","knits","greet","loads","manic","scone","darin","pills","earth","gored","socks","fauna","ditch","wakes","savvy","quiet","nulls","sizes","diana","mayan","velds","dines","punch","bales","sykes","spiky","hover","teats","lusts","ricky","think","culls","bribe","pairs","month","cored","packs","lobes","older","hefts","faxes","cased","swain","bawdy","troop","woven","stomp","swags","beads","check","shill","broad","souse","pouch","lived","iambs","teaks","clams","outed","maxed","plain","sappy","cabal","penal","shame","budge","offed","kooks","gybed","basin","thoth","arced","hypos","flows","fetch","needs","davis","jared","bongo","added","sames","randy","tunes","jamar","smash","blows","grows","palmy","miler","chins","viola","tower","cream","molls","cello","sucks","fears","stone","leans","zions","nutty","tasha","ratty","tenet","raven","coast","roods","mixes","kmart","looms","scram","chapt","lites","trent","baron","rasps","ringo","fazed","thank","masts","trawl","softy","toils","romes","norma","teens","blank","chili","anise","truss","cheat","tithe","lawns","reese","slash","prate","comet","runts","shall","hosed","harpy","dikes","knock","strip","boded","tough","spend","coats","husky","tyree","menes","liver","coins","axles","macho","jawed","weeps","goods","pryor","carts","dumps","posts","donor","daunt","limbo","books","bowls","welds","leper","benny","couch","spell","burst","elvin","limbs","regal","loyal","gaily","blade","wheal","zests","seine","hubby","sheen","tapes","slugs","bench","lungs","pipes","bride","selma","berry","burns","skins","bowen","gills","conan","yucky","gauls","voled","crust","jerky","moans","plump","sided","disks","gleam","larry","billy","aloud","match","udder","rises","wryer","deter","cling","brisk","lever","chaps","tansy","gland","rocky","lists","joins","tubed","react","farsi","dopes","chats","olsen","stern","gully","youth","wiles","slink","cooke","arise","bores","maims","danny","rives","rusts","plots","loxes","troys","cleat","waxes","booze","haven","dilly","shaun","gasps","rains","panda","quips","kings","frets","backs","arabs","rhino","beets","fiber","duffy","parry","sever","hunks","cheap","beeps","fifes","deers","purls","hello","wolfs","stays","lands","hawks","feels","swiss","tyros","nerve","stirs","mixed","tombs","saves","cater","studs","dorky","cinch","spice","shady","elder","plato","hairs","newts","slump","boots","lives","walls","spunk","bucks","mined","parch","disco","newel","doris","glues","brawn","abner","piked","laxes","bulky","moran","cozen","tinge","dowry","snare","sagan","harms","burch","plows","sunni","fades","coach","girls","typed","slush","saver","bulls","grass","holed","coven","dukes","ocher","texan","cakes","gilts","jenny","salon","divas","maris","costs","sulla","lends","gushy","pears","teddy","huffy","sited","rhone","euler","solve","grace","snarl","taste","sally","allay","suers","bogey","pooch","songs","cameo","molts","snipe","cargo","forge","reins","hoses","crams","fines","tings","wings","spoor","twice","waxed","mixer","bongs","stung","gages","yelps","croci","corks","bolls","madge","honer","riled","camus","trick","bowed","overt","steed","ripes","stave","crick","great","scott","scald","point","finch","bulks","chant","kiddo","cover","drunk","sered","dicky","wider","saith","mutts","blind","lyres","sized","darby","rebel","zones","title","yawns","laths","sting","taine","paris","route","livia","roots","belay","daubs","spoof","camel","colds","foist","saned","doles","slays","woody","leads","stout","caper","erika","lance","earns","vines","mercy","antis","terri","messy","lords","shims","serfs","jinni","caged","threw","rainy","bumpy","arias","wails","romeo","gorge","dolls","risks","skyed","fumes","payed","mites","choir","piles","scene","flake","solon","brahe","bikes","dawes","goofs","payne","cried","slavs","hives","snack","cribs","aways","fired","swarm","pumas","paved","smith","gooey","liefs","safer","banes","slake","doled","dummy","gazed","heaps","loped","scoff","crash","balmy","hexed","lunch","guide","loges","alien","rated","stabs","whets","blest","poops","cowls","canes","story","cunts","tusks","pinto","scats","flier","chose","brute","laked","swabs","preps","loose","merle","farms","gapes","lindy","share","floes","scary","bungs","smart","craps","curbs","vices","tally","beret","lenny","waked","brats","carpi","night","junes","signs","karla","dowdy","devil","toned","araby","trait","puffy","dimer","honor","moose","synch","murks","doric","muted","quite","sedan","snort","rumps","teary","heard","slice","alter","barer","whole","steep","catty","bidet","bayes","suits","dunes","jades","colin","ferry","blown","bryon","sways","bayed","fairy","bevel","pined","stoop","smear","mitty","sanes","riggs","order","palsy","reels","talon","cools","retch","olive","dotty","nanny","surat","gross","rafts","broth","mewls","craze","nerdy","barfs","johns","brims","surer","carve","beers","baker","deena","shows","fumed","horde","kicky","wrapt","waits","shane","buffy","lurks","treat","savor","wiper","bided","funny","dairy","wispy","flees","midge","hooch","sired","brett","putty","caked","witch","rearm","stubs","putts","chase","jesus","posed","dates","dosed","yawed","wombs","idles","hmong","sofas","capek","goner","musts","tangy","cheer","sinks","fatal","rubin","wrest","crank","bared","zilch","bunny","islet","spies","spent","filth","docks","notes","gripe","flair","quire","snuck","foray","cooks","godly","dorms","silos","camps","mumps","spins","cites","sulky","stink","strap","fists","tends","adobe","vivas","sulks","hasps","poser","bethe","sudan","faust","bused","plume","yoked","silly","wades","relay","brent","cower","sasha","staci","haves","dumbs","based","loser","genes","grape","lilia","acted","steel","award","mares","crabs","rocks","lines","margo","blahs","honda","rides","spine","taxed","salty","eater","bland","sweat","sores","ovens","stash","token","drink","swans","heine","gents","reads","piers","yowls","risky","tided","blips","myths","cline","tiers","racer","limed","poled","sluts","chump","greek","wines","mangy","fools","bands","smock","prowl","china","prove","oases","gilda","brews","sandy","leers","watch","tango","keven","banns","wefts","crass","cloud","hunch","cluck","reams","comic","spool","becky","grown","spike","lingo","tease","fixed","linda","bleep","funky","fanny","curve","josie","minds","musty","toxin","drags","coors","dears","beams","wooer","dells","brave","drake","merge","hippo","lodge","taper","roles","plums","dandy","harps","lutes","fails","navel","lyons","magic","walks","sonic","voles","raped","stamp","minus","hazel","clods","tiffs","hayed","rajah","pared","hates","makes","hinds","splay","flags","tempe","waifs","roved","dills","jonas","avers","balds","balks","perms","dully","lithe","aisha","witty","ellie","dived","range","lefty","wined","booby","decor","jaded","knobs","roded","moots","whens","valet","talks","blare","heeds","cuing","needy","knees","broke","bored","henna","rages","vises","perch","laded","emily","spark","tracy","tevet","faith","sweet","grays","teams","adder","miffs","tubae","marin","folds","basis","drugs","prick","tucks","fifth","treks","taney","romps","jerry","bulgy","anton","codes","bones","quota","turns","melts","croat","woken","wried","leash","spacy","bless","lager","rakes","pukes","cushy","silks","auden","dotes","hinge","noisy","coked","hiked","garth","natty","novel","peeve","macaw","sloth","warns","soles","lobed","aimee","toads","plugs","chasm","pries","douse","ruled","venus","robes","aglow","waves","swore","strum","stael","seeps","snots","freed","truck","hilly","fixer","rarer","rhyme","smugs","demos","ships","piped","jumpy","grant","dirty","climb","quell","pulps","puers","comte","kirks","waver","fever","swear","straw","serum","cowed","blent","yuppy","ropes","conks","boozy","feeds","japes","auger","noons","wench","tasty","honed","balms","trams","pasha","mummy","tides","shove","shyer","trope","clash","promo","harem","never","humus","burks","plans","tempi","crude","vocal","lames","guppy","crime","cough","rural","break","codex","baggy","camry","muses","exile","harte","evens","uriel","bombs","wrens","goren","clark","groom","tinny","alias","irwin","ruddy","twins","rears","ogden","joker","shaky","sodas","larch","lelia","longs","leeds","store","scars","plush","speck","lamar","baser","geeky","wilda","sonny","gummy","porch","grain","testy","wreck","spurs","belie","ached","vapid","chaos","brice","finks","lamed","prize","tsars","drubs","direr","shelf","ceres","swops","weirs","vader","benet","gurus","boors","mucky","gilds","pride","angus","hutch","vance","candy","pesky","favor","glenn","denim","mines","frump","surge","burro","gated","badge","snore","fires","omens","sicks","built","baits","crate","nifty","laser","fords","kneel","louse","earls","greed","miked","tunic","takes","align","robed","acres","least","sleek","motes","hales","idled","faked","bunks","biped","sowed","lucky","grunt","clear","flops","grill","pinch","bodes","delta","lopes","booms","lifer","stunk","avery","wight","flaps","yokel","burgs","racks","claus","haled","nears","finns","chore","stove","dunce","boles","askew","timid","panic","words","soupy","perks","bilge","elias","crush","pagan","silts","clive","shuck","fulls","boner","claws","panza","blurb","soaks","skips","shape","yells","raved","poppy","lease","trued","minks","estes","aisle","penes","kathy","combo","viper","chops","blend","jolly","gimpy","burma","cohan","gazer","drums","gnaws","clone","drain","morns","wages","moths","slues","slobs","warps","brand","popes","triad","ounce","stilt","shins","greer","hodge","minos","tweed","sexed","alger","floss","timer","steve","birch","known","aryan","hedge","fully","jumps","bites","shots","curer","board","lenin","corns","dough","named","kinda","truce","games","lanes","suave","leann","pesos","masks","ghats","stows","mules","hexes","chuck","alden","aping","dives","thurs","nancy","kicks","gibed","burly","sager","filly","onset","anons","yokes","tryst","rangy","pours","rotes","hided","touch","shads","tonya","finer","moors","texas","shoot","tears","elope","tills"};
    dict.insert(begin(m), end(m));
    print(s.findLadders("catch", "choir", dict));

    dict.clear();
    string l[] = {"a","b","c"};
    dict.insert(begin(l), end(l));
    print(s.findLadders("a", "c", dict));

    dict.clear();
    string a[] = {"hot","dog"};
    dict.insert(begin(a), end(a));
    print(s.findLadders("hot", "dog", dict));

    dict.clear();
    string b[] = {"hot","dog","dot"};
    dict.insert(begin(b), end(b));
    print(s.findLadders("hot", "dog", dict));

    dict.clear();
    dict.insert(begin(b), end(b));
    print(s.findLadders("hot", "dot", dict));

    dict.clear();
    string c[] = {"hot","cog","dog","tot","hog","hop","pot","dot"};
    dict.insert(begin(c), end(c));
    print(s.findLadders("hot", "dog", dict));

    dict.clear();
    string d[] = {"hot","dog","cog","pot","dot"};
    dict.insert(begin(d), end(d));
    print(s.findLadders("hot", "dog", dict));

    dict.clear();
    string e[] = {"hot","cog","dot","dog","hit","lot","log"};
    dict.insert(begin(e), end(e));
    print(s.findLadders("hit", "cog", dict));

    dict.clear();
    string f[] = {"hot","hit","cog","dot","dog"};
    dict.insert(begin(f), end(f));
    print(s.findLadders("hit", "cog", dict));

    dict.clear();
    string g[] = {"ted","tex","red","tax","tad","den","rex","pee"};
    dict.insert(begin(g), end(g));
    print(s.findLadders("red", "tax", dict));

    dict.clear();
    string h[] = {"most","fist","lost","cost","fish"};
    dict.insert(begin(h), end(h));
    print(s.findLadders("lost", "cost", dict));

    dict.clear();
    string i[] = {"most","mist","miss","lost","fist","fish"};
    dict.insert(begin(i), end(i));
    print(s.findLadders("lost", "miss", dict));

    dict.clear();
    string j[] = {"lest","leet","lose","code","lode","robe","lost"};
    dict.insert(begin(j), end(j));
    print(s.findLadders("leet", "code", dict));

    dict.clear();
    string k[] = {"talk","tons","fall","tail","gale","hall","negs"};
    dict.insert(begin(k), end(k));
    print(s.findLadders("talk", "tail", dict));

    return 0;
}

