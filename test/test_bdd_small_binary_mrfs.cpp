#include "bdd_solver.h"
#include <vector>
#include <string>
#include <iostream>
#include "test.h"

using namespace LPMP;

void test_problem(const std::string input_string, const double expected_lb, std::vector<std::string> args)
{
	for (auto it = args.begin(); it != args.end(); it++)
		std::cout << *it << " " << std::flush;
	std::cout << std::endl;
	args.push_back("-t");
	args.push_back("1e-16");
	args.push_back("-p");
    args.push_back("--lp_input_string");
    args.push_back(input_string);
    bdd_solver solver(args);
    const double initial_lb = solver.lower_bound();
    solver.solve();
    const double lb = solver.lower_bound();

    test(std::abs(lb - expected_lb) <= 1e-01);

    solver.round();
}


const char * short_chain = 
R"(Minimize
2 mu_1_0 + 1 mu_1_1 - 1 mu_2_0 + 0 mu_2_1
+ 1 mu_00 + 2 mu_10 + 1 mu_01 + 0 mu_11
Subject To
mu_1_0 + mu_1_1 = 1
mu_2_0 + mu_2_1 = 1
mu_00 + mu_10 + mu_01 + mu_11 = 1
mu_1_0 - mu_00 - mu_01 = 0
mu_1_1 - mu_10 - mu_11 = 0
mu_2_0 - mu_00 - mu_10 = 0
mu_2_1 - mu_01 - mu_11 = 0
End)";

const char * short_chain_shuffled = 
R"(Minimize
+ 1 mu_2_1 + 1 mu_10 + 0 mu_1_1 + 0 mu_11
-1 mu_1_0 + 1 mu_00 + 2 mu_01 + 2 mu_2_0
Subject To
mu_1_0 + mu_1_1 = 1
mu_2_0 + mu_2_1 = 1
mu_00 + mu_10 + mu_01 + mu_11 = 1
mu_1_0 - mu_00 - mu_01 = 0
mu_1_1 - mu_10 - mu_11 = 0
mu_2_0 - mu_00 - mu_10 = 0
mu_2_1 - mu_01 - mu_11 = 0
End)";

const char * long_chain = 
R"(Minimize
2 mu_0_0 - 1 mu_0_1 + 3 mu_1_0 - 1 mu_1_1
+ 3 mu_2_0 + 2 mu_2_1 - 1 mu_3_0 - 2 mu_3_1
- 2 mu_4_0 - 1 mu_4_1 + 1 mu_5_0 - 1 mu_5_1
+ 1 mu_6_0 + 1 mu_6_1 - 3 mu_7_0 + 2 mu_7_1
+ 0 mu_8_0 + 2 mu_8_1
+ 1 mu_01_00 - 2 mu_01_01 + 2 mu_01_10 - 1 mu_01_11
+ 0 mu_12_00 - 1 mu_12_01 + 1 mu_12_10 + 0 mu_12_11
- 1 mu_23_00 + 2 mu_23_01 + 1 mu_23_10 - 2 mu_23_11
+ 2 mu_34_00 + 0 mu_34_01 + 2 mu_34_10 + 2 mu_34_11
+ 1 mu_45_00 - 2 mu_45_01 - 3 mu_45_10 - 1 mu_45_11
- 2 mu_56_00 + 0 mu_56_01 + 1 mu_56_10 + 3 mu_56_11
- 1 mu_67_00 - 2 mu_67_01 - 1 mu_67_10 - 1 mu_67_11
+ 2 mu_78_00 + 0 mu_78_01 + 2 mu_78_10 + 3 mu_78_11
Subject To
mu_0_0 + mu_0_1 = 1
mu_1_0 + mu_1_1 = 1
mu_2_0 + mu_2_1 = 1
mu_3_0 + mu_3_1 = 1
mu_4_0 + mu_4_1 = 1
mu_5_0 + mu_5_1 = 1
mu_6_0 + mu_6_1 = 1
mu_7_0 + mu_7_1 = 1
mu_8_0 + mu_8_1 = 1
mu_01_00 + mu_01_10 + mu_01_01 + mu_01_11 = 1
mu_12_00 + mu_12_10 + mu_12_01 + mu_12_11 = 1
mu_23_00 + mu_23_10 + mu_23_01 + mu_23_11 = 1
mu_34_00 + mu_34_10 + mu_34_01 + mu_34_11 = 1
mu_45_00 + mu_45_10 + mu_45_01 + mu_45_11 = 1
mu_56_00 + mu_56_10 + mu_56_01 + mu_56_11 = 1
mu_67_00 + mu_67_10 + mu_67_01 + mu_67_11 = 1
mu_78_00 + mu_78_10 + mu_78_01 + mu_78_11 = 1
mu_0_0 - mu_01_00 - mu_01_01 = 0
mu_0_1 - mu_01_10 - mu_01_11 = 0
mu_1_0 - mu_01_00 - mu_01_10 = 0
mu_1_1 - mu_01_01 - mu_01_11 = 0
mu_1_0 - mu_12_00 - mu_12_01 = 0
mu_1_1 - mu_12_10 - mu_12_11 = 0
mu_2_0 - mu_12_00 - mu_12_10 = 0
mu_2_1 - mu_12_01 - mu_12_11 = 0
mu_2_0 - mu_23_00 - mu_23_01 = 0
mu_2_1 - mu_23_10 - mu_23_11 = 0
mu_3_0 - mu_23_00 - mu_23_10 = 0
mu_3_1 - mu_23_01 - mu_23_11 = 0
mu_3_0 - mu_34_00 - mu_34_01 = 0
mu_3_1 - mu_34_10 - mu_34_11 = 0
mu_4_0 - mu_34_00 - mu_34_10 = 0
mu_4_1 - mu_34_01 - mu_34_11 = 0
mu_4_0 - mu_45_00 - mu_45_01 = 0
mu_4_1 - mu_45_10 - mu_45_11 = 0
mu_5_0 - mu_45_00 - mu_45_10 = 0
mu_5_1 - mu_45_01 - mu_45_11 = 0
mu_5_0 - mu_56_00 - mu_56_01 = 0
mu_5_1 - mu_56_10 - mu_56_11 = 0
mu_6_0 - mu_56_00 - mu_56_10 = 0
mu_6_1 - mu_56_01 - mu_56_11 = 0
mu_6_0 - mu_67_00 - mu_67_01 = 0
mu_6_1 - mu_67_10 - mu_67_11 = 0
mu_7_0 - mu_67_00 - mu_67_10 = 0
mu_7_1 - mu_67_01 - mu_67_11 = 0
mu_7_0 - mu_78_00 - mu_78_01 = 0
mu_7_1 - mu_78_10 - mu_78_11 = 0
mu_8_0 - mu_78_00 - mu_78_10 = 0
mu_8_1 - mu_78_01 - mu_78_11 = 0
End)";

