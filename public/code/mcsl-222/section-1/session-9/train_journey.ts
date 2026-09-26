// train_journey.ts -- MCSL-222 Session 9, Q21
// Figure 1.16 (Train Journey -- Train) in TypeScript, no dependencies, as a
// TWO-WAY association: TrainJourney.assignedTrain (0..1) and Train.assignedJourny (0..*).
// Run: node train_journey.ts   (Node 22.18 or later strips the types itself)
"use strict";

// Both boxes in the figure carry a Train_No; the getters compare against it.
interface TrainNumbered {
  readonly Train_No: number;
}

function isTrain(x: TrainNumbered, train_no: number): boolean { return train_no === x.Train_No; }

// -------------------------------------------------------- TrainJourney
class TrainJourney implements TrainNumbered {
  Train_No: number = 0;
  Source_St: string;
  Destination_St: string;
  readonly Journy_Time: number;
  assignedTrain: Train | null = null; // role assignedTrain, multiplicity 0..1

  constructor(src: string, dst: string, hours: number) {
    this.Source_St = src;
    this.Destination_St = dst;
    this.Journy_Time = hours;
  }

  Set_Source_St(source: string): void { this.Source_St = source; }
  Set_Dastination_St(destination: string): void { this.Destination_St = destination; }
  // The figure passes Train_No to the getters, so they answer only for
  // the train this journey is assigned to.
  Get_Source_St(train_no: number): string { return isTrain(this, train_no) ? this.Source_St : "(not this train)"; }
  Get_Journy_Time(train_no: number): number { return isTrain(this, train_no) ? this.Journy_Time : -1; }
}

// --------------------------------------------------------------- Train
class Train implements TrainNumbered {
  readonly Train_No: number;
  Train_Type: string;
  readonly Max_Speed: number;
  readonly assignedJourny: TrainJourney[] = []; // role assignedJourny, multiplicity 0..*

  constructor(no: number, type: string, speed: number) {
    this.Train_No = no;
    this.Train_Type = type;
    this.Max_Speed = speed;
  }

  Get_Train_No(): number { return this.Train_No; }
  Set_Train_Type(trtype: string): void { this.Train_Type = trtype; }
  Get_Train_Speed(train_no: number): number { return isTrain(this, train_no) ? this.Max_Speed : -1; }
}

// ---------------------------------------------- keeping both ends in step
// Both ends change in one place, so a journey can never point at a train
// that does not list it, and vice versa.
function unassign(j: TrainJourney): void {
  const t = j.assignedTrain;
  if (t !== null) {
    t.assignedJourny.splice(t.assignedJourny.indexOf(j), 1);
    j.assignedTrain = null;
    j.Train_No = 0;
  }
}

function assign(t: Train, j: TrainJourney): void {
  unassign(j); // a journey has at most one train (0..1)
  j.assignedTrain = t;
  j.Train_No = t.Train_No;
  t.assignedJourny.push(j);
}

// ---------------------------------------------------------------- main
function printTrain(t: Train): void {
  console.log(`Train ${t.Get_Train_No()} (${t.Train_Type}, ${t.Max_Speed} km/h) runs ${t.assignedJourny.length} journey(s)`);
  for (const j of t.assignedJourny) {
    console.log(`  ${j.Source_St} -> ${j.Destination_St}, ${j.Journy_Time} h, Train_No stored in journey = ${j.Train_No}`);
  }
}

function main(): void {
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
  // assignedTrain is `Train | null`; `!` tells the checker j1 is assigned here.
  console.log(`j1.assignedTrain->Train_Type = ${j1.assignedTrain!.Train_Type}`);

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
