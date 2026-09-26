#!/usr/bin/env python3
"""Railway Reservation System (RRS) - MCS-217 Session 13.

Console implementation of modules 2 to 5 of the RRS specified in
Sessions 1, 3, 4, 5 and 6:
  2. Train and Schedule Management  (Administrator)
  3. Search and Availability        (Passenger)
  4. Booking                        (Passenger)
  5. Cancellation and Refund        (Passenger)

Standard library only. All data lives in rrs_data.json next to this file.
"""
import json
import os
import random
from datetime import date, datetime, timedelta

DATA_FILE = os.path.join(os.path.dirname(os.path.abspath(__file__)), "rrs_data.json")
CLASSES = ("SL", "3A", "2A", "1A")
BERTHS = ("LB", "MB", "UB", "SL", "SU")
CLERKAGE = 60          # flat clerkage in rupees (business rule, Session 3)
MAX_PASSENGERS = 6     # per PNR (business rule, Session 3)

# ---------------------------------------------------------------- persistence


def load_data():
    """Read rrs_data.json; seed two trains and two schedules on first run."""
    if os.path.exists(DATA_FILE):
        with open(DATA_FILE) as fh:
            return json.load(fh)
    data = {"trains": {}, "schedules": {}, "bookings": {}}
    data["trains"]["12951"] = {
        "name": "Mumbai Rajdhani", "type": "Rajdhani",
        "route": [
            {"station_code": "BCT", "name": "Mumbai Central", "sequence": 1,
             "arrival_time": "--", "departure_time": "17:00", "distance_km": 0},
            {"station_code": "KOTA", "name": "Kota Jn", "sequence": 2,
             "arrival_time": "01:35", "departure_time": "01:40", "distance_km": 869},
            {"station_code": "NDLS", "name": "New Delhi", "sequence": 3,
             "arrival_time": "08:35", "departure_time": "--", "distance_km": 1384},
        ],
        "coaches": {"3A": [2, 64], "2A": [1, 48], "1A": [1, 18]},
        "fares": {"3A": 2.10, "2A": 2.90, "1A": 4.80},
    }
    data["trains"]["12137"] = {
        "name": "Punjab Mail", "type": "Mail",
        "route": [
            {"station_code": "CSMT", "name": "Mumbai CSMT", "sequence": 1,
             "arrival_time": "--", "departure_time": "19:35", "distance_km": 0},
            {"station_code": "BPL", "name": "Bhopal Jn", "sequence": 2,
             "arrival_time": "09:15", "departure_time": "09:25", "distance_km": 837},
            {"station_code": "NDLS", "name": "New Delhi", "sequence": 3,
             "arrival_time": "20:35", "departure_time": "--", "distance_km": 1541},
        ],
        "coaches": {"SL": [3, 72], "3A": [1, 64]},
        "fares": {"SL": 0.60, "3A": 1.60},
    }
    in_10_days = (date.today() + timedelta(days=10)).isoformat()
    for sid, tno in (("S001", "12951"), ("S002", "12137")):
        data["schedules"][sid] = new_schedule(tno, in_10_days, data["trains"][tno])
    save_data(data)
    return data


def save_data(data):
    """Write the whole data dictionary back to rrs_data.json."""
    with open(DATA_FILE, "w") as fh:
        json.dump(data, fh, indent=1)


def new_schedule(train_no, run_date, train):
    """Build a Schedule record with empty seat maps and waitlists per class."""
    return {"train_no": train_no, "run_date": run_date, "status": "SCHEDULED",
            "allocated": {c: {} for c in train["coaches"]},
            "waitlist": {c: [] for c in train["coaches"]}}

# ---------------------------------------------------------------- input helpers


def ask(prompt, check=lambda s: True, error="Invalid value, try again."):
    """Prompt until check(value) is true; returns the stripped string."""
    while True:
        value = input(prompt).strip()
        if value and check(value):
            return value
        print(error)


def ask_int(prompt, lo, hi):
    """Prompt for an integer in the closed range lo..hi."""
    return int(ask(prompt, lambda s: s.isdigit() and lo <= int(s) <= hi,
                   "Enter a number from %d to %d." % (lo, hi)))


