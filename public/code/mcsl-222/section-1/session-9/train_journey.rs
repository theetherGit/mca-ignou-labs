// train_journey.rs -- MCSL-222 Session 9, Q21
// Figure 1.16 (Train Journey -- Train) in Rust 2021, standard library only, as a
// TWO-WAY association: TrainJourney.assignedTrain (0..1) and Train.assignedJourny (0..*).
// Ownership: Rc<RefCell<T>>; Train.assignedJourny holds Rc links and TrainJourney.assignedTrain holds a Weak back link, so the two-way link is not an Rc cycle.
// Build: rustc -O --edition 2021 train_journey.rs && ./train_journey
#![allow(non_snake_case)] // attribute and operation names are kept exactly as in the figure

use std::cell::RefCell;
use std::rc::{Rc, Weak};

type Ref<T> = Rc<RefCell<T>>;

fn new_ref<T>(x: T) -> Ref<T> {
    Rc::new(RefCell::new(x))
}

// -------------------------------------------------------- TrainJourney
struct TrainJourney {
    Train_No: i32,
    Source_St: String,
    Destination_St: String,
    Journy_Time: f32,
    assignedTrain: Option<Weak<RefCell<Train>>>, // role assignedTrain, multiplicity 0..1
}

impl TrainJourney {
    fn new(src: &str, dst: &str, hours: f32) -> Ref<TrainJourney> {
        new_ref(TrainJourney {
            Train_No: 0,
            Source_St: src.into(),
            Destination_St: dst.into(),
            Journy_Time: hours,
            assignedTrain: None,
        })
    }

    fn Set_Source_St(&mut self, source: &str) {
        self.Source_St = source.into();
    }
    fn Set_Dastination_St(&mut self, destination: &str) {
        self.Destination_St = destination.into();
    }
    // The figure passes Train_No to the getters, so they answer only for
    // the train this journey is assigned to.
    fn Get_Source_St(&self, train_no: i32) -> String {
        if train_no == self.Train_No { self.Source_St.clone() } else { "(not this train)".into() }
    }
    fn Get_Journy_Time(&self, train_no: i32) -> f32 {
        if train_no == self.Train_No { self.Journy_Time } else { -1.0 }
    }
    // Follows the Weak back link; None when unassigned.
    fn train(&self) -> Option<Ref<Train>> {
        self.assignedTrain.as_ref().and_then(Weak::upgrade)
    }
}

// --------------------------------------------------------------- Train
struct Train {
    Train_No: i32,
    Train_Type: String,
    Max_Speed: f32,
    assignedJourny: Vec<Ref<TrainJourney>>, // role assignedJourny, multiplicity 0..*
}

impl Train {
    fn new(no: i32, ttype: &str, speed: f32) -> Ref<Train> {
        new_ref(Train { Train_No: no, Train_Type: ttype.into(), Max_Speed: speed, assignedJourny: Vec::new() })
    }

    fn Get_Train_No(&self) -> i32 {
        self.Train_No
    }
    fn Set_Train_Type(&mut self, trtype: &str) {
        self.Train_Type = trtype.into();
    }
    fn Get_Train_Speed(&self, train_no: i32) -> f32 {
        if train_no == self.Train_No { self.Max_Speed } else { -1.0 }
    }
}

// ---------------------------------------------- keeping both ends in step
// Both ends change in one place, so a journey can never point at a train
// that does not list it, and vice versa.
fn unassign(j: &Ref<TrainJourney>) {
    let old = j.borrow().train();
    if let Some(t) = old {
        t.borrow_mut().assignedJourny.retain(|x| !Rc::ptr_eq(x, j));
        let mut jj = j.borrow_mut();
        jj.assignedTrain = None;
        jj.Train_No = 0;
    }
}

fn assign(t: &Ref<Train>, j: &Ref<TrainJourney>) {
    unassign(j); // a journey has at most one train (0..1)
    let mut jj = j.borrow_mut();
    jj.assignedTrain = Some(Rc::downgrade(t));
    jj.Train_No = t.borrow().Train_No;
    t.borrow_mut().assignedJourny.push(Rc::clone(j));
}

// ---------------------------------------------------------------- main
fn print_train(t: &Train) {
    println!(
        "Train {} ({}, {} km/h) runs {} journey(s)",
        t.Get_Train_No(),
        t.Train_Type,
        t.Max_Speed,
        t.assignedJourny.len()
    );
    for j in &t.assignedJourny {
        let j = j.borrow();
        println!(
            "  {} -> {}, {} h, Train_No stored in journey = {}",
            j.Source_St, j.Destination_St, j.Journy_Time, j.Train_No
        );
    }
}

fn main() {
    let rajdhani = Train::new(12951, "Rajdhani", 130.0);
    let shatabdi = Train::new(12009, "Shatabdi", 150.0);

    let j1 = TrainJourney::new("Mumbai", "Delhi", 15.5);
    let j2 = TrainJourney::new("Delhi", "Mumbai", 15.75);
    let j3 = TrainJourney::new("Mumbai", "Ahmedabad", 6.25);

    assign(&rajdhani, &j1);
    assign(&rajdhani, &j2);
    assign(&shatabdi, &j3);

    println!("--- after assignment ---");
    print_train(&rajdhani.borrow());
    print_train(&shatabdi.borrow());

    println!("--- operations from the figure ---");
    j3.borrow_mut().Set_Source_St("Mumbai Central");
    j3.borrow_mut().Set_Dastination_St("Ahmedabad Jn");
    shatabdi.borrow_mut().Set_Train_Type("Shatabdi Express");
    println!("j3.Get_Source_St(12009) = {}", j3.borrow().Get_Source_St(12009));
    println!("j3.Get_Source_St(12951) = {}", j3.borrow().Get_Source_St(12951));
    println!("j3.Get_Journy_Time(12009) = {}", j3.borrow().Get_Journy_Time(12009));
    println!("shatabdi.Get_Train_Speed(12009) = {}", shatabdi.borrow().Get_Train_Speed(12009));
    let t1 = j1.borrow().train().unwrap();
    println!("j1.assignedTrain->Train_Type = {}", t1.borrow().Train_Type);

    println!("--- move j2 to the Shatabdi (0..1 keeps only one train) ---");
    assign(&shatabdi, &j2);
    print_train(&rajdhani.borrow());
    print_train(&shatabdi.borrow());

    println!("--- unassign j3 ---");
    unassign(&j3);
    // "nullptr" is printed for an empty link so the output matches the C++ version.
    println!(
        "j3.assignedTrain is {}, shatabdi lists {} journey(s)",
        if j3.borrow().assignedTrain.is_some() { "set" } else { "nullptr" },
        shatabdi.borrow().assignedJourny.len()
    );
}
