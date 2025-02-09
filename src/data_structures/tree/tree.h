template <typename Key, typename Data>
class ITree {
public:
    virtual void insert(Data& data) = 0;
    virtual void remove(Key& key) = 0;
    virtual bool search(Key& key) = 0;
    virtual void traverse() = 0;
};
