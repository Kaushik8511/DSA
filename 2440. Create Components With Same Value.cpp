#define MAX 20001


int n;



class Solution {
    
    
    bool bfs(vector<int> adj[], int s, vector<int> degree, vector<int> value) {
        queue<int> q;
        for(int i=0; i<n; i++) if(degree[i] == 1) q.push(i);
        
        while(!q.empty()) {
            int curr = q.front(); q.pop();
            if(degree[curr] == 0) continue;
            degree[curr] = 0;
            
            // cout << s << " " << curr << "\n";
            
            if(value[curr] == s) {
                for(int ad: adj[curr]) {
                    degree[ad]--;
                    if(degree[ad] == 0) return value[ad] == s;
                    else if(degree[ad] == 1) q.push(ad);
                }
            }
            else {
                for(int ad: adj[curr]) {
                    if(degree[ad] > 0) {
                        degree[ad]--;
                        value[ad] += value[curr];
                        if(degree[ad] == 0) return value[ad] == s;
                        else if (degree[ad] == 1) q.push(ad);
                    }
                }
            }
            
        }
        // cout << s << " last \n";
        return true;
    }
    
public:
    int componentValue(vector<int>& nums, vector<vector<int>>& edges) {
        n = nums.size();
        if(n == 1) return 0;
        int sum = 0;
        for(int &i: nums) sum += i;
        
        //values
        vector<int> value(n);
        for(int i=0; i<n; i++) value[i] = nums[i];
        
        //degree
        vector<int> degree(n, 0);
        
        //create graph and fill degree array
        vector<int> adj[n];
        for(auto &vec: edges) {
            int u = vec[0], v = vec[1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            degree[u]++;
            degree[v]++;
        }
        
        // cout << "sum = " << sum << "\n";
        
        for(int i=1; i<=sum; i++) {
            if(sum % i == 0 && bfs(adj, i, degree, value)) {
                cout << i ;
                return sum / i - 1;
            }
        }
        
        
        return 0;
        
    }
};