def ask_date(prompt):
    """Prompt for a date in YYYY-MM-DD form."""
    def ok(s):
        try:
            date.fromisoformat(s)
            return True
        except ValueError:
            return False
    return ask(prompt, ok, "Use the form YYYY-MM-DD.")

# ---------------------------------------------------------------- domain helpers


def seat_labels(train, cls):
    """All seat labels of a class in allocation order, e.g. 3A1-17."""
    coaches, per_coach = train["coaches"][cls]
    return ["%s%d-%d" % (cls, c, s) for c in range(1, coaches + 1)
            for s in range(1, per_coach + 1)]


def free_seats(data, sched, cls):
    """Seat labels of this class not yet allocated on this schedule."""
    train = data["trains"][sched["train_no"]]
    return [s for s in seat_labels(train, cls) if s not in sched["allocated"][cls]]


def departure(data, sched):
    """Datetime at which the schedule leaves its first station."""
    first = data["trains"][sched["train_no"]]["route"][0]
    return datetime.fromisoformat(sched["run_date"] + " " + first["departure_time"])


def stop_index(train, code):
    """Index of a station code in the train route, or -1."""
    for i, stop in enumerate(train["route"]):
        if stop["station_code"] == code:
            return i
    return -1


def new_pnr(data):
    """Unique 10-digit PNR."""
    while True:
        pnr = str(random.randint(10 ** 9, 10 ** 10 - 1))
        if pnr not in data["bookings"]:
            return pnr


def find_schedules(data, src, dst, run_date):
    """Schedules on run_date whose route has src before dst and not yet departed."""
    found = []
    for sid, sched in sorted(data["schedules"].items()):
        train = data["trains"][sched["train_no"]]
        i, j = stop_index(train, src), stop_index(train, dst)
        if sched["run_date"] == run_date and 0 <= i < j and departure(data, sched) > datetime.now():
            found.append((sid, sched, train, i, j))
    return found


def print_availability(data, sched):
    """One line per class: free seats or waitlist length."""
    for cls in sched["allocated"]:
        free, wl = len(free_seats(data, sched, cls)), len(sched["waitlist"][cls])
        print("   %-3s %s" % (cls, "AVAILABLE %d" % free if free else "WL %d" % (wl + 1)))


def promote_waitlist(data, sched, cls):
    """Move waitlisted bookings of this class to CONFIRMED while seats allow."""
    wl = sched["waitlist"][cls]
    while wl:
        booking = data["bookings"][wl[0]]
        free = free_seats(data, sched, cls)
        if len(free) < len(booking["passengers"]):
            return
        for p, seat in zip(booking["passengers"], free):
            p["seat"] = seat
            sched["allocated"][cls][seat] = wl[0]
        booking["status"] = "CONFIRMED"
        print("Waitlisted PNR %s promoted to CONFIRMED." % wl.pop(0))

# ---------------------------------------------------------------- admin actions


def add_train(data):
    """Admin: add a train with its route stations, coaches and per-km fares."""
    train_no = ask("Train number (5 digits): ", lambda s: s.isdigit() and len(s) == 5)
    if train_no in data["trains"]:
        print("Train %s already exists." % train_no)
        return
    train = {"name": ask("Train name: "), "type": ask("Type (Rajdhani/Mail/Express): "),
             "route": [], "coaches": {}, "fares": {}}
    stops = ask_int("Number of stations on the route (2-20): ", 2, 20)
    for seq in range(1, stops + 1):
        print("Station %d of %d" % (seq, stops))
        train["route"].append({
            "station_code": ask("  code: ").upper(), "name": ask("  name: "), "sequence": seq,
            "arrival_time": "--" if seq == 1 else ask("  arrival HH:MM: "),
            "departure_time": "--" if seq == stops else ask("  departure HH:MM: "),
            "distance_km": 0 if seq == 1 else ask_int("  distance from origin (km): ", 1, 5000)})
    for cls in CLASSES:
        n = ask_int("Coaches of class %s (0-10): " % cls, 0, 10)
        if n:
            train["coaches"][cls] = [n, ask_int("  seats per %s coach (1-80): " % cls, 1, 80)]
            train["fares"][cls] = float(ask("  fare per km for %s (rupees): " % cls,
                                            lambda s: s.replace(".", "", 1).isdigit()))
    data["trains"][train_no] = train
    save_data(data)
    print("Train %s %s added with %d stations." % (train_no, train["name"], stops))


