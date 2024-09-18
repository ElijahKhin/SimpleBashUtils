#include <string.h>
#include <gtest/gtest.h>

#include "s21_common.h"

TEST(s21_atoi, all_tests) {
	char escape[] = {9, 10, 11, 12, 13, 0};
	std::string e(escape);

	EXPECT_EQ(s21_atoi((e + "1").c_str()), 1);
	EXPECT_EQ(s21_atoi((e + "a1").c_str()), 0);
	EXPECT_EQ(s21_atoi((e + "--1").c_str()), 0);
	EXPECT_EQ(s21_atoi((e + "++1").c_str()), 0);
	EXPECT_EQ(s21_atoi((e + "+1").c_str()), 1);
	EXPECT_EQ(s21_atoi((e + "-1").c_str()), -1);
	EXPECT_EQ(s21_atoi((e + "0").c_str()), 0);
	EXPECT_EQ(s21_atoi((e + "+42lyon").c_str()), 42);
	EXPECT_EQ(s21_atoi((e + "+101").c_str()), 101);
	EXPECT_EQ(s21_atoi((e + std::to_string(MAX_INT)).c_str()), MAX_INT);
	EXPECT_EQ(s21_atoi((e + std::to_string(MIN_INT)).c_str()), MIN_INT);
	EXPECT_EQ(s21_atoi("+-42"), 0);
	EXPECT_EQ(s21_atoi("-+42"), 0);
	EXPECT_EQ(s21_atoi((std::string("+") + e + std::to_string(MIN_INT)).c_str()), 0);
	EXPECT_EQ(s21_atoi((std::string("-") + e + std::to_string(MIN_INT)).c_str()), 0);
	EXPECT_EQ(s21_atoi((std::string("1") + e + std::to_string(MIN_INT)).c_str()), 1);
	EXPECT_EQ(s21_atoi((std::string("-1") + e + std::to_string(MIN_INT)).c_str()), -1);
}

TEST(s21_isdigit, all_tests) {
	EXPECT_EQ(s21_isdigit('0' - 1), 0);
	EXPECT_EQ(s21_isdigit('0'), 1);
	EXPECT_EQ(s21_isdigit('9' + 1), 0);
	EXPECT_EQ(s21_isdigit('9'), 1);
}

TEST(s21_itoa, all_tests) {
	char *test_itoa;  

	test_itoa = s21_itoa(MAX_INT);
	EXPECT_EQ(strcmp(test_itoa, std::to_string(MAX_INT).c_str()), 0);
	free(test_itoa);

	test_itoa = s21_itoa(MIN_INT);
	EXPECT_EQ(strcmp(test_itoa,std::to_string(MIN_INT).c_str()), 0);
	free(test_itoa);

	test_itoa = s21_itoa(0);
	EXPECT_EQ(strcmp(test_itoa,std::to_string(0).c_str()), 0);
	free(test_itoa);

	test_itoa = s21_itoa(1);
	EXPECT_EQ(strcmp(test_itoa,std::to_string(1).c_str()), 0);
	free(test_itoa);

	test_itoa = s21_itoa(-1);
	EXPECT_EQ(strcmp(test_itoa,std::to_string(-1).c_str()), 0);
	free(test_itoa);

	test_itoa = s21_itoa(21);
	EXPECT_EQ(strcmp(test_itoa, std::to_string(21).c_str()), 0);
	free(test_itoa);
}

//void freeTab(char **tab)
//{
//	for (int i = 0; tab[i] != NULL; ++i)
//		free(tab[i]);
//	free(tab);
//}

//TEST(s21_split, all_tests) {
//	char **tab = s21_split("  elijahkhin  21  ", ' ');
//
//	EXPECT_EQ(strcmp(tab[0], "elijahkhin"), 0);
//	EXPECT_EQ(strcmp(tab[1], "21"), 0);
//	EXPECT_EQ(strcmp(tab[2], NULL), 0);
////	freeTab(tab);
//}

