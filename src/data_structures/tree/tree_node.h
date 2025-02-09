#include <stdexcept>

template<typename Key, typename Data>
class TreeNode{
    private:
        TreeNode** children;
        int children_size;
        int current_children_size = 0;
        TreeNode* prev_node;
        TreeNode* next_node;

    public:
        Data data;
        Key key;

        TreeNode(Key key, Data data, int children_size){
            this->key = key;
            this->data = data;
            this->prev_node = nullptr;
            this->next_node = nullptr;
            this->children_size = children_size;
            this->current_children_size = 0;
            this->children = new TreeNode*[children_size];
            for(int i=0; i<children_size; ++i){
                this->children[i] = nullptr;
            }
        };

        void set_next_node(TreeNode* next) {
            this->next_node = next;
        }

        void set_prev_node(TreeNode* prev) {
            this->prev_node = prev;
        }

        TreeNode* get_next_node() const {
            return this->next_node;
        }

        TreeNode* get_prev_node() const {
            return this->prev_node;
        }

        void add_child(TreeNode* child, int index) {
            if (index < 0 || index > this->current_children_size)
                throw std::out_of_range("Index out of range");
            if (this->current_children_size >= this->children_size)
                throw std::overflow_error("Maximum children size reached");
            if (this->children[index] != nullptr)
                throw std::runtime_error("Child already exists at this index");
            this->children[index] = child;
            ++this->current_children_size;
        }

        TreeNode* remove_child(int index) {
            if (index < 0 || index >= this->current_children_size) {
                throw std::out_of_range("Index out of range");
            }
            TreeNode* child_to_remove = this->children[index];
            this->children[index] = nullptr;
            --this->current_children_size;
            return child_to_remove;
        }

        int get_current_children_size() const {
            return this->current_children_size;
        }

        int get_children_size() const {
            return this->children_size;
        }

        TreeNode** get_children() const {
            return this->children;
        }

    ~TreeNode() {
        delete[] children;
    }
};