#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(int argc, char** argv) {
    int shape_size, color_size, hook_size, param_a, param_b;
    cin >> shape_size >> color_size >> hook_size >> param_a >> param_b;
    vector<vector<int>> product_cnt(shape_size, vector<int>(color_size));
    for (int i=0;i<shape_size;++i) for (int j=0;j<color_size;++j) cin >> product_cnt[i][j];
    vector<int> hook_cnt(shape_size);
    for (int i=0;i<shape_size;++i) cin >> hook_cnt[i];
    vector<vector<int>> shape_change_cost(shape_size, vector<int>(shape_size));
    for (int i=0;i<shape_size;++i) for (int j=0;j<shape_size;++j) cin >> shape_change_cost[i][j];
    vector<vector<int>> color_change_cost(color_size, vector<int>(color_size));
    for (int i=0;i<color_size;++i) for (int j=0;j<color_size;++j) cin >> color_change_cost[i][j];
}
