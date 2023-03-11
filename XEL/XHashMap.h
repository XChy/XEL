#ifndef XHASHMAP_H
#define XHASHMAP_H

#include <XEL/xel_global.h>
#include <XEL/SharedData.h>

namespace XEL {

// XHashMap
// No copy on write
// using std::unordermap

template <typename K, typename V>
class XEL_EXPORT XHashMap
{
   public:
    XHashMap() {}
    XHashMap(const XHashMap<K, V>& other) : map(other.map) {}
    void insert(const K& key, const V& v) { map[key] = v; }
    typedef typename std::unordered_map<K, V>::mapped_type mapped_type;
    const mapped_type& operator[](const K& key) const { return map[key]; }
    mapped_type& operator[](const K& key) { return map[key]; }
    const V value(const K& key) { return map[key]; }
    typedef typename std::unordered_map<K, V>::iterator iterator;
    iterator begin() { return map.begin(); }
    iterator end() { return map.end(); }

    typedef typename std::unordered_map<K, V>::const_iterator const_iterator;
    const_iterator begin() const { return map.begin(); }
    const_iterator end() const { return map.end(); }

    void remove(const K& key) { map.erase(key); }

    bool contains(const K& key) { return map.find(key) != map.end(); }

    bool isEmpty() const { return map.empty(); }

    size_t size() const { return map.size(); }

    std::unordered_map<K, V>& data() { return map; }
    const std::unordered_map<K, V>& data() const { return map; }

   private:
    std::unordered_map<K, V> map;
};

}  // namespace XEL
#endif  // XHASHMAP_H