///* 1 */ check(!strcmp(s, to_string(INT_MAX).c_str()));
//	/* 2 */ mcheck(s, strlen(to_string(INT_MAX).c_str()) + 1); free(s); showLeaks();
//
//	s = ft_itoa(INT_MIN);
//	/* 3 */ check(!strcmp(s, to_string(INT_MIN).c_str()));
//	/* 4 */ mcheck(s, strlen(to_string(INT_MIN).c_str()) + 1); free(s); showLeaks();
//
//	s = ft_itoa(0);
//	/* 5 */ check(!strcmp(s, to_string(0).c_str()));
//	/* 6 */ mcheck(s, strlen(to_string(0).c_str()) + 1); free(s); showLeaks();
//	s = ft_itoa(1);
//	/* 7 */ check(!strcmp(s, to_string(1).c_str()));
//	/* 8 */ mcheck(s, strlen(to_string(1).c_str()) + 1); free(s); showLeaks();
//	s = ft_itoa(-1);
//	/* 9 */ check(!strcmp(s, to_string(-1).c_str()));
//	/* 10 */ mcheck(s, strlen(to_string(-1).c_str()) + 1); free(s); showLeaks();
//
//	s = ft_itoa(42);
//	/* 11 */ check(!strcmp(s, to_string(42).c_str()));
//	/* 12 */ mcheck(s, strlen(to_string(42).c_str()) + 1); free(s); showLeaks();
int main(int argc, char** argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

//TEST(Dijkstra_Exception, out_of_range_right) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Weighted";
//  graph.LoadGraphFromFile(fileName);
//  try {
//    unsigned long long res =
//        graph_algo.GetShortestPathBetweenVertices(graph, 31, 1);
//  } catch (std::invalid_argument& e) {
//    EXPECT_EQ(std::string(ERROR_WRONG_NUMBER) + std::to_string(30) + "]",
//              e.what());
//  }
//  try {
//    unsigned long long res =
//        graph_algo.GetShortestPathBetweenVertices(graph, 1, 31);
//  } catch (std::invalid_argument& e) {
//    EXPECT_EQ(std::string(ERROR_WRONG_NUMBER) + std::to_string(30) + "]",
//              e.what());
//  }
//}
//
//TEST(Dijkstra_Borders, LeftBorder) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Weighted";
//
//  graph.LoadGraphFromFile(fileName);
//
//  int res = graph_algo.GetShortestPathBetweenVertices(graph, 1, 30);
//  int right = std::numeric_limits<int>::max();
//
//  EXPECT_EQ(res, right);
//}
//
//TEST(Dijkstra_Borders, RightBorder) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Weighted";
//
//  graph.LoadGraphFromFile(fileName);
//
//  unsigned long long res =
//      graph_algo.GetShortestPathBetweenVertices(graph, 30, 1);
//  unsigned long long right = 2;
//
//  EXPECT_EQ(res, right);
//}
//
//TEST(Dijkstra, Random1) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Weighted";
//
//  graph.LoadGraphFromFile(fileName);
//
//  unsigned long long res =
//      graph_algo.GetShortestPathBetweenVertices(graph, 4, 24);
//  unsigned long long right = 2;
//
//  EXPECT_EQ(res, right);
//}
//
//TEST(Dijkstra, Random2) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Weighted";
//
//  graph.LoadGraphFromFile(fileName);
//
//  unsigned long long res =
//      graph_algo.GetShortestPathBetweenVertices(graph, 21, 27);
//  unsigned long long right = 2;
//
//  EXPECT_EQ(res, right);
//}
//
//TEST(Dijkstra, Random3) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Weighted";
//
//  graph.LoadGraphFromFile(fileName);
//
//  unsigned long long res =
//      graph_algo.GetShortestPathBetweenVertices(graph, 8, 3);
//  unsigned long long right = 4;
//
//  EXPECT_EQ(res, right);
//}
//
//TEST(Dijkstra, SameVertices1) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Weighted";
//
//  graph.LoadGraphFromFile(fileName);
//
//  unsigned long long res =
//      graph_algo.GetShortestPathBetweenVertices(graph, 1, 1);
//  unsigned long long right = 0;
//
//  EXPECT_EQ(res, right);
//}
//
//TEST(Dijkstra, SameVertices2) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Weighted";
//
//  graph.LoadGraphFromFile(fileName);
//
//  unsigned long long res =
//      graph_algo.GetShortestPathBetweenVertices(graph, 24, 24);
//  unsigned long long right = 0;
//
//  EXPECT_EQ(res, right);
//}
//
//TEST(Dijkstra, SameVertices3) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Weighted";
//
//  graph.LoadGraphFromFile(fileName);
//
//  unsigned long long res =
//      graph_algo.GetShortestPathBetweenVertices(graph, 30, 30);
//  unsigned long long right = 0;
//
//  EXPECT_EQ(res, right);
//}
//
//TEST(Dijkstra, Huge100) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Huge";
//  callHugeGMA(fileName);
//  graph.LoadGraphFromFile(fileName);
//
//  unsigned long long res =
//      graph_algo.GetShortestPathBetweenVertices(graph, 1, 88);
//  unsigned long long right = 4;
//
//  EXPECT_EQ(res, right);
//}
//
//TEST(FloydWarshall, Combo) {
//  Graph graph;
//  Graph answerFloyd;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Weighted";
//  graph.LoadGraphFromFile(fileName);
//
//  std::string fileNameAnswer = "./testFiles/Floyd";
//  callAnswerFloyd(fileNameAnswer);
//  answerFloyd.LoadGraphFromFile(fileNameAnswer);
//
//  std::vector<std::vector<int>> res =
//      graph_algo.GetShortestPathsBetweenAllVertices(graph);
//
//  EXPECT_EQ(answerFloyd.get_adjacency_matrix(), res);
//}
//
//TEST(FloydWarshall, Huge) {
//  Graph graph;
//  Graph answerFloyd;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Huge";
//  graph.LoadGraphFromFile(fileName);
//
//  std::string fileNameAnswer = "./testFiles/HugeAnswerFloyd";
//  callAnswerFloydHuge(fileNameAnswer);
//  answerFloyd.LoadGraphFromFile(fileNameAnswer);
//
//  std::vector<std::vector<int>> res =
//      graph_algo.GetShortestPathsBetweenAllVertices(graph);
//
//  EXPECT_EQ(answerFloyd.get_adjacency_matrix(), res);
//}
//
//TEST(FloydWarshall, Combo1) {
//  Graph graph;
//  Graph answerFloyd;
//  GraphAlgorithms graph_algo;
//
//  std::string fileName = "./testFiles/Weighted";
//  graph.LoadGraphFromFile(fileName);
//
//  std::string fileNameAnswer = "./testFiles/Floyd";
//  callAnswerFloyd(fileNameAnswer);
//  answerFloyd.LoadGraphFromFile(fileNameAnswer);
//
//  std::vector<std::vector<int>> res =
//      graph_algo.GetShortestPathsBetweenAllVertices(graph);
//
//  EXPECT_EQ(answerFloyd.get_adjacency_matrix(), res);
//}
//
//TEST(DFS_Exception, out_of_range_left) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Basic";
//  callBasicGMA(fileName);
//  graph.LoadGraphFromFile(fileName);
//
//  try {
//    std::vector<int> res = graph_algo.DepthFirstSearch(graph, 0);
//  } catch (std::invalid_argument& e) {
//    EXPECT_EQ(std::string(ERROR_WRONG_NUMBER) + std::to_string(8) + "]",
//              e.what());
//  }
//}
//
//TEST(BFS_Exception, out_of_range_left) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Basic";
//
//  callBasicGMA(fileName);
//  graph.LoadGraphFromFile(fileName);
//
//  try {
//    std::vector<int> res = graph_algo.BreadthFirstSearch(graph, 0);
//  } catch (std::invalid_argument& e) {
//    EXPECT_EQ(std::string(ERROR_WRONG_NUMBER) + std::to_string(8) + "]",
//              e.what());
//  }
//}
//
//TEST(DFS_Exception, out_of_range_right) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Basic";
//
//  graph.LoadGraphFromFile(fileName);
//
//  try {
//    std::vector<int> res = graph_algo.DepthFirstSearch(graph, 9);
//  } catch (std::invalid_argument& e) {
//    EXPECT_EQ(std::string(ERROR_WRONG_NUMBER) + std::to_string(8) + "]",
//              e.what());
//  }
//}
//
//TEST(BFS_Exception, out_of_range_right) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Basic";
//
//  graph.LoadGraphFromFile(fileName);
//
//  try {
//    std::vector<int> res = graph_algo.BreadthFirstSearch(graph, 9);
//  } catch (std::invalid_argument& e) {
//    EXPECT_EQ(std::string(ERROR_WRONG_NUMBER) + std::to_string(8) + "]",
//              e.what());
//  }
//}
//
//TEST(DFS_Borders, LeftBorder) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Basic";
//
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(1);
//  right.push_back(2);
//  right.push_back(4);
//  right.push_back(3);
//  right.push_back(5);
//  right.push_back(6);
//  right.push_back(7);
//  right.push_back(8);
//
//  std::vector<int> res = graph_algo.DepthFirstSearch(graph, 1);
//  EXPECT_EQ(res, right);
//}
//
//TEST(BFS_Borders, LeftBorder) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Basic";
//
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(1);
//  right.push_back(2);
//  right.push_back(4);
//  right.push_back(6);
//  right.push_back(7);
//  right.push_back(8);
//  right.push_back(3);
//  right.push_back(5);
//
//  std::vector<int> res = graph_algo.BreadthFirstSearch(graph, 1);
//  EXPECT_EQ(res, right);
//}
//
//TEST(DFS_Borders, RightBorder) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Basic";
//
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(8);
//
//  std::vector<int> res = graph_algo.DepthFirstSearch(graph, 8);
//  EXPECT_EQ(res, right);
//}
//
//TEST(BFS_Borders, RightBorder) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Basic";
//
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(8);
//
//  std::vector<int> res = graph_algo.BreadthFirstSearch(graph, 8);
//  EXPECT_EQ(res, right);
//}
//
//TEST(DFS_Loops, Loops) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Loops";
//
//  callLoopsGMA(fileName);
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(1);
//  right.push_back(2);
//  right.push_back(4);
//  right.push_back(3);
//  right.push_back(5);
//  right.push_back(6);
//  right.push_back(7);
//  right.push_back(8);
//
//  std::vector<int> res = graph_algo.DepthFirstSearch(graph, 1);
//  EXPECT_EQ(res, right);
//}
//
//TEST(BFS_Loops, Loops) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Loops";
//
//  callLoopsGMA(fileName);
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(1);
//  right.push_back(2);
//  right.push_back(4);
//  right.push_back(6);
//  right.push_back(7);
//  right.push_back(8);
//  right.push_back(3);
//  right.push_back(5);
//
//  std::vector<int> res = graph_algo.BreadthFirstSearch(graph, 1);
//  EXPECT_EQ(res, right);
//}
//
//TEST(DFS_RandomVertices, Fourth) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Loops";
//
//  callLoopsGMA(fileName);
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(4);
//  right.push_back(1);
//  right.push_back(2);
//  right.push_back(6);
//  right.push_back(7);
//  right.push_back(8);
//  right.push_back(3);
//  right.push_back(5);
//
//  std::vector<int> res = graph_algo.DepthFirstSearch(graph, 4);
//  EXPECT_EQ(res, right);
//}
//
//TEST(BFS_RandomVertices, Fourth) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Loops";
//
//  callLoopsGMA(fileName);
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(4);
//  right.push_back(1);
//  right.push_back(3);
//  right.push_back(5);
//  right.push_back(6);
//  right.push_back(7);
//  right.push_back(8);
//  right.push_back(2);
//
//  std::vector<int> res = graph_algo.BreadthFirstSearch(graph, 4);
//  EXPECT_EQ(res, right);
//}
//
//TEST(DFS_RandomVertices, Second) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Loops";
//
//  callLoopsGMA(fileName);
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(2);
//  right.push_back(4);
//  right.push_back(1);
//  right.push_back(3);
//  right.push_back(5);
//  right.push_back(6);
//  right.push_back(7);
//  right.push_back(8);
//
//  std::vector<int> res = graph_algo.DepthFirstSearch(graph, 2);
//  EXPECT_EQ(res, right);
//}
//
//TEST(BFS_RandomVertices, Second) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Loops";
//
//  callLoopsGMA(fileName);
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(2);
//  right.push_back(4);
//  right.push_back(6);
//  right.push_back(7);
//  right.push_back(8);
//  right.push_back(1);
//  right.push_back(3);
//  right.push_back(5);
//
//  std::vector<int> res = graph_algo.BreadthFirstSearch(graph, 2);
//  EXPECT_EQ(res, right);
//}
//
//TEST(DFS_Enclave, Enclave) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Enclave";
//
//  callEnclaveGMA(fileName);
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(9);
//  right.push_back(3);
//  right.push_back(5);
//
//  std::vector<int> res = graph_algo.DepthFirstSearch(graph, 9);
//  EXPECT_EQ(res, right);
//}
//
//TEST(BFS_Enclave, Enclave) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::vector<int> right;
//
//  std::string fileName = "./testFiles/Enclave";
//
//  callEnclaveGMA(fileName);
//  graph.LoadGraphFromFile(fileName);
//
//  right.push_back(9);
//  right.push_back(3);
//  right.push_back(5);
//
//  std::vector<int> res = graph_algo.BreadthFirstSearch(graph, 9);
//  EXPECT_EQ(res, right);
//}
//
//static int sumMatrix(std::vector<std::vector<int>> matrix) {
//  int res = 0;
//  for (unsigned long i = 0; i < matrix.size(); i++) {
//    for (unsigned long j = 0; j < matrix.size(); j++) {
//      res += matrix.at(i).at(j);
//    }
//  }
//  return res;
//}
//
//TEST(Prim_basic, basic) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::string fileName = "./testFiles/PrimBasic";
//
//  callPrimBasic(fileName);
//  graph.LoadGraphFromFile(fileName);
//  std::vector<std::vector<int>> res = graph_algo.GetLeastSpanningTree(graph);
//  int sumRes = sumMatrix(res);
//  EXPECT_EQ(sumRes, 16);
//  EXPECT_EQ(res.at(0), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(1), (std::vector<int>{2, 0, 0, 1, 0, 0, 4}));
//  EXPECT_EQ(res.at(2), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(3), (std::vector<int>{0, 0, 0, 0, 2, 0, 0}));
//  EXPECT_EQ(res.at(4), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(5), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(6), (std::vector<int>{0, 0, 6, 0, 0, 1, 0}));
//}
//
//TEST(Prim_diff_weights, weights) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::string fileName = "./testFiles/PrimDiffWeights";
//
//  callPrimDiffWeights(fileName);
//  graph.LoadGraphFromFile(fileName);
//  std::vector<std::vector<int>> res = graph_algo.GetLeastSpanningTree(graph);
//  int sumRes = sumMatrix(res);
//  EXPECT_EQ(sumRes, 15);
//  EXPECT_EQ(res.at(0), (std::vector<int>{0, 1, 0, 1, 0, 0, 0}));
//  EXPECT_EQ(res.at(1), (std::vector<int>{0, 0, 0, 0, 0, 0, 4}));
//  EXPECT_EQ(res.at(2), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(3), (std::vector<int>{0, 0, 0, 0, 2, 0, 0}));
//  EXPECT_EQ(res.at(4), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(5), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(6), (std::vector<int>{0, 0, 6, 0, 0, 1, 0}));
//}
//
//TEST(Prim_diff_weights, weights2) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::string fileName = "./testFiles/PrimDiffWeights2";
//
//  callPrimDiffWeights2(fileName);
//  graph.LoadGraphFromFile(fileName);
//  std::vector<std::vector<int>> res = graph_algo.GetLeastSpanningTree(graph);
//  int sumRes = sumMatrix(res);
//  EXPECT_EQ(sumRes, 15);
//  EXPECT_EQ(res.at(0), (std::vector<int>{0, 0, 0, 1, 0, 0, 0}));
//  EXPECT_EQ(res.at(1), (std::vector<int>{1, 0, 0, 0, 0, 0, 4}));
//  EXPECT_EQ(res.at(2), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(3), (std::vector<int>{0, 0, 0, 0, 2, 0, 0}));
//  EXPECT_EQ(res.at(4), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(5), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(6), (std::vector<int>{0, 0, 6, 0, 0, 1, 0}));
//}
//
//TEST(Prim_Oriented, first) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::string fileName = "./testFiles/PrimOriented1";
//
//  callPrimOriented1(fileName);
//  graph.LoadGraphFromFile(fileName);
//  std::vector<std::vector<int>> res = graph_algo.GetLeastSpanningTree(graph);
//  int sumRes = sumMatrix(res);
//  EXPECT_EQ(sumRes, 15);
//  EXPECT_EQ(res.at(0), (std::vector<int>{0, 1, 0, 1, 0, 0, 0}));
//  EXPECT_EQ(res.at(1), (std::vector<int>{0, 0, 0, 0, 0, 0, 4}));
//  EXPECT_EQ(res.at(2), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(3), (std::vector<int>{0, 0, 0, 0, 2, 0, 0}));
//  EXPECT_EQ(res.at(4), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(5), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(6), (std::vector<int>{0, 0, 6, 0, 0, 1, 0}));
//}
//
//TEST(Prim_Oriented, second) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::string fileName = "./testFiles/PrimOriented2";
//
//  callPrimOriented2(fileName);
//  graph.LoadGraphFromFile(fileName);
//  std::vector<std::vector<int>> res = graph_algo.GetLeastSpanningTree(graph);
//
//  int sumRes = sumMatrix(res);
//  EXPECT_EQ(sumRes, 15);
//  EXPECT_EQ(res.at(0), (std::vector<int>{0, 1, 0, 1, 0, 0, 0}));
//  EXPECT_EQ(res.at(1), (std::vector<int>{0, 0, 0, 0, 0, 0, 4}));
//  EXPECT_EQ(res.at(2), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(3), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(4), (std::vector<int>{0, 0, 0, 2, 0, 0, 0}));
//  EXPECT_EQ(res.at(5), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(6), (std::vector<int>{0, 0, 6, 0, 0, 1, 0}));
//}
//
//TEST(Prim_Combo, combo) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::string fileName = "./testFiles/PrimCombo";
//
//  callPrimCombo(fileName);
//  graph.LoadGraphFromFile(fileName);
//  std::vector<std::vector<int>> res = graph_algo.GetLeastSpanningTree(graph);
//
//  int sumRes = sumMatrix(res);
//  EXPECT_EQ(sumRes, 21);
//  EXPECT_EQ(res.at(0), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(1), (std::vector<int>{1, 0, 2, 3, 4, 5, 6}));
//  EXPECT_EQ(res.at(2), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(3), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(4), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(5), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(6), (std::vector<int>{0, 0, 0, 0, 0, 0, 0}));
//}
//
//TEST(PrimGlebs10, EbanyiFicksik) {
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::string fileName = "./testFiles/EbanyiFicksik";
//
//  callPrimGlebs10(fileName);
//  graph.LoadGraphFromFile(fileName);
//  std::vector<std::vector<int>> res = graph_algo.GetLeastSpanningTree(graph);
//
//  int sumRes = sumMatrix(res);
//  EXPECT_EQ(sumRes, 102);
//  EXPECT_EQ(res.at(0),
//            (std::vector<int>{0, 5, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(1),
//            (std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(2),
//            (std::vector<int>{0, 0, 0, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(3),
//            (std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 3, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(4),
//            (std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(5),
//            (std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(6),
//            (std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(7),
//            (std::vector<int>{0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(8),
//            (std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(9),
//            (std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 5, 0, 0}));
//  EXPECT_EQ(res.at(10),
//            (std::vector<int>{0, 0, 0, 0, 11, 0, 0, 0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(11),
//            (std::vector<int>{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 7}));
//  EXPECT_EQ(res.at(12),
//            (std::vector<int>{0, 0, 0, 0, 0, 42, 0, 0, 0, 0, 0, 0, 0, 0}));
//  EXPECT_EQ(res.at(13),
//            (std::vector<int>{0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0}));
//}
//
//TEST(ACO, LastTest) {
//  TR res;
//  Graph graph;
//  GraphAlgorithms graph_algo;
//  std::string fileName = "./testFiles/aco5";
//
//  callACO(fileName);
//  graph.LoadGraphFromFile(fileName);
//  res = graph_algo.SolveTravellingSalesmanProblem(graph);
//
//  EXPECT_EQ(res.distance, 26);
//}
//
