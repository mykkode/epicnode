using namespace std;

#include "../inc/evaluator.hpp"

evaluator::evaluator() {
    jobID = 0;
    exerciseID = 0;
}

void evaluator::dec() {
    sprintf(buffer, "/var/epicnode/jobs/%d/raport.json", jobID);
    fstream in(buffer, fstream::in);
    in >> raport;
}

void evaluator::enc() {
    sprintf(buffer, "/var/epicnode/jobs/%d/raport.json", jobID);
    fstream out(buffer, fstream::out);
    out << raport;
}

void evaluator::setValues(int job, int exercise) {
    jobID = job;
    exerciseID = exercise;
}

int evaluator::evaluate() {
    string textBaseString = raport["testBase"];
    strcpy(testBase, textBaseString.c_str());
    for (int thisTest = 0; thisTest < raport["numberOfTests"]; thisTest++) {
        bool failed = 0;
        sprintf(buffer, "%s%d", testBase, thisTest);
        if (raport["tests"][buffer]["executed"] && !raport["tests"][buffer]["halted"]) {
            sprintf(buffer, "/var/epicnode/ex/%d/ref/%s%d.ref", exerciseID, testBase, thisTest);
            ifstream reference(buffer);
            sprintf(buffer, "/var/epicnode/jobs/%d/output/%s%d.out", jobID, testBase, thisTest);
            ifstream output(buffer);
            int i, j;
            while (reference >> i) {
                if (output >> j) {
                    if (i != j) {

                        failed = 1;
                        break;
                    }
                } else {
                    failed = 1;
                }
            }
            sprintf(buffer, "%s%d", testBase, thisTest);
            if (failed) {
                raport["tests"][buffer]["passed"] = 0;
            } else {
                if (output >> j) {
                    raport["tests"][buffer]["passed"] = false;
                } else {
                    raport["tests"][buffer]["passed"] = true;
                }

            }
        }
    }
}

