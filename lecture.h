#ifndef LECTURE_H
#define LECTURE_H

#include <iostream>
#include <string>
#include <vector>

class Lecture {
public:
    Lecture(std::string weekday, float startTime, float durationTime, std::string type);
    Lecture(const Lecture& lecture);

    void setWeekday(std::string weekday){ weekday_ = weekday; }
    std::string getWeekday() const { return weekday_; }

    void setStartTime(float starTime){ startTime_ = starTime; }
    float getStartTime() const {return startTime_;}

    void setDurationTime(float durationTime){ durationTime_ = durationTime; }
    float getDurationTime() const { return durationTime_; }

    void setType(std::string type){ type_ = type; }
    std::string getType() const { return type_; }

    /**
     * A method to compare two lectures.\n
     * Time Complexity: O(1).
     * @param a A pointer to a lecture.
     * @param b A pointer to other lecture.
     * @return A boolean that tells if a is smaller than b.
     */
    static bool compareLecture(Lecture* a, Lecture* b);

    /**
    * A method to print the information about a lecture.\n
    * It prints the corresponding weekday for the lecture followed by its start time, duration time and type.\n
    * Time Complexity: O(1).
    */
    void show() const;

private:
    std::string weekday_;
    float startTime_;
    float durationTime_;
    std::string type_;
    static const std::vector<std::pair<std::string, int>> weekDays_;
};


#endif
