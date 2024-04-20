#ifndef ACTIVITY_H
#define ACTIVITY_H

#include <string>

using namespace std;

class Activity {
public:
  enum Activity_Code {
    Assembly_Line,
    Baseball,
    Basketball_Shooting_Baskets,
    Basketball_Game,
    Bicycling_Under_10mph,
    Bicycling,
    Cooking,
    Dance,
    Football,
    Hiking,
    House_Cleaning,
    Gardening,
    Miniature_Golf,
    Racquetball,
    Rowing,
    Running_6_Mph,
    Running_7_Mph,
    Running_8_Mph,
    Shopping,
    Soccer,
    Softball,
    Stairs,
    Swimming_Laps,
    Tennis,
    Walking_3mph,
    Walking_4mph,
    Weight_Lifting,
    Yoga
  };
  Activity()
      : minutesDone(0.0), activity(Activity::Activity_Code::Assembly_Line){};
  Activity(double minsDone, Activity::Activity_Code activityCode)
      : minutesDone(minsDone), activity(activityCode) {}

  void setMinutesDone(double min) { minutesDone = min; }
  string getActivityName() const { return ACTIVITY_NAMES[static_cast<int>(activity)]; }
  int getStepsInOneMinute() const { return STEPS_IN_1_MIN[static_cast<int>(activity)]; }
  double getInMiles(float height) const;
  friend std::ostream &operator<<(std::ostream &os, Activity &activity) {
    os << ACTIVITY_NAMES[activity.activity];
    return os;
  }
private:
  const static string ACTIVITY_NAMES[Activity_Code::Yoga + 1];
  const static int STEPS_IN_1_MIN[Activity_Code::Yoga + 1];
  double minutesDone;
  Activity::Activity_Code activity;
};

#endif