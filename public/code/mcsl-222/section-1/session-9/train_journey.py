# train_journey.py -- MCSL-222 Session 9, Q21
# Figure 1.16 (Train Journey -- Train) in Python 3, standard library only, as a
# TWO-WAY association: TrainJourney.assignedTrain (0..1) and Train.assignedJourny (0..*).
# Run: python3 train_journey.py
# eq=False keeps identity comparison, so list.remove() unlinks that exact journey
# and the two-way links cannot recurse through a field-by-field ==.
from __future__ import annotations

from dataclasses import dataclass, field
from typing import Optional


def g(x: float) -> str:
    """Print a float the way C++ streams do by default: 130, 15.5, 6.25."""
    return f"{x:g}"


# -------------------------------------------------------- TrainJourney
@dataclass(eq=False)
class TrainJourney:
    Source_St: str
    Destination_St: str
    Journy_Time: float
    Train_No: int = 0
    assignedTrain: Optional[Train] = None  # role assignedTrain, multiplicity 0..1

    def Set_Source_St(self, source: str) -> None:
        self.Source_St = source

    def Set_Dastination_St(self, destination: str) -> None:
        self.Destination_St = destination

    # The figure passes Train_No to the getters, so they answer only for
    # the train this journey is assigned to.
    def Get_Source_St(self, train_no: int) -> str:
        return self.Source_St if train_no == self.Train_No else "(not this train)"

    def Get_Journy_Time(self, train_no: int) -> float:
        return self.Journy_Time if train_no == self.Train_No else -1.0


# --------------------------------------------------------------- Train
@dataclass(eq=False)
class Train:
    Train_No: int
    Train_Type: str
    Max_Speed: float
    assignedJourny: list[TrainJourney] = field(default_factory=list)  # role assignedJourny, 0..*

    def Get_Train_No(self) -> int:
        return self.Train_No

    def Set_Train_Type(self, trtype: str) -> None:
        self.Train_Type = trtype

    def Get_Train_Speed(self, train_no: int) -> float:
        return self.Max_Speed if train_no == self.Train_No else -1.0


# ---------------------------------------------- keeping both ends in step
# Both ends change in one place, so a journey can never point at a train
# that does not list it, and vice versa.
def unassign(j: TrainJourney) -> None:
    t = j.assignedTrain
    if t is not None:
        t.assignedJourny.remove(j)
        j.assignedTrain = None
        j.Train_No = 0


def assign(t: Train, j: TrainJourney) -> None:
    unassign(j)  # a journey has at most one train (0..1)
    j.assignedTrain = t
    j.Train_No = t.Train_No
    t.assignedJourny.append(j)


# ---------------------------------------------------------------- main
def printTrain(t: Train) -> None:
    print(f"Train {t.Get_Train_No()} ({t.Train_Type}, {g(t.Max_Speed)} km/h) "
          f"runs {len(t.assignedJourny)} journey(s)")
    for j in t.assignedJourny:
        print(f"  {j.Source_St} -> {j.Destination_St}, {g(j.Journy_Time)} h, "
              f"Train_No stored in journey = {j.Train_No}")


def main() -> None:
    rajdhani = Train(12951, "Rajdhani", 130.0)
    shatabdi = Train(12009, "Shatabdi", 150.0)

    j1 = TrainJourney("Mumbai", "Delhi", 15.5)
    j2 = TrainJourney("Delhi", "Mumbai", 15.75)
    j3 = TrainJourney("Mumbai", "Ahmedabad", 6.25)

    assign(rajdhani, j1)
    assign(rajdhani, j2)
    assign(shatabdi, j3)

    print("--- after assignment ---")
    printTrain(rajdhani)
    printTrain(shatabdi)

    print("--- operations from the figure ---")
    j3.Set_Source_St("Mumbai Central")
    j3.Set_Dastination_St("Ahmedabad Jn")
    shatabdi.Set_Train_Type("Shatabdi Express")
    print(f"j3.Get_Source_St(12009) = {j3.Get_Source_St(12009)}")
    print(f"j3.Get_Source_St(12951) = {j3.Get_Source_St(12951)}")
    print(f"j3.Get_Journy_Time(12009) = {g(j3.Get_Journy_Time(12009))}")
    print(f"shatabdi.Get_Train_Speed(12009) = {g(shatabdi.Get_Train_Speed(12009))}")
    print(f"j1.assignedTrain->Train_Type = {j1.assignedTrain.Train_Type}")

    print("--- move j2 to the Shatabdi (0..1 keeps only one train) ---")
    assign(shatabdi, j2)
    printTrain(rajdhani)
    printTrain(shatabdi)

    print("--- unassign j3 ---")
    unassign(j3)
    # "nullptr" is printed for an empty link so the output matches the C++ version.
    state = "set" if j3.assignedTrain else "nullptr"
    print(f"j3.assignedTrain is {state}, shatabdi lists {len(shatabdi.assignedJourny)} journey(s)")


if __name__ == "__main__":
    main()
