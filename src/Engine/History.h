//
// Created by Marko Jovanovic on 8.2.26..
//

#ifndef OOP1PROJEKAT_HISTORY_H
#define OOP1PROJEKAT_HISTORY_H
#include <string>
#include <vector>

// History - zaduzen za cuvanje istorije izvrsenih komandi

class History {
public:
    explicit History(int capacity = 100) : m_capacity(capacity){};

    // Dodaje novu liniju u istoriju - ako je kapacitet pun, brise najstariju
    void addExecuted(const std::string& line);

    // Vraca poslednju unetu liniju
    std::string last() const;

    // Vraca k-tu izvrsenu liniju
    std::string getKth(size_t index) const;

    void clear() {  m_lines.clear(); }
    bool empty() const {  return m_lines.empty(); }
    size_t size() const { return m_lines.size(); }

private:
    std::vector<std::string> m_lines; // istorija
    size_t m_capacity; // maksimalni dozvoljeni broj sacuvanih linija

};


#endif //OOP1PROJEKAT_HISTORY_H