def add_schedule(data):
    """Admin: create a run of an existing train on a given date."""
    list_trains(data)
    train_no = ask("Train number: ", lambda s: s in data["trains"], "No such train.")
    run_date = ask_date("Run date (YYYY-MM-DD): ")
    if any(s["train_no"] == train_no and s["run_date"] == run_date for s in data["schedules"].values()):
        print("That train already runs on %s." % run_date)
        return
    sid = "S%03d" % (len(data["schedules"]) + 1)
    data["schedules"][sid] = new_schedule(train_no, run_date, data["trains"][train_no])
    save_data(data)
    print("Schedule %s created: %s on %s." % (sid, train_no, run_date))


def list_trains(data):
    """Admin: print every train with its route and classes."""
    for train_no, t in sorted(data["trains"].items()):
        stations = " > ".join(s["station_code"] for s in t["route"])
        print("%s %-16s %s  classes: %s" % (train_no, t["name"], stations, ", ".join(t["coaches"])))

# ---------------------------------------------------------------- passenger actions


def search_trains(data):
    """Passenger: list trains between two stations on a date with availability."""
    src, dst = ask("From station code: ").upper(), ask("To station code: ").upper()
    run_date = ask_date("Journey date (YYYY-MM-DD): ")
    found = find_schedules(data, src, dst, run_date)
    if not found:
        print("No trains found for %s to %s on %s." % (src, dst, run_date))
        return
    for sid, sched, train, i, j in found:
        km = train["route"][j]["distance_km"] - train["route"][i]["distance_km"]
        print("%s  %s %s  dep %s  arr %s  %d km" % (sid, sched["train_no"], train["name"],
              train["route"][i]["departure_time"], train["route"][j]["arrival_time"], km))
        print_availability(data, sched)


def check_availability(data):
    """Passenger: seat availability per class for one schedule."""
    sid = ask("Schedule id: ", lambda s: s in data["schedules"], "No such schedule.")
    sched = data["schedules"][sid]
    print("%s %s on %s" % (sched["train_no"], data["trains"][sched["train_no"]]["name"], sched["run_date"]))
    print_availability(data, sched)


def book_ticket(data):
    """Passenger: book up to six passengers, allocate seats, generate PNR."""
    sid = ask("Schedule id: ", lambda s: s in data["schedules"], "No such schedule.")
    sched = data["schedules"][sid]
    train = data["trains"][sched["train_no"]]
    if departure(data, sched) <= datetime.now():
        print("This train has already departed. Booking refused.")
        return
    src = ask("From station code: ", lambda s: stop_index(train, s.upper()) >= 0, "Not on route.").upper()
    dst = ask("To station code: ",
              lambda s: stop_index(train, s.upper()) > stop_index(train, src), "Must be after %s." % src).upper()
    cls = ask("Class (%s): " % "/".join(train["coaches"]), lambda s: s.upper() in train["coaches"]).upper()
    n = ask_int("Number of passengers (1-%d): " % MAX_PASSENGERS, 1, MAX_PASSENGERS)
    passengers = []
    for k in range(1, n + 1):
        passengers.append({"name": ask("Passenger %d name: " % k),
                           "age": ask_int("Passenger %d age: " % k, 1, 120),
                           "gender": ask("Passenger %d gender (M/F/O): " % k, lambda s: s.upper() in "MFO").upper(),
                           "berth_preference": ask("Passenger %d berth preference (LB/MB/UB/SL/SU): " % k,
                                                   lambda s: s.upper() in BERTHS).upper(), "seat": None})
    km = train["route"][stop_index(train, dst)]["distance_km"] - train["route"][stop_index(train, src)]["distance_km"]
    fare = round(train["fares"][cls] * km * n, 2)
    free = free_seats(data, sched, cls)
    status = "CONFIRMED" if len(free) >= n else "WAITLISTED"
    print("Fare: %d km x Rs %.2f/km x %d passengers = Rs %.2f  [%s]" % (km, train["fares"][cls], n, fare, status))
    if ask("Confirm booking (Y/N): ", lambda s: s.upper() in "YN").upper() != "Y":
        print("Booking abandoned.")
        return
    pnr = new_pnr(data)
    if status == "CONFIRMED":
        for p, seat in zip(passengers, free):
            p["seat"] = seat
            sched["allocated"][cls][seat] = pnr
    else:
        sched["waitlist"][cls].append(pnr)
    data["bookings"][pnr] = {"pnr": pnr, "schedule_id": sid, "from_station": src, "to_station": dst,
                             "class": cls, "booking_time": datetime.now().isoformat(timespec="seconds"),
                             "status": status, "total_fare": fare, "passengers": passengers}
    save_data(data)
    print("Booked. PNR %s  status %s" % (pnr, status))
    print_booking(data, pnr)


