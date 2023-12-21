#ifndef TREEMULTIMAP_INCLUDED
#define TREEMULTIMAP_INCLUDED
#include <iostream>
#include <algorithm>


template <typename KeyType, typename ValueType>
class TreeMultimap
{
private:
  struct Node{
      KeyType key;
      Node* left;
      Node* right;
      std::vector<ValueType> values;
      
      Node(const KeyType& k, const ValueType& v)
      :key(k), left(nullptr), right(nullptr), values({v}){}
  };
    Node* root;
    void insert_helper(Node*& node, const KeyType& key, const ValueType& value){
        if(node == nullptr){
            node = new Node(key, value);
        } else if(key < node->key){
            insert_helper(node->left, key, value);
        } else if(key > node->key){
            insert_helper(node->right, key, value);
        } else{
            node->values.push_back(value);
        }
    }
    
    Node* find_helper(Node* node, const KeyType& key) const{
        if(node == nullptr){
            return node;
        }
        if(node->key == key){
            return node;
        }
        if(key < node->key){
            return find_helper(node->left, key);
        } else{
            return find_helper(node->right, key);
        }
    }
    
  public:
    class Iterator
    {
      public:
        Iterator() : node(nullptr), pos(0){}

        Iterator(const Node* n, int x) : node(n), pos(x){}

        const ValueType& get_value() const {
                return node->values[pos];
            }

        bool is_valid() const {return (node != nullptr && pos < node->values.size());}

        void advance()
        {
            if(is_valid()){
                if(pos + 1 < node->values.size()){
                    pos++;
                } else{
                    node = nullptr;
                    pos = 0;
                }
            }
        }

      private:
        const Node* node;
        int pos;
    };

    TreeMultimap():root(nullptr){}

    ~TreeMultimap(){
        del_tree(root);
    }

    void del_tree(Node* root){
        if(root != nullptr){
            del_tree(root->left);
            del_tree(root->right);
            delete root;
        }
    }
    
    void insert(const KeyType& key, const ValueType& value) {insert_helper(root, key, value);}

    Iterator find(const KeyType& key) const
    {
        Node* x = find_helper(root, key);
        return Iterator(x, 0);
    }
};



#endif // TREEMULTIMAP_INCLUDED
