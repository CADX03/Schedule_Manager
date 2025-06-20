#include "lecture.h"

const std::vector<std::pair<std::string, int>> Lecture::weekDays_ = {std::make_pair("Monday", 0), std::make_pair("Tuesday", 1), std::make_pair("Wednesday", 2), std::make_pair("Thursday", 3), std::make_pair("Friday", 4)};

Lecture::Lecture(std::string weekday, float startTime, float durationTime, std::string type) {
    weekday_ = weekday;
    startTime_ = startTime;
    durationTime_ = durationTime;
    type_ = type;
}

Lecture::Lecture(const Lecture& lecture) {
    weekday_ = lecture.getWeekday();
    startTime_ = lecture.getStartTime();
    durationTime_ = lecture.getDurationTime();
    type_ = lecture.getType();
}

void Lecture::show() const { std::cout << weekday_ << "  \t" << startTime_ << "   \t\t" << durationTime_ << "\t\t\t" << type_;}

bool Lecture::compareLecture(Lecture* a, Lecture* b) {
    int aWeekDay;
    int bWeekDay;
    for(const auto& weekDay : weekDays_){
        if(a->getWeekday() == weekDay.first)
            aWeekDay = weekDay.second;
        if(b->getWeekday() == weekDay.first)
            bWeekDay = weekDay.second;
    }
    return aWeekDay < bWeekDay || (aWeekDay == bWeekDay && a->getStartTime() < b->getStartTime());
}
