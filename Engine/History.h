//
// Created by Marko Jovanovic on 8.2.26..
//

#ifndef OOP1PROJEKAT_HISTORY_H
#define OOP1PROJEKAT_HISTORY_H
#include <string>
#include <vector>


class History {
public:
    explicit History(int capacity = 100) : m_capacity(capacity){};

    void addExecuted(const std::string& line);
    std::string last() const;
    std::string getLast(size_t index) const;

    void clear() {  m_lines.clear(); }
    bool empty() const {  return m_lines.empty(); }
    size_t size() const { return m_lines.size(); }

private:
    std::vector<std::string> m_lines;
    size_t m_capacity;

};


#endif //OOP1PROJEKAT_HISTORY_H