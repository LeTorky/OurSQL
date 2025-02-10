#include "../tree.h"
#include "./binary_plus_tree_node.h"
#include "./../../../common/compare_result.h"

template <typename Key, typename Value>
class BPlusTree: public ITree<Key, Data> {
    private:
        BPlusTreeNode<Key, Value>* __root;
        int __key_size;
        int __children_size;
        CompareResult (*__comparator)(Key left_key, Key right_key);

        Value __search(
            Key search_key,
            BPlusTreeNode<Key, Value>* current_node, 
            int start_index,
            int end_index
        ){
            int middle_index = (start_index + end_index) / 2;

            // middle_index > 0 then check if Key exists in current node.
            if( middle_index > 0 ){
                //TODO: get_key(int index)
                Key middle_key = current_node->get_key(middle_index);
                CompareResult compare_result = this->__comparator(search_key, middle_key);

                switch (expression){
                    case Equal:
                        //TODO: get_value(Key search_key)
                        return current_node.get_value(middle_key);
                    
                    case Less:
                        return this->__search(
                            search_key,
                            current_node,
                            start_index,
                            // Middle is the last index.
                            middle_index,
                        );

                    case Greater:
                        return this->__search(
                            search_key,
                            current_node,
                            // Middle is the first index.
                            middle_index,
                            start_index,
                        );
                }
            }

            // middle_key < 0 then key might exist in a child.
            BPlusTreeNode<Key, Value>* child;
            Key start_key = current_node->get_key(start_index);
            Key end_key = current_node->get_key(end_index);

            CompareResult start_compare = this->__comparator(search_key, start_key);
            CompareResult end_compare = this->__comparator(search_key, end_key);

            if (start_compare == Less) {
                //TODO: get_child(index)
                child = current_node->get_child(start_index - 1);
            } else if (end_compare == Less) {
                child = current_node->get_child(start_index + 1);
            } else {
                child = current_node->get_child(end_index + 1);
            }

            //TODO: get_key_count()
            return this->__search(search_key, child, 0, current_node->get_key_count());
        }
    public:
        Value search(Key key){

        }
};