#include <process.h>

#include <cstdlib>
#include <ctime>
#include <random>
#include <sstream>
#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

int Process::lastPid = 0;

Process Process::generate() {
    int pid = ++lastPid;
    int cpu = gen_cpu();
    int mem = gen_mem();

    return {pid, cpu, mem};
}

int Process::gen_int(int min, int max) {
    std::random_device rd;
    std::default_random_engine engine(rd());
    std::uniform_real_distribution<int> distribution(min, max);
    return distribution(engine);
}

Process Process::from_tuple(const ProcessTuple &t) {
    return {std::get<0>(t), std::get<1>(t), std::get<2>(t)};
}

ProcessTuple Process::as_tuple() {
    return {_pid, _cpu, _mem};
}

std::string Process::to_string() {
    std::stringstream ss;
    ss << _pid << "," << _cpu << "," << _mem;
    return ss.str();
}

Process Process::from_string(const std::string &str) {
    std::vector<std::string> tokens;
    boost::split(tokens, str, boost::is_any_of(","));

    ProcessTuple tuple = std::make_tuple(
            std::stoi(tokens[0]),
            std::stoi(tokens[1]),
            std::stoi(tokens[2])
    );

    return Process::from_tuple(tuple);
}

void Process::read_from_stdin(std::vector<Process> &out_procs) {
    out_procs.clear();
    for (std::string raw; std::getline(std::cin, raw, ';');) {
        if (raw == "\n" || raw.empty()) { // newline means done -- empty string is not likely
            break;
        }
        out_procs.push_back(Process::from_string(raw));
    }
}