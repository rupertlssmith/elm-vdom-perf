#ifndef ASM_DOM_CMAKE_MODEL_HPP
#define ASM_DOM_CMAKE_MODEL_HPP

struct Entry {
    std::string description;
    bool completed;
    bool editing;
    int id;
};

struct Model {
    std::vector<Entry> entries;
    std::string field;
    int uid;
    std::string visibility;
};

#endif //ASM_DOM_CMAKE_MODEL_HPP
