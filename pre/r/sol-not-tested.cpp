#include <iostream>
#include <vector>

using namespace std;

struct Influence {
    double proportion;
    int painting_no;
};

struct Painting {
    Painting() : greatness(0.0), solved(false) {}
    double greatness;
    bool solved;
    vector<Influence> influences;
};

void Input(vector<Painting>* paintings) {
    int N, M;
    cin >> N; cin >> M;

    paintings->resize(N + 1);  // for easier numbering

    for (int i = 1; i <= N; i++) {
        cin >> (*paintings)[i].greatness;
    }

    for (int i = 0; i < M; i++) {
        int a;
        Influence influence;
        cin >> a >> influence.painting_no >> influence.proportion;
        (*paintings)[a].influences.push_back(influence);
    }
}

void ComputeGreatness(Painting* p, vector<Painting>* paintings) {
    if (!p->solved) {
        for (auto& i : p->influences) {
	  Painting& r = paintings->at(i.painting_no);
            ComputeGreatness(&r, paintings);
            p->greatness += i.proportion * r.greatness;
        }
        p->solved = true;
    }
}

void Output(const vector<Painting>& paintings) {
  for (int i = 1; i < paintings.size(); i++) {
    cout << paintings[i].greatness;
    if (i == paintings.size() - 1) {
      cout << endl;
    } else {
      cout << " ";
    }
  }
}

int main() {
    vector<Painting> paintings;
    Input(&paintings);
    
    for (auto& p : paintings) {
        ComputeGreatness(&p, &paintings);
    }

    Output(paintings);
    return 0;
}