const char * grid_graph_3x3 = 
R"(Minimize
2 mu_0_0 - 1 mu_0_1 + 3 mu_1_0 - 1 mu_1_1
+ 3 mu_2_0 + 2 mu_2_1 - 1 mu_3_0 - 2 mu_3_1
- 2 mu_4_0 - 1 mu_4_1 + 3 mu_5_0 - 1 mu_5_1
+ 1 mu_6_0 + 1 mu_6_1 - 3 mu_7_0 + 2 mu_7_1
+ 0 mu_8_0 + 2 mu_8_1
+ 1 mu_01_00 - 2 mu_01_01 + 2 mu_01_10 - 1 mu_01_11
+ 0 mu_12_00 + 1 mu_12_01 + 1 mu_12_10 + 0 mu_12_11
- 1 mu_03_00 + 2 mu_03_01 + 0 mu_03_10 - 2 mu_03_11
+ 2 mu_14_00 + 0 mu_14_01 + 2 mu_14_10 + 2 mu_14_11
+ 1 mu_25_00 - 2 mu_25_01 - 3 mu_25_10 - 1 mu_25_11
+ 0 mu_34_00 + 1 mu_34_01 + 1 mu_34_10 + 1 mu_34_11
- 1 mu_45_00 - 2 mu_45_01 + 4 mu_45_10 - 2 mu_45_11
- 2 mu_36_00 + 0 mu_36_01 + 1 mu_36_10 + 3 mu_36_11
+ 3 mu_47_00 - 2 mu_47_01 - 2 mu_47_10 - 1 mu_47_11
+ 0 mu_58_00 + 1 mu_58_01 + 1 mu_58_10 + 1 mu_58_11
- 1 mu_67_00 + 2 mu_67_01 - 1 mu_67_10 - 1 mu_67_11
+ 2 mu_78_00 + 0 mu_78_01 + 2 mu_78_10 + 2 mu_78_11
Subject To
mu_0_0 + mu_0_1 = 1
mu_1_0 + mu_1_1 = 1
mu_2_0 + mu_2_1 = 1
mu_3_0 + mu_3_1 = 1
mu_4_0 + mu_4_1 = 1
mu_5_0 + mu_5_1 = 1
mu_6_0 + mu_6_1 = 1
mu_7_0 + mu_7_1 = 1
mu_8_0 + mu_8_1 = 1
mu_01_00 + mu_01_10 + mu_01_01 + mu_01_11 = 1
mu_12_00 + mu_12_10 + mu_12_01 + mu_12_11 = 1
mu_03_00 + mu_03_10 + mu_03_01 + mu_03_11 = 1
mu_14_00 + mu_14_10 + mu_14_01 + mu_14_11 = 1
mu_25_00 + mu_25_10 + mu_25_01 + mu_25_11 = 1
mu_34_00 + mu_34_10 + mu_34_01 + mu_34_11 = 1
mu_45_00 + mu_45_10 + mu_45_01 + mu_45_11 = 1
mu_36_00 + mu_36_10 + mu_36_01 + mu_36_11 = 1
mu_47_00 + mu_47_10 + mu_47_01 + mu_47_11 = 1
mu_58_00 + mu_58_10 + mu_58_01 + mu_58_11 = 1
mu_67_00 + mu_67_10 + mu_67_01 + mu_67_11 = 1
mu_78_00 + mu_78_10 + mu_78_01 + mu_78_11 = 1
mu_0_0 - mu_01_00 - mu_01_01 = 0
mu_0_1 - mu_01_10 - mu_01_11 = 0
mu_0_0 - mu_03_00 - mu_03_01 = 0
mu_0_1 - mu_03_10 - mu_03_11 = 0
mu_1_0 - mu_01_00 - mu_01_10 = 0
mu_1_1 - mu_01_01 - mu_01_11 = 0
mu_1_0 - mu_12_00 - mu_12_01 = 0
mu_1_1 - mu_12_10 - mu_12_11 = 0
mu_1_0 - mu_14_00 - mu_14_01 = 0
mu_1_1 - mu_14_10 - mu_14_11 = 0
mu_2_0 - mu_12_00 - mu_12_10 = 0
mu_2_1 - mu_12_01 - mu_12_11 = 0
mu_2_0 - mu_25_00 - mu_25_01 = 0
mu_2_1 - mu_25_10 - mu_25_11 = 0
mu_3_0 - mu_03_00 - mu_03_10 = 0
mu_3_1 - mu_03_01 - mu_03_11 = 0
mu_3_0 - mu_34_00 - mu_34_01 = 0
mu_3_1 - mu_34_10 - mu_34_11 = 0
mu_3_0 - mu_36_00 - mu_36_01 = 0
mu_3_1 - mu_36_10 - mu_36_11 = 0
mu_4_0 - mu_14_00 - mu_14_10 = 0
mu_4_1 - mu_14_01 - mu_14_11 = 0
mu_4_0 - mu_34_00 - mu_34_10 = 0
mu_4_1 - mu_34_01 - mu_34_11 = 0
mu_4_0 - mu_45_00 - mu_45_01 = 0
mu_4_1 - mu_45_10 - mu_45_11 = 0
mu_4_0 - mu_47_00 - mu_47_01 = 0
mu_4_1 - mu_47_10 - mu_47_11 = 0
mu_5_0 - mu_25_00 - mu_25_10 = 0
mu_5_1 - mu_25_01 - mu_25_11 = 0
mu_5_0 - mu_45_00 - mu_45_10 = 0
mu_5_1 - mu_45_01 - mu_45_11 = 0
mu_5_0 - mu_58_00 - mu_58_01 = 0
mu_5_1 - mu_58_10 - mu_58_11 = 0
mu_6_0 - mu_36_00 - mu_36_10 = 0
mu_6_1 - mu_36_01 - mu_36_11 = 0
mu_6_0 - mu_67_00 - mu_67_01 = 0
mu_6_1 - mu_67_10 - mu_67_11 = 0
mu_7_0 - mu_47_00 - mu_47_10 = 0
mu_7_1 - mu_47_01 - mu_47_11 = 0
mu_7_0 - mu_67_00 - mu_67_10 = 0
mu_7_1 - mu_67_01 - mu_67_11 = 0
mu_7_0 - mu_78_00 - mu_78_01 = 0
mu_7_1 - mu_78_10 - mu_78_11 = 0
mu_8_0 - mu_58_00 - mu_58_10 = 0
mu_8_1 - mu_58_01 - mu_58_11 = 0
mu_8_0 - mu_78_00 - mu_78_10 = 0
mu_8_1 - mu_78_01 - mu_78_11 = 0
End)";


