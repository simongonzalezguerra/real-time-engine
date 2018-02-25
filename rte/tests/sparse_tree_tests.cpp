#include "sparse_tree.hpp"
#include "gtest/gtest.h"

#include <iostream>
#include <vector>

using namespace rte;

struct my_struct : public tree_node
{
    my_struct() : m_val(0) {}
    my_struct(int val) : m_val(val) {}

    int m_val;
};

typedef sparse_vector<my_struct> my_vector;

class sparse_tree_test : public ::testing::Test
{
protected:
    sparse_tree_test() {}
    virtual ~sparse_tree_test() {}
};

TEST_F(sparse_tree_test, default_construction) {
    my_vector st;
    ASSERT_EQ(st.size(), 0U);
}

TEST_F(sparse_tree_test, insert_one_node) {
    my_vector st;
    auto new_index = tree_insert(st, my_struct(1));
    ASSERT_EQ(new_index, 0U);
}

bool find_value(int value, const my_vector& st, index_type root_index, index_type& index_out)
{
    std::vector<index_type> pending_nodes;
    pending_nodes.push_back(root_index);
    bool found = false;
    while (!found && !pending_nodes.empty()) {
        auto node_index = pending_nodes.back();
        pending_nodes.pop_back();
        auto& node = st.at(node_index);
        if (node.m_val == value) {
            found = true;
            index_out = node_index;
        }

        my_vector::const_reverse_iterator it; // To test default construction of the iterator
        for (it = tree_rbegin(st, node_index); it != tree_rend(st, node_index); ++it) {
            pending_nodes.push_back(index(it));
        }
    }

    return found;
}
// 
// void print_tree(const my_vector& st, index_type root_index)
// {
//     struct context { index_type node_index; unsigned int indentation; };
//     std::vector<context> pending_nodes;
//     pending_nodes.push_back({root_index, 0});
//     while (!pending_nodes.empty()) {
//         auto current = pending_nodes.back();
//         pending_nodes.pop_back();
// 
//         for (unsigned int i = 0; i < current.indentation; i++) {
//             std::cout << "    ";
//         }
//         auto& node = st.at(current.node_index);
//         std::cout << node;
//         std::cout << "\n";
// 
//         // This tests the const version of rbegin() and rend()
//         for (auto it = node.rbegin(); it != node.rend(); ++it) {
//             pending_nodes.push_back({index(it), current.indentation + 1});
//         }
//     }
// }
// 
// void print_first_level(const my_vector& st)
// {
//     // This tests the const version of at()
//     auto& root_node = st.at(my_vector::value_type::root);
//     // This tests the const version of begin() and end()
//     for (auto it = root_node.begin(); it != root_node.end(); ++it) {
//         // to test tree_node_iterator::operator-> and tree_node_iterator::operator*
//         std::cout << "value: " << it->m_elem << " parent: " << (*it).m_parent << "\n";
//     }
// }
// 
// // Test tree:
// // 1
// //   2
// //     3
// //     4
// //   5
// //   6
// //     7
// //     8
// TEST_F(sparse_tree_test, insert_erase_search) {
//     my_vector st;
//     auto new_index = st.insert(1, my_vector::value_type::root);
//     ASSERT_EQ(new_index, 1U);
// 
//     new_index = st.insert(2, 1);
//     ASSERT_EQ(new_index, 2U);
// 
//     new_index = st.insert(3, 2);
//     ASSERT_EQ(new_index, 3U);
// 
//     new_index = st.insert(4, 2);
//     ASSERT_EQ(new_index, 4U);
// 
//     new_index = st.insert(5, 1);
//     ASSERT_EQ(new_index, 5U);
// 
//     new_index = st.insert(6, 1);
//     ASSERT_EQ(new_index, 6U);
// 
//     new_index = st.insert(7, 6);
//     ASSERT_EQ(new_index, 7U);
// 
//     new_index = st.insert(8, 6);
//     ASSERT_EQ(new_index, 8U);
// 
//     index_type search_index = 0;
//     bool search_result = false;
//     search_result = find_value(7, st, 0, search_index);
//     ASSERT_EQ(search_result, true);
//     ASSERT_EQ(search_index, 7U);
// 
//     std::cout << "tree before erasing node 7:\n";
//     print_tree(st, 1);
//     st.erase(7);
//     std::cout << "tree after erasing node 7:\n";
//     print_tree(st, 1);
// 
//     st.erase(2);
//     std::cout << "tree after erasing node 2:\n";
//     print_tree(st, 1);
// 
//     search_result = find_value(7, st, 0, search_index);
//     ASSERT_EQ(search_result, false);
// }
// 
// // Initial tree:
// // 1
// //   2
// //     3
// //     4
// //   5
// //   6
// //     7
// //     8
// // Tree to add:
// // 9
// //   10
// //     11
// //     12
// //     13
// //   14
// //     15
// //       16
// TEST_F(sparse_tree_test, insert_tree) {
//     // build initial tree
//     my_vector ot;
//     ot.insert(1, 0);
//     ot.insert(2, 1);
//     ot.insert(3, 2);
//     ot.insert(4, 2);
//     ot.insert(5, 1);
//     ot.insert(6, 1);
//     ot.insert(7, 6);
//     ot.insert(8, 6);
//     std::cout << "initial tree:\n";
//     print_tree(ot, 1);
// 
//     // build tree to add
//     my_vector it;
//     it.insert(9, 0);
//     it.insert(10, 1);
//     it.insert(11, 2);
//     it.insert(12, 2);
//     it.insert(13, 2);
//     it.insert(14, 1);
//     it.insert(15, 6);
//     it.insert(16, 7);
//     std::cout << "tree to add:\n";
//     print_tree(it, 1);
// 
//     ot.insert(it, 1, 4);
// 
//     std::cout << "tree after adding:\n";
//     print_tree(ot, 1);
// 
//     bool search_result = false;
//     index_type search_index = my_vector::value_type::npos;
//     search_result = find_value(9, ot, 0, search_index);
//     ASSERT_EQ(search_result, true);
//     ASSERT_EQ(search_index, 9U);
// 
//     search_result = find_value(10, ot, 0, search_index);
//     ASSERT_EQ(search_result, true);
//     ASSERT_EQ(search_index, 10U);
// 
//     search_result = find_value(16, ot, 0, search_index);
//     ASSERT_EQ(search_result, true);
//     ASSERT_EQ(search_index, 16U);
// }
// 
// index_type get_number_of_nodes_with_begin(my_vector& st)
// {
//     index_type ret = 0U;
//     std::vector<index_type> pending_nodes;
//     pending_nodes.push_back(my_vector::value_type::root);
//     while (!pending_nodes.empty()) {
//         auto& node_index = pending_nodes.back();
//         auto& node = st.at(node_index); // This tests the non-const version of at()
//         pending_nodes.pop_back();
//         ret++;
//         // This tests the non-const version of begin() and end()
//         for (auto it = node.begin(); it != node.end(); it++) {
//             pending_nodes.push_back(index(it));
//         }
//     }
// 
//     return ret;
// }
// 
// index_type get_number_of_nodes_with_cbegin(my_vector& st)
// {
//     index_type ret = 0U;
//     std::vector<index_type> pending_nodes;
//     pending_nodes.push_back(my_vector::value_type::root);
//     while (!pending_nodes.empty()) {
//         auto& node_index = pending_nodes.back();
//         auto& node = st.at(node_index);
//         pending_nodes.pop_back();
//         ret++;
//         for (auto it = node.cbegin(); it != node.cend(); it++) {
//             pending_nodes.push_back(index(it));
//         }
//     }
// 
//     return ret;
// }
// 
// index_type get_number_of_nodes_with_rbegin(my_vector& st)
// {
//     index_type ret = 0U;
//     std::vector<index_type> pending_nodes;
//     pending_nodes.push_back(my_vector::value_type::root);
//     while (!pending_nodes.empty()) {
//         auto& node_index = pending_nodes.back();
//         auto& node = st.at(node_index);
//         pending_nodes.pop_back();
//         ret++;
//         // This tests the non-const version of rbegin() and rend()
//         for (auto it = node.rbegin(); it != node.rend(); it++) {
//             pending_nodes.push_back(index(it));
//         }
//     }
// 
//     return ret;
// }
// 
// index_type get_number_of_nodes_with_crbegin(my_vector& st)
// {
//     index_type ret = 0U;
//     std::vector<index_type> pending_nodes;
//     pending_nodes.push_back(my_vector::value_type::root);
//     while (!pending_nodes.empty()) {
//         auto& node_index = pending_nodes.back();
//         auto& node = st.at(node_index);
//         pending_nodes.pop_back();
//         ret++;
//         for (auto it = node.crbegin(); it != node.crend(); it++) {
//             pending_nodes.push_back(index(it));
//         }
//     }
// 
//     return ret;
// }
// 
// index_type get_number_of_nodes_with_begin_backwards(my_vector& st)
// {
//     index_type ret = 0U;
//     std::vector<index_type> pending_nodes;
//     pending_nodes.push_back(my_vector::value_type::root);
//     while (!pending_nodes.empty()) {
//         auto& node_index = pending_nodes.back();
//         auto& node = st.at(node_index);
//         pending_nodes.pop_back();
//         ret++;
// 
//         my_vector::iterator it = node.end();
//         it--;
//         while (it != node.end()) {
//             pending_nodes.push_back(index(it));
//             it--;
//         }
//     }
// 
//     return ret;
// }
// 
// TEST_F(sparse_tree_test, iteration) {
//     // build initial tree
//     my_vector st;
//     st.insert(1, 0);
//     st.insert(2, 1);
//     st.insert(3, 2);
//     st.insert(4, 2);
//     st.insert(5, 1);
//     st.insert(6, 1);
//     st.insert(7, 6);
//     st.insert(8, 6);
// 
//     ASSERT_EQ(get_number_of_nodes_with_begin(st), 9U);
//     ASSERT_EQ(get_number_of_nodes_with_cbegin(st), 9U);
//     ASSERT_EQ(get_number_of_nodes_with_rbegin(st), 9U);
//     ASSERT_EQ(get_number_of_nodes_with_crbegin(st), 9U);
//     ASSERT_EQ(get_number_of_nodes_with_begin_backwards(st), 9U);
// }
// 
// TEST_F(sparse_tree_test, clear) {
//     // build initial tree
//     my_vector st;
//     st.insert(1, 0);
//     st.insert(2, 1);
//     st.insert(3, 2);
//     st.insert(4, 2);
//     st.insert(5, 1);
//     st.insert(6, 1);
//     st.insert(7, 6);
//     st.insert(8, 6);
// 
//     st.clear();
//     ASSERT_EQ(get_number_of_nodes_with_begin(st), 1U);
// }
// 
// TEST_F(sparse_tree_test, dereference) {
//     // build initial tree
//     my_vector st;
//     st.insert(1, 0);
//     st.insert(2, 1);
//     st.insert(3, 2);
//     st.insert(4, 2);
//     st.insert(5, 1);
//     st.insert(6, 1);
//     st.insert(7, 6);
//     st.insert(8, 6);
// 
//     print_first_level(st);
// }
// 
// TEST_F(sparse_tree_test, swap) {
//     // build initial tree
//     my_vector st;
//     st.insert(1, 0);
//     st.insert(2, 1);
//     st.insert(3, 2);
//     st.insert(4, 2);
//     st.insert(5, 1);
//     st.insert(6, 1);
//     st.insert(7, 6);
//     st.insert(8, 6);
// 
//     ASSERT_EQ(get_number_of_nodes_with_begin(st), 9U);
//     my_vector().swap(st);
//     ASSERT_EQ(get_number_of_nodes_with_begin(st), 1U);
// }
// 
// TEST_F(sparse_tree_test, assignment) {
//     // build initial tree
//     my_vector st1;
//     st1.insert(1, 0);
//     st1.insert(2, 1);
//     st1.insert(3, 2);
//     st1.insert(4, 2);
//     st1.insert(5, 1);
//     st1.insert(6, 1);
//     st1.insert(7, 6);
//     st1.insert(8, 6);
//     ASSERT_EQ(get_number_of_nodes_with_begin(st1), 9U);
// 
//     my_vector st2;
//     st2 = st1;
//     ASSERT_EQ(get_number_of_nodes_with_begin(st2), 9U);
// }

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
