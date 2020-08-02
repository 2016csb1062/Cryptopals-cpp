#include<unordered_map>

using namespace std;

class map_helper
{
    public:
    template <typename a , typename b>
        void print(unordered_map<a,b> map)
        {
            typename unordered_map<a , b>::iterator itr = map.begin();
            while(itr!=map.end())
            {
                cout<<itr->first<<" : "<<itr->second<<endl;
                itr++;
            }
        }
};