def cancel_ticket(data):
    """Passenger: cancel by PNR, compute refund, promote waitlist."""
    pnr = ask("PNR: ", lambda s: s in data["bookings"], "No such PNR.")
    booking = data["bookings"][pnr]
    if booking["status"] == "CANCELLED":
        print("PNR %s is already cancelled." % pnr)
        return
    sched = data["schedules"][booking["schedule_id"]]
    hours = (departure(data, sched) - datetime.now()).total_seconds() / 3600
    if booking["status"] == "WAITLISTED":
        refund, rule = booking["total_fare"] - CLERKAGE, "waitlisted, fare minus clerkage"
        sched["waitlist"][booking["class"]].remove(pnr)
    elif hours > 48:
        refund, rule = booking["total_fare"] - CLERKAGE, "more than 48 h before departure"
    elif hours >= 12:
        refund, rule = booking["total_fare"] * 0.5, "between 48 h and 12 h before departure"
    else:
        refund, rule = 0.0, "less than 12 h before departure"
    refund = round(max(refund, 0.0), 2)
    print("Refund: Rs %.2f (%s)" % (refund, rule))
    if ask("Confirm cancellation (Y/N): ", lambda s: s.upper() in "YN").upper() != "Y":
        print("Cancellation abandoned.")
        return
    if booking["status"] == "CONFIRMED":
        for p in booking["passengers"]:
            del sched["allocated"][booking["class"]][p["seat"]]
            p["seat"] = None
    booking["status"] = "CANCELLED"
    booking["refund"] = {"amount": refund, "reason": rule,
                         "processed_at": datetime.now().isoformat(timespec="seconds")}
    promote_waitlist(data, sched, booking["class"])
    save_data(data)
    print("PNR %s cancelled." % pnr)


def pnr_lookup(data):
    """Passenger: show a booking by PNR."""
    print_booking(data, ask("PNR: ", lambda s: s in data["bookings"], "No such PNR."))


def print_booking(data, pnr):
    """Print one booking with its passengers and seats."""
    b = data["bookings"][pnr]
    sched = data["schedules"][b["schedule_id"]]
    print("PNR %s  %s %s  %s  %s > %s  class %s  fare Rs %.2f  %s" % (
        pnr, sched["train_no"], data["trains"][sched["train_no"]]["name"], sched["run_date"],
        b["from_station"], b["to_station"], b["class"], b["total_fare"], b["status"]))
    for p in b["passengers"]:
        print("   %-12s %3d %s  pref %-2s  seat %s" % (p["name"], p["age"], p["gender"],
                                                       p["berth_preference"], p["seat"] or "--"))

# ---------------------------------------------------------------- menus


def run_menu(title, actions, data):
    """Print a numbered menu and dispatch until the user chooses 0."""
    while True:
        print("\n== %s ==" % title)
        for k, (label, _) in enumerate(actions, 1):
            print(" %d. %s" % (k, label))
        print(" 0. Back")
        choice = ask_int("Choice: ", 0, len(actions))
        if choice == 0:
            return
        actions[choice - 1][1](data)


def main():
    """Entry point: role selection."""
    data = load_data()
    admin = [("Add train", add_train), ("Add schedule", add_schedule), ("List trains", list_trains)]
    passenger = [("Search trains", search_trains), ("Check availability", check_availability),
                 ("Book ticket", book_ticket), ("Cancel ticket", cancel_ticket), ("PNR lookup", pnr_lookup)]
    roles = [("Administrator", lambda d: run_menu("Administrator", admin, d)),
             ("Passenger", lambda d: run_menu("Passenger", passenger, d))]
    print("Railway Reservation System (Session 13 build)")
    try:
        run_menu("Main menu", roles, data)
    except EOFError:
        pass
    print("Bye.")


if __name__ == "__main__":
    main()
