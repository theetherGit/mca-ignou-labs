// train_journey.js -- MCSL-222 Session 9, Q21
// Figure 1.16 (Train Journey -- Train) in Node.js, no dependencies, as a
// TWO-WAY association: TrainJourney.assignedTrain (0..1) and Train.assignedJourny (0..*).
// Run: node train_journey.js
"use strict";

// -------------------------------------------------------- TrainJourney
class TrainJourney {
  constructor(src, dst, hours) {
    this.Train_No = 0;
    this.Source_St = src;
    this.Destination_St = dst;
    this.Journy_Time = hours;
    this.assignedTrain = null; // role assignedTrain, multiplicity 0..1
  }

  Set_Source_St(source) { this.Source_St = source; }
  Set_Dastination_St(destination) { this.Destination_St = destination; }
  // The figure passes Train_No to the getters, so they answer only for
  // the train this journey is assigned to.
  Get_Source_St(train_no) { return train_no === this.Train_No ? this.Source_St : "(not this train)"; }
  Get_Journy_Time(train_no) { return train_no === this.Train_No ? this.Journy_Time : -1; }
}

// --------------------------------------------------------------- Train
class Train {
  constructor(no, type, speed) {
    this.Train_No = no;
    this.Train_Type = type;
    this.Max_Speed = speed;
    this.assignedJourny = []; // role assignedJourny, multiplicity 0..*
  }

  Get_Train_No() { return this.Train_No; }
  Set_Train_Type(trtype) { this.Train_Type = trtype; }
  Get_Train_Speed(train_no) { return train_no === this.Train_No ? this.Max_Speed : -1; }
}

// ---------------------------------------------- keeping both ends in step
// Both ends change in one place, so a journey can never point at a train
// that does not list it, and vice versa.
function unassign(j) {
  const t = j.assignedTrain;
  if (t !== null) {
    t.assignedJourny.splice(t.assignedJourny.indexOf(j), 1);
    j.assignedTrain = null;
    j.Train_No = 0;
  }
}

function assign(t, j) {
  unassign(j); // a journey has at most one train (0..1)
  j.assignedTrain = t;
  j.Train_No = t.Train_No;
  t.assignedJourny.push(j);
}

// ---------------------------------------------------------------- main
function printTrain(t) {
  console.log(`Train ${t.Get_Train_No()} (${t.Train_Type}, ${t.Max_Speed} km/h) runs ${t.assignedJourny.length} journey(s)`);
  for (const j of t.assignedJourny) {
    console.log(`  ${j.Source_St} -> ${j.Destination_St}, ${j.Journy_Time} h, Train_No stored in journey = ${j.Train_No}`);
  }
}

function main() {
  const rajdhani = new Train(12951, "Rajdhani", 130.0);
  const shatabdi = new Train(12009, "Shatabdi", 150.0);

  const j1 = new TrainJourney("Mumbai", "Delhi", 15.5);
  const j2 = new TrainJourney("Delhi", "Mumbai", 15.75);
  const j3 = new TrainJourney("Mumbai", "Ahmedabad", 6.25);

  assign(rajdhani, j1);
  assign(rajdhani, j2);
  assign(shatabdi, j3);

  console.log("--- after assignment ---");
  printTrain(rajdhani);
  printTrain(shatabdi);

  console.log("--- operations from the figure ---");
  j3.Set_Source_St("Mumbai Central");
  j3.Set_Dastination_St("Ahmedabad Jn");
  shatabdi.Set_Train_Type("Shatabdi Express");
  console.log(`j3.Get_Source_St(12009) = ${j3.Get_Source_St(12009)}`);
  console.log(`j3.Get_Source_St(12951) = ${j3.Get_Source_St(12951)}`);
  console.log(`j3.Get_Journy_Time(12009) = ${j3.Get_Journy_Time(12009)}`);
  console.log(`shatabdi.Get_Train_Speed(12009) = ${shatabdi.Get_Train_Speed(12009)}`);
  console.log(`j1.assignedTrain->Train_Type = ${j1.assignedTrain.Train_Type}`);

  console.log("--- move j2 to the Shatabdi (0..1 keeps only one train) ---");
  assign(shatabdi, j2);
  printTrain(rajdhani);
  printTrain(shatabdi);

  console.log("--- unassign j3 ---");
  unassign(j3);
  // "nullptr" is printed for an empty link so the output matches the C++ version.
  console.log(`j3.assignedTrain is ${j3.assignedTrain ? "set" : "nullptr"}, shatabdi lists ${shatabdi.assignedJourny.length} journey(s)`);
}

main();
