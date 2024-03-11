#include <algorithm>
#include <vector>
#include <iostream>
#include <queue>
#include <stack>
#include <string>
#include <unordered_map>
#include<unordered_set>
using namespace std;

/**
 * 2788. 按分隔符拆分字符串
 */
vector<string> splitWordsBySeparator(vector<string> &words, char separator)
{
    vector<string> ans;

    for (int i = 0; i < words.size(); i++)
    {
        string temp = "";
        for (int j = 0; j < words[i].size(); j++)
        {
            if (words[i][j] == separator)
            {
                if (temp != "")
                {
                    ans.push_back(temp);
                }
                temp = "";
            }
            else
            {
                temp += words[i][j];
            }
        }
        if (temp != "")
        {
            ans.push_back(temp);
        }
    }
    return ans;
}

/**
 * 670. 最大交换
 */
int maximumSwap(int num)
{
    string s = to_string(num);
    int len = s.size();

    int maxV = -1;
    for (int i = 0; i < len; i++)
    {
        for (int j = i + 1; j < len; j++)
        {
            if (s[j] > s[i])
            {
                string st = s;
                char t = st[i];
                st[i] = st[j];
                st[j] = t;

                if (maxV < stoi(st))
                {
                    maxV = stoi(st);
                }
            }
        }
    }
    if (maxV == -1)
    {
        return num;
    }
    return maxV;
}

/**
 * 15. 三数之和
 */
vector<vector<int>> threeSum(vector<int> &nums)
{
    vector<vector<int>> ans;
    sort(nums.begin(), nums.end());

    if (nums[0] > 0)
    {
        return ans;
    }

    int len = nums.size();
    for (int i = 0; i < len; i++)
    {
        if (i > 0 && nums[i] == nums[i - 1])
        {
            continue;
        }
        int target = -nums[i];
        int third = len - 1;
        for (int j = i + 1; j < len; j++)
        {
            if (j > i + 1 && nums[j] == nums[j - 1])
            {
                continue;
            }
            while (third > j && nums[j] + nums[third] > target)
            {
                third--;
            }

            if (third == j)
            {
                break;
            }
            if (nums[j] + nums[third] == target)
            {
                ans.push_back({nums[i], nums[j], nums[third]});
            }
        }
    }
    return ans;
}

/**
 * 135. 分发糖果
 */
int candy(vector<int> &ratings)
{
    int ans = 1;
    int pre = 1;
    int dec = 0;
    int inc = 1;
    for (int i = 1; i < ratings.size(); i++)
    {
        if (ratings[i] >= ratings[i - 1])
        {
            dec = 0;
            pre = ratings[i] == ratings[i - 1] ? 1 : pre + 1;
            ans += pre;
            inc = pre;
        }
        else
        {
            dec++;
            if (dec == inc)
            {
                dec++;
            }
            ans += dec;
            pre = 1;
        }
    }
    return ans;
}

/**
 * LCR 183. 望远镜中最高的海拔
 */
vector<int> maxAltitude(vector<int> &heights, int limit)
{

    deque<int> dq;
    vector<int> ans;
    int len = heights.size();
    if (len == 0)
    {
        return ans;
    }
    for (int i = 0; i < limit; i++)
    {
        while (!dq.empty() && heights[dq.back()] < heights[i])
        {
            dq.pop_back();
        }
        dq.push_back(i);
    }
    ans.push_back(heights[dq.front()]);
    for (int i = limit; i < len; i++)
    {
        while (!dq.empty() && heights[dq.back()] < heights[i])
        {
            dq.pop_back();
        }
        dq.push_back(i);

        while (dq.front() <= i - limit)
        {
            dq.pop_front();
        }
        ans.push_back(heights[dq.front()]);
    }
    return ans;
}

/**
 * 1944. 队列中可以看到的人数
 */
vector<int> canSeePersonsCount(vector<int> &heights)
{
    int len = heights.size();
    vector<int> ans(len, 0);
    vector<int> st;

    for (int i = len - 1; i >= 0; i--)
    {
        int t = 0;
        while (!st.empty() && heights[i] > st.back())
        {
            st.pop_back();
            t++;
        }
        if (!st.empty())
        {
            t++;
        }
        ans[i] = t;
        st.push_back(heights[i]);
    }
    return ans;
}

/**
 * 84. 柱状图中最大的矩形
 */
