#include "../../../src/data_structures/tree/tree_node.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace std;

class TestTreeNode{
    public:
        void test_node_construction(){
            string key = "Test";
            int data = 1;
            int children_size = 5;
            auto node = new TreeNode<string, int>(key, data, children_size);
            assert(node->get_prev_node() == nullptr);
            assert(node->get_next_node() == nullptr);
            assert(node->key == key);
            assert(node->data == data);
            assert(node->get_current_children_size() == 0);
            assert(node->get_children_size() == children_size);
        }

        void test_insert_and_pop(){
            string key = "Test";
            int data = 1;
            auto node = new TreeNode<string, int>(key, data, 5);

            // Insert children
            string child_key1 = "Child1";
            int child_data1 = 2;
            TreeNode<string, int> child_node1(child_key1, child_data1, 5);
            node->add_child(&child_node1, 0);
            assert(node->get_current_children_size() == 1);

            string child_key2 = "Child2";
            int child_data2 = 3;
            TreeNode<string, int> child_node2(child_key2, child_data2, 5);
            node->add_child(&child_node2, 1);
            assert(node->get_current_children_size() == 2);

            // Remove children
            TreeNode<string, int>* removed_child1 = node->remove_child(1);
            assert(removed_child1->key == child_key2);
            assert(removed_child1->data == child_data2);
            assert(node->get_current_children_size() == 1);

            TreeNode<string, int>* removed_child2 = node->remove_child(0);
            assert(removed_child2->key == child_key1);
            assert(removed_child2->data == child_data1);
            assert(node->get_current_children_size() == 0);
        }

        void test_overflow_append() {
            string key = "Test";
            int data = 1;
            auto node = new TreeNode<string, int>(key, data, 2);

            // Insert children
            string child_key1 = "Child1";
            int child_data1 = 2;
            TreeNode<string, int> child_node1(child_key1, child_data1, 2);
            node->add_child(&child_node1, 0);
            assert(node->get_current_children_size() == 1);

            string child_key2 = "Child2";
            int child_data2 = 3;
            TreeNode<string, int> child_node2(child_key2, child_data2, 2);
            node->add_child(&child_node2, 1);
            assert(node->get_current_children_size() == 2);

            // Attempt to insert another child should throw overflow error
            string child_key3 = "Child3";
            int child_data3 = 4;
            TreeNode<string, int> child_node3(child_key3, child_data3, 2);
            try {
                node->add_child(&child_node3, 2);
                assert(false); // Should not reach here
            } catch (const overflow_error& e) {
                assert(true); // Expected exception
            }
        }

        void test_underflow_pop() {
            string key = "Test";
            int data = 1;
            auto node = new TreeNode<string, int>(key, data, 2);

            // Attempt to remove child from empty node should throw out of range error
            try {
                node->remove_child(0);
                assert(false); // Should not reach here
            } catch (const out_of_range& e) {
                assert(true); // Expected exception
            }

            // Insert a child and remove it
            string child_key1 = "Child1";
            int child_data1 = 2;
            TreeNode<string, int> child_node1(child_key1, child_data1, 2);
            node->add_child(&child_node1, 0);
            assert(node->get_current_children_size() == 1);

            TreeNode<string, int>* removed_child = node->remove_child(0);
            assert(removed_child->key == child_key1);
            assert(removed_child->data == child_data1);
            assert(node->get_current_children_size() == 0);

            // Attempt to remove again should throw out of range error
            try {
                node->remove_child(0);
                assert(false); // Should not reach here
            } catch (const out_of_range& e) {
                assert(true); // Expected exception
            }
        }
};

int main(){
    TestTreeNode test_class = TestTreeNode();
    test_class.test_node_construction();
    test_class.test_insert_and_pop();
    test_class.test_overflow_append();
    test_class.test_underflow_pop();
}
