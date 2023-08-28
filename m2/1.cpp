/*
Реализуйте структуру данных типа “множество строк” на основе 
динамической хеш-таблицы с открытой адресацией. Хранимые строки непустые 
и состоят из строчных латинских букв.
Хеш-функция строки должна быть реализована с помощью вычисления значения 
многочлена методом Горнера. Начальный размер таблицы должен быть равным 8-ми. 
Перехеширование выполняйте при добавлении элементов в случае, 
когда коэффициент заполнения таблицы достигает 3/4.
Структура данных должна поддерживать операции добавления строки в множество, 
удаления строки из множества и проверки принадлежности данной строки множеству.
Вариант 2. Для разрешения коллизий используйте двойное хеширование.
*/

#include <iostream>
#include <string>
#include <vector>

size_t str_hash1(const std::string &data) {
    size_t hash = 0;
    for (char i: data) {
        hash = hash * 13 + i;
    }
    return hash;
}

size_t str_hash2(const std::string &data) {
    size_t hash = 0;
    for (char i: data) {
        hash = hash * 7 + i;
    }
  //  hash = hash * 2 + 3;
    return hash;
}

static constexpr size_t BUCKETS_SIZES_LIST[] = {
    7, 17, 37, 73, 149, 251, 509, 1021, 2027, 5003, 10837, 21067, 42767, 104849 
};

template< class Key > struct Hash;

template<> struct Hash<int> {
    size_t operator()(const int value) const {
        return value;
    }
}; 


template<> struct Hash<std::string> {
    size_t operator()(const int value) const {
        return value;
    }
    size_t operator()(const std::string& value) const {
        return str_hash1(value);
    }
    size_t operator()(const std::string& value, int i) const {
        size_t hash = str_hash1(value) + (i * str_hash2(value));
        return hash;
    }
};

template<typename Key, typename Value, typename Hasher = Hash<Key> >
class HashTable {
    static constexpr size_t MAX_LOAD_FACTOR = 7;
    struct Node {
        enum Status {
            empty,
            data,
            deleted
        };
        Key key;
        Value value;
        Status status;

        Node(): status(empty) {
        }
    };
public:
    HashTable(Hasher hasher = Hasher()) : hasher(hasher), items_count(0), buckets_count(0), buckets_sizes_idx(0) {
    }
    ~HashTable() = default;
   
    HashTable(const HashTable&) = delete;
    HashTable(HashTable&&) = delete;
    HashTable operator=(const HashTable&) = delete;
    HashTable operator=(HashTable&&) = delete;

    Value* find(const Key& key) {
        for (int i = 0; i < buckets.size(); i++) {
            size_t hash = hasher(key, i);
            size_t bucket_idx = hash % buckets.size();

            Node cur = buckets[bucket_idx];
            if (cur.status == Node::deleted)
                continue;
            else if (cur.status == Node::data) {
                if (cur.key == key)
                    return &buckets[bucket_idx].value;
                else 
                    continue;
            } else if (cur.status == Node::empty) 
                return nullptr;
        }
        return nullptr;
    };

    bool insert(const Key& key, const Value& value) {
        if (find(key)) {
            return false;
        }
        if (items_count >= (3 * buckets.size() / 4)) {
            grow();
        }
        bool has_deleted = false;
        size_t deleted_pos = 0;
        for (int i = 0; i < buckets.size(); i++) {
            size_t hash = hasher(key, i);
            size_t bucket_idx = hash % buckets.size();
            Node cur = buckets[bucket_idx];
            if (cur.status == Node::deleted) {
                if (!has_deleted) {
                    deleted_pos = bucket_idx;
                    has_deleted = true;
                }
                continue;
            }
            else if (cur.status == Node::data) {
                continue;
            }
            else if (cur.status == Node::empty) {
                cur.key = key;
                cur.value = value;
                cur.status = Node::data;
                buckets[bucket_idx] = cur;
                items_count++;
                return true;
            }
        }
        if (has_deleted) {
            buckets[deleted_pos].key = key;
            buckets[deleted_pos].value = value;
            buckets[deleted_pos].status = Node::data;
            items_count++;
            return true;
        }
        grow();
        return insert(key, value);
    };

    bool erase(const Key& key) {
       for (int i = 0; i < buckets.size(); i++) {
            size_t hash = hasher(key, i);
            size_t bucket_idx = hash % buckets.size();
            Node cur = buckets[bucket_idx];
            if (cur.status == Node::deleted)
                continue;
            else if (cur.status == Node::data) {
                if (cur.key == key) {
                    items_count--;
                    buckets[bucket_idx].status = Node::deleted;
                    return true;
                } else
                    continue;
            } else if (cur.status == Node::empty)
                return false;
        }
        return false;
    };

    size_t size() const { return items_count; }
    
    private:
    void grow() {
        size_t new_buckets_count = BUCKETS_SIZES_LIST[buckets_sizes_idx++];
        std::vector<Node> new_buckets(new_buckets_count);
        std::vector<Node> tmp_buckets;
        tmp_buckets = buckets;
        buckets = new_buckets;
        items_count = 0;
        for (int i = 0; i < tmp_buckets.size(); i++) {
            if (tmp_buckets[i].status == Node::data)
                insert(tmp_buckets[i].key, 0);
        }
    } 
    Hasher hasher;
    std::vector<Node> buckets;
    size_t items_count;
    size_t buckets_count;
    size_t buckets_sizes_idx;
};

int main() {
   HashTable<std::string, int> ht;
   char operation = '\0';
   std::string value;
   bool operation_result = false;
   while (std::cin >> operation >> value) {
    switch (operation)
    {
    case '+':
        operation_result =  ht.insert(value, 0);
        if (operation_result) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
        break;
    case '-':
        operation_result =  ht.erase(value);
        if (operation_result) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
        break;
    case '?':
        operation_result =  ht.find(value) != nullptr;
        if (operation_result) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
    default:
        break;
    }
   }
    return 0;
}