int main(int argc, char** arv)
{
	std::cout << "--- Short chain shuffled ---" << std::endl;

	test_problem(short_chain_shuffled, 1.0, {"-s", "mma_vec", "-o", "input", "--max_iter", "5"});
    return 0;
	test_problem(short_chain_shuffled, 1.0, {"-s", "mma_vec", "-o", "bfs", "--max_iter", "5"});
	test_problem(short_chain_shuffled, 1.0, {"-s", "mma_vec", "-o", "cuthill", "--max_iter", "5"});
	// // test_problem(short_chain_shuffled, 1.0, {"-s", "mma", "-o", "mindegree", "--max_iter", "5"});
	// test_problem(short_chain_shuffled, 1.0, {"-s", "mma_srmp", "-o", "input", "--max_iter", "5"});
	// // test_problem(short_chain_shuffled, 1.0, {"-s", "mma_srmp", "-o", "bfs", "--max_iter", "5"});
	// test_problem(short_chain_shuffled, 1.0, {"-s", "mma_srmp", "-o", "cuthill", "--max_iter", "5"});
	// // test_problem(short_chain_shuffled, 1.0, {"-s", "mma_srmp", "-o", "mindegree", "--max_iter", "5"});
	// test_problem(short_chain_shuffled, 1.0, {"-s", "mma_agg", "-o", "input", "--max_iter", "5"});
	// // test_problem(short_chain_shuffled, 1.0, {"-s", "mma_agg", "-o", "bfs", "--max_iter", "5"});
	// test_problem(short_chain_shuffled, 1.0, {"-s", "mma_agg", "-o", "cuthill", "--max_iter", "5"});
	// // test_problem(short_chain_shuffled, 1.0, {"-s", "mma_agg", "-o", "mindegree", "--max_iter", "5"});

	std::cout << "--- Long chain ---" << std::endl;

	// test_problem(long_chain, -9.0, {"-s", "mma", "-o", "input", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "mma", "-o", "bfs", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "mma", "-o", "cuthill", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "mma", "-o", "mindegree", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "mma_srmp", "-o", "input", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "mma_srmp", "-o", "bfs", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "mma_srmp", "-o", "cuthill", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "mma_srmp", "-o", "mindegree", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "mma_agg", "-o", "input", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "mma_agg", "-o", "bfs", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "mma_agg", "-o", "cuthill", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "mma_agg", "-o", "mindegree", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "anisotropic_mma", "-o", "input", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "anisotropic_mma", "-o", "bfs", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "anisotropic_mma", "-o", "cuthill", "--max_iter", "10"});
	// test_problem(long_chain, -9.0, {"-s", "anisotropic_mma", "-o", "mindegree", "--max_iter", "10"});

	std::cout << "--- Grid graph ---" << std::endl;

	// test_problem(grid_graph_3x3, -8.0, {"-s", "mma_vec", "-o", "input", "--max_iter", "20"});
	// test_problem(grid_graph_3x3, -8.0, {"-s", "mma", "-o", "bfs", "--max_iter", "20"});
	// test_problem(grid_graph_3x3, -8.0, {"-s", "mma_vec", "-o", "cuthill", "--max_iter", "20"});
	// test_problem(grid_graph_3x3, -8.0, {"-s", "mma", "-o", "mindegree", "--max_iter", "20"});
	test_problem(grid_graph_3x3, -8.0, {"-s", "mma_srmp", "-o", "input", "--max_iter", "20"});
	// test_problem(grid_graph_3x3, -8.0, {"-s", "mma_srmp", "-o", "bfs", "--max_iter", "20"});
	test_problem(grid_graph_3x3, -8.0, {"-s", "mma_srmp", "-o", "cuthill", "--max_iter", "20"});
	// test_problem(grid_graph_3x3, -8.0, {"-s", "mma_srmp", "-o", "mindegree", "--max_iter", "20"});
	test_problem(grid_graph_3x3, -8.0, {"-s", "mma_agg", "-o", "input", "--max_iter", "20"});
	// test_problem(grid_graph_3x3, -8.0, {"-s", "mma_agg", "-o", "bfs", "--max_iter", "20"});
	test_problem(grid_graph_3x3, -8.0, {"-s", "mma_agg", "-o", "cuthill", "--max_iter", "20"});
	// test_problem(grid_graph_3x3, -8.0, {"-s", "mma_agg", "-o", "mindegree", "--max_iter", "20"});
	// test_problem(grid_graph_3x3, -8.0, {"-s", "anisotropic_mma", "-o", "input", "--max_iter", "20"});
	// test_problem(grid_graph_3x3, -8.0, {"-s", "anisotropic_mma", "-o", "bfs", "--max_iter", "20"});
	// test_problem(grid_graph_3x3, -8.0, {"-s", "anisotropic_mma", "-o", "cuthill", "--max_iter", "20"});
	// test_problem(grid_graph_3x3, -8.0, {"-s", "anisotropic_mma", "-o", "mindegree", "--max_iter", "20"});
}
