#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Activity {
    string name;
    int start;
    int end;
};

// 比较函数，用于按活动结束时间排序
bool compare(const Activity& a, const Activity& b) {
    return a.end < b.end;
}

// 活动安排函数
vector<Activity> activitySelection(vector<Activity> activities) {
    if (activities.empty()) return {};
    vector<Activity> selected;
    // 按结束时间排序
    sort(activities.begin(), activities.end(), compare);
    selected.push_back(activities[0]);
    int lastEnd = activities[0].end;
    for (size_t i = 1; i < activities.size(); ++i) {
        if (activities[i].start >= lastEnd) {
            selected.push_back(activities[i]);
            lastEnd = activities[i].end;
        }
    }
    return selected;
}

int main() {
    int num;
    cout << "请输入活动数量: ";
    cin >> num;
    vector<Activity> allActivities;
    for (int i = 0; i < num; ++i) {
        Activity act;
        cout << "请输入活动名称: ";
        cin >> act.name;
        cout << "请输入活动开始时间: ";
        cin >> act.start;
        cout << "请输入活动结束时间: ";
        cin >> act.end;
        allActivities.push_back(act);
    }

    vector<Activity> result = activitySelection(allActivities);
    cout << "选取的活动数: " << result.size() << endl;
    for (const auto& act : result) {
        cout << "活动名称: " << act.name << "，开始时间: " << act.start << "，结束时间: " << act.end << endl;
    }

    return 0;
}