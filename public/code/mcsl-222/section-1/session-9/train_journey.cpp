// train_journey.cpp -- MCSL-222 Session 9, Q21
// Figure 1.16 (Train Journey -- Train) implemented in C++17 as a TWO-WAY
// association: TrainJourney.assignedTrain (0..1) and Train.assignedJourny (0..*).
// Build: clang++ -std=c++17 -Wall -Wextra -o train_journey train_journey.cpp

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Train;

// -------------------------------------------------------- TrainJourney
class TrainJourney {
public:
    int Train_No = 0;
    std::string Source_St;
    std::string Destination_St;
    float Journy_Time = 0.0f;
    Train* assignedTrain = nullptr;  // role assignedTrain, multiplicity 0..1

    TrainJourney(std::string src, std::string dst, float hours)
        : Source_St(std::move(src)), Destination_St(std::move(dst)), Journy_Time(hours) {}

    void Set_Source_St(const std::string& source) { Source_St = source; }
    void Set_Dastination_St(const std::string& destination) { Destination_St = destination; }
    // The figure passes Train_No to the getters, so they answer only for
    // the train this journey is assigned to.
    std::string Get_Source_St(int train_no) const {
        return train_no == Train_No ? Source_St : std::string("(not this train)");
    }
    float Get_Journy_Time(int train_no) const {
        return train_no == Train_No ? Journy_Time : -1.0f;
    }
};

// --------------------------------------------------------------- Train
class Train {
public:
    int Train_No;
    std::string Train_Type;
    float Max_Speed;
    std::vector<TrainJourney*> assignedJourny;  // role assignedJourny, multiplicity 0..*

    Train(int no, std::string type, float speed)
        : Train_No(no), Train_Type(std::move(type)), Max_Speed(speed) {}

    int Get_Train_No() const { return Train_No; }
    void Set_Train_Type(const std::string& trtype) { Train_Type = trtype; }
    float Get_Train_Speed(int train_no) const {
        return train_no == Train_No ? Max_Speed : -1.0f;
    }
};

// ---------------------------------------------- keeping both ends in step
// Both ends change in one place, so a journey can never point at a train
// that does not list it, and vice versa.
static void unassign(TrainJourney& j) {
    if (Train* t = j.assignedTrain) {
        t->assignedJourny.erase(
            std::remove(t->assignedJourny.begin(), t->assignedJourny.end(), &j),
            t->assignedJourny.end());
        j.assignedTrain = nullptr;
        j.Train_No = 0;
    }
}

static void assign(Train& t, TrainJourney& j) {
    unassign(j);  // a journey has at most one train (0..1)
    j.assignedTrain = &t;
    j.Train_No = t.Train_No;
    t.assignedJourny.push_back(&j);
}

// ---------------------------------------------------------------- main
static void printTrain(const Train& t) {
    std::cout << "Train " << t.Get_Train_No() << " (" << t.Train_Type << ", "
              << t.Max_Speed << " km/h) runs " << t.assignedJourny.size() << " journey(s)\n";
    for (const TrainJourney* j : t.assignedJourny)
        std::cout << "  " << j->Source_St << " -> " << j->Destination_St << ", "
                  << j->Journy_Time << " h, Train_No stored in journey = " << j->Train_No
                  << "\n";
}

int main() {
    Train rajdhani(12951, "Rajdhani", 130.0f);
    Train shatabdi(12009, "Shatabdi", 150.0f);

    TrainJourney j1("Mumbai", "Delhi", 15.5f);
    TrainJourney j2("Delhi", "Mumbai", 15.75f);
    TrainJourney j3("Mumbai", "Ahmedabad", 6.25f);

    assign(rajdhani, j1);
    assign(rajdhani, j2);
    assign(shatabdi, j3);

    std::cout << "--- after assignment ---\n";
    printTrain(rajdhani);
    printTrain(shatabdi);

    std::cout << "--- operations from the figure ---\n";
    j3.Set_Source_St("Mumbai Central");
    j3.Set_Dastination_St("Ahmedabad Jn");
    shatabdi.Set_Train_Type("Shatabdi Express");
    std::cout << "j3.Get_Source_St(12009) = " << j3.Get_Source_St(12009) << "\n";
    std::cout << "j3.Get_Source_St(12951) = " << j3.Get_Source_St(12951) << "\n";
    std::cout << "j3.Get_Journy_Time(12009) = " << j3.Get_Journy_Time(12009) << "\n";
    std::cout << "shatabdi.Get_Train_Speed(12009) = " << shatabdi.Get_Train_Speed(12009) << "\n";
    std::cout << "j1.assignedTrain->Train_Type = " << j1.assignedTrain->Train_Type << "\n";

    std::cout << "--- move j2 to the Shatabdi (0..1 keeps only one train) ---\n";
    assign(shatabdi, j2);
    printTrain(rajdhani);
    printTrain(shatabdi);

    std::cout << "--- unassign j3 ---\n";
    unassign(j3);
    std::cout << "j3.assignedTrain is " << (j3.assignedTrain ? "set" : "nullptr")
              << ", shatabdi lists " << shatabdi.assignedJourny.size() << " journey(s)\n";
    return 0;
}
