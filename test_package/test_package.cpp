#include <fstream>
#include <iostream>
#include "transwarp.h"

namespace tw = transwarp;

double adder(double x, int y) {
    return x + y;
}

int main() {

    // Building the task graph
    auto task1 = tw::make_value_task("something", 13.3);
    auto task2 = tw::make_value_task("something else", 42);
    auto task3 = tw::make_task(tw::consume, "adder", adder, task1, task2);

    // Creating a dot-style graph for visualization
    const auto graph = task3->get_graph();
    std::ofstream("basic_with_three_tasks.dot") << tw::to_string(graph);

    // schedule() can now be called as much as desired. The task graph
    // only has to be built once

    // Parallel execution with 4 threads for independent tasks
    tw::parallel executor{4};

    task3->schedule_all(executor);  // Schedules all tasks for execution
    std::cout << "result = " << task3->get() << std::endl;  // result = 55.3

    // Modifying data input
    task1->set_value(15.8);
    task2->set_value(43);

    task3->schedule_all(executor);  // Re-schedules all tasks for execution
    std::cout << "result = " << task3->get() << std::endl;  // result = 58.8
}