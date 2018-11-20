#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Occupation {
public:
    Occupation(const string& name, const string& occupation) : name_(name), occupation_(occupation) {
    }

    virtual ~Occupation() {
    }

    string Occp() const {
      return occupation_;
    }

    string Name() const {
        return name_;
    }

    ostream& OccupiedHuman() const {
      return cout << Occp() << ". " << Name();
    }

    virtual void Walk(const string& destination) const {
        OccupiedHuman() << " walks to: " << destination << endl;
    }

private:
  const string name_;
  const string occupation_;
};

class Student : public Occupation {
public:
    Student(const string& name, const string& favouriteSong) : Occupation(name, "Student"), favouriteSong_(favouriteSong) {
    }

    void Learn() const {
        OccupiedHuman() << " learns" << endl;
    }

    void SingSong() const {
        OccupiedHuman() << " sings a song: " << favouriteSong_ << endl;
    }

    void Walk(const string& destination) const override {
        Occupation :: Walk(destination);
        SingSong();
    }

public:
    const string favouriteSong_;
};

class Teacher : public Occupation {
public:
    Teacher(const string& name, const string& subject) : Occupation(name, "Teacher"), subject_(subject) {
    }

    void Teach() const {
        OccupiedHuman() << " teaches: " << subject_ << endl;
    }

public:
    const string subject_;
};

class Policeman : public Occupation {
public:
    Policeman(const string& name) : Occupation(name, "Policeman") {
    }

    void Check(const Occupation& o) const {
        OccupiedHuman() << " checks " << o.Occp() << ". " << o.Occp() << "'s name is: " << o.Name() << endl;
    }

};

void VisitPlaces(const Occupation& o, vector<string> places) {
    for (auto p : places) {
        o.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, {"Moscow", "London"});
    p.Check(s);
    VisitPlaces(s, {"Moscow", "London"});
    return 0;
}
