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


        }
    public:
        Value search(Key key){

        }
};