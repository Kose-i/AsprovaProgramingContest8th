#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct SortType {
    int s, c;
    int cost;
};
bool operator<(SortType& l, SortType& r) {
    return l.cost < r.cost;
}

struct ProductProcess {
    int s, c;
    int list_idx; // search for list
    int list_shape_same_idx;
    vector<SortType> list;
    vector<SortType> list_shape_same;
};

struct AnsType {
    int query;
    int s, c;
};
void print_ans(const vector<AnsType>& ans);

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

    vector<AnsType> answer;
    //process
    vector<vector<ProductProcess>> vec(shape_size, vector<ProductProcess>(color_size));
    for (int i=0;i<shape_size;++i) {
        for (int j=0;j<color_size;++j) {
            //[i][j]
            vec[i][j].s = i; vec[i][j].c = j; vec[i][j].list_shape_same_idx = 0; vec[i][j].list_idx = 0;
            SortType tmp_sorttype;
            for (int k=0;k<shape_size;++k) {
                tmp_sorttype.s = k;
                for (int l=0;l<color_size;++l) {
                    tmp_sorttype.c = l;
                    if (i == k) {
                        tmp_sorttype.cost = color_change_cost[j][l];
                        vec[i][j].list_shape_same.push_back(tmp_sorttype);
                    } else {
                        tmp_sorttype.cost = std::max(shape_change_cost[i][k], color_change_cost[j][l]);
                        vec[i][j].list.push_back(tmp_sorttype);
                    }
                }
            }
        }
    }
    for (int i=0;i<shape_size;++i) {
        for (int j=0;j<color_size;++j) {
            std::sort(vec[i][j].list.begin(), vec[i][j].list.end());
            std::sort(vec[i][j].list_shape_same.begin(), vec[i][j].list_shape_same.end());
        }
    }

    for (int ans_s=0;ans_s<shape_size;++ans_s) {
        for (int ans_c=0;ans_c<color_size;++ans_c) {
            while (product_cnt[ans_s][ans_c]!=0) {
                int cnt = std::min(hook_cnt[ans_s], product_cnt[ans_s][ans_c]);
                product_cnt[ans_s][ans_c] -= cnt;
                for (int i=0;i<hook_size;++i) {
                    if (cnt > 0) {
                        AnsType tmp_answer; tmp_answer.query = 0;
                        tmp_answer.s = ans_s; tmp_answer.c = ans_c;
                        answer.push_back(tmp_answer);
                        --cnt;
                    } else {
                        AnsType tmp_answer; tmp_answer.query = -2;
                        answer.push_back(tmp_answer);
                    }
                }
            }
        }
    }

    // output
    print_ans(answer);
}

void print_ans(const vector<AnsType>& ans) {
    cout << ans.size() << '\n';
    for (const AnsType& e : ans) {
        if (e.query == 0) {
            cout << e.s+1 << ' ' << e.c+1 << '\n';
        } else {
            cout << e.query << '\n';
        }
    }
}