int largestRectangleArea(vector<int> &heights)
{
    int ans = 0;
    int len = heights.size();
    stack<int> st;
    vector<int> left(len), right(len);

    for (int i = 0; i < len; i++)
    {
        while (!st.empty() && heights[st.top()] >= heights[i])
        {
            st.pop();
        }

        left[i] = st.empty() ? -1 : st.top();
        st.push(i);
    }
    stack<int> sr;
    for (int i = len; i >= 0; i--)
    {
        while (!sr.empty() && heights[sr.top()] >= heights[i])
        {
            sr.pop();
        }
        right[i] = sr.empty() ? len : sr.top();
        sr.push(i);
    }

    for (int i = 0; i < len; i++)
    {
        ans = max(ans, (right[i] - left[i] - 1) * heights[i]);
    }

    return ans;
}

/**
 * 使用优先队列实现迪杰斯特拉算法
 */

struct edge
{
    long long weight;
    int begin;
    int end;

    edge(long long w,int b,int e):weight(w),begin(b),end(e){}
};

static bool cmp(edge& a,edge& b) {
    return a.weight < b.weight;
}
int countPaths(int n, vector<vector<int>> &roads)
{
    vector<bool> visited(n);
    priority_queue<edge,vector<edge>,decltype(&cmp)> pq(cmp);
    vector<vector<pair<int, long long>>> arr(n);
    for (int i = 0; i < n; i++)
    {
        int x = roads[i][0];
        int y = roads[i][1];
        int path = roads[i][2];
        arr[x].push_back({y, path});
        arr[y].push_back({x, path});
    }
    
    vector<long long> dist(n, LLONG_MAX);
    dist[0] = 0;
    pq.push(edge(0,0,0));
    while(!pq.empty()) {
        auto temp = pq.top();
        pq.pop();
        if(visited[temp.begin]) {
            continue;
        }
        visited[temp.begin] = true;
        for(auto t : arr[temp.end]) {
            int to = t.first;
            int w = t.second;

            if(!visited[to] && dist[temp.end] + w < dist[to]) {
                dist[to] = dist[temp.end] + w;
                pq.push(edge(dist[to],temp.end,t.first));
            }
        }
    }
    return 0;
}

/**
 * 1976. 到达目的地的方案数
*/
int countPaths(int n, vector<vector<int>>& roads) {

    vector<vector<pair<int,int>>> edge(n);
    for(auto e : roads) {
        edge[e[0]].push_back({e[1],e[2]});
        edge[e[1]].push_back({e[0],e[2]});
    }

    priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>> pq;

    pq.emplace(0,0);
    vector<long long> dis(n, LLONG_MAX);
    vector<long long> ways(n);

    dis[0] = 0;
    ways[0] = 1;

    while (!pq.empty()) {
        auto [t,u] = pq.top();
        pq.pop();

        if(t > dis[u]) {
            continue;
        }
        for(auto &[v,w] : edge[u]) {
            if(t + w < dis[v]) {
                dis[v] = t+w;
                ways[v] = ways[u];
                pq.emplace(dis[v],v);
            }else if(t + w == dis[v]) {
                ways[v] = (ways[u] + ways[v]) % 1000000007;
            }
        }
    }
    return ways[n-1];
}

/**
 * 2834. 找出美丽数组的最小和
*/
int minimumPossibleSum(int n, int target) {

    int m = target/2;
    if(n <=m) {
        long long ans = n * (n+1) /2;
        return ans%1000000007;
    }else{

        long long ans = (long long) (m+1)*m/2;
        long long ans1 = ((long long) target + target + n - m -1) * (n - m) /2;

        return (ans + ans1) % 1000000007;
    }
}

/**
 * 
*/
string capitalizeTitle(string title) {
    title.append(" ");
    int len = title.size();
    int begin = 0;
    int end = 0;
      while(end < len) {
        if(title[end] == ' ') {
            cout<<begin<<" "<<end<<endl;
            if(end - begin <= 2) {
                while(begin <= end) {
                    if(title[begin] <= 'Z' && title[begin] >= 'A') {
                        title[begin] += 32;
                    }
                    begin++;
                }
            }else{
                if(title[begin] >= 'a' && title[begin] <= 'z') {
                    title[begin] -= 32;
                }
                begin++;
                 while(begin <= end) {
                    if(title[begin] <= 'Z'&& title[begin] >= 'A') {
                        title[begin] += 32;
                    }
                    begin++;
                }
            }
        }
    title.erase(len-1);
    return title;
}