/*
В одной военной части решили построить в одну шеренгу по росту. 
Т.к. часть была далеко не образцовая, то солдаты часто приходили не вовремя, 
а то их и вовсе приходилось выгонять из шеренги за плохо начищенные сапоги.
 Однако солдаты в процессе прихода и ухода должны были всегда быть 
 выстроены по росту – сначала самые высокие, а в конце – самые низкие. 
 За расстановку солдат отвечал прапорщик, который заметил интересную 
 особенность – все солдаты в части разного роста. Ваша задача состоит в том, 
 чтобы помочь прапорщику правильно расставлять солдат, а именно для каждого 
 приходящего солдата указывать, перед каким солдатом в строе он должен 
 становится. Требуемая скорость выполнения команды - O(log n).
Формат ввода
Первая строка содержит число N – количество команд (1 ≤ N ≤ 90 000). 
В каждой следующей строке содержится описание команды: число 1 и X если 
солдат приходит в строй (X – рост солдата, натуральное число 
до 100 000 включительно) и число 2 и Y если солдата, стоящим 
в строе на месте Y надо удалить из строя. Солдаты в строе нумеруются с нуля.
Формат вывода
На каждую команду 1 (добавление в строй) вы должны выводить число 
K – номер позиции, на которую должен встать этот солдат 
(все стоящие за ним двигаются назад).
*/
#include <iostream>

template <class T>
struct DefaultComparator
{
    int operator () (const T& l, const T& r) const 
    {
        if ( l < r ) return -1;
        if ( l > r ) return 1;
        return 0;
    }
};

template <class Key, class Value, class Comparator = DefaultComparator<Key> >
class AVLTree 
{
    struct Node 
    {
        Key key;
        Value value;
        
        uint8_t height;
        uint16_t count;
        
        Node* left;
        Node* right;
        
        Node( const Key& key, const Value& value ) :
            key( key ),
            value( value ),
            height( 1 ),
            count ( 1 ),
            left( nullptr ),
            right( nullptr ) {
        }
    };
public:
    AVLTree( Comparator comp = Comparator() ) : root( nullptr ), tree_size( 0 ), comp( comp )
    {
    }
    
    AVLTree( const AVLTree& ) = delete;
    AVLTree( AVLTree&& ) = delete;
    AVLTree& operator =( const AVLTree& ) = delete;
    AVLTree& operator =( AVLTree&& ) = delete;
    
    ~AVLTree() {
        free(root);
    }
    
    Value* find( const Key& key )
    {
        return _find( root, key );
    }
    const Value* find( const Key& key ) const
    {
        return find(key);
    }
    
    void insert( const Key& key, const Value& value )
    {
        root = _insert(root, key, value);
    }
    
    void erase( const Key& key )
    {
        root = _erase( root, key );
    }

    void erase_pos(int pos)
    {
        root = _erase( root, _find_key(pos) );
    }

    int find_pos(const Key &key) const {
        return _find_pos(key, root);
    }
    
private:
    void free(Node *node){
        if (node->left)
            free(node->left);
        if (node->right)
            free(node->right);
        delete node;
    }

    Value* _find( Node* node, const Key& key)
    {
        if ( !node )
        {
            return nullptr;
        }
        int comp_res  = comp(key, node->key);
        if (comp_res == -1) 
        {
            return _find(node->left, key);
        } 
        else if (comp_res == 1) 
        {
            return _find(node->right, key);
        }
        return &(node->value);
    }
    
    Node* _insert( Node* node, const Key& key, const Value& value)
    {
        if ( !node ) 
        {
            tree_size++;
            return new Node(key, value);
        }
        
        int comp_res  = comp(key, node->key);
        if (comp_res == -1) 
        {
            node->left = _insert(node->left, key, value);
        }
        else 
        {
            node->right = _insert(node->right, key, value);
        }
        return balance(node);
    }
    
    Node* _erase( Node* node, const Key& key )
    {
        if ( !node )
        {
            return nullptr;
        }
        
        int comp_res = comp(key, node->key);
        if ( comp_res == -1 )
        {
            node->left = _erase(node->left, key);
        }
        else if ( comp_res == 1 )
        {
            node->right = _erase(node->right, key);
        }
        else
        {
            Node* left = node->left;
            Node* right = node->right;
            
            delete node;
            
            if ( !right )
            {
                return left;
            }
            
            Node* min_node = find_min(right);
            min_node->right = remove_min(right);
            min_node->left = left;
            
            return balance(min_node);
        }
        return balance( node );
    }
    
    Node* find_min( Node* node )
    {
        if ( !node->left )
        {
            return node;
        }
        return find_min(node->left);
    }
    
    Node* remove_min( Node* node )
    {
        if ( !node->left )
        {
            return node->right;
        }
        node->left = remove_min( node->left );
        return balance( node );
    }
    int count(Node *node) {
    if (!node)
        return 0;
    return node->count;
    }

    uint8_t height( Node* node ) const
    {
        return node ? node->height : 0;
    }
    
    void fix_height( Node* node )
    {
        node->height = std::max(height(node->left), height(node->right)) + 1;
        node->count = count(node->left) + count(node->right) + 1;
    }
    
    int bfactor( Node* node ) const
    {
        return height(node->right) - height(node->left);
    }
    
    Node* rotate_left( Node* node ){
        Node *tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;

        fix_height(node);
        fix_height(tmp);

        return tmp;
    }
    
    Node* rotate_right( Node* node ){
        Node *tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;

        fix_height(node);
        fix_height(tmp);

        return tmp;
    }

    Node* balance( Node* node )
    {
        fix_height(node);
        int bf = bfactor( node );
        
        if ( bf == 2 )
        {
            if ( bfactor( node->right ) < 0 )
            {
                node->right  = rotate_right( node->right );
            }
            return rotate_left( node );
        }
        else if ( bf == -2 )
        {
            if ( bfactor( node->left ) > 0 )
            {
                node->left  = rotate_left( node->left );
            }
            return rotate_right( node );
        }
        return node;
    }

    int _find_pos(const Key &key, Node *node) const {
    if (!node)
        return -1;
    Node *tmp = node;
    int comp_res = 0;
    int i = 0;
    while (tmp != nullptr){
        comp_res = comp(key, tmp->key);
        if (comp_res == -1) {
            if (tmp->right) {
                i += tmp->right->count + 1;
                tmp = tmp->left;
            } else {
                tmp = tmp->left;
                i += 1;
            }
        } else if (comp_res == 1) {
            tmp = tmp->right;
        } else {
            if (tmp->right) {
                return i + tmp->right->count;
            } else {
                return i;
            }
        }
    }
    return -1;
    }
    
    int _find_key(int k){
        Node* node = root;
        while (node) {
            int tmp = node->right ? node->right->count : 0;
            if (tmp == k)
                return node->key;
            if (tmp > k)
                node = node->right;
            else {
                node = node->left;
                k = k - 1 - tmp;
            }
        }
        return -1;
    }

    Node* root;
    size_t tree_size;
    Comparator comp;
};

int main() {
    AVLTree<int, int> at;
    int n, com, val;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        std::cin >> com >> val;
        if (com == 1) {
            at.insert(val, 0);
            std::cout << at.find_pos(val) << std::endl;
        } else if (com == 2){
            at.erase_pos(val);
        }  
    }
    return 0;
}