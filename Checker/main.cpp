#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>
#include <limits>
#include <set>

#include "../Solver/PbReader.h"
#include "../Solver/GraphColoring.pb.h"


using namespace std;
using namespace pb;


int main(int argc, char *argv[]) {
    enum CheckerFlag {
        IoError = 0x0,
        FormatError = 0x1,
        ColorConflictError = 0x2
    };

    static constexpr double GeometricalGraphObjScale = 100;

    string inputPath;
    string outputPath;

    if (argc > 1) {
        inputPath = argv[1];
    } else {
        cerr << "input path: " << flush;
        cin >> inputPath;
    }

    if (argc > 2) {
        outputPath = argv[2];
    } else {
        cerr << "output path: " << flush;
        cin >> outputPath;
    }

    pb::GraphColoring::Input input;
    if (!load(inputPath, input)) { return ~CheckerFlag::IoError; }

    pb::GraphColoring::Output output;
    ifstream ifs(outputPath);
    if (!ifs.is_open()) { return ~CheckerFlag::IoError; }
    string submission;
    getline(ifs, submission); // skip the first line.
    ostringstream oss;
    oss << ifs.rdbuf();
    jsonToProtobuf(oss.str(), output);

    if (output.nodecolors().size() != input.graph().nodenum()) { return ~CheckerFlag::FormatError; }

    // check solution.
    int error = 0;
    // check constraints.
    for (auto e = input.graph().edges().begin(); e != input.graph().edges().end(); ++e) {
        if (output.nodecolors(e->src()) == output.nodecolors(e->dst())) { error |= CheckerFlag::ColorConflictError; }
    }
    // check objective.
    set<int> colors;
    for (auto n = output.nodecolors().begin(); n != output.nodecolors().end(); ++n) {
        colors.insert(*n);
    }
    int colorNum = static_cast<int>(colors.size());

    int returnCode = (error == 0) ? colorNum : ~error;
    cout << ((error == 0) ? colorNum : returnCode) << endl;
    return returnCode;
}
