////////////////////////////////
/// usage : 1.	data that identifies a guillotine cut problem and its solution.
/// 
/// note  : 1.	
////////////////////////////////

#ifndef SMART_SZX_GRAPH_COLORING_PROBLEM_H
#define SMART_SZX_GRAPH_COLORING_PROBLEM_H


#include "Config.h"

#include <iostream>
#include <fstream>
#include <sstream>

#include "Common.h"
#include "PbReader.h"
#include "GraphColoring.pb.h"


namespace szx {

class Problem {
    #pragma region Type
public:
    using Input = pb::GraphColoring::Input;
    
    struct Output {
        auto nodecolors() const { return output.nodecolors(); }
        auto nodecolors(ID n) const { return output.nodecolors(n); }
        auto mutable_nodecolors() { return output.mutable_nodecolors(); }

        ID colorNum = 0;
        pb::GraphColoring::Output output;
    };
    #pragma endregion Type

    #pragma region Constant
public:
    enum {
        MaxNodeNum = 5000,
        MaxColorNum = 5000,

        InvalidId = -1,
    };
    #pragma endregion Constant

    #pragma region Constructor
public:
    #pragma endregion Constructor

    #pragma region Method
public:
    static bool loadInput(Input &input, const String &path) { return pb::load(path, input); }
    static bool saveOutput(const Output &output, const String &path, pb::Submission &submission) {
        std::ofstream ofs(path);
        if (!ofs.is_open()) { return false; }

        // TODO[0]: fill the submission information.
        submission.set_author("szx");
        submission.set_algorithm("rand");
        submission.set_cpu("Intel Core i5-7400 3.00GHz");
        submission.set_ram("16G 2400MHz");
        submission.set_language("C++");
        submission.set_compiler("VS2017");
        submission.set_os("Windows 10");
        submission.set_problem("GraphColoring");

        ofs << protobufToJson(submission, false) << std::endl << protobufToJson(output.output);
        return true;
    }
    #pragma endregion Method

    #pragma region Field
public:
    #pragma endregion Field
}; // Problem

}


#endif // SMART_SZX_GRAPH_COLORING_PROBLEM_H
