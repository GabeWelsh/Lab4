#include "activity.h"

const string Activity::ACTIVITY_NAMES[Activity_Code::Yoga + 1] = {
    "Assembly Line",
    "Baseball",
    "Basketball (shooting baskets)",
    "Basketball game",
    "Bicycling under 10mph",
    "Bicycling",
    "Cooking",
    "Dance",
    "Football",
    "Hiking",
    "House cleaning",
    "Gardening",
    "Miniature golf",
    "Racquetball",
    "Rowing",
    "Running 6 mph",
    "Running 7 mph",
    "Running 8 mph",
    "Shopping",
    "Soccer",
    "Softball",
    "Stairs",
    "Swimming laps",
    "Tennis",
    "Walking 3mph",
    "Walking 4mph",
    "Weight lifting",
    "Yoga"};

const int Activity::STEPS_IN_1_MIN[Activity_Code::Yoga + 1] = {
    85,  152, 136, 242, 121, 242, 61,  167, 242, 182, 91,  99,  91,  212,
    212, 303, 348, 409, 70,  212, 152, 273, 212, 212, 100, 152, 121, 76};

// returns the total number of miles walked based on the activity,
// minutesDone, and supplied height
double Activity::getInMiles(float height) const {
  double stepLength = ((0.413 * height) / 12);
  double totalFeetWalked = (stepLength * minutesDone * getStepsInOneMinute());
  double totalMilesWalked = totalFeetWalked / 5280;
  return totalMilesWalked